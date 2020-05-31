// Albert Chang
// Csc 33200 - S

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
  // x = num of chapters
  // y = num of homeworks
  int x, y;
  double average;
  int row_count, col_count, manager_counter, p_count, status;
  printf("Enter the number of chapters: ");
  scanf("%d", &x);
  printf("Enter the number of Homeworks per chapter: ");
  scanf("%d", &y);
  const int num_rows = 10;
  const int num_col = x*y;

  // 2D-Array to store grades
  double grades [num_col][num_rows];
  // Array to store HW averages
  double averages [num_col];

  // Opens target file with read-only format
  FILE *source = fopen("quiz_grades.txt", "r");

  // Obtains 2D-array values from targeted source file
  while (row_count < num_rows) {
    while (col_count < num_col) {
      fscanf(source, "%lf", &grades[col_count][row_count]);
      col_count++;
    }
      col_count =0;
      row_count++;
  }

  row_count = 0;
  col_count = 0;

  while(manager_counter < x) {
    wait(&status);
    pid_t manager_pid = fork();
    if(manager_pid == 0) {
      col_count = y * manager_counter;
      while(p_count < y) {
        wait(&status);
        pid_t worker_pid= fork();
        if(worker_pid == 0){
          while(row_count < num_rows){
            // All values in column gets added up
            average += grades[col_count][row_count];
            row_count++;
          }

          // Calculates average and stores it into the array
          averages[col_count] = average / num_rows;

          // Print average grade of each HW assignment
          printf("Average Homework Grade #%d: %f \n",(col_count + 1), averages[col_count]);
          exit(0);
        }

        // Fork error check
        else if (worker_pid < 0) {
          perror("Fork Error");
        }
        else {
          // Parent waits for child process to terminate first
          if(wait(&status) == -1){
            printf("Error\n");
          }
        }
        // Reset Counter
        row_count = 0;
        col_count++;
        p_count++;
      }
      exit(0);
    }

    // Fork error check
    else if(manager_pid < 0){
      perror("Fork Error");
      return 1;
    }

      // Parent waits for child process to terminate first
      else {
      if(wait(&status) == -1) {
        printf("Error\n");
      }
    }
    p_count = 0;
    manager_counter++;
  }
  fclose(source);
  return 0;
}
