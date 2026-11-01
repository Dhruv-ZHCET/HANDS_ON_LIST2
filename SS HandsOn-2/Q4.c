#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <x86gprintrin.h>
#include <x86intrin.h>

// Function to read Time Stamp Counter
// static __inline__ uint64_t rdtsc(void) {
//     unsigned int lo, hi;
//     __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
//     return ((uint64_t)hi << 32) | lo;
// }

int main() {
    uint64_t start, end;
    int i;

    // Measure start time
    start = _rdtsc();

    // Execute getppid() 100 times
    for (i = 0; i < 100; i++) {
        getppid();
    }

    // Measure end time
    end = _rdtsc();

    printf("Start TSC: %lu\n", start);
    printf("End   TSC: %lu\n", end);
    printf("Cycles taken for 100 getppid() calls: %lu\n", end - start);
    printf("Average cycles per getppid(): %lu\n", (end - start) / 100);

    return 0;
}


