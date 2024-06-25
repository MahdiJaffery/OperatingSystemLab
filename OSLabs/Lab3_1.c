#include "Header.h"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <alphanumericals>\n", argv[0]);
        return 1;
    }

    int fd[2];
    pipe(fd);
    int pid = fork();

    if (pid)
    {
        int pid2 = fork();
        if (pid2)
        { //  Parent
            wait(NULL);
            wait(NULL);

            printf("\n\nIn Parent\n\n");

            int len;
            read(fd[0], &len, sizeof(int));
            printf("Recieved Length : %d\n", len);

            char *alpha = (char *)malloc(sizeof(char) * len);
            read(fd[0], alpha, sizeof(char) * len);

            for (int i = 0; i < len; i++)
                printf("%c", alpha[i]);

            printf("\n\n");
        }
        else
        { //  Child 2
            printf("In Child 2\n[PID : %u]\n\n", getpid());
        }
    }
    else
    { //  Child 1
        printf("\n\nIn Child 1\n\n");
        int lenCmd = strlen(argv[1]);
        char *alpha = (char *)malloc(sizeof(char) * lenCmd);

        alpha = argv[1];

        int count = 0;
        for (int i = 0; i < lenCmd; i++)
            if (!(alpha[i] >= 'a' && alpha[i] <= 'z' || alpha[i] >= 'A' && alpha[i] <= 'Z'))
                count++;

        printf("Count : %d\n", count);

        char *modifiedAlpha = (char *)malloc(sizeof(int) * (lenCmd - count));

        int index = 0;

        for (int i = 0; i < lenCmd; i++)
            if (alpha[i] >= 'a' && alpha[i] <= 'z' || alpha[i] >= 'A' && alpha[i] <= 'Z')
                modifiedAlpha[index++] = alpha[i];

        lenCmd -= count;

        if (write(fd[1], &lenCmd, sizeof(int)))
            printf("Sending Length %d to Parent\n", lenCmd);
        if (write(fd[1], modifiedAlpha, lenCmd * sizeof(char)))
            printf("\n\nExiting Child 1\n\n");
    }
}