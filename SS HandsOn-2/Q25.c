
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds buf;

    // Generate key and create/get message queue
    key = ftok(".", 'B');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Get message queue info
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    printf("Message Queue ID: %d\n", msgid);
    printf("Access Permissions: %o\n", buf.msg_perm.mode & 0777);
    printf("Owner UID: %d, GID: %d\n", buf.msg_perm.uid, buf.msg_perm.gid);
    printf("Last message sent: %s", ctime(&buf.msg_stime));
    printf("Last message received: %s", ctime(&buf.msg_rtime));
    printf("Last change: %s", ctime(&buf.msg_ctime));
    printf("Current bytes in queue: %ld\n", buf.__msg_cbytes);
    printf("Number of messages in queue: %ld\n", buf.msg_qnum);
    printf("Maximum bytes allowed in queue: %ld\n", buf.msg_qbytes);
    printf("PID of last msgsnd: %d\n", buf.msg_lspid);
    printf("PID of last msgrcv: %d\n", buf.msg_lrpid);

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q25.c -o Q25
./Q25

====================== Sample Output ================================

Message Queue ID: 12346
Access Permissions: 666
Owner UID: 1000, GID: 1000
Last message sent: Thu Sep 30 10:30:01 2025
Last message received: Thu Sep 30 10:29:50 2025
Last change: Thu Sep 30 10:30:01 2025
Current bytes in queue: 0
Number of messages in queue: 0
Maximum bytes allowed in queue: 8192
PID of last msgsnd: 0
PID of last msgrcv: 0

===========================================================
*/
