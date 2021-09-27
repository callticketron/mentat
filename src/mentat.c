#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>  // needed for memset


int
main(int argc, char *argv[])
{
	struct termios tio;
	struct termios stdio;
	int tty_fd;
    pid_t pid;

    tty_fd = posix_openpt();

	close(tty_fd);
	return 0;
}
