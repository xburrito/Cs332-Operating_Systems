#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(){
  int pipefd[2];
  pid_t pid1, pid2;

  // Create the pipe
  pipe(pipefd);

  // Fork first child (Process ID)
  pid1 = fork();

  if(pid1 == 0){
    // Child 1
    close(pipefd[0]);
    dup2(pipefd[1],1); // Redirects stdout to pipe
    execlp("ls", "ls", "-F", (char*)NULL); // Executes

  }

  // Fork second child (Process ID 2)
  pid2 = fork();

  if(pid2 == 0){
    // Child 2
    close(pipefd[1]);
    dup2(pipefd[0],0); // Redirect stdout to pipe
    execlp("nl", "nl",(char*)NULL); // Executes

  }

  // Parent processes (Closes both ends of the Parent)
  close(pipefd[0]);
  close(pipefd[1]);

  // Wait for the two children to end (Prevents zombies)
  wait(NULL);
  wait(NULL);

  // Message to mark end of parent process
  printf("The Parent process has ended successfully!\n");

  return 0;
}
