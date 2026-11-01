
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *msg = "Hello from Client";
    char buffer[BUF_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Replace "127.0.0.1" with SERVER's IP address if on different machines
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        exit(EXIT_FAILURE);
    }

    // Send message
    send(sock, msg, strlen(msg), 0);
    printf("Client sent message\n");

    // Receive reply
    read(sock, buffer, BUF_SIZE);
    printf("Server says: %s\n", buffer);

    close(sock);
    return 0;
}

/*
================= Compilation & Run =================

gcc Q33_client.c -o client
./client

Client sent message
Server says: Hello from Server

*/
