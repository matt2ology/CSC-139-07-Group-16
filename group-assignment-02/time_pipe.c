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
#define LB_SIZE 1000  // LB_SIZE is defined here (LB_SIZE is the size of the buffer)

int main(int argc, char const *argv[])
{
    int fd[2];            // fd is an array of two integers
    pid_t pid;            // pid is a process ID
    struct timeval tv;    // tv is a struct timeval object
    char buffer[LB_SIZE]; // buffer is a character array of size LB_SIZE
    time_t nowtime;       // nowtime is a time_t object
    struct tm *nowtm;     // nowtm is a struct tm object
    char tmbuf[64];       // tmbuf is a character array of size 64

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

    if (pid == 0)
    {                                  // if pid is 0
        close(fd[0]);                  // close the read end of the pipe
        gettimeofday(&tv, NULL);       // tv is set to the current time
        write(fd[1], &tv, sizeof(tv)); // write the current time to the pipe
        close(fd[1]);                  // close the write end of the pipe
        exit(EXIT_SUCCESS);            // exit with a success
    }
    else
    {                                 // if pid is not 0
        close(fd[1]);                 // close the write end of the pipe
        read(fd[0], &tv, sizeof(tv)); // read the current time from the pipe
        close(fd[0]);                 // close the read end of the pipe
        wait(NULL);                   // wait for the child process to terminate
        nowtime = tv.tv_sec;          // nowtime is set to the number of
                                      // elapsed seconds since January 1, 1970
        nowtm = localtime(&nowtime);  // nowtm is set to the local time
        // tmbuf is set to the formatted time
        strftime(tmbuf, sizeof(tmbuf), "%Y-%m-%d %H:%M:%S", nowtm);
        /*
        print the formatted time and the message
        "Child terminated at: " to the console (stdout) with a newline character
        at the end (printf automatically adds a newline character at the end)
        */
        printf("%s.%06ld %s %s", tmbuf, tv.tv_usec, "Parent", "Child terminated at: ");
        exit(EXIT_SUCCESS); // exit with a success
    }
}
