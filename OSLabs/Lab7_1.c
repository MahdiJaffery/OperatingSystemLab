#include "Header.h"

void *func(void *param)
{
    printf("Thread ID : %lu\nProcess ID : %u\n\n", pthread_self(), getpid());
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <Number of Threads>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    pthread_t *Threads;

    Threads = (pthread_t *)malloc(sizeof(pthread_t) * atoi(argv[1]));

    for (int i = 0; i < n; i++)
        pthread_create(&Threads[i], NULL, func, NULL);

    for (int i = 0; i < n; i++)
        pthread_join(Threads[i], NULL);

    return 0;
}