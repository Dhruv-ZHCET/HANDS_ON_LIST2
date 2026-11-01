
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int parent_to_child[2]; // Pipe 1
    int child_to_parent[2]; // Pipe 2
    pid_t pid;
    char parent_msg[] = "Hello Child, this is Parent";
    char child_msg[] = "Hello Parent, this is Child";
    char buffer[100];

    // Create pipes
    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid > 0) { // Parent process
        close(parent_to_child[0]); // Close read end of pipe1
        close(child_to_parent[1]); // Close write end of pipe2

        // Send message to child
        write(parent_to_child[1], parent_msg, strlen(parent_msg) + 1);

        // Receive message from child
        read(child_to_parent[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);

        close(parent_to_child[1]);
        close(child_to_parent[0]);
    }
    else { // Child process
        close(parent_to_child[1]); // Close write end of pipe1
        close(child_to_parent[0]); // Close read end of pipe2

        // Receive message from parent
        read(parent_to_child[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);

        // Send reply to parent
        write(child_to_parent[1], child_msg, strlen(child_msg) + 1);

        close(parent_to_child[0]);
        close(child_to_parent[1]);
    }

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q16.c -o Q16
./Q16

====================== Sample Output ================================

Child received: Hello Child, this is Parent
Parent received: Hello Parent, this is Child

===========================================================
*/
