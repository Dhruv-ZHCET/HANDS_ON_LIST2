
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    struct rlimit limit;

    printf("===== System Limits =====\n\n");

    // a. Maximum length of arguments to exec
    long max_args = sysconf(_SC_ARG_MAX);
    printf("Maximum length of arguments to exec: %ld\n", max_args);

    // b. Maximum number of simultaneous processes per user id
    if (getrlimit(RLIMIT_NPROC, &limit) == 0)
        printf("Max simultaneous processes per user: %ld\n", (long)limit.rlim_cur);
    else
        perror("RLIMIT_NPROC");

    // c. Number of clock ticks per second
    long ticks = sysconf(_SC_CLK_TCK);
    printf("Number of clock ticks (jiffies) per second: %ld\n", ticks);

    // d. Maximum number of open files
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0)
        printf("Maximum number of open files: %ld\n", (long)limit.rlim_cur);
    else
        perror("RLIMIT_NOFILE");

    // e. Size of a page
    long page_size = sysconf(_SC_PAGESIZE);
    printf("Page size (bytes): %ld\n", page_size);

    // f. Total number of pages in physical memory
    long phys_pages = sysconf(_SC_PHYS_PAGES);
    printf("Total number of pages in physical memory: %ld\n", phys_pages);

    // g. Number of currently available pages in physical memory
    long avail_pages = sysconf(_SC_AVPHYS_PAGES);
    printf("Available pages in physical memory: %ld\n", avail_pages);

    return 0;
}
