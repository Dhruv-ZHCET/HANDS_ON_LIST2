
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    // Ignore SIGINT
    printf("Ignoring SIGINT for 5 seconds (Ctrl+C will be ignored)...\n");
    signal(SIGINT, SIG_IGN);
    sleep(5);

    // Reset default action
    printf("Resetting SIGINT to default action (Ctrl+C will now terminate)...\n");
    signal(SIGINT, SIG_DFL);
    sleep(5);

    printf("Program running. Press Ctrl+C to test default SIGINT action.\n");
    while(1); // Keep running to test SIGINT

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q9.c -o Q9
./Q9

====================== Sample Output ================================

Ignoring SIGINT for 5 seconds (Ctrl+C will be ignored)...
(Pressing Ctrl+C now has no effect)
^C
Resetting SIGINT to default action (Ctrl+C will now terminate)...
Program running. Press Ctrl+C to test default SIGINT action.
^C

===========================================================
*/
