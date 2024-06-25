#include "Header.h"

int replaceWordInFile(char *filename, char *wordtoReplace, char *replacement)
{
    int fd = open(filename, O_RDWR);
    if (fd == -1)
    {
        return -1;
    }

    char *map = (char *)mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
    {
        return -2;
    }

    printf("Original Contents of file: %s\n\n", map);

    char newArr[100];
    int k = 0;
    bool flg;
    for (int i = 0; map[i] != '\0'; i++)
    {
        flg = false;
        if (map[i] == wordtoReplace[0])
        {
            flg = true;
            int j = 1;
            for (j; flg && wordtoReplace[j] != '\0'; j++)
            {
                if (map[i + j] != wordtoReplace[j])
                    flg = false;
            }
            if (flg)
            {
                for (int a = 0; replacement[a] != 0; a++)
                {
                    newArr[k] = replacement[a];
                    k++;
                }
                i += j;
            }
        }
        newArr[k] = map[i];
        k++;
    }

    newArr[k] = '\0';
    printf("Updated Array: %s\n", newArr);

    for (int i = 0; i < k; i++)
    {
        map[i] = newArr[i];
    }

    if (munmap(map, sizeof(char) * k) == -1)
    {
        return -3;
    }

    close(fd);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s filename.txt <wordtoReplace> <replacement> \n", argv[0]);
        return 0;
    }

    replaceWordInFile(argv[1], argv[2], argv[3]);

    return 0;
}