#include "../Header.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <Pipe Name>\n", argv[0]);
        return 1;
    }

    int fd = mkfifo(argv[1], S_IRUSR | S_IWUSR);

    if (fd == -1)
        printf("Pipe Failed\n");
    else
        printf("Pipe Successful\n");

    return 0;
}