
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    // Generate unique key
    key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q24.c -o Q24
./Q24

====================== Sample Output ================================

Message Queue Key: 65538
Message Queue ID: 12345

===========================================================
*/
