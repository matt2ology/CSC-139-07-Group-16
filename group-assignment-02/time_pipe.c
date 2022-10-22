/*
time_pipe.c: version will use a pipe.
The child will write the starting time to the pipe, and the parent will read
from it following the termination of the child process.
You will use the gettimeofday() function to record the current timestamp.

This gettimeofday function is passed a pointer to a struct timeval object,
which contains two members: tv_sec and tv_usec.

These represent the number of elapsed seconds and microseconds since
January 1, 1970 (known as the UNIX EPOCH).
 */

#include <stdio.h>    // printf and fprintf functions are defined here
#include <stdlib.h>   // exit function is defined here (exit(0) is a successful exit)
#include <string.h>   // strlen function is defined here (strlen("string") returns the length of the string)
#include <sys/time.h> // gettimeofday function is defined here (gettimeofday(&tv, NULL) returns the current time)
#include <time.h>     // time_t and struct tm are defined here (time_t is a type used to represent time)
#include <unistd.h>   // fork function is defined here (fork() returns the process ID of the child process)
#include <sys/wait.h> // wait function is defined here (wait(NULL) waits for the child process to terminate)

int main(int argc, char const *argv[])
{
    int fd[2];                 // fd is an array of two integers
    pid_t pid;                 // pid is a process ID
    struct timeval start_time; // tv is a struct timeval object
    struct timeval end_time;
    struct timeval elapsed_time;

    if (pipe(fd) == -1)
    {                       // if pipe(fd) returns -1
        perror("pipe");     // print the error message
        exit(EXIT_FAILURE); // exit with a failure
    }

    pid = fork(); // pid is set to the process ID of the child process

    if (pid == -1)
    {                       // if pid is -1
        perror("fork");     // print the error message
        exit(EXIT_FAILURE); // exit with a failure
    }

    if (pid == 0) //child
    {

        char *arr[argc - 1];
        for (int i = 0; i < argc; i++)
        {
            arr[i] = argv[i + 1];
        }
        close(fd[0]);                                  // close the read end of the pipe
        gettimeofday(&start_time, 0);                  // tv is set to the current time
        write(fd[1], &start_time, sizeof(start_time)); // write the current time to the pipe
        close(fd[1]);                                  // close the write end of the pipe
        execvp(argv[1], arr);
    }
    else                                              //parent
    {                                                 // if pid is not 0
        close(fd[1]);                                 // close the write end of the pipe
        read(fd[0], &start_time, sizeof(start_time)); // read the current time from the pipe
        close(fd[0]);                                 // close the read end of the pipe
        wait(NULL);                                   // wait for the child process to terminate
        gettimeofday(&end_time, 0);
        timersub(&end_time, &start_time, &elapsed_time);
        printf("\nElapsed time: %d.%06d seconds\n", elapsed_time.tv_sec, elapsed_time.tv_usec);

        exit(EXIT_SUCCESS); // exit with a success
    }
}
