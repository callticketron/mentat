#define BUFSIZE 1024
#define TOKENSIZE 64
#define DELIMITERS " \t\n\r\a"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char
*msh_readline(void)
{
    int c;
    int bufsize = BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * BUFSIZE);

    if (!buffer) {
        fprintf(stderr, "msh allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        c = getchar();

        if (c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else if (c == EOF) {
            exit(EXIT_SUCCESS);
        } else {
            buffer[position] = c;
        }

        position++;

        if (position >= bufsize) {
            bufsize += BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "msh allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char
**msh_splitline(char *line)
{
    int bufsize, position;
    char *token;
    char **tokens = malloc(TOKENSIZE * sizeof(char *));

    bufsize = TOKENSIZE;
    position = 0;

    if (!tokens) {
        fprintf(stderr, "msh allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DELIMITERS);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOKENSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "msh allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIMITERS);
    }

    tokens[position] = NULL;
    return tokens;
}

int
msh_launch(char **command)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(command[0], command) == -1) {
            perror("msh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("msh");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return -1;
}

int
msh_execute(char **command)
{
    int i;

    if (command[0] == NULL) {
        //Was empty
        return 1;
    }

    return msh_launch(command);
}

void msh_loop(void)
{
    char *line;
    char **command;
    int status;

    do {
        printf("msh> ");
        line = msh_readline();
        command = msh_splitline(line);
        status = msh_execute(command);

        free(line);
        free(command);

    } while (status);
}

int
main(int argc, char *argv[])
{
    msh_loop();
    return 0;
}
