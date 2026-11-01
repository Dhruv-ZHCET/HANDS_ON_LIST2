#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigsegv_handler(int sig) {
    printf("Caught SIGSEGV (signal %d)\n", sig);
    exit(1);
}

void sigint_handler(int sig) {
    printf("Caught SIGINT (signal %d)\n", sig);
}

void sigfpe_handler(int sig) {
    printf("Caught SIGFPE (signal %d)\n", sig);
    exit(1);
}

int main() {
    int choice;
    struct sigaction sa;

    printf("Select signal to test:\n");
    printf("1. SIGSEGV\n2. SIGINT\n3. SIGFPE\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: // SIGSEGV
            sa.sa_handler = sigsegv_handler;
            sigemptyset(&sa.sa_mask);
            sa.sa_flags = 0;
            sigaction(SIGSEGV, &sa, NULL);

            printf("Triggering SIGSEGV...\n");
            int *p = NULL;
            *p = 10; // Causes segmentation fault
            break;

        case 2: // SIGINT
            sa.sa_handler = sigint_handler;
            sigemptyset(&sa.sa_mask);
            sa.sa_flags = 0;
            sigaction(SIGINT, &sa, NULL);

            printf("Press Ctrl+C to trigger SIGINT...\n");
            while(1) pause();
            break;

        case 3: // SIGFPE
            sa.sa_handler = sigfpe_handler;
            sigemptyset(&sa.sa_mask);
            sa.sa_flags = 0;
            sigaction(SIGFPE, &sa, NULL);

            printf("Triggering SIGFPE...\n");
            int a = 1, b = 0;
            int c = a / b; // Division by zero
            printf("Result: %d\n", c);
            break;

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q10.c -o Q10
./Q10

====================== Sample Output ================================

Select signal to test:
1. SIGSEGV
2. SIGINT
3. SIGFPE
Enter choice (1-3): 2
Press Ctrl+C to trigger SIGINT...
^C
Caught SIGINT (signal 2)

Select signal to test: 1
Triggering SIGSEGV...
Caught SIGSEGV (signal 11)

Select signal to test: 3
Triggering SIGFPE...
Caught SIGFPE (signal 8)

===========================================================
*/
