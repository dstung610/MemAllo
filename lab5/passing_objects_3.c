#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define LOOPS 20
#define BUF_SIZE 4

int buffer[BUF_SIZE];
int count, in = 0, out = 0;
sem_t count_empty, count_full;

void pushing(int val)
{
    /* TO DO */

    /* NOTE: pay attention to where to put the call to printf to be
       sure it can be helpful for debugging */
    printf("Push %lu\n", pthread_self());
    sem_wait(&count_empty);
    printf("pushing value %d\n",val);
    buffer[in] = val;
    in = (in + 1) % BUF_SIZE;
    sem_post(&count_full);
}

int fetching(void)
{
    int val=-1;

    /* TO DO */

    /* NOTE: pay attention to where to put the call to printf to be
       sure it can be helpful for debugging */
    printf("Fetch %lu\n", pthread_self());
    sem_wait(&count_full);
    val = buffer[out];
    out = (out + 1) % BUF_SIZE;
    sem_post(&count_empty);
    //usleep(100);


    printf("\t feched value %d\n",val);

    return val;
}

void* thread_generating(void* arg)
{
    int i = 0;
    int new_value = 0;
    
    for(i=0; i<LOOPS; i++){
        new_value = rand()%10;
        pushing(new_value);
    }

    return NULL;
}


void* thread_using(void* arg)
{
    int i = 0;
    int value = 0;
    
    for(i=0; i<LOOPS; i++){
        value = fetching();
    }

    return NULL;
}



int main(void)
{
    int n=2;
    pthread_t tids[n];
    int i=0;
    sem_init(&count_full, 0, 0);
    sem_init(&count_empty, 0, BUF_SIZE);
    struct timespec tt;
    clock_gettime(CLOCK_MONOTONIC, &tt);
    /* seed for the random number generator */
    srand(tt.tv_sec);
    
    for(int index = 0; index < n; index+=2){
    if(pthread_create (&tids[index], NULL, thread_using, NULL) != 0){
        fprintf(stderr,"Failed to create the using thread\n");
        return EXIT_FAILURE;
    }

    if(pthread_create (&tids[index+1], NULL, thread_generating, NULL) != 0){
        fprintf(stderr,"Failed to create the generating thread\n");
        return EXIT_FAILURE;
    }
    }
    
    /* Wait until every thread ended */ 
    for (i = 0; i < n; i++){
        pthread_join (tids[i], NULL) ;
    }  
    
    return EXIT_SUCCESS;
}
