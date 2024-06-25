#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    char buffer[100];
    int fdInput = open("input.txt", O_RDONLY);

    int len = read(fdInput, buffer, 100);

    int fdOutput = open("output.txt", O_WRONLY | O_CREAT, 0777);

    dup2(fdOutput, 1);

    printf("%s", buffer);

    return 0;
}