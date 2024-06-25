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

    srand(time(NULL));

    int n = rand() % 50 + 1;
    int *Arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        Arr[i] = rand() % 100 + 1;

    if (write(fd, &n, sizeof(int)) == -1)
    {
        perror("Failed to Write to Pipe\n");
        return 3;
    }
    else
    {
        printf("Size Sent: %d\n", n);
    }
    if (write(fd, Arr, sizeof(int) * n) == -1)
    {
        perror("Failed to Write to Pipe\n");
        return 4;
    }
    sleep(1);

    printf("Array Sent: ");
    for (int i = 0; i < n; i++)
        printf("%d\t", Arr[i]);
    printf("\n\n");

    int sum;
    read(fd, &sum, sizeof(int));

    printf("Size Recieved: %d\n", sum);

    return 0;
}