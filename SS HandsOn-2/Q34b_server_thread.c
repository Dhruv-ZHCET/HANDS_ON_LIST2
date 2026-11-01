
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8082
#define BUF_SIZE 1024

void *handle_client(void *arg) {
    int new_socket = *(int *)arg;
    free(arg);

    char buffer[BUF_SIZE];
    char *reply = "Hello from Thread Server";

    memset(buffer, 0, BUF_SIZE);
    read(new_socket, buffer, BUF_SIZE);
    printf("Thread %lu received: %s\n", pthread_self(), buffer);
    send(new_socket, reply, strlen(reply), 0);

    close(new_socket);
    pthread_exit(NULL);
}

int main() {
    int server_fd, *new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Thread Server listening on port %d...\n", PORT);

    while (1) {
        new_socket = malloc(sizeof(int));
        *new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (*new_socket < 0) {
            perror("accept failed");
            free(new_socket);
            continue;
        }

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, new_socket);
        pthread_detach(tid); // No need to join
    }

    return 0;
}

/*
================= Compilation & Run =================

gcc Q34b_server_thread.c -o thread_server -lpthread
./thread_server

================= Sample Output =================
Thread Server listening on port 8082...
Thread 140451234567888 received: Hello from Client

*/
