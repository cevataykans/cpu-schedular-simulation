#include "PSThread.h"
#include <pthread.h>
#include <stdio.h>

void runner(void *param)
{
    int threadID = ((struct threadargs *)param)->id;
    printf("Thread isready!\n");

    int i = 0;
    // Send CPU BURST

    //mark it as available

    /*while ( i < duration)
    {

        // wait for mutex conditional variable

        // 
        
    }*/
}

void sendCPUBurst()
{
}