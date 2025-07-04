#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main(void) {
    pid_t pid, ppid;
    pid = getpid();
    ppid = getppid();
    printf("children: %u, parent: %u\n", pid, ppid);

    return (0);
}