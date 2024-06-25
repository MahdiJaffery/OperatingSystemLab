#include "../Header.h"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Usage: %s <Pipe Name> <Arithmetic Symbol> <Number> <Number>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);

    if (fd == -1)
    {
        perror("Failed to Open Pipe\n");
        return 2;
    }

    char *Symbol = argv[2];
    int a = atoi(argv[3]), b = atoi(argv[4]);

    write(fd, &Symbol[0], sizeof(char));
    write(fd, &a, sizeof(int));
    write(fd, &b, sizeof(int));

    sleep(1);

    int Ans;
    read(fd, &Ans, sizeof(int));

    printf("%d %s %d = %d\n", a, Symbol, b, Ans);

    return 0;
}