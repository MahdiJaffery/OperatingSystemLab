#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{

    if (argc != 4 || argv[2][0] != '>' || argv[2][1] != '\0')
    {
        printf("Usage: %s <Input File> \">\" <Output File>\n", argv[0]);
        return 1;
    }

    int fdInput = open(argv[1], O_RDONLY);

    if (fdInput == -1)
    {
        printf("Error Opening Input File\n");
        return 2;
    }

    int fdOutput = open(argv[3], O_WRONLY);

    if (fdOutput == -1)
    {
        printf("Failed to Open Output File\n");
        return 3;
    }

    char buffer[4096];

    int len = read(fdInput, buffer, 4096);

    if (len == -1)
    {
        printf("Failed to Read from %s\n", argv[1]);
        return 4;
    }

    if (dup2(fdOutput, 1) == -1)
    {
        printf("Failed to Redirect\n");
        return 5;
    }
    write(1, buffer, sizeof(char) * len);
    return 0;
}