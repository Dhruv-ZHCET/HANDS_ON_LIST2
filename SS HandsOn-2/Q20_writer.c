
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    char *fifo_name = "myfifo";
    char msg[] = "Hello from Dhruv via FIFO";

    // Create FIFO if it doesn't exist
    if (mkfifo(fifo_name, 0666) == -1) {
        perror("mkfifo");
    }

    int fd = open(fifo_name, O_WRONLY);
    if (fd == -1) {
        perror("open FIFO for writing failed");
        exit(1);
    }

    write(fd, msg, sizeof(msg));
    printf("Writer sent: %s\n", msg);

    close(fd);
    return 0;
}


