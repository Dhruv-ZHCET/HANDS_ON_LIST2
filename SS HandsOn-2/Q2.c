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

    printf("%-20s : ", name);

    if (limit.rlim_cur == RLIM_INFINITY)
        printf("Soft = unlimited, ");
    else
        printf("Soft = %ld, ", (long)limit.rlim_cur);

    if (limit.rlim_max == RLIM_INFINITY)
        printf("Hard = unlimited\n");
    else
        printf("Hard = %ld\n", (long)limit.rlim_max);
}

int main() {
    printf("======= System Resource Limits =======\n\n");

    print_limit(RLIMIT_CPU, "CPU time (sec)");
    print_limit(RLIMIT_FSIZE, "File size (bytes)");
    print_limit(RLIMIT_DATA, "Data seg size (bytes)");
    print_limit(RLIMIT_STACK, "Stack size (bytes)");
    print_limit(RLIMIT_CORE, "Core file size (bytes)");
    print_limit(RLIMIT_RSS, "Resident set size");
    print_limit(RLIMIT_NOFILE, "Open files");
    print_limit(RLIMIT_AS, "Address space (bytes)");
    print_limit(RLIMIT_NPROC, "Number of processes");
    print_limit(RLIMIT_MEMLOCK, "Locked memory (bytes)");
    print_limit(RLIMIT_MSGQUEUE, "POSIX msg queue (bytes)");
    print_limit(RLIMIT_NICE, "Max nice priority");
    print_limit(RLIMIT_RTPRIO, "Max real-time priority");

    printf("\n======================================\n");

    return 0;
}

