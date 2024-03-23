#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

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

int main(int argc, char **argv)
{
    signal(SIGINT, handle_signit);

    char buffer[500], *params1[100];
    int r = 0;
    while (1)
    {
        printf(ANSI_COLOR_BLUE "cat> $ " ANSI_COLOR_BLUE);
        printf(ANSI_COLOR_RESET "" ANSI_COLOR_RESET);
        fgets(buffer, 500, stdin);
        Token(params1, &r, buffer, " ");

        if (strstr(params1[0], "cat"))
        {

            int a = 0;
            int b = 0;
            int c = 0;
            if (params1[2] == NULL)
            {
                if (params1[1] == NULL)
                {
                    if (fork() > 0)
                    {
                        wait(NULL);
                    }
                    else
                    {
                        execvp(params1[0], params1);
                        printf("Please enter a valid input\n");
                        exit(1);
                    }
                    c++;
                }
            }
            if (c == 0 && strstr(params1[1], "-e") && params1[2] != NULL)
            {

                if (fork() > 0)
                {
                    wait(NULL);
                }
                else
                {
                    execvp(params1[0], params1);
                    printf("Please enter a valid input\n");
                    exit(1);
                }
                printf("\n");
                a++;
            }
            if (c == 0 && strstr(params1[1], "-n") && params1[2] != NULL)
            {

                if (fork() > 0)
                {
                    wait(NULL);
                }
                else
                {
                    execvp(params1[0], params1);
                    printf("Please enter a valid input\n");
                    exit(1);
                }
                printf("\n");
                a++;
            }
            if (params1[3] != NULL)
            {
                printf("Too many arguments\n");
                b++;
            }
            if (a == 0 && b == 0 && c == 0)
            {
                printf("No such file or directory\n");
            }
        }
        else if (strstr(params1[0], "exit"))
        {
            exit(0);
        }
        else
        {

            printf("Invalid Command\n");
        }
    }
    return 0;
}
