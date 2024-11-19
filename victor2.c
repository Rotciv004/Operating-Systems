#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 256


int main(int argc, char *argv[])
{
	// pd[0] READ	pd[1] WRITE
	int pd[2];	// {12345, 		14789}
	if (pipe(pd) == -1)
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}
	
	int pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	
	// in copil
	if (pid == 0)
	{
		close(pd[1]); 		// inchid descriptorul de scriere
		
		int N = 0;
		read(pd[0], &N, sizeof(int));
		char fisier[MAX_SIZE];
		read(pd[0], fisier, MAX_SIZE);
		
		printf("N: %d\n", n);
		printf("Fisier: %s\n", fisier);
		
		char cuvant[MAX_SIZE];
		while(read(pd[0], cuvant, MAX_SIZE) > 0)
		{
			printf("Cuvant: %s\n", cuvant);
		}
		
		close(pd[0]);		// inchid descriptorul de citire
		exit(0);
	}
	
	// in parinte
	close(pd[0]);		// inchid descriptorul de citire
	
	// citesc valoarea lui N
	int N = 0;
	printf("N: ");
	scanf("%d", &N);
	write(pd[1], &N, sizeof(int));
	
	getchar();
	
	// citesc numele fisierului
	char fisier[MAX_SIZE];
	printf("Fisier: ");
	scanf("%s", fisier);
	write(pd[1], fisier, MAX_SIZE);
	
	// deschid fisierul
	FILE* fd = fopen(fisier, "r");
	if (fd == NULL)
	{
		perror("fopen()");
		exit(EXIT_FAILURE);
	}
	
	// citesc fisierul
	char cuvant[MAX_SIZE];
	while(fscanf(fd, "%s", cuvant) > 0)
		write(pd[1], cuvant, MAX_SIZE);
	
	close(pd[1]); 		// inchid descriptorul de scriere
	fclose(fd);
	wait(NULL);

	return 0;
}
