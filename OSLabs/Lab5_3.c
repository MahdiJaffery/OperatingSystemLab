#include "Header.h"

int main(int argc, char *argv[])
{

    int fdRead = open("inputLab5_3.txt", O_RDONLY);
    int fdWrite = open("outputLab5_3.txt", O_WRONLY);

    if (fdRead == -1)
    {
        perror("Failed to Open Read File");
        return 1;
    }

    if (fdWrite == -1)
    {
        perror("Failed to Open Write File");
        return 2;
    }

    int fd[2];
    pipe(fd);

    int pid = fork();

    if (pid)
    {
        char buffer[4096];
        int len = read(fdRead, buffer, 4096);

        printf("Recieved Datee from File: %s\n", buffer);

        write(fd[1], &len, sizeof(int));
        write(fd[1], buffer, sizeof(char) * len);
    }
    else
    {
        int len;
        char *buffer;

        read(fd[0], &len, sizeof(int));
        buffer = (char *)malloc(sizeof(char) * len);

        read(fd[0], buffer, sizeof(int) * len);

        printf("Recieved Data from Parent: %s\n", buffer);

        if (write(fdWrite, buffer, sizeof(char) * len) > -1)
            printf("Data written in Write File\n");
        else
            printf("Failed to write Data in Write File\n");
    }
}