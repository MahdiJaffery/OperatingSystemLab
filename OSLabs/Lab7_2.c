#include "Header.h"

void *Sum(void *i)
{
    int *n = (int *)i;
    int *result = malloc(sizeof(int));

    *result = (*n) - 1;

    pthread_exit(result);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <Number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]), *result = malloc(sizeof(int) * n);
    pthread_t *Threads = (pthread_t *)malloc(sizeof(pthread_t) * n);

    int *Vals = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        Vals[i] = n - i + 1;
        pthread_create(&Threads[i], NULL, Sum, &Vals[i]);
    }

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int *res_ptr;
        pthread_join(Threads[i], (void **)&res_ptr);
        sum += *res_ptr;
        free(res_ptr);
    }
    printf("Summation: %d\n", sum);
    return 0;
}