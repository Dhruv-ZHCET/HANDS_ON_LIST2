#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
    const char *fifo_name = "myfifo";
    char buffer[100];

    /* Step 1: Create FIFO if it does not exist */
    if (mkfifo(fifo_name, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo failed");
        return 1;
    }

    /* Step 2: Open FIFO for reading without blocking */
    int fd = open(fifo_name, O_RDONLY | O_NONBLOCK);

    if (fd == -1) {
        perror("open FIFO failed");
        return 1;
    }

    /*
     * Step 3: Keep a writer end open.
     * This prevents EOF from making the FIFO appear
     * readable when no external writer has sent data.
     */
    int keep_fd = open(fifo_name, O_WRONLY | O_NONBLOCK);

    if (keep_fd == -1) {
        perror("open FIFO writer end failed");
        close(fd);
        return 1;
    }

    /* Step 4: Prepare the read descriptor set */
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    /* Step 5: Set timeout to 10 seconds */
    struct timeval timeout;

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for FIFO data for 10 seconds...\n");
    fflush(stdout);

    /* Step 6: Wait for FIFO readability */
    int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (ret == -1) {
        perror("select failed");
    }
    else if (ret == 0) {
        printf("Timeout! No data received within 10 seconds.\n");
    }
    else if (FD_ISSET(fd, &readfds)) {
        /* Step 7: Read the available data */
        ssize_t n = read(fd, buffer, sizeof(buffer) - 1);

        if (n > 0) {
            buffer[n] = '\0';
            printf("Data received: %s\n", buffer);
        }
        else if (n == 0) {
            printf("FIFO reached EOF.\n");
        }
        else {
            perror("read failed");
        }
    }

    /* Step 8: Close descriptors */
    close(keep_fd);
    close(fd);

    return 0;
}