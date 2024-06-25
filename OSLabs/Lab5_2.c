#include "Header.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int fd[2];
    pipe(fd);

    int pid = fork();

    if (pid)
    {
        int n, *Arr;
        n = rand() % 50;

        Arr = (int *)malloc(sizeof(int) * n);

        for (int i = 0; i < n; i++)
            Arr[i] = rand() % 101;

        printf("Array of size : %d\n", n);
        printf("Array: \n");

        for (int i = 0; i < n; i++)
            printf("%d\t", Arr[i]);

        write(fd[1], &n, sizeof(int));
        write(fd[1], Arr, sizeof(int) * n);

        wait(NULL);

        int sum;
        read(fd[0], &sum, sizeof(int));

        printf("\n\nSum of Array: %d\n", sum);
    }
    else
    {
        int n, *Arr;

        read(fd[0], &n, sizeof(int));
        read(fd[0], Arr, sizeof(int) * n);

        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += Arr[i];

        write(fd[1], &sum, sizeof(int));
    }
}