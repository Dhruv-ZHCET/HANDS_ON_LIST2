#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t threads[3];

void* thread_func(void* arg) {
    pthread_t tid = pthread_self();
    pthread_t tid1 = threads[*((int *)arg)];

    printf("Thread %d ID: %lu\n", *((int*)arg), (unsigned long)tid);
    return NULL;
}

int main() {
    int thread_ids[3];
    int i;

    // Create 3 threads
    for (i = 0; i < 3; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have finished.\n");
    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q7.c -o Q7 -pthread
./Q7

====================== Sample Output ================================

Thread 3 ID: 140463347882752
Thread 1 ID: 140463364668160
Thread 2 ID: 140463356275456
All threads have finished.

===========================================================
*/
