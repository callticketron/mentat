#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    char *command[] = {"/usr/bin/bash", "", "\0"};
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        printf("I am the child pid %d and my parent is %d\n", getpid(), getppid());
        execvp(command[0], command);
    } else {
        printf("I am the parent at %d\n", getpid());
    }

    return 0;
}
