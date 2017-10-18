#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char **argv){
	if(argc != 5){
		exit(-1);
	}

	nb_fr_supp = argv[1];
	nb_fr_time = argv[2];
	nb_eng_supp = argv[3];
	nb_eng_time = argv[4];

	
}
