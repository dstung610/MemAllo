#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char *alloc_block;
	alloc_block = (char *)malloc(12);
	printf("%d\n", getpid());
	printf("%p\n", alloc_block);


	sleep(30);
	return 0;
}
