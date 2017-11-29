#include <stdio.h>
#include <strings.h>
#include <pthread.h>


#include "babble_registration.h"
pthread_mutex_t mutex_reg = PTHREAD_MUTEX_INITIALIZER;

client_bundle_t *registration_table[MAX_CLIENT];
int nb_registered_clients;

void registration_init(void)
{
    nb_registered_clients=0;

    bzero(registration_table, MAX_CLIENT * sizeof(client_bundle_t*));
}

client_bundle_t* registration_lookup(unsigned long key)
{
    int i=0;
    pthread_mutex_lock(&mutex_reg);
    for(i=0; i< nb_registered_clients; i++){
        if(registration_table[i]->key == key){
            pthread_mutex_unlock(&mutex_reg);
            return registration_table[i];
        }
    }
    pthread_mutex_unlock(&mutex_reg);
    return NULL;
}

int registration_insert(client_bundle_t* cl)
{
    if(nb_registered_clients == MAX_CLIENT){
        return -1;
    }

    /* lookup to find if key already exists*/
    client_bundle_t* lp= registration_lookup(cl->key);
    if(lp != NULL){
        fprintf(stderr, "Error -- id % ld already in use\n", cl->key);
        return -1;
    }


    /* insert cl */
    pthread_mutex_lock(&mutex_reg);
    registration_table[nb_registered_clients]=cl;
    nb_registered_clients++;
    pthread_mutex_unlock(&mutex_reg);

    return 0;
}


client_bundle_t* registration_remove(unsigned long key)
{
    int i=0;
    pthread_mutex_lock(&mutex_reg);
    for(i=0; i<nb_registered_clients; i++){
        if(registration_table[i]->key == key){
            break;
        }
    }

    if(i == nb_registered_clients){
        fprintf(stderr, "Error -- no client found\n");
        pthread_mutex_unlock(&mutex_reg);
        return NULL;
    }


    client_bundle_t* cl= registration_table[i];

    nb_registered_clients--;
    registration_table[i] = registration_table[nb_registered_clients];
    pthread_mutex_unlock(&mutex_reg);
    return cl;
}
