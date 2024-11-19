#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_SIZE 200


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
		
		int n = 0;
		read(pd[0], &n, sizeof(int));
		printf("Am citit %n\n", n);
		
		char ch = '\0';
		read(pd[0], &ch, sizeof(char));
		printf("Am citit %c\n", n);
		
		char mesaj[MAX_SIZE];
		read(pd[0], mesaj, MAX_SIZE);
		printf("Am citit %s\n", mesaj);
		
		close(pd[0]);		// inchid descriptorul de citire
		exit(0);
	}
	
	// in parinte
	close(pd[0]);		// inchid descriptorul de citire
	
	int n = 10;
	write(pd[1], &n, sizeof(int));
	
	char ch = '\0';
	write(pd[1], &ch, sizeof(char));
	
	char mesaj[] = "Salut din pipe !";
	write(pd[1], mesaj, MAX_SIZE);
	
	close(pd[1]); 		// inchid descriptorul de scriere
	wait(NULL);

	return 0;
}
