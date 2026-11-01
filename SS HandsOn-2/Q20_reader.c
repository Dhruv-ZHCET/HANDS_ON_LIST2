
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    char *fifo_name = "myfifo";
    char buffer[100];

    int fd = open(fifo_name, O_RDONLY);
    if (fd == -1) {
        perror("open FIFO for reading failed");
        exit(1);
    }

    read(fd, buffer, sizeof(buffer));
    printf("Reader received: %s\n", buffer);

    close(fd);
    return 0;
}

