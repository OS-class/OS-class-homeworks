#include <stdio.h>
#include <sys/resource.h>

int main() {

    struct rlimit limit;

    getrlimit (RLIMIT_STACK, &limit);
    printf("stack size: %ld\n", limit.rlim_max);

    getrlimit (RLIMIT_NPROC, &limit);
    printf("process limit: %ld\n", limit.rlim_max);

    getrlimit (RLIMIT_NOFILE, &limit);
    printf("max file descriptors: %ld\n", limit.rlim_max);

    return 0;
}
