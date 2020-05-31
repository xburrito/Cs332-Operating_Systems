// ALbert Chang
//Csc 33200 - S

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	int pid_1, pid_2;

	// Child 1 created
	pid_1 = fork();

	if(pid_1 == 0) {

		// Child 1 Process
		printf("Child 1\n");
		char *const argv[] = {"Process_P1", NULL};

		execv(argv[0], argv);
		printf("EXECV Failed! Did you compile Prcs_P1.c yet? \n");

	}
	else {
		// 1 second wait time before processing second child
		sleep(1);
		pid_2 = fork();

		if (pid_2 == 0) {

			// Child 2 Process
			printf("Child 2\n");
			char *const argv[] = {"Process_P2", NULL};

			execv(argv[0], argv);
			printf("EXECV Failed! Did you compile Process_P2.c yet? \n");
		}
	}
	return 0;

}
