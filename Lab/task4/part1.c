// Albert Chang
// Csc 33200 - S

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char* argv[]) {
  int pid, status;
  char size[256];
	char *ar[64] = {NULL};
	char *token;

	printf ("Enter a command line ['quit' to terminate]: ");
	scanf(" %[^\n]s", size);

  // Program terminates if user types 'quit'
	while (strcmp(size,"quit")) {
		token = strtok(size," ");
		int i = 0;

		while(token != NULL) {
      // arguments stored in an array
	    ar[i]= token;
	    token = strtok(NULL," ");
	    i++;
    }

    // Child process created
		pid = fork();
		wait(&status);

		if (pid == 0) {
	  	execvp (ar[0],ar);
	  	printf ("EXECVP was unsuccessful\n");
    }

    int j;
		for (j=0; j < i; ++j){
      // Clears the array
      ar[j] = NULL;
    }

		i = 0;
		printf ("Enter a command line ['quit' to terminate]: ");
		scanf(" %[^\n]s", size);
	}

	return 0;
}
