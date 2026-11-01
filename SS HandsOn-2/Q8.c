#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
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

void sigalrm_handler(int sig) {
    printf("Caught SIGALRM (signal %d)\n", sig);
}

void sigvtalrm_handler(int sig) {
    printf("Caught SIGVTALRM (signal %d)\n", sig);
}

void sigprof_handler(int sig) {
    printf("Caught SIGPROF (signal %d)\n", sig);
}

int main() {
    int choice;
    struct itimerval timer;

    printf("Select signal to test:\n");
    printf("1. SIGSEGV\n2. SIGINT\n3. SIGFPE\n4. SIGALRM (alarm)\n");
    printf("5. SIGALRM (setitimer)\n6. SIGVTALRM (setitimer)\n7. SIGPROF (setitimer)\n");
    printf("Enter choice (1-7): ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: // SIGSEGV
            signal(SIGSEGV, sigsegv_handler);
            printf("Triggering SIGSEGV...\n");
            int *p = NULL;
            *p = 10; // Causes segmentation fault
            break;

        case 2: // SIGINT
            signal(SIGINT, sigint_handler);
            printf("Press Ctrl+C to trigger SIGINT...\n");
            while(1) pause();
            break;

        case 3: // SIGFPE
            signal(SIGFPE, sigfpe_handler);
            printf("Triggering SIGFPE...\n");
            int a = 1, b = 0;
            int c = a / b; // Division by zero
            printf("Result: %d\n", c);
            break;

        case 4: // SIGALRM using alarm()
            signal(SIGALRM, sigalrm_handler);
            printf("Alarm set for 3 seconds...\n");
            alarm(3);
            while(1) pause();
            break;

        case 5: // SIGALRM using setitimer
            signal(SIGALRM, sigalrm_handler);
            timer.it_value.tv_sec = 3; timer.it_value.tv_usec = 0;
            timer.it_interval.tv_sec = 0; timer.it_interval.tv_usec = 0;
            setitimer(ITIMER_REAL, &timer, NULL);
            printf("Waiting for SIGALRM (setitimer)...\n");
            while(1) pause();
            break;

        case 6: // SIGVTALRM
            signal(SIGVTALRM, sigvtalrm_handler);
            timer.it_value.tv_sec = 0; timer.it_value.tv_usec = 10;
            timer.it_interval.tv_sec = 0; timer.it_interval.tv_usec = 10;
            setitimer(ITIMER_VIRTUAL, &timer, NULL);
            printf("Running busy loop to trigger SIGVTALRM...\n");
            while(1);
            break;

        case 7: // SIGPROF
            signal(SIGPROF, sigprof_handler);
            timer.it_value.tv_sec = 0; timer.it_value.tv_usec = 10;
            timer.it_interval.tv_sec = 0; timer.it_interval.tv_usec = 10;
            setitimer(ITIMER_PROF, &timer, NULL);
            printf("Running busy loop to trigger SIGPROF...\n");
            while(1);
            break;

        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q8.c -o Q8
./Q8

====================== Sample Output ================================

Select signal to test:
1. SIGSEGV
2. SIGINT
3. SIGFPE
4. SIGALRM (alarm)
5. SIGALRM (setitimer)
6. SIGVTALRM (setitimer)
7. SIGPROF (setitimer)
Enter choice (1-7): 2
Press Ctrl+C to trigger SIGINT...
^C
Caught SIGINT (signal 2)

===========================================================

=== SIGSEGV ===
Triggering SIGSEGV...
Caught SIGSEGV (signal 11)

=== SIGFPE ===
Triggering SIGFPE...
Caught SIGFPE (signal 8)

=== SIGINT ===
Press Ctrl+C to trigger SIGINT...
^C
Caught SIGINT (signal 2)

=== SIGALRM (alarm) ===
Alarm set for 3 seconds...
Caught SIGALRM (signal 14)

=== SIGALRM (setitimer) ===
Waiting for SIGALRM (setitimer)...
Caught SIGALRM (signal 14)

=== SIGVTALRM ===
Running busy loop to trigger SIGVTALRM...
Caught SIGVTALRM (signal 26)
Caught SIGVTALRM (signal 26)
Caught SIGVTALRM (signal 26)
...

=== SIGPROF ===
Running busy loop to trigger SIGPROF...
Caught SIGPROF (signal 27)
Caught SIGPROF (signal 27)
Caught SIGPROF (signal 27)
...

===========================================================
*/
