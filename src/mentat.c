#define BUFSIZE 1024

#include <stdio.h>
#include <stdlib.h>

void
*msh_readline(void)
{
    int c;
    int position = 0;
    char *buffer;

    if (!(buffer = malloc(sizeof(char) * BUFSIZE))) {
        fprintf(stderr, "msh allocation error\n");
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

int
main(int argc, char *argv[])
{
    return 0;
}
