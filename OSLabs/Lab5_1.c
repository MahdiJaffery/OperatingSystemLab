#include "Header.h"

void switchCase(char *alpha, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (alpha[i] >= 'a' && alpha[i] <= 'z')
            alpha[i] -= 32;
        else if (alpha[i] >= 'A' && alpha[i] <= 'Z')
            alpha[i] += 32;
    }
}

int main(int argc, char *argv[])
{
    int fd[2];
    int fd_File = open("inputLab5_1.txt", O_RDWR);
    pipe(fd);

    int pid = fork();

    if (pid)
    {
        char buffer[4096];
        int len = read(fd_File, buffer, 4096);

        write(fd[1], &len, sizeof(int));
        write(fd[1], buffer, sizeof(char) * len);

        printf("Sending to Child: %s\n", buffer);
    }
    else
    {
        int len;
        read(fd[0], &len, sizeof(int));

        char *buffer = (char *)malloc(sizeof(char) * len);
        read(fd[0], buffer, sizeof(char) * len);

        switchCase(buffer, len);

        printf("Recieved from Parent: %s\n", buffer);
    }
}