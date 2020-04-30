/*
    Assignment 3
    Tamara Pando 
    March 19, 2020
    
    Create one process with three threads 
*/

#include <stdlib.h>
#include <stdio.h> 
#include <time.h> 
#include <sys/stat.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[]){

    pid_t pid; 
    int status; 

    if((pid = fork()) == -1)
    {
        perror("Error creating process\n"); 
        exit(EXIT_FAILURE); 
    }
    if(pid == 0)
    {
       // process code create three threads
        printf("PID: %d PPID: %d\n", getpid(), getppid());
        printf("Process 1\n"); 
        exit(0); 
    }
    pid = wait(&status);
    printf("Process(pid = %d) exited with the status %d. \n", pid, status);
    return 0;
}


