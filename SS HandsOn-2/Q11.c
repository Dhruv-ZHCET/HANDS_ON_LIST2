
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction sa;

    // Ignore SIGINT
    printf("Ignoring SIGINT (Ctrl+C will be ignored) for 5 seconds...\n");
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sleep(5);

    // Reset default action
    printf("Resetting SIGINT to default action (Ctrl+C will now terminate the program)...\n");
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sleep(5);

    printf("Program running. Press Ctrl+C to test default SIGINT action.\n");
    while(1); // Keep running to test SIGINT

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q11.c -o Q11
./Q11

====================== Sample Output ================================

Ignoring SIGINT (Ctrl+C will be ignored) for 5 seconds...
^C
Resetting SIGINT to default action (Ctrl+C will now terminate the program)...
Program running. Press Ctrl+C to test default SIGINT action.
^C

===========================================================
*/
