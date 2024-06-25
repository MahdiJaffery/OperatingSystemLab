#include "../Header.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <Pipe Name>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);

    if (fd == -1)
    {
        perror("Failed to Open Pipe\n");
        return 2;
    }

    printf("Enter a String: ");
    char buffer[4096];
    fgets(buffer, 4096, stdin);

    int len = strlen(buffer);

    if (write(fd, &len, sizeof(int)) == -1)
    {
        perror("Failed Write\n");
        return 3;
    }

    if (write(fd, buffer, strlen(buffer) * sizeof(char)) == -1)
    {
        perror("Failed Write\n");
        return 3;
    }

    printf("Sent String: %s\n", buffer);

    return 0;
}