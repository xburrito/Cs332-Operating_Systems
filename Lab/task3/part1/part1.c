// ALbert Chang
//Csc 33200 - S

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	int status, pid_1;

	// Child 1 created
	pid_1 = fork();
	wait(&status);

	if(pid_1 != 0) {
		printf("I am the parent, my PID is: %d\n", getpid());
	}

	else {

		// This prints if pid_1 = 0 and will result in creation of another child
		printf("I am child one, my PID is: %d\n", getpid());
		
		execl("/bin/date", "date", NULL);
		printf("EXECL Failed\n");
	}

	return 0;
}
