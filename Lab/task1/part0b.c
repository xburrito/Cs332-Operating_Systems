// Albert Chang
// Csc 33200 - S

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char* argv[])
{
  char* filepath = argv[1];
  int fd;

    // Creates the new file and sets it to read/write mode
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    fd = open(filepath, O_RDWR|O_CREAT, "rw");
    printf("\nThe file has been successfully created and opened...\n");

  close(fd);
  return 0;
}
