
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int fd[2]; // fd[0]: read end, fd[1]: write end
    char write_msg[] = "Hello I'm Dhruv!";
    char read_msg[100];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    // Write to pipe
    write(fd[1], write_msg, strlen(write_msg) + 1); // include null terminator

    // Read from pipe
    read(fd[0], read_msg, sizeof(read_msg));

    printf("Message read from pipe: %s\n", read_msg);

    // Close pipe
    close(fd[0]);
    close(fd[1]);

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q14.c -o Q14
./Q14

====================== Sample Output ================================

Message read from pipe: Hello I'm Dhruv!

===========================================================
*/
