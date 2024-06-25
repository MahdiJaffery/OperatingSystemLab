#include "Header.h"

int main(int argc, char *argv[])
{
    int fd = open("numbers.txt", O_RDONLY);

    char buffer[100];

    int len = read(fd, buffer, 100);

    printf("Buffer Holds: %s\nLength: %d\n", buffer, len);

    int shmid = shmget((key_t)1, 4096, 0666 | IPC_CREAT);

    char *ptr = shmat(shmid, NULL, 0);

    strncpy(ptr, buffer, len * sizeof(char));
    sleep(1);

    shmdt(&shmid);

    return 0;
}