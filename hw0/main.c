#include <stdio.h>
#include <sys/resource.h>

int main() {
    
    struct rlimit lim;

    int pL = getrlimit(RLIMIT_NPROC, &lim);

    printf("\n\nstack size: %ld\n", 0L);
    printf("process limit: %ld\n", lim.rlim_cur);
    printf("max file descriptors: %ld\n", 0L);
    return 0;
}
