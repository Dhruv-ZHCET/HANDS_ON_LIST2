
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>


struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;
    struct msgbuf message;

    // Generate key and get message queue
    key = ftok(".", 'C');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    msgid = msgget(key, IPC_CREAT|0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("=== Blocking receive (flag = 0) ===\n");
    if (msgrcv(msgid, &message, sizeof(message.mtext), 0, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }
    printf("Received message: %s\n", message.mtext);

    printf("\n=== Non-blocking receive (flag = IPC_NOWAIT) ===\n");
    if (msgrcv(msgid, &message, sizeof(message.mtext), 0, IPC_NOWAIT) == -1) {
        if (errno == ENOMSG) {
            printf("No message available (non-blocking)\n");
        } else {
            perror("msgrcv failed");
            exit(1);
        }
    } else {
        printf("Received message: %s\n", message.mtext);
    }

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q27.c -o Q27
./Q27

====================== Sample Output ================================

=== Blocking receive (flag = 0) ===
Received message: Hello, this is a message

=== Non-blocking receive (flag = IPC_NOWAIT) ===
No message available (non-blocking)

===========================================================
*/
