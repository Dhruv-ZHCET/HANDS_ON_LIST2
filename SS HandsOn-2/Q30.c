
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main() {
    key_t key;
    int shmid;
    char *shmaddr;

    // Generate key
    key = ftok(".", 'D');
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create shared memory
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }
    printf("Shared memory created with ID: %d\n", shmid);

    // Attach shared memory (read-write)
    shmaddr = (char *) shmat(shmid, NULL, 0);
    if (shmaddr == (char *) -1) {
        perror("shmat failed");
        exit(1);
    }

    // Write data to shared memory
    strcpy(shmaddr, "Hello from shared memory");
    printf("Data written to shared memory: %s\n", shmaddr);

    // Attach shared memory read-only
    char *shm_ro = (char *) shmat(shmid, NULL, SHM_RDONLY);
    if (shm_ro == (char *) -1) {
        perror("shmat read-only failed");
    } else {
        printf("Attached read-only. Current data: %s\n", shm_ro);
        // Attempt to overwrite (should fail / not allowed)
        // shm_ro[0] = 'h'; // Uncommenting this may cause segmentation fault
        shmdt(shm_ro);
    }

    // Detach shared memory
    if (shmdt(shmaddr) == -1) {
        perror("shmdt failed");
        exit(1);
    }
    printf("Shared memory detached successfully.\n");

    // Remove shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID failed");
        exit(1);
    }
    printf("Shared memory removed successfully.\n");

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q30.c -o Q30
./Q30

====================== Sample Output ================================

Shared memory created with ID: 32768
Data written to shared memory: Hello from shared memory
Attached read-only. Current data: Hello from shared memory
Shared memory detached successfully.
Shared memory removed successfully.

===========================================================
*/
