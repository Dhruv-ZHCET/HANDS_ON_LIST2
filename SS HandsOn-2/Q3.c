
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <errno.h>

void print_limit(int resource, const char *name) {
    struct rlimit limit;
    if (getrlimit(resource, &limit) == -1) {
        perror("getrlimit failed");
        return;
    }

    printf("%-20s : Soft = %ld, Hard = %ld\n", 
            name, (long)limit.rlim_cur, (long)limit.rlim_max);
}

int main() {
    struct rlimit limit;

    printf("======= Before changing limit =======\n");
    print_limit(RLIMIT_NOFILE, "Open files");

    // Set new limit (soft = 2048, hard = 4096)
    limit.rlim_cur = 2048;   // new soft limit
    limit.rlim_max = 4096;   // new hard limit

    if (setrlimit(RLIMIT_NOFILE, &limit) == -1) {
        perror("setrlimit failed");
        exit(1);
    }

    printf("\n======= After changing limit =======\n");
    print_limit(RLIMIT_NOFILE, "Open files");

    return 0;
}

/*
====================== Compilation & Execution ======================

gcc Q3.c -o Q3
./Q3

====================== Sample Output ================================

======= Before changing limit =======
Open files           : Soft = 1024, Hard = 1048576

======= After changing limit =======
Open files           : Soft = 2048, Hard = 4096

=====================================================================
*/
