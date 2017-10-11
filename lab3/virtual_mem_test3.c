#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	char *alloc_block;
	printf("%d\n", getpid());
	for(int i = 0; i < 100; i++){
		alloc_block = (char *)malloc(10000000);
		printf("%p\n", alloc_block);

	}

	sleep(30);
	return 0;
}
