#include "Header.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <File Name> <Word>\n", argv[0]);
        return 2;
    }

    int fd = open(argv[1], O_RDWR);

    if (fd == -1)
    {
        perror("Failed to open File");
        return 1;
    }

    int wordLen = strlen(argv[2]);
    char buffer[4096], *word = (char *)malloc(sizeof(char) * wordLen);
    word = argv[2];
    int len = read(fd, buffer, 4096), wordCount = 0, index = 0, count = 0;
    printf("Length of Word: %d\nLength of File: %d\n", wordLen, len);

    for (int i = 0; i < len; i++)
    {
        int wordIndex = 0;
        for (int j = i; buffer[j] != ' '; j++)
        {
            if (buffer[j] == word[wordIndex])
                wordIndex++;
            else
                break;
            if (wordIndex == wordLen)
                break;
        }
        if (wordIndex == wordLen)
            count++;
    }

    printf("Found %d Occourences of the Word: %s\n", count, word);
}