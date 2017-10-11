#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(){
	printf("%d\n", getpid());

	int fd;
	char *map;
	int total = 0;
	fd = open("map_test_file.txt", O_RDONLY);
	do {
		map = mmap(NULL, 200000000, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, fd, 0);
		total++;
	} while(map != MAP_FAILED);
	
	printf("%d\n", total);
	printf("%d\n", getpid());
	sleep(30);
	return 0;
}
