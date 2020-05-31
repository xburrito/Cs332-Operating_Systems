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
	int src, rd, acs, destination1, destination2;

	src = open("source.txt", O_RDONLY);

	destination1 = open("destination1.txt", O_CREAT | O_RDWR, S_IRWXU);
	destination2 = open("destination2.txt", O_CREAT | O_RDWR, S_IRWXU);

	if (src == -1 && destination1 == -1 && destination2 == -1)
	{
		printf("Error: [%s]\n", strerror(errno));
	}
	else{

		// Array of index size 101 allows it to read through 100 characters
		char buffer[101];
		int n = 101;

		while ( (rd = read(src, buffer, n)) > 0){

			if (n == 101) {

				for (int i = 0; i < sizeof(buffer); i++){
					// Checks first 100 characters. If a '1' is found, it will be replaced with an 'A' in destination1.txt
					if (buffer[i] == '1')
						buffer[i] = 'A';

				}

				write(destination1, buffer, rd);
				n = 51;
			}
			else{
				for (int i = 0; i < sizeof(buffer); i++){
					if (buffer[i] == '2')
						buffer[i] = 'B';
				}

				write(destination2, buffer, rd);
				n = 101;
			}
		}
	}

	close(src);
	close(destination1);
	close(destination2);

	return 0;
}
