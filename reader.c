#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_SIZE 500


int main(int argc, char *argv[])
{
	printf("Inainte de open()...\n");

	// deschid sau creez FIFO
	int pd = open("fifo2", O_RDONLY);
	if (pd < 0)
	{
		perror("open()");
		exit(1);
	}

	printf("Dupa open()...\n");

	// scriu in FIFO
	char mesaj[MAX_SIZE];
	read(pd, mesaj, MAX_SIZE);
	printf("Mesaj: %s\n", mesaj);

	// inchid FIFO
	close(pd);

	return 0;
}
