#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>

#include "gpioLib.h"

void intHandler(int);

volatile int running = 1;
int main(int argc, char *argv[])
{
    int delay_ms = 100;
    if(argc > 1)
        delay_ms = atoi(argv[1]);
    signal(SIGINT, intHandler);
    printf("Initializing GPIO library... ");
    int ret;
    int i;
    uint8_t *val = (uint8_t *)malloc(sizeof(uint8_t));

    struct timespec delay = {(delay_ms / 1000), (delay_ms % 1000) * 1000000};
    ret = gpioLibInit();
    if(ret == OK)
        printf("OK\n");
    else
        printf("ERROR\n");

    i = 17;
    while(running)
    {
        gpioPinSetValue(i, 0);
        nanosleep(&delay, 0);
        gpioPinSetValue(i, 1);
        nanosleep(&delay, 0);
    }

    gpioPinSetValue(i, 0);
    printf("\rPIN %2d: ", i);
    gpioPinRead(i, val);
    if(*val)
        printf("HIGH\n");
    else
        printf("LOW\n");


    return 0;
}

void intHandler(int sig)
{
    running = 0;
}
