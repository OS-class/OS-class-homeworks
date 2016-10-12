#include <stdio.h>
#include <stdlib.h>

int staticdata = 31;

void f(int v) {
	if(v == -1) return;
	int temp = v;
	printf("recur call %d: stack@ %lx\n", v, (long unsigned int)&temp);
	f(v-1);
}

int main() {
	int i;
	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	printf("_main @ %lx\n", (long unsigned int)&main);
	printf("_recur @ %lx\n", (long unsigned int)&f);
	printf("_main stack: %lx\n", (long unsigned int)&i);
	printf("static data: %lx\n", (long unsigned int)&staticdata);
	printf("Heap: malloc 1: %p\n", a);
	printf("Heap: malloc 2: %p\n", b);
	f(3);
}


