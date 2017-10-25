#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define N_ITER 1000000

int result;

void talk(int index){
	printf("My thread number is: %d", index);
}

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
  tids = malloc (nb_threads*sizeof(pthread_t));

  pthread_create(&tids[0], NULL, talk, "1");
  pthread_join(&tids[0], NULL);
  pthread_create(&tids[1], NULL, talk, "1");
  pthread_create(&tids[2], NULL, talk, "2");
  pthread_join(&tids[1], NULL);
  pthread_join(&tids[2], NULL);
  pthread_create(&tids[3], NULL, talk, "3");
  pthread_create(&tids[4], NULL, talk, "4");
  pthread_create(&tids[5], NULL, talk, "5");
  pthread_create(&tids[6], NULL, talk, "6");
  pthread_create(&tids[7], NULL, talk, "7");
  pthread_create(&tids[8], NULL, talk, "8");
  pthread_create(&tids[9], NULL, talk, "9");

  free (tids) ;

  return EXIT_SUCCESS;
}
