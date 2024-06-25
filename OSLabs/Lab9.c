#include "Header.h"

int x = 1, in = 0, nums[100];
sem_t s1;

void *addVals(void *n)
{
    sem_wait(&s1);
    int ind = in;
    ind += 10;
    for (int i = in; i < ind; i++)
        nums[i] = x;
    printf("X Value for this: %d\n", x);
    in += 10;
    x++;
    sem_post(&s1);
}

int main(int argc, char *argv[])
{
    sem_init(&s1, 0, 1);
    pthread_t Threads[10];

    for (int i = 0; i < 10; i++)
        pthread_create(&Threads[i], NULL, addVals, (void *)&x);

    for (int i = 0; i < 10; i++)
        pthread_join(Threads[i], NULL);

    int sum = 0;
    for (int i = 0; i < 100; i++)
    {
        printf("%d\t", nums[i]);
        sum += nums[i];
    }
    printf("\n\nSum is: %d\n\n", sum);

    sem_destroy(&s1);
}