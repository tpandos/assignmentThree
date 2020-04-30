/*
    Assignment 2
    Tamara Pando 
    March 19, 2020
*/

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h> 
#include <time.h> 

#define THREAD_NUMBER 2
#define BOUND 10000
pthread_t tid[THREAD_NUMBER]; 
pthread_mutex_t mutexLock; 

void *threadFunc();  // thread function prototype 

int main(int argc, char* argv[]){

    clock_t tStart = clock(); // start clock

    int i = 0, returnVal; 

    if(pthread_mutex_init(&mutexLock, NULL) != 0){  // check that mutex was initialized 
        printf("mutex initializer failed\n"); 
        return 1; 
    }
    
    //---- creating threads 
    while(i < THREAD_NUMBER){

        returnVal = pthread_create(&(tid[i]), NULL, threadFunc, NULL); 

        if(returnVal != 0){     // test for error in pthread_create
            printf("\nERROR: Thread can't be created \n"); 
            return 1; 
        }
        i++; 
    }
    printf("%d threads created\n", i); 

    // loop for joining threads
    for(int j = 0; j < THREAD_NUMBER; j++){ 
        pthread_join(tid[j],NULL);
    }
    
    pthread_mutex_destroy(&mutexLock); 
    println("Thread 1");
    //printf("Program execution time: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC); 
    
    return 0;
}

// thread function implementation 
void *threadFunc(){

    pthread_mutex_lock(&mutexLock); // locking the variables until work is done

    // lock and thread 
    println("Thread 2"); 

    pthread_mutex_unlock(&mutexLock); // unlocking after work is done 
    return NULL; 
} 
