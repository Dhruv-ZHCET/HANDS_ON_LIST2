
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; // fd[0]: read end, fd[1]: write end
    pid_t pid;
    char write_msg[] = "Data from parent to child";
    char read_msg[100];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid > 0) { // Parent process
        close(fd[0]); // Close read end
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
        printf("Parent sent data to child.\n");
    }
    else { // Child process
        close(fd[1]); // Close write end
        read(fd[0], read_msg, sizeof(read_msg));
        close(fd[0]);
        printf("Child received data: %s\n", read_msg);
    }

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q15.c -o Q15
./Q15

====================== Sample Output ================================

Parent sent data to child.
Child received data: Data from parent to child

===========================================================
*/
