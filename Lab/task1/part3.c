// Albert Chang
// Csc 33200 - S

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int file1, file2;
    int counter = 0;
    char buffer[1024];
    int n1;

    // Prints an error if the file fails to open
    if(((file1 = open(argv[1], O_RDONLY)) == -1) || ((file2=open(argv[2],O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1)){
        perror("There is an error opening the file...");
        exit(1);
    }

    while ( (n1 = read(file1, buffer, 1024)) > 0){

        //Whenever the counter reaches 100 (100 # are printed, XYZ will be appended)
        // Counter will then be reset to work with the next 100 values.
        if(counter == 100){
          printf("XYZ");
          counter = 0;
        }

        // Everytime the new file has a 1 that's meant to be printed, an "A" will take its place.
        while(n1 == 1){
          printf("A");
          counter = 0;
        }

        // Printed if there is an error writing to the file.
        if(write(file2, buffer, n1) != n1){
            perror("There is an error writing to the file...");
            exit(3);
        }
        // Counter will increment once the buffer is completed one cycle.
        counter++;
    }

    // Closes both of the existing files
    close(file1);
    close(file2);
}
