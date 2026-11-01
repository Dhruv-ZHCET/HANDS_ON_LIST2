
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <PID of receiver>\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    printf("Sending SIGSTOP to PID %d\n", pid);
    
    if (kill(pid, SIGSTOP) == -1) {
        perror("kill failed");
    } else {
        printf("SIGSTOP sent.\n");
    }

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q13_sender.c -o Q13_sender
./Q13_sender 5678   (replace 5678 with receiver PID)

====================== Sample Output ================================

Sending SIGSTOP to PID 5678
SIGSTOP sent.

===========================================================
*/
