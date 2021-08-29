#define BUFSIZE 1024

#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char *argv[])
{
    char *buffer = malloc(BUFSIZE);
    free(buffer);
    return 0;
}
