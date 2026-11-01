
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

    int fd_read = open(fifo1, O_RDONLY);
    int fd_write = open(fifo2, O_WRONLY);

    read(fd_read, buffer, sizeof(buffer));
    printf("Process B received: %s\n", buffer);

    char msg[] = "Hello from Process B";
    write(fd_write, msg, strlen(msg)+1);
    printf("Process B sent: %s\n", msg);

    close(fd_read);
    close(fd_write);
    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q21_reader_writer.c -o Q21_reader_writer
./Q21_reader_writer

====================== Sample Output ================================

Process A sent: Hello from Process A
Process B received: Hello from Process A
Process B sent: Hello from Process B
Process A received: Hello from Process B

===========================================================
*/
