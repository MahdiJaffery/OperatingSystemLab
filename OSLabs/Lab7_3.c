#include "Header.h"

int globalLen, *globalVals;

void *fibThread(void *param)
{
    int n = *(int *)param;

    int *Arr = malloc(sizeof(int) * n);
    if (n == 0)
        pthread_exit(NULL);
    if (n == 1)
    {
        Arr[0] = 0;
        pthread_exit(Arr);
    }
    if (n == 2)
    {
        Arr[0] = 0, Arr[1] = 1;
        pthread_exit(Arr);
    }
    else
    {
        Arr[0] = 0, Arr[1] = 1;
        for (int i = 2; i < n; i++)
            Arr[i] = Arr[i - 1] + Arr[i - 2];

        pthread_exit(Arr);
    }
}

void *countEven(void *param)
{
    int count = 0;
    int n = *(int *)param;

    for (int i = 0; i < n; i++)
        if (!(globalVals[i] & 1))
            count++;

    int *res = malloc(sizeof(int));
    *res = count;
    pthread_exit(res);
}

void *countOdd(void *param)
{
    int count = 0;
    int n = *(int *)param;

    for (int i = 0; i < n; i++)
        if (globalVals[i] & 1)
            count++;

    int *res = malloc(sizeof(int));
    *res = count;
    pthread_exit(res);
}

void *SumFib(void *param)
{
    int n = *(int *)param;

    int Sum = 0;
    for (int i = 0; i < n; i++)
        Sum += globalVals[i];

    int *res = malloc(sizeof(int));
    *res = Sum;
    pthread_exit(res);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <n Terms>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]), *Even, *Odd, *Sum;
    globalLen = n;

    pthread_t Threads[4];
    int *Vals = malloc(sizeof(int) * n);

    pthread_create(&Threads[0], NULL, fibThread, (void **)&n);
    pthread_join(Threads[0], (void **)&Vals);

    globalVals = Vals;

    pthread_create(&Threads[1], NULL, countEven, (void **)&n);
    pthread_join(Threads[1], (void **)&Even);

    pthread_create(&Threads[2], NULL, countOdd, (void **)&n);
    pthread_join(Threads[2], (void **)&Odd);

    pthread_create(&Threads[4], NULL, SumFib, (void **)&n);
    pthread_join(Threads[4], (void **)&Sum);

    printf("Series: ");
    for (int i = 0; i < n; i++)
        printf("%d\t", Vals[i]);

    printf("\nEven: %d", *Even);
    printf("\nOdd: %d", *Odd);
    printf("\nSummation: %d\n", *Sum);
}
