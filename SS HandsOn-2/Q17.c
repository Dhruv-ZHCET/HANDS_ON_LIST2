
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void method_dup() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        close(fd[0]);
        dup(fd[1]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    }

    if (fork() == 0) {
        close(fd[1]);
        dup(fd[0]);
        close(fd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp failed");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
}

void method_dup2() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    }

    if (fork() == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("wc", "wc", NULL);
        perror("execlp failed");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
}

void method_fcntl() {
    int fd[2];
    pipe(fd);

    if (fork() == 0) {
        fcntl(fd[1], F_DUPFD, STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    }

    if (fork() == 0) {
        fcntl(fd[0], F_DUPFD, STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("wc", "wc", NULL);
        perror("execlp failed");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
}

int main() {
    printf("=== Using dup ===\n");
    method_dup();

    printf("\n=== Using dup2 ===\n");
    method_dup2();

    printf("\n=== Using fcntl ===\n");
    method_fcntl();

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q17.c -o Q17
./Q17

====================== Sample Output ================================

=== Using dup ===
      10      40     300

=== Using dup2 ===
      10      40     300

=== Using fcntl ===
      10      40     300

===========================================================
*/
