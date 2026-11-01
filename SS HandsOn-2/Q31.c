
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// Union required for semctl
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t key1, key2;
    int semid_binary, semid_counting;
    union semun arg;

    // Generate keys
    key1 = ftok(".", 'E');
    key2 = ftok(".", 'F');
    if (key1 == -1 || key2 == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create a binary semaphore (1 semaphore in set)
    semid_binary = semget(key1, 1, 0666 | IPC_CREAT);
    if (semid_binary == -1) {
        perror("semget binary failed");
        exit(1);
    }

    // Initialize binary semaphore with value 1
    arg.val = 1;
    if (semctl(semid_binary, 0, SETVAL, arg) == -1) {
        perror("semctl binary failed");
        exit(1);
    }
    printf("Binary semaphore created with ID: %d, initialized to 1\n", semid_binary);

    // Create a counting semaphore (1 semaphore in set)
    semid_counting = semget(key2, 1, 0666 | IPC_CREAT);
    if (semid_counting == -1) {
        perror("semget counting failed");
        exit(1);
    }

    // Initialize counting semaphore with value 5
    arg.val = 5;
    if (semctl(semid_counting, 0, SETVAL, arg) == -1) {
        perror("semctl counting failed");
        exit(1);
    }
    printf("Counting semaphore created with ID: %d, initialized to 5\n", semid_counting);

    // Show semaphores in system
    printf("\n--- ipcs -s output ---\n");
    system("ipcs -s");

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q31.c -o Q31
./Q31

====================== Sample Output ================================

Binary semaphore created with ID: 65536, initialized to 1
Counting semaphore created with ID: 65537, initialized to 5

--- ipcs -s output ---

------ Semaphore Arrays --------
key        semid      owner      perms      nsems
0x45000004 65536      devanshi   666        1
0x46000004 65537      devanshi   666        1

===========================================================
*/
