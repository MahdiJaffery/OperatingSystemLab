#include "../Header.h"

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
    if (argc != 2)
    {
        printf("Usage: %s <Pipe Name>\n", argv[0]);
        return 1;
    }

    int len;
    char *buffer;

    int fd = open(argv[1], O_RDWR);

    if (fd == -1)
    {
        perror("Failed to Open Pipe\n");
        return 2;
    }

    read(fd, &len, sizeof(int));

    buffer = (char *)malloc(sizeof(char) * len);
    read(fd, buffer, sizeof(char) * len);

    switchCase(buffer, len);

    printf("Recieved String: %s\n", buffer);

    return 0;
}