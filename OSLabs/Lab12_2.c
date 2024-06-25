#include "Header.h"

int size;

void *ThreadFunc(void *param)
{
    char *Arr = (char *)param;

    char *new = (char *)malloc(size * sizeof(char)); // Dynamically allocate memory for the new array

    printf("Original Contents of file: \n\n");
    for (int i = 0; i < size; i++)
    {
        printf("%c", Arr[i]);
    }

    printf("\n\n");

    for (int i = 0; i <= size; i++)
    {
        if (Arr[i] >= '0' && Arr[i] <= '9')
            new[i] = ' ';
        else
            new[i] = Arr[i];
    }

    pthread_exit(new);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s filename.txt\n", argv[0]);
        return 0;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1)
    {
        return -1;
    }

    char *map = (char *)mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
    {
        return -2;
    }

    size = 0;
    for (int i = 0; map[i] != '\0'; i++)
    {
        size++;
    }

    size /= 2;

    pthread_t T[2];

    pthread_create(&T[0], NULL, ThreadFunc, (void *)map);
    pthread_create(&T[1], NULL, ThreadFunc, (void *)(map + size));

    char *updated1;
    char *updated2;
    pthread_join(T[0], (void **)&updated1);
    pthread_join(T[1], (void **)&updated2);

    printf("Updated:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%c", updated1[i]);
    }
    for (int i = 0; i < size; i++)
    {
        printf("%c", updated2[i]);
    }

    int k = 0, l = 0;
    for (int i = 0; i <= size * 2; i++)
    {
        if (i <= size)
        {
            map[i] = updated1[k];
            k++;
        }
        else
        {
            map[i] = updated2[l];
            l++;
        }
    }

    free(updated2);
    free(updated1);

    return 0;
}