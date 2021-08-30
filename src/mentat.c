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
    int position = 0;
    char *buffer = malloc(sizeof(char) * BUFSIZE);

    if (!buffer) {
        fprintf(stderr, "msh allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;
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
main(int argc, char *argv[])
{
    char *line = msh_readline();
    char **command = msh_splitline(line);
    free(line);
    free(command);
    return 0;
}
