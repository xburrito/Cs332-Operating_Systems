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
	int fd_1, fd_2;
	errno = 0;

	// Opens and creates "destination1.txt" with read-write permissions
	fd_1 = open("destination1.txt", O_CREAT | O_RDWR, S_IRWXU);

	if (fd_1 == -1) {
		printf("Failed to open with error [%s]\n", strerror(errno));
	}
	else {
		printf("Destination 1: Opened\n");
	}
	close(fd_1);

	// Opens and creates "destination2.txt" with read-write permissions
	fd_2 = open("destination2.txt", O_CREAT | O_RDWR, S_IRWXU);

	if (fd_2 == -1) {
		printf("\n Failed to open with error [%s]\n", strerror(errno));
	}
	else {
		printf("Destination 2: Opened\n");
	}
	close(fd_2);

return 0;
}
