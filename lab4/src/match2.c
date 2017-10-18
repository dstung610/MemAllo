#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct support{
	int nb_supp;
	int nb_time;
	char* lyric;
}support;

void *supporter (void *arg){
  support *input =  (support *)arg ;
  char *lyric = input->lyric;
  int nb_song = input->nb_time;
  int       i ;
  int       pid ;
  pthread_t tid ;  
  pid = getpid () ;
  tid = pthread_self () ;
  srand ((int) tid) ;

  for (i = 0; i < nb_song; i++){
      printf ("Process %d Thread %x : %s \n", pid, (unsigned int) tid, lyric);
  }
  return (void *) tid ;
}

int main (int argc, char **argv){

  int nb_supp_fr, nb_supp_eng, nb_time_fr, nb_time_eng;
  int i ;
  int nb_threads = 0 ;
  pthread_t *tids ;

  if (argc != 5){
    fprintf(stderr, "usage : %s nb_supp_fr nb_sing_fr nb_supp_eng nb_sing_eng\n", argv[0]) ;
    exit (-1) ;
  }

  nb_supp_fr = atoi(argv[1]);
  nb_time_fr = atoi(argv[2]);
  char *lyric_fr = "French lyric has been sung";
  nb_supp_eng = atoi(argv[3]);
  nb_time_eng = atoi(argv[4]);
  char *lyric_eng = "English lyric has been sung";

  support support_fr = {nb_supp_fr, nb_time_fr, lyric_fr};
  support support_eng = {nb_supp_eng, nb_time_eng, lyric_eng};

  nb_threads = nb_supp_fr + nb_supp_eng; 
  tids = malloc (nb_threads*sizeof(pthread_t)) ;

  /* Create the threads for team1 */
  for (i = 0 ; i < nb_supp_fr; i++){
    pthread_create (&tids[i], NULL, supporter, (void*) &support_fr) ;
  }
  /* Create the other threads (ie. team2) */
  for ( ; i < nb_threads; i++){
    pthread_create (&tids[i], NULL, supporter, (void*) &support_eng) ;
  }  

  /* Wait until every thread ended */ 
    for (i = 0; i < nb_threads; i++){
    pthread_join (tids[i], NULL) ;
  }
  
  free (tids) ;
  return EXIT_SUCCESS;
}
