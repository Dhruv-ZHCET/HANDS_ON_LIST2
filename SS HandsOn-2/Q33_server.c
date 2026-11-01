
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024
#define LOG_FILE "server_log.txt"

void log_message(const char *msg) {
    FILE *fp = fopen(LOG_FILE, "a"); // append mode
    if (fp == NULL) {
        perror("fopen failed");
        return;
    }
    fprintf(fp, "%s\n", msg);
    fclose(fp);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[BUF_SIZE] = {0};
    char *reply = "Hello from Server";
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connection
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);
    log_message("Server listening on port 8080...");

    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Read message from client
    read(new_socket, buffer, BUF_SIZE);
    printf("Client says: %s\n", buffer);

    char logbuf[BUF_SIZE + 50];
    snprintf(logbuf, sizeof(logbuf), "Client says: %s", buffer);
    log_message(logbuf);

    // Send reply to client
    send(new_socket, reply, strlen(reply), 0);
    printf("Server sent reply\n");
    log_message("Server sent reply");

    close(new_socket);
    close(server_fd);
    return 0;
}

/*
================= Compilation & Run =================

gcc Q33_server.c -o server
./server

# Output will be printed on console AND appended to server_log.txt

================= Sample server_log.txt after one run =================
Server listening on port 8080...
Client says: Hello from Client
Server sent reply

*/
