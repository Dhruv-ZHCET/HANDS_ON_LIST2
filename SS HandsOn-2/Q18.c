
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];

    // Create two pipes
    pipe(pipe1);
    pipe(pipe2);

    // First child: ls -l
    if (fork() == 0) {
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls failed");
        exit(1);
    }

    // Second child: grep ^d
    if (fork() == 0) {
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("grep", "grep", "^d", NULL);
        perror("execlp grep failed");
        exit(1);
    }

    // Third child: wc
    if (fork() == 0) {
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc failed");
        exit(1);
    }

    // Parent closes all pipes
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    // Wait for all children
    for (int i = 0; i < 3; i++) wait(NULL);

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q18.c -o Q18
./Q18

====================== Sample Output ================================

10

===========================================================
*/
