
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key;
    int msgid;
    struct msqid_ds buf;

    // Generate key and get message queue
    key = ftok(".", 'C');  // Same key as previous message queue
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Get current message queue info
    if (msgctl(msgid, IPC_STAT, &buf) == -1) {
        perror("msgctl IPC_STAT failed");
        exit(1);
    }

    printf("Current permissions: %o\n", buf.msg_perm.mode & 0777);

    // Change permissions to 644
    buf.msg_perm.mode = 0644;
    if (msgctl(msgid, IPC_SET, &buf) == -1) {
        perror("msgctl IPC_SET failed");
        exit(1);
    }

    printf("Permissions updated to: %o\n", buf.msg_perm.mode & 0777);

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q28.c -o Q28
./Q28

====================== Sample Output ================================

Current permissions: 666
Permissions updated to: 644

===========================================================
*/
