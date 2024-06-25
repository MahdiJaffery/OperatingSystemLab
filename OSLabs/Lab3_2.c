#include "Header.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <File Name>\n", argv[0]);
        return 1;
    }

    int fd = open("inputLab3_2.txt", O_RDWR);

    lseek(fd, 0, SEEK_SET); //  Moves Cursor to the start of the file

    char alpha;

    int skip;

    printf("Enter Skipping Factor\n");
    scanf("%d", &skip);

    while (read(fd, &alpha, sizeof(char)) > 0)
    {
        lseek(fd, (off_t)skip, SEEK_CUR); //  Moves the cursor to current position + offset (i.e. skip)
        printf("%c", alpha);
    }
    printf("\n\n");
}