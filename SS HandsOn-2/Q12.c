
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid > 0) { // Parent process
        printf("Parent process PID: %d\n", getpid());
        printf("Child process PID: %d\n", pid);
        // Sleep to allow child to send SIGKILL
        sleep(5);
        printf("Parent still alive (this should not print if SIGKILL works)\n");
    }
    else { // Child process
        printf("Child process running, PID: %d\n", getpid());
        sleep(2);
        printf("Child sending SIGKILL to parent (PID: %d)\n", getppid());
        kill(getppid(), SIGKILL); // Kill parent
        printf("Child continuing execution, parent killed.\n");
        sleep(5);
        printf("Child PID: %d now orphaned (adopted by init/systemd)\n", getpid());
    }

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q12.c -o Q12
./Q12

====================== Sample Output ================================

Parent process PID: 1234
Child process PID: 1235
Child process running, PID: 1235
Child sending SIGKILL to parent (PID: 1234)
Child continuing execution, parent killed.
Child PID: 1235 now orphaned (adopted by init/systemd)

===========================================================
*/
