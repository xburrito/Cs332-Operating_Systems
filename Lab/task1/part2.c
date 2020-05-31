// Albert Chang
// Csc 33200 - S

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int file1, file2;
    char buffer[1024];
    long int n1;

    // Prints an error if the file does not open properly...
    if(((file1 = open(argv[1], O_RDONLY)) == -1) || ((file2=open(argv[2],O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1)){
        perror("There is an issue opening the file...");
        exit(1);
    }

    // Appends to the new file what is stored in the buffer until the EOF (End of file)
    while ( (n1 = read(file1, buffer, 1024)) > 0){
        if(write(file2, buffer, n1) != n1){
            perror("There is an issue writing to the new file...");
            exit(3);
        }
    }

    // Closes out both files that were in use
    close(file1);
    close(file2);
}
