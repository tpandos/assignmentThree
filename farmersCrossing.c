/*
    Assignment 3
    Tamara Pando 
    April 30, 2020
*/

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h> 
#include <time.h> 
#include <unistd.h>  // for sleep 

#define THREAD_NUMBER 6         //  threads numbers for farmers 

pthread_t goingNorth[THREAD_NUMBER];    // farmer goingNorth thread
pthread_t goingSouth[THREAD_NUMBER];    // farmer goingSouth thread 

pthread_mutex_t mutexLock; // deckare mutex
int northBound = 1, southBound = 1; // farmer numbers 

void *southboundFarmerThread(void *param);  // thread function crossing southbound 
void *northboundFarmerTheard(void *param);  // thread function crossing northbound
 
int main(int argc, char* argv[]){

    srand(time(NULL)); 
    int south, north, i = 0, j = 0; 

    if(pthread_mutex_init(&mutexLock, NULL) != 0)            // uinitialize mutex 
    {  
        printf("mutex initializer failed\n"); 
        return 1; 
    }
    
    //---- creating threads 
    while(i < THREAD_NUMBER){

        north = pthread_create(&(goingNorth[i]), NULL, northboundFarmerTheard, NULL);   // creating threads 
        if(north != 0){     // test for error in pthread_create
            printf("\nERROR: Thread can't be created \n"); 
            return 1; 
        }
        south = pthread_create(&(goingSouth[i]), NULL, southboundFarmerThread, NULL);   // creating threads 
        if(south != 0){     // test for error in pthread_create
            printf("\nERROR: Thread can't be created \n"); 
            return 1; 
        }
        i++; 
    }
    //printf("%d threads created\n", i); 

    while(j < THREAD_NUMBER)                    // loop for joining threads
    {
        if((pthread_join(goingNorth[j],NULL)) != 0  || (pthread_join(goingSouth[j],NULL) != 0))
        {
            perror("Thread joinging failed\n"); 
            exit(EXIT_FAILURE); 
        }
        j++;
    }

    pthread_mutex_destroy(&mutexLock);      // destroy the mutex 
    return 0;
}

// thread for going south throguh the bridge 
void *southboundFarmerThread(void *param)
{
    pthread_mutex_lock(&mutexLock);     // lock 
    printf("\nNorth Tunbridge #%d farmer can cross the bridge\n", southBound);
    printf("North Tunbridge #%d is traveling on the bridge...\n", southBound);
    sleep(rand() % 4);  // sleep requirement 
    printf("North Tunbridge #%d farmer has left the bridge\n", southBound);
    southBound++; // keep track number of farmers going south
    pthread_mutex_unlock(&mutexLock); // unlock 
}

// thread for going north 
void *northboundFarmerTheard(void *param)
{
    pthread_mutex_lock(&mutexLock); // lock 
    printf("\nSouth Tunbridge #%d farmer can cross the bridge\n", northBound);
    printf("South Tunbridge #%d is traveling on the bridge...\n", northBound);
    sleep(rand() % 4);  
    printf("South Tunbridge #%d farmer has left the bridge\n", northBound);
    northBound++; // keep track number of farmers going north
    pthread_mutex_unlock(&mutexLock);   //unlock
}
