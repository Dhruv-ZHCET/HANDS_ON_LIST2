
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msgbuf {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;
    struct msgbuf message;

    // Generate key and create/get message queue
    key = ftok(".", 'C');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // message.mtype = 1; // Message type
    strcpy(message.mtext, "Hello, this is a message");

    if (msgsnd(msgid, &message, sizeof(message.mtext)+1, 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Message sent to queue (ID: %d)\n", msgid);
    printf("Check message queue using: ipcs -q\n");

    return 0;
}


