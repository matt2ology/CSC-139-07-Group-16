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
#include <typeinfo>

using namespace std;
DWORD WINAPI Execute(LPVOID Param)
{
	//	char* args = static_cast<char*>(Param);
	//	char* arg = (char*)Param;
	//	cout << typeid(arg).name();
	cout << *(char *)Param;
	return 0;
}
int main(int argc, char const *argv[])
{
	// Create an infinite loop

	while (TRUE)
	{
		// use fgets() to read a line of input from the user
		char input[100];
		printf("myShell> ");
		fgets(input, 100, stdin);

		// use strtok() to parse the user input into its arguments
		char *token = strtok(input, " \n");
		char *args[4];
		int i = 0;
		while (token != NULL)
		{
			args[i] = token;
			token = strtok(NULL, " \n");
			i++;
		}
		DWORD ThreadId;
		HANDLE ThreadHandle;
		ThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Execute, args, 0, &ThreadId);
		WaitForSingleObject(ThreadHandle, INFINITE);
		CloseHandle(ThreadHandle);

		//		std::cout << "USER ARGS ARE " << args[0];
		// compare the user input against the list of supported commands
		// execute the command entered by the user
		// exit the program when the user enters "exit"
		if (strcmp(args[0], "dir") == 0)
		{
			system("dir");
		}
		else if (strcmp(args[0], "help") == 0)
		{
			system("help");
		}
		else if (strcmp(args[0], "vol") == 0)
		{
			system("vol");
		}
		else if (strcmp(args[0], "path") == 0)
		{
			system("path");
		}
		else if (strcmp(args[0], "tasklist") == 0)
		{
			system("tasklist");
		}
		else if (strcmp(args[0], "notepad") == 0)
		{
			system("notepad");
		}
		else if (strcmp(args[0], "echo") == 0)
		{
			printf("%s %s %s %s", args[1], args[2], args[3], args[4]);
		}
		else if (strcmp(args[0], "color") == 0) // change text color
		{
			// convert string to int
			int color = atoi(args[1]);
			// change text color
			// 0 = black
			// 1 = blue
			// 2 = green
			// 3 = cyan
			// 4 = red
			// 5 = purple
			// 6 = yellow
			// 7 = white
			// 8 = gray
			// 9 = light blue
			// 10 = light green
			// 11 = light cyan
			// 12 = light red
			// 13 = light purple
			// 14 = light yellow
			// 15 = bright white
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		}
		else if (strcmp(args[0], "ping") == 0)
		{
			// use strcpy() to copy the user input into a new string
			char command[100];
			strcpy(command, "ping ");
			// use strcat() to concatenate the user input into the new string
			strcat(command, args[1]);
			strcat(command, " -n 4");
			// execute the command
			system(command);
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
