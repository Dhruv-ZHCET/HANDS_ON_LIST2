
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>



int main() {
    struct rlimit rl;
    int pipefd[2];

    // Maximum number of files per process
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) {
        perror("getrlimit failed");
        exit(1);
    }
    printf("Maximum number of files a process can open: %ld\n", rl.rlim_cur);

    // Create a pipe to find pipe size
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }

#ifdef F_GETPIPE_SZ
    int pipe_size = fcntl(pipefd[0], F_GETPIPE_SZ);
    if (pipe_size == -1) {
        perror("fcntl F_GETPIPE_SZ failed");
    } else {
        printf("Size of pipe (circular buffer): %d bytes\n", pipe_size);
    }
#else
    printf("F_GETPIPE_SZ not supported on this system.\n");
#endif

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q23.c -o Q23
./Q23

====================== Sample Output ================================

Maximum number of files a process can open: 1024
Size of pipe (circular buffer): 65536 bytes

===========================================================
*/
