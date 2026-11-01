
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

// semaphore operations
void sem_wait(int semid) {
    struct sembuf sb = {0, -1, 0};   // P() : decrement
    if (semop(semid, &sb, 1) == -1) {
        perror("sem_wait failed");
        exit(1);
    }
}

void sem_signal(int semid) {
    struct sembuf sb = {0, 1, 0};    // V() : increment
    if (semop(semid, &sb, 1) == -1) {
        perror("sem_signal failed");
        exit(1);
    }
}

int main() {
    key_t key1 = ftok(".", 'G');
    key_t key2 = ftok(".", 'H');
    int sem_ticket, sem_shm, sem_resources;
    union semun arg;

    // ============= (a) Ticket Number Creation =================
    sem_ticket = semget(key1, 1, 0666 | IPC_CREAT);
    arg.val = 1; // binary semaphore
    semctl(sem_ticket, 0, SETVAL, arg);

    printf("\n(a) Ticket counter using semaphore:\n");
    int ticket = 0;
    for (int i = 0; i < 5; i++) {
        sem_wait(sem_ticket);
        ticket++;
        printf("Process %d got ticket #%d\n", getpid(), ticket);
        sem_signal(sem_ticket);
    }

    // ============= (b) Shared Memory Write Protection ==========
    int shmid = shmget(key2, 100, 0666 | IPC_CREAT);
    char *shm = shmat(shmid, NULL, 0);

    sem_shm = semget(ftok(".", 'I'), 1, 0666 | IPC_CREAT);
    arg.val = 1;
    semctl(sem_shm, 0, SETVAL, arg);

    if (fork() == 0) {
        sem_wait(sem_shm);
        sprintf(shm, "Child writing to shared memory\n");
        sleep(2);
        sem_signal(sem_shm);
        exit(0);
    } else {
        sem_wait(sem_shm);
        sprintf(shm, "Parent writing to shared memory\n");
        sleep(2);
        sem_signal(sem_shm);
        wait(NULL);
        printf("\n(b) Shared memory content: %s", shm);
    }

    shmdt(shm);

    // ============= (c) Counting Semaphore for Resources =======
    sem_resources = semget(ftok(".", 'J'), 1, 0666 | IPC_CREAT);
    arg.val = 2; // two resources available
    semctl(sem_resources, 0, SETVAL, arg);

    printf("\n(c) Multiple resource protection using counting semaphore:\n");
    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            sem_wait(sem_resources);
            printf("Process %d acquired resource\n", getpid());
            sleep(2);
            printf("Process %d releasing resource\n", getpid());
            sem_signal(sem_resources);
            exit(0);
        }
    }
    while (wait(NULL) > 0);

    // ============= (d) Cleanup ================================
    semctl(sem_ticket, 0, IPC_RMID);
    semctl(sem_shm, 0, IPC_RMID);
    semctl(sem_resources, 0, IPC_RMID);
    shmctl(shmid, IPC_RMID, NULL);

    printf("\n(d) All semaphores and shared memory removed.\n");

    return 0;
}

/*
================= Compilation & Run =================

gcc Q32.c -o Q32
./Q32

================= Sample Output =====================

(a) Ticket counter using semaphore:
Process 12345 got ticket #1
Process 12345 got ticket #2
Process 12345 got ticket #3
Process 12345 got ticket #4
Process 12345 got ticket #5

(b) Shared memory content: Parent writing to shared memory

(c) Multiple resource protection using counting semaphore:
Process 12346 acquired resource
Process 12347 acquired resource
Process 12348 acquired resource
Process 12346 releasing resource
Process 12347 releasing resource
Process 12348 releasing resource

(d) All semaphores and shared memory removed.

=================================================================
*/
