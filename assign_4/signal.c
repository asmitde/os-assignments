/* Assignment 4 - Question 1
 * File: signal.c
 * Description: Implementation of SIGALRM and SIGCHLD
 * Author: Asmit De 10/CSE/53
 * Date: 28-Mar-2013
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

// Signal handler for SIGALRM
void catch_SIGALRM(int sig_num)
{
	printf("Child received signal: %d\n", sig_num);
	exit(0);
}

// Signal handler for SIGCHLD
void catch_SIGCHLD(int sig_num)
{
	printf("Parent received signal: %d\n", sig_num);
	exit(0);
}

int main()
{
	pid_t pid;
	
	// Initialize handler for SIGCHLD
	signal(SIGCHLD, catch_SIGCHLD);
	
	pid = fork();
	if(pid == 0)		// Code executed by child process
	{
		// Initialize handler for SIGALRM
		signal(SIGALRM, catch_SIGALRM);
		
		// Loop indefinitely
		while(1)
		{
			printf("Child waiting...\n");
		}
	}
	else if(pid == -1)
	{
		// Error handling for fork errors
		perror("Error");
	}
	else			// Code executed by parent process
 	{
	 	// Sleep for 1 second
	 	sleep(1);
	 	
	 	// Send SIGALRM to child
	 	kill(pid, SIGALRM);
	 	
	 	// Loop indefinitely
	 	while(1)
	 	{
	 		printf("Parent waiting...\n");
	 	}
 	}
 	
 	return 0;
}
