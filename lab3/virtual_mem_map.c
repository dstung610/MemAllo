#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>

int main(){
	printf("%d\n", getpid());

	int fd;
	fd = open("map_test_file.txt", O_RDONLY);
	char *map_shar = mmap(NULL, 200, PROT_NONE, MAP_SHARED, fd, 0);
	char *map_priv = mmap(NULL, 1000, PROT_NONE, MAP_PRIVATE, fd,0);
	char *map_shar_ano = mmap(NULL, 200, PROT_NONE, MAP_SHARED | MAP_ANONYMOUS, fd, 0);
	char *map_priv_ano = mmap(NULL, 200, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, fd, 0);
	printf("MAP_SHARE: %p\n", map_shar);
	printf("MAP_PRIVATE: %p\n", map_priv);
	printf("MAP_SHARE_ANONYMOUS: %p\n", map_shar_ano);
	printf("MAP_PRIVATE_ANONYMOUS: %p\n", map_priv_ano);
	printf("%d\n", getpid());
	sleep(30);
	return 0;
}
