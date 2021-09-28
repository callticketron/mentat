#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pty.h>
#include <utmp.h>
#include <string.h>  // needed for memset


int
main(int argc, char *argv[])
{
    int *main;
    char name[256];
    pid_t pid;

    pid = forkpty(main, name, NULL, NULL);

	close(*main);
	return 0;
}
