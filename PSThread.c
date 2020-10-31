#include "PSThread.h"
#include "SEThread.h"
#include "random.h"
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void runner(void *param)
{
    int threadId = ((struct threadargs *)param)->id;
    printf("Thread %d begins\n", threadId);

    if (fileName != NULL)
    {
        printf("File name is not null, setting my own arguments");
    }

    sleep(1);
    //waitForExecution[threadId] = 1;

    int i = 0;
    while (i < data.duration)
    {

        // wait for mutex conditional variable

        // read burst time sent to the

        i++;
    }
    pthread_exit(0);
}

void sendCPUBurst()
{
}