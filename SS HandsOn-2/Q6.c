
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_func(void* arg) {
    int id = *((int*)arg);
    printf("Thread %d is running.\n", id);
    return NULL;
}

int main() {
    pthread_t threads[3];
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
