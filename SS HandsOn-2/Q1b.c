
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("ITIMER_VIRTUAL: Timer expired (signal %d)\n", sig);
}

int main() {
    struct itimerval timer;

    signal(SIGVTALRM, handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer failed");
        exit(1);
    }

    printf("ITIMER_VIRTUAL set for 10s + 10us intervals...\n");

    // Busy loop so process consumes CPU time
    while (1);

    return 0;
}


