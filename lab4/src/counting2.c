#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define N_ITER 1000000

int result;

int main (int argc, char **argv)
{

  int i ;
  int nb_threads = 0 ;
  pthread_t *tids;

  if (argc != 2){
    fprintf(stderr, "usage : %s nb_threads\n", argv[0]) ;
    exit (-1) ;
  }

  nb_threads = 10;
  tids = malloc (nb_threads*sizeof(pthread_t)) ;

  for (i = 0 ; i < nb_threads; i++){

  }


  while(1){
	for(i = 0; i < nb_threads; i++){
		pthread_join(tids[i], NULL);
	}
  }

  free (tids) ;

  return EXIT_SUCCESS;
}
