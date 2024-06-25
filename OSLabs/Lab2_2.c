#include "Header.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <File Name>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    int fd_Fork[2];
    pipe(fd_Fork);

    char buffer[4096];
    int len = read(fd, buffer, 4096);

    int pid = fork();

    if (pid)
    { //  Parent
        wait(NULL);
        printf("\n\nIn Parent Process\n\n");
        char storeChar[5] = {'"', '\'', '&', '.', ','};
        int *charCount = (int *)malloc(sizeof(int) * 5);

        read(fd_Fork[0], charCount, 5 * sizeof(int));

        for (int i = 0; i < 5; i++)
            printf("Occourance of %c : %d\n", storeChar[i], charCount[i]);
    }
    else
    { //  Child
        printf("\n\nIn Child Process\n\n");
        int count = 0;
        int charCount[5] = {0, 0, 0, 0, 0};

        for (int i = 0; i < len; i++)
        {
            // printf("%c", buffer[i]);
            if (buffer[i] == '"')
            {
                charCount[0]++;
                printf("%d", charCount[0]);
            }
            if (buffer[i] == '\'')
            {
                charCount[1]++;
                printf("%d", charCount[1]);
            }
            if (buffer[i] == '&')
            {
                charCount[2]++;
                printf("%d", charCount[2]);
            }
            if (buffer[i] == '.')
            {
                charCount[3]++;
                printf("%d", charCount[3]);
            }
            if (buffer[i] == ',')
            {
                charCount[4]++;
                printf("%d", charCount[4]);
            }
        }
        write(fd_Fork[1], charCount, sizeof(int) * 5);
    }
}