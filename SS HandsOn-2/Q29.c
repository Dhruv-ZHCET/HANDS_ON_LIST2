
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;

    // Generate key and get message queue
    key = ftok(".", 'C');  // Same key used in previous message queue
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Remove message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID failed");
        exit(1);
    }

    printf("Message queue with ID %d removed successfully.\n", msgid);
    printf("Check removal using: ipcs -q\n");

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q29.c -o Q29
./Q29
ipcs -q

====================== Sample Output ================================

Message queue with ID 12347 removed successfully.
$ ipcs -q
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
(No message queues)

===========================================================
*/
