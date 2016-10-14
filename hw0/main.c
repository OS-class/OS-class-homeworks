#include <stdio.h>
#include <sys/resource.h>
int main() {
	struct rlimit limit;
	getrlimit(RLIMIT_STACK, &limit);
	printf("Stack limit: %d\n", (int)limit.rlim_cur);
	getrlimit(RLIMIT_NPROC, &limit);
	printf("Process limit: %d\n", (int)limit.rlim_cur);
	getrlimit(RLIMIT_NOFILE, &limit);
	printf("Max file descriptor: %d\n", (int)limit.rlim_cur);
	
}
