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
	// creez un FIFO
	char cale[100];
	printf("FIFO: ");
	scanf("%s", cale);
	if (mkfifo(cale, 0666) == -1)
	{
		perror("mkfifo()");
		exit(1);
	}

	printf("Inainte de open()...\n");

	// deschid sau creez FIFO
	int pd = open(cale, O_WRONLY);
	if (pd < 0)
	{
		perror("open()");
		exit(1);
	}

	printf("Dupa open()...\n");

	// scriu in FIFO
	char mesaj[] = "Salut din FIFO !";
	write(pd, mesaj, MAX_SIZE);

	// inchid FIFO
	close(pd);

	unlink(cale);

	return 0;
}
