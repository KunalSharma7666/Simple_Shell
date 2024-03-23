#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_BLUE "\x1b[34m"

void handle_signit(int a) {}

void ClearSpace(char *buffer)
{
	if (buffer[0] == ' ' || buffer[0] == '\n')
		memmove(buffer, buffer + 1, strlen(buffer));
	if (buffer[strlen(buffer) - 1] == ' ' || buffer[strlen(buffer) - 1] == '\n')
		buffer[strlen(buffer) - 1] = '\0';
}

void Token(char **param, int *nr, char *buf, const char *c)
{
	char *token;
	token = strtok(buf, c);
	int pc = -1;
	while (token)
	{
		param[++pc] = malloc(sizeof(token) + 1);
		strcpy(param[pc], token);
		ClearSpace(param[pc]);
		token = strtok(NULL, c);
	}
	param[++pc] = NULL;
	*nr = pc;
}

void execute(char **argv)
{
	if (fork() > 0)
	{
		wait(NULL);
	}
	else
	{
		execvp(argv[0], argv);
		printf("Please enter a valid input\n");
		exit(1);
	}
}

void *Thread_execution(void *buffer)
{
	system(buffer);
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	signal(SIGINT, handle_signit);
	printf("\n");
	printf(ANSI_COLOR_GREEN "         **         **     *********       ********          **         \n" ANSI_COLOR_GREEN);
	printf(ANSI_COLOR_GREEN "         **         **     **********      *********       * **         \n" ANSI_COLOR_GREEN);
	printf(ANSI_COLOR_GREEN "         **         **     **      **             **     *   **         \n" ANSI_COLOR_GREEN);
	printf(ANSI_COLOR_GREEN "         **         **     **      **             **         **         \n" ANSI_COLOR_GREEN);
	printf(ANSI_COLOR_GREEN "         *************     **********      ********          **         \n" ANSI_COLOR_GREEN);
	printf(ANSI_COLOR_GREEN "         *************     *********       ********          **         \n" ANSI_COLOR_GREEN);
	printf(ANSI_COLOR_GREEN "         **         **     **  **                 **         **         \n" ANSI_COLOR_GREEN);
	printf(ANSI_COLOR_GREEN "         **         **     **   **                **         **         \n" ANSI_COLOR_GREEN);
	printf(ANSI_COLOR_GREEN "         **         **     **    **        *********     **********     \n" ANSI_COLOR_GREEN);
	printf(ANSI_COLOR_GREEN "         **         **     **     **       ********      **********     \n" ANSI_COLOR_GREEN);
	printf("\n");

	char buffer[500], *params1[100];
	char buffer1[500];
	int r = 0;

	while (1)
	{
		printf(ANSI_COLOR_BLUE "HR31> $ " ANSI_COLOR_BLUE);
		printf(ANSI_COLOR_RESET "" ANSI_COLOR_RESET);
		buffer1[0] = '\0';
		memset(buffer1, '\0', 500);
		fgets(buffer, 500, stdin);
		for (int i = 3; i < strlen(buffer); i++)
		{
			buffer1[i - 3] = buffer[i];
		}
		Token(params1, &r, buffer, " ");

		if (strstr(params1[0], "cd"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			int d = 0;
			if (params1[1] == NULL)
			{
				chdir(getenv("HOME"));
				a++;
			}

			if (a == 0 && strstr(params1[1], "-") && params1[2] == NULL)
			{
				chdir("..");
				c++;
			}
			if (c == 0 && a == 0 && strstr(params1[1], "~") && params1[2] == NULL)
			{
				chdir(getenv("HOME"));
				d++;
			}
			
			if (a == 0 && c == 0 && d == 0 && params1[2] == NULL)
			{
				if (chdir(params1[1]) != 0)
				{
					printf("No such directory\n");
					b++;
				}
				else
				{
					chdir(params1[1]);
					b++;
				}
			}
			if (a == 0 && b == 0 && c == 0 && d == 0)
			{
				printf("Too many arguments\n");
			}
		}

		else if (strstr(params1[0], "exit"))
		{
			exit(0);
		}

		else if (strstr(params1[0], "ls"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			if (params1[1] == NULL)
			{
				execute(params1);
				c++;
			}
			if (c == 0 && strstr(params1[1], "-a") && params1[2] == NULL)
			{
				execute(params1);
				a++;
			}
			if (c == 0 && strstr(params1[1], "-l") && params1[2] == NULL)
			{
				execute(params1);
				a++;
			}
			if (a == 0 && c == 0 && params1[2] != NULL)
			{
				printf("Too many arguments\n");
				b++;
			}
			if (a == 0 && b == 0 && c == 0)
			{
				printf("Available commands ls -a and ls -l. choose one of them\n");
			}
		}

		else if (strstr(params1[0], "cat"))
		{

			int a = 0;
			int b = 0;
			int c = 0;
			if (params1[2] == NULL)
			{
				execute(params1);
				c++;
			}
			if (c == 0 && strstr(params1[1], "-e") && params1[2] != NULL)
			{
				execute(params1);
				printf("\n");
				a++;
			}
			if (c == 0 && strstr(params1[1], "-n") && params1[2] != NULL)
			{
				execute(params1);
				printf("\n");
				a++;
			}
			if (a == 0 && c == 0 && params1[3] != NULL)
			{
				printf("Too many arguments\n");
				b++;
			}
			if (a == 0 && b == 0 && c == 0)
			{
				printf("No such file or directory\n");
			}
		}
		else if (strstr(params1[0], "date"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			if (params1[1] == NULL)
			{
				execute(params1);
				c++;
			}
			if (c == 0 && strstr(params1[1], "-u") && params1[2] == NULL)
			{
				execute(params1);
				a++;
			}
			if (c == 0 && strstr(params1[1], "-R") && params1[2] == NULL)
			{
				execute(params1);
				a++;
			}
			if (a == 0 && c == 0 && params1[2] != NULL)
			{
				printf("Too many arguments\n");
				b++;
			}
			if (a == 0 && b == 0 && c == 0)
			{
				printf("Available commands date -u and date -R. choose one of them\n");
			}
		}
		else if (strstr(params1[0], "rm"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			if (params1[2] == NULL)
			{
				execute(params1);
				c++;
			}
			if (c == 0 && strstr(params1[1], "-i") && params1[3] == NULL)
			{
				execute(params1);
				a++;
			}
			if (c == 0 && strstr(params1[1], "-ri") && params1[3] == NULL)
			{
				execute(params1);
				a++;
			}
			if (a == 0 && c == 0 && params1[3] != NULL)
			{
				printf("Too many arguments\n");
				b++;
			}
			if (a == 0 && b == 0 && c == 0)
			{
				printf("Available commands rm -i filename and rm -ri directory name. choose one of them\n");
			}
		}
		else if (strstr(params1[0], "mkdir"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			if (params1[2] == NULL)
			{
				execute(params1);
				c++;
			}

			if (c == 0 && strstr(params1[1], "-v") && params1[3] == NULL)
			{
				execute(params1);
				a++;
			}
			if (c == 0 && strstr(params1[1], "-p") && params1[3] == NULL)
			{
				execute(params1);
				a++;
			}
			if (a == 0 && c == 0 && params1[3] != NULL)
			{
				printf("Too many arguments\n");
				b++;
			}
			if (a == 0 && b == 0 && c == 0)
			{
				printf("Available commands mkdir -v folder name and mkdir -p folder name. choose one of them\n");
			}
		}
		else if (strstr(params1[0], "echo"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			int d = 0;
			if (params1[1] == NULL)
			{
				execute(params1);
				a++;
			}
			if (a == 0 && strstr(params1[1], "-n"))
			{
				if (params1[2] != NULL)
				{
					int i = 2;
					while (params1[i] != NULL)
					{
						for (int j = 0; j < strlen(params1[i]); j++)
						{
							if (params1[i][j] != '"')
							{
								printf("%c", params1[i][j]);
							}
						}
						printf(" ");
						i++;
					}
				}
				b++;
			}

			if (a == 0 && b == 0 && strstr(params1[1], "*"))
			{
				params1[0] = "ls";
				params1[1] = NULL;
				execute(params1);
				c++;
			}

			if (a == 0 && b == 0 && c == 0)
			{
				execute(params1);
			}
		}

		else if (strstr(params1[0], "pwd"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			int d = 0;
			if (params1[1] == NULL)
			{
				char a[500];
				getcwd(a, 500);
				c++;
				printf("%s\n", a);
			}
			if (c == 0 && strstr(params1[1], "-L") && params1[2] == NULL)
			{
				char b[500];
				getcwd(b, 500);
				printf("%s\n", b);
				a++;
			}
			if (a == 0 && c == 0 && strstr(params1[1], "-P") && params1[2] == NULL)
			{
				char c[500];
				getcwd(c, 500);
				printf("%s\n", c);
				b++;
			}
			if (a == 0 && c == 0 && b == 0 && params1[2] != NULL)
			{
				printf("Too many arguments\n");
				d++;
			}
			if (a == 0 && b == 0 && c == 0 && d == 0)
			{
				printf("Available commands pwd -P and pwd -L. choose one of them\n");
			}
		}

		else if (strstr(params1[0], "&t") && strstr(params1[1], "ls"))
		{
			int a = 0;
			int b = 0;
			int c = 0;

			if (params1[2] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				c++;
			}
			if (c == 0 && strstr(params1[2], "-a") && params1[3] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				a++;
			}
			if (c == 0 && strstr(params1[2], "-l") && params1[3] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				a++;
			}
			if (a == 0 && c == 0 && params1[3] != NULL)
			{
				printf("Too many arguments\n");
				b++;
			}
			if (a == 0 && b == 0 && c == 0)
			{
				printf("Available commands &t ls -a and &t ls -l. choose one of them\n");
			}
		}

		else if (strstr(params1[0], "&t") && strstr(params1[1], "cat"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			if (params1[3] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				c++;
			}
			if (c == 0 && strstr(params1[2], "-e") && params1[3] != NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				printf("\n");
				a++;
			}
			if (c == 0 && strstr(params1[2], "-n") && params1[3] != NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				printf("\n");
				a++;
			}
			if (a == 0 && c == 0 && params1[4] != NULL)
			{
				printf("Too many arguments\n");
				b++;
			}
			if (a == 0 && b == 0 && c == 0)
			{
				printf("No such file or directory\n");
			}
		}
		else if (strstr(params1[0], "&t") && strstr(params1[1], "date"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			if (params1[2] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				c++;
			}
			if (c == 0 && strstr(params1[2], "-u") && params1[3] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				a++;
			}
			if (c == 0 && strstr(params1[2], "-R") && params1[3] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				a++;
			}
			if (a == 0 && c == 0 && params1[3] != NULL)
			{
				printf("Too many arguments\n");
				b++;
			}
			if (a == 0 && b == 0 && c == 0)
			{
				printf("Available commands &t date -u and &t date -R. choose one of them\n");
			}
		}
		else if (strstr(params1[0], "&t") && strstr(params1[1], "rm"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			if (params1[3] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				c++;
			}
			if (c == 0 && strstr(params1[2], "-i") && params1[4] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				a++;
			}
			if (c == 0 && strstr(params1[2], "-ri") && params1[4] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				a++;
			}
			if (a == 0 && c == 0 && params1[4] != NULL)
			{
				printf("Too many arguments\n");
				b++;
			}
			if (a == 0 && b == 0 && c == 0)
			{
				printf("Available commands &t rm -i filename and &t rm -ri directory name. choose one of them\n");
			}
		}
		else if (strstr(params1[0], "&t") && strstr(params1[1], "mkdir"))
		{
			int a = 0;
			int b = 0;
			int c = 0;
			if (params1[3] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				c++;
			}

			if (c == 0 && strstr(params1[2], "-v") && params1[4] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				a++;
			}
			if (c == 0 && strstr(params1[2], "-p") && params1[4] == NULL)
			{
				pthread_t pid;
				pthread_create(&pid, NULL, Thread_execution, &buffer1);
				pthread_join(pid, NULL);
				a++;
			}
			if (a == 0 && c == 0 && params1[4] != NULL)
			{
				printf("Too many arguments\n");
				b++;
			}
			if (a == 0 && b == 0 && c == 0)
			{
				printf("Available commands &t mkdir -v folder name and &t mkdir -p folder name. choose one of them\n");
			}
		}
		else if (params1[0][0] == '\0' || params1[0][0] == '\n')
		{
			continue;
		}

		else
		{
			printf("Invalid Command\n");
		}
	}
	return 0;
}
