#include "Header.h"

#define line printf("\n\n")

int timeElapsed;

void myHandler(int sig)
{
    if (sig == SIGCHLD)
        printf("Total Time Elapsed: %d\n\nRecieved SIGCHLD\n", timeElapsed);
    exit(0);
}

int main(int argc, char *argv[])
{

    if (signal(SIGCHLD, myHandler) == SIG_ERR)
        printf("Signal Failed\n");

    int laps, duration;
    printf("Enter the numebr of Laps: ");
    scanf("%d", &laps);
    printf("Enter the Time Duration of the Laps(seconds): ");
    scanf("%d", &duration);
    timeElapsed = laps * duration;

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork Failed\n");
        return 1;
    }

    if (pid)
    {
        wait(NULL);
        // exit(0);
    }
    else
    {
        for (int i = 0; i < laps; i++)
        {
            sleep(duration);
            printf("Lap %d Complete\n", i);
        }
        line;
    }
}