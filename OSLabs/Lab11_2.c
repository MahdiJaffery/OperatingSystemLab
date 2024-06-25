#include "Header.h"

int main()
{
    int shmid = shmget((key_t)1, 4096, 0666);

    char *ptr = shmat(shmid, NULL, 0);

    int Arr[100], index = 0;

    printf("Array Recieved: %s\n", ptr);
    for (int i = 0; ptr[i] != '\0'; i++)
        if (ptr[i] != ' ')
            Arr[index] = Arr[index] * 10 + ptr[i] - '0';
        else
            index++;
    index++;

    int sum = 0;
    float average;

    printf("Converted to int: ");

    for (int i = 0; i < index; i++)
    {
        printf("%d ", Arr[i]);
        sum += Arr[i];
    }

    average = sum / index;

    printf("\nSum of Array: %d\nAverage of the Array: %f\n", sum, average);

    shmdt(&shmid);

    return 0;
}