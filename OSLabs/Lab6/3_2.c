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

    char Symbol;
    int a, b;

    read(fd, &Symbol, sizeof(char));
    read(fd, &a, sizeof(int));
    read(fd, &b, sizeof(int));

    if (Symbol == '+')
        a += b;
    if (Symbol == '-')
        a -= b;
    if (Symbol == '*')
        a *= b;
    if (Symbol == '/')
        a /= b;

    write(fd, &a, sizeof(int));
    return 0;
}