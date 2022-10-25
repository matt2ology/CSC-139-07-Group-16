/*
time_shm.c, will have the child process write the starting time to a region of
shared memory before it calls execvp(). After the child process terminates,
the parent will read the starting time from shared memory.

The region of shared memory should be established before the child process
is forked, allowing both the parent and child processes access to the region
of shared memory.
*/

#include <stdio.h>    // printf and fprintf functions are defined here
#include <stdlib.h>   // exit function is defined here (exit(0) is a successful exit)
#include <string.h>   // strlen function is defined here (strlen("string") returns the length of the string)
#include <sys/time.h> // gettimeofday function is defined here (gettimeofday(&tv, NULL) returns the current time)
#include <time.h>     // time_t and struct tm are defined here (time_t is a type used to represent time)
#include <unistd.h>   // fork function is defined here (fork() returns the process ID of the child process)
#include <sys/wait.h> // wait function is defined here (wait(NULL) waits for the child process to terminate)
#include <sys/shm.h>  // shmget, shmat, and shmdt functions are defined here
#define LB_SIZE 1000  // LB_SIZE is defined here (LB_SIZE is the size of the buffer)

int main(int argc, char const *argv[])
{
    int shmid;            // shmid is an integer
    pid_t pid;            // pid is a process ID
    struct timeval *tv;   // tv is a struct timeval object
    char buffer[LB_SIZE]; // buffer is a character array of size LB_SIZE
    // char tmbuf[64];       // tmbuf is a character array of size 64
    struct timeval end_time, elapsed_time;

    shmid = shmget(IPC_PRIVATE, sizeof(struct timeval), 0600); // shmid is set to the shared memory ID
    if (shmid == -1)
    {                       // if shmid is -1
        perror("shmget");   // print the error message
        exit(EXIT_FAILURE); // exit with a failure
    }

    tv = shmat(shmid, NULL, 0); // tv is set to the shared memory address
    if (tv == (void *)-1)
    {                       // if tv is -1
        perror("shmat");    // print the error message
        exit(EXIT_FAILURE); // exit with a failure
    }

    pid = fork(); // pid is set to the process ID of the child process

    if (pid == -1)
    {                       // if pid is -1
        perror("fork");     // print the error message
        exit(EXIT_FAILURE); // exit with a failure
    }

    if (pid == 0)
    {                                  // if pid is 0
        gettimeofday(tv, NULL);        // tv is set to the current time
        execvp(argv[1], &argv[1]);     // execute the command
        perror("execvp");              // print the error message
        exit(EXIT_FAILURE);            // exit with a failure
    }
    else
    {                                 // if pid is not 0
        wait(NULL);                   // wait for the child process to terminate
        gettimeofday(&end_time, NULL);
        timersub(&end_time, &(*tv), &elapsed_time);
        printf("\nElapsed time: %d.%06d seconds\n", elapsed_time.tv_sec, elapsed_time.tv_usec);
        shmdt(tv);                    // detach the shared memory
        shmctl(shmid, IPC_RMID, NULL); // remove the shared memory
    }

    return EXIT_SUCCESS; // EXIT_SUCCESS is a macro defined in stdlib.h
}