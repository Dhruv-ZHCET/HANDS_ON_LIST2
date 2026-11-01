
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) {
    printf("ITIMER_PROF: Timer expired (signal %d)\n", sig);
}

int main() {
    struct itimerval timer;

    signal(SIGPROF, handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer failed");
        exit(1);
    }

    printf("ITIMER_PROF set for 10s + 10us intervals...\n");

    // Busy loop to consume both user + kernel time
    while (1);

    return 0;
}

