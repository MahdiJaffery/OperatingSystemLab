#include "../Header.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <Pipe Name>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);

    if (fd == -1)
    {
        perror("Failed to Open Pipe\n");
        return 2;
    }

    int n, *Arr;

    if (read(fd, &n, sizeof(int)) == -1)
    {
        perror("Failed to Read from Pipe\n");
        return 3;
    }

    Arr = (int *)malloc(sizeof(int) * n);
    if (read(fd, Arr, sizeof(int) * n) == -1)
    {
        perror("Failed to Read from Pipe\n");
        return 3;
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += Arr[i];

    printf("Sum of Array: %d\n", sum);

    write(fd, &sum, sizeof(int));

    return 0;
}