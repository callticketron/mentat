#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int master;
    char *slavename;

    master = posix_openpt(O_RDWR);
    grantpt(master);
    unlockpt(master);
    slavename = ptsname(master);

    printf("%s\n", slavename);

    close(master);
	return 0;
}
