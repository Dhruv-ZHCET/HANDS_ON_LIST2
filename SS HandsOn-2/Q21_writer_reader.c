
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    char *fifo1 = "fifo1"; // A -> B
    char *fifo2 = "fifo2"; // B -> A
    char buffer[100];

    // Create FIFOs if they don't exist
    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    int fd_write = open(fifo1, O_WRONLY);
    int fd_read = open(fifo2, O_RDONLY);

    char msg[] = "Hello from Process A";
    write(fd_write, msg, strlen(msg)+1);
    printf("Process A sent: %s\n", msg);

    read(fd_read, buffer, sizeof(buffer));
    printf("Process A received: %s\n", buffer);

    close(fd_write);
    close(fd_read);
    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q21_writer_reader.c -o Q21_writer_reader
./Q21_writer_reader

===========================================================
*/
