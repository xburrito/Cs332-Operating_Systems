// Albert Chang
// Csc 33200 - S

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int status, pid1, pid2;
	// Creates the first child
	pid1 = fork();
	wait(&status);

	if(pid1 != 0){
		printf("I am the parent, my PID is: %d \n", getpid());
	}

	else{
		printf("I am child one, my PID is: %d \n", getpid());
		// Creates the second child
		pid2 = fork();
		wait(&status);

		if (pid2 == 0){
		printf("I am child two, my PID is: %d \n", getpid());
		}
	}

	return 0;
}
