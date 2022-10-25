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
#include <stdlib.h>   // exit function is defined here
                      // (exit(0) is a successful exit)
#include <string.h>   // strlen function is defined here
                      // (strlen("string") returns the length of the string)
#include <sys/time.h> // gettimeofday function is defined here
                      // (gettimeofday(&tv, NULL) returns the current time)
#include <time.h>     // time_t and struct tm are defined here
                      // (time_t is a type used to represent time)
#include <unistd.h>   // fork function is defined here
                      // (fork() returns the process ID of the child process)
#include <sys/wait.h> // wait function is defined here
                      // (wait(NULL) waits for the child process to terminate)

int main(int argc, char const *argv[])
{
    int fd[2];                 // fd is an array of two integers
    pid_t pid;                 // pid is a process ID
    struct timeval start_time; // tv is a struct timeval object
    struct timeval end_time;
    struct timeval elapsed_time; // elapsed_time is a struct timeval object

    if (pipe(fd) == -1)
    {                       // if pipe(fd) returns -1
        perror("pipe");     // print the error message "pipe"
        exit(EXIT_FAILURE); // exit with a failure status
    }

    pid = fork(); // pid is set to the process ID of the child process

    if (pid == -1)
    {                       // if pid is -1
        perror("fork");     // print the error message "fork"
        exit(EXIT_FAILURE); // exit with a failure status code
    }

    if (pid == 0) // child 
    {

        char *arr[argc - 1];
        for (int i = 0; i < argc; i++) // for each argument
        {
            // fix  to 'char *' from 'const char *' discards qualifiers
            arr[i] = (char *)argv[i + 1]; // set arr[i] to the argument
        }

        // close the read end of the pipe (fd[0])
        close(fd[0]);
        // tv is set to the current time (using gettimeofday)
        gettimeofday(&start_time, 0);
        // write the current time to the pipe
        write(fd[1], &start_time, sizeof(start_time));
        // close the write end of the pipe (we are done writing)
        close(fd[1]);
        // execute the command with the arguments passed to the program
        execvp(argv[1], arr);
    }
    else // else if pid is not 0
    {
        // close the write end of the pipe (we only want to read)
        close(fd[1]);
        // read the current time from the pipe into tv and store it in tv
        read(fd[0], &start_time, sizeof(start_time));
        // close the read end of the pipe (we are done reading)
        close(fd[0]);
        // wait for the child process to terminate (wait(NULL))
        wait(NULL);

        gettimeofday(&end_time, 0); // tv is set to the current time following
                                    // the termination of the child process
        // elapsed_time = end_time - start_time
        timersub(&end_time, &start_time, &elapsed_time);
        // type cast the time to a long int and print it to the screen
        printf("\n Elapsed time: %ld.%06ld seconds \n",
               (long int)elapsed_time.tv_sec,
               (long int)elapsed_time.tv_usec);
        exit(EXIT_SUCCESS); // exit with a success
    }
}
