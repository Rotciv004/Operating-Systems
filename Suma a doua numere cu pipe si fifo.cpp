#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int pp[2]; // Canal de comunicare (0: citire, 1: scriere)

    if (pipe(pp) == -1) {
        perror("pipe()");
        exit(1);
    }

    int pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
        // Procesul copil
        close(pp[0]); // Închidem canalul de citire

        int a = atoi(argv[1]), b = atoi(argv[2]);

        write(pp[1], &a, sizeof(int));
        write(pp[1], &b, sizeof(int));

        printf("Am citit ambele numere: a = %d, b = %d\n", a, b);

        close(pp[1]);
        exit(0);
    }
    else {
        // Procesul părinte
        close(pp[1]); // Închidem canalul de scriere

        int a = 0, b = 0; // Exemplu: a și b sunt numerele pe care le trimitem

        read(pp[0], &a, sizeof(int));
        read(pp[0], &b, sizeof(int));

        printf("Am preluat a = %d și b = %d\n", a, b);

        if (mkfifo("fifo", 0666) == -1)
        {
            perror("fifo");
            exit(1);
        }
        else
        {
            int fif = open("fifo", O_WRONLY);

            if (fif == -1)
            {
                perror("fif");
                exit(1);
            }
            else
            {
                printf("Am intrat in fifo\n");

                write(fif, &a, sizeof(int));
                write(fif, &b, sizeof(int));

                close(fif);
                unlink("fifo");

            }
        }

        close(pp[0]);
        wait(NULL); // Așteptăm copilul să termine
    }

    return 0;
}








#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
    int fif = open("fifo", O_RDONLY);

    if (fif == -1)
    {
        perror("fif\n");
        exit(1);
    }
    else
    {
        int a, b;

        read(fif, &a, sizeof(int));
        read(fif, &b, sizeof(int));

        printf("SUMA a+b = %d\n", a + b);

        close(fif);
    }

    printf("executat ok!\n");

    return 0;
}