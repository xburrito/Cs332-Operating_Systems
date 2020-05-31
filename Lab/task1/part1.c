// Albert Chang
// Csc 33200 - S

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <string.h>
#include <errno.h>
//#include <stdlib.h>

int main(int argc, char *argv[]) {
  // file descriptor
  int file, size;
  int returnval;

  // file
  char *filename = argv[1];

  // Checks to see if the file exists and could be accessed.
  returnval = access (filename, F_OK);
  if (returnval == 0)
    printf ("\nThe file %s exists.\n", filename);
  else {
    if (errno == ENOENT)
      printf ("%s does not exist.\n", filename);
    else if (errno == EACCES)
      printf ("%s is not accessible.\n", filename);
      return 0;
  }

  // open file
  file = open(filename, O_RDONLY);

  errno = 0;

  // Checks to see if the file has read permissions. Else, it will state otherwise.
  if(-1 == file) {
    printf("\nThe file doesn't have read permission. [%s]\n",strerror(errno));
    return 1;
  }
  else {
     printf("\nThe file opened successfully!\n");
  }

  // The file will be read and displayed right onto the terminal
  char *content[1024];
  size = read(file,content, sizeof(content)-1);


  write(1, content, size);
  printf("\n");

  // close file
  close(file);
  return 0;

}
