#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>
#include <terminals.h>
#include <hardware.h>
void writer(void *);

char string[] = "abcdefghijklmnopqrstuvwxyz";
int length = sizeof(string) - 1;

int main(int argc, char **argv)
{
    InitTerminalDriver();
    InitTerminal(1);
    if (argc > 1) HardwareOutputSpeed(1, atoi(argv[1]));
    if (argc > 2) HardwareInputSpeed(1, atoi(argv[2]));


    while(1) {
        ThreadCreate(writer, NULL);
        sleep(3);
    }
    ThreadWaitAll();

    exit(0);
}

void
writer(void *arg)
{
    int status;

    printf("Doing WriteTerminal... '");
    fflush(stdout);
    status = WriteTerminal(1, string, length);
    printf("'. Done: status = %d.\n", status);
    fflush(stdout);
}
