
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int sig) {
    printf("Caught signal %d\n", sig);
}

int main() {
    printf("Receiver PID: %d\n", getpid());
    
    // Attempt to catch SIGSTOP
    if (signal(SIGSTOP, sig_handler) == SIG_ERR) {
        printf("SIGSTOP cannot be caught or ignored!\n");
    }

    printf("Waiting... Try sending SIGSTOP from another program.\n");
    while(1) {
        sleep(1); // Wait indefinitely
    }

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q13_receiver.c -o Q13_receiver
./Q13_receiver

Sample Output:
Receiver PID: 5678
SIGSTOP cannot be caught or ignored!
Waiting... Try sending SIGSTOP from another program.

===========================================================
*/
