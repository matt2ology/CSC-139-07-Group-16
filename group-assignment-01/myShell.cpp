/* Write a C/C++ program to implement an interactive shell in which users can
execute commands.
1. Call this program myShell.
2. Create an infinite loop (while(1))
	that repeatedly prompts the user to enter a command
3. Consider using fgets() to read a line of input from the user.
	Before executing the command entered by the user
4. The command must be compared against the list of supported commands:
	dir, help, vol, path, tasklist, notepad, echo, color, and ping
5. Since some commands require more than one argument (e.g. echo, color, ping),
	you will need to parse the user input into its arguments.
	Consider using the strtok() function

Assumptions: Assume arguments within myShell do not contain spaces. In other
words, don't worry about parsing out quoted strings in your argument list. You may
assume that no more than four arguments will be used on the command line (i.e. similar
to argv[0], argv[1], argv[2], and argv[3])
*/

#include <iostream>	 // for cout, cin, endl etc.
#include <string>	 // for string class and functions (e.g. getline)
#include <cstring>	 // for strtok function (string tokenizer) and strcpy function (string copy)
#include <windows.h> // for SetConsoleTextAttribute function (change text color)
#include <stdio.h>	 // for system function (execute command) and exit function (exit program)

using namespace std;
char input[100];
char *args[4];

// Function prototypes for the threads that will execute system calls
DWORD WINAPI sysDir(LPVOID);
DWORD WINAPI sysHelp(LPVOID);
DWORD WINAPI sysVol(LPVOID);
DWORD WINAPI sysPath(LPVOID);
DWORD WINAPI sysTaskList(LPVOID);
DWORD WINAPI sysNotepad(LPVOID);
DWORD WINAPI sysEcho(LPVOID);
DWORD WINAPI sysColor(LPVOID);
DWORD WINAPI sysPing(LPVOID);

int main(int argc, char const *argv[])
{
	// Create an infinite loop
	DWORD ThreadID;
	HANDLE ThreadHandle;
	while (TRUE)
	{
		// use fgets() to read a line of input from the user
		// char input[100];
		printf("myShell> ");
		fgets(input, 100, stdin);

		// use strtok() to parse the user input into its arguments
		char *token = strtok(input, " \n");
		int i = 0;

		while (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, " \n");
			i++;
		}

		if (strcmp(args[0], "dir") == 0)
		{
			// CreateThread() function and arguments adapted from ch4 PowerPoint slides
			ThreadHandle = CreateThread(
				NULL,		// Security attributes
				0,			// Stack size
				sysDir,		// Thread function
				NULL,		// Parameter to thread function
				0,			// Creation flags
				&ThreadID); // Thread identifier
			if (ThreadHandle != NULL)
			{
				WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
				CloseHandle(ThreadHandle);
			}
		}
		else if (strcmp(args[0], "help") == 0)
		{
			// CreateThread() function and arguments adapted from ch4 PowerPoint slides
			ThreadHandle = CreateThread(
				NULL,		// Security attributes
				0,			// Stack size
				sysHelp,	// Thread function
				NULL,		// Parameter to thread function
				0,			// Creation flags
				&ThreadID); // Thread identifier
			if (ThreadHandle != NULL)
			{
				WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
				CloseHandle(ThreadHandle);
			}
		}
		else if (strcmp(args[0], "vol") == 0)
		{
			// CreateThread() function and arguments adapted from ch4 PowerPoint slides
			ThreadHandle = CreateThread(
				NULL,		// Security attributes
				0,			// Stack size
				sysVol,		// Thread function
				NULL,		// Parameter to thread function
				0,			// Creation flags
				&ThreadID); // Thread identifier
			if (ThreadHandle != NULL)
			{
				WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
				CloseHandle(ThreadHandle);
			}
		}
		else if (strcmp(args[0], "path") == 0)
		{
			// CreateThread() function and arguments adapted from ch4 PowerPoint slides
			ThreadHandle = CreateThread(
				NULL,		// Security attributes
				0,			// Stack size
				sysPath,	// Thread function
				NULL,		// Parameter to thread function
				0,			// Creation flags
				&ThreadID); // Thread identifier
			if (ThreadHandle != NULL)
			{
				WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
				CloseHandle(ThreadHandle);
			}
		}
		else if (strcmp(args[0], "tasklist") == 0)
		{
			// CreateThread() function and arguments adapted from ch4 PowerPoint slides
			ThreadHandle = CreateThread(
				NULL,		 // Security attributes
				0,			 // Stack size
				sysTaskList, // Thread function
				NULL,		 // Parameter to thread function
				0,			 // Creation flags
				&ThreadID);	 // Thread identifier
			if (ThreadHandle != NULL)
			{
				WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
				CloseHandle(ThreadHandle);
			}
		}
		else if (strcmp(args[0], "notepad") == 0)
		{
			// CreateThread() function and arguments adapted from ch4 PowerPoint slides
			ThreadHandle = CreateThread(
				NULL,		// Security attributes
				0,			// Stack size
				sysNotepad, // Thread function
				NULL,		// Parameter to thread function
				0,			// Creation flags
				&ThreadID); // Thread identifier
			if (ThreadHandle != NULL)
			{
				WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
				CloseHandle(ThreadHandle);
			}
		}
		else if (strcmp(args[0], "echo") == 0)
		{
			// CreateThread() function and arguments adapted from ch4 PowerPoint slides
			ThreadHandle = CreateThread(
				NULL,		// Security attributes
				0,			// Stack size
				sysEcho,	// Thread function
				NULL,		// Parameter to thread function
				0,			// Creation flags
				&ThreadID); // Thread identifier
			if (ThreadHandle != NULL)
			{
				WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
				CloseHandle(ThreadHandle);
			}
		}
		else if (strcmp(args[0], "color") == 0) // change text color
		{
			// CreateThread() function and arguments adapted from ch4 PowerPoint slides
			ThreadHandle = CreateThread(
				NULL,		// Security attributes
				0,			// Stack size
				sysColor,	// Thread function
				NULL,		// Parameter to thread function
				0,			// Creation flags
				&ThreadID); // Thread identifier
			if (ThreadHandle != NULL)
			{
				WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
				CloseHandle(ThreadHandle);
			}
		}
		else if (strcmp(args[0], "ping") == 0)
		{
			// CreateThread() function and arguments adapted from ch4 PowerPoint slides
			ThreadHandle = CreateThread(
				NULL,		// Security attributes
				0,			// Stack size
				sysPing,	// Thread function
				NULL,	// Parameter to thread function
				0,			// Creation flags
				&ThreadID); // Thread identifier
			if (ThreadHandle != NULL)
			{
				WaitForSingleObject(ThreadHandle, INFINITE); // Wait for thread to finish
				CloseHandle(ThreadHandle);
			}
		}
		else if (strcmp(args[0], "exit") == 0)
		{
			break; // exit the program when the user enters "exit"
		}
		else
		{
			printf("Command not found. Please try again.\n");
		}
	}

	return EXIT_SUCCESS;
}

DWORD WINAPI sysDir(LPVOID Parameter)
{
	system("dir");
	return 0;
}
DWORD WINAPI sysHelp(LPVOID Parameter)
{
	char command[100];
	strcpy(command, "help ");
	strcat(command, args[1]);
	system(command);
	return 0;
}
DWORD WINAPI sysVol(LPVOID Parameter)
{
	system(input);
	return 0;
}
DWORD WINAPI sysPath(LPVOID Parameter)
{
	system("path");
	return 0;
}
DWORD WINAPI sysTaskList(LPVOID Parameter)
{
	system("tasklist");
	return 0;
}
DWORD WINAPI sysNotepad(LPVOID Parameter)
{
	system("notepad");
	return 0;
}
DWORD WINAPI sysEcho(LPVOID Parameter)
{
	char command[100];
	strcpy(command, "echo ");
	strcat(command, args[1]);
	strcat(command, " ");
	strcat(command, args[2]);
	strcat(command, " ");
	strcat(command, args[3]);
	system(command);
	return 0;
}
DWORD WINAPI sysColor(LPVOID Parameter)
{
	int color = atoi(args[1]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return 0;
}
DWORD WINAPI sysPing(LPVOID Parameter)
{
	char command[100];
	strcpy(command, "ping ");
	// use strcat() to concatenate the user input into the new string
	strcat(command, args[1]);
	strcat(command, " -n 4");
	// execute the command
	system(command);
	return 0;
}