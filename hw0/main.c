#include <stdio.h>
#include <sys/resource.h>

int main() {
    
    struct rlimit lim;

    int stackSize = getrlimit(RLIMIT_STACK, &lim);
    printf("\n\nstack size: %ld\n", lim.rlim_cur);
    
    int processLimit = getrlimit(RLIMIT_NPROC, &lim);
    printf("process limit: %ld\n", lim.rlim_cur);
    
    int maxFileDesc = getrlimit(RLIMIT_NOFILE, &lim);
    printf("max file descriptors: %ld\n", lim.rlim_cur);
    return 0;
}
