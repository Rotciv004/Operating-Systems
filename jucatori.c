//program A

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    if (mkfifo("fifoAC", 0666) == -1)
    {
        perror("fifoAC");
        exit(1);
    }

    int fifoAC = open("fifoAC", O_WRONLY);

    if (fifoAC == -1)
    {
        perror("open fifoAC");
        exit(1);
    }

    for (int i = 0; i < 5; ++i)
    {
        srand(time(NULL));

        for (int j = 0; j < 6; ++j)
        {
            int a = rand() % 49;

            write(fifoAC, &a, sizeof(int));
        }
    }


    close(fifoAC);


    int fifoCA = open("fifoAC", O_RDONLY);

    if (fifoCA == -1)
    {
        perror("open fiofCA");
        exit(1);
    }

    for (int i = 0; i < 30; ++i)
    {
        int a;
        read(fifoCA, &a, sizeof(int));

        if (a != -1)
            printf("%d/n", a);
    }

    close(fifoCA);

    unlink("fifoCA");

    return 0;

}

// program B


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    if (mkfifo("fifoBC", 0666) == -1)
    {
        perror("fifoBC");
        exit(1);
    }

    int fifoBC = open("fifoBC", O_WRONLY);

    if (fifoBC == -1)
    {
        perror("open fifoBC");
        exit(1);
    }

    for (int i = 0; i < 5; ++i)
    {
        srand(time(NULL));

        for (int j = 0; j < 6; ++j)
        {
            int b = rand() % 49;

            write(fifoBC, &b, sizeof(int));
        }
    }

    close(fifoBC);


    int fifoCB = open("fifoBC", O_RDONLY);

    if (fifoCB == -1)
    {
        perror("open fiofCB");
        exit(1);
    }

    for (int i = 0; i < 30; ++i)
    {
        int b;
        read(fifoCB, &b, sizeof(int));

        if (b != -1)
            printf("%d/n", b);
    }

    close(fifoCB);

    unlink("fifoBC");

    return 0;

}




//Program C


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int random[6], send[30];

    for (int i = 0; i < 6; ++i)
        random[i] = rand() % 49;

    int fifoAC = open("fifoAC", O_RDONLY);

    if (fifoAC == -1)
    {
        perror("open fifoAC");
        exit(1);
    }

    for (int i = 0; i < 30; ++i)
    {
        int c;
        read(fifoAC, &c, sizeof(int));

        for (int j = 0; j < 6; ++j)
            if (c == random[j])
                send[i] = c;
            else
                send[i] = -1;
    }

    close(fifoAC);

    int fifoCA = open("fifoAC", O_WRONLY);

    if (fifoCA == -1)
    {
        perror("open fifoCA");
        exit(1);
    }

    for (int i = 0; i < 30; ++i)
        write(fifoCA, &send[i], sizeof(int));

    close(fifoCA);

    //B


    for (int i = 0; i < 6; ++i)
        random[i] = rand() % 49;

    int fifoBC = open("fifoBC", O_RDONLY);

    if (fifoBC == -1)
    {
        perror("open fifoBC");
        exit(1);
    }

    for (int i = 0; i < 30; ++i)
    {
        int c;
        read(fifoBC, &c, sizeof(int));

        for (int j = 0; j < 6; ++j)
            if (c == random[j])
                send[i] = c;
            else
                send[i] = -1;
    }

    close(fifoBC);

    int fifoCB = open("fifoBC", O_WRONLY);

    if (fifoCB == -1)
    {
        perror("open fifoCB");
        exit(1);
    }

    for (int i = 0; i < 30; ++i)
        write(fifoCB, &send[i], sizeof(int));

    close(fifoCB);
    return 0;
}