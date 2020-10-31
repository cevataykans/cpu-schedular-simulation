#include "PSThread.h"
#include "CommonFuncs.h"
#include <pthread.h>
#include <stdio.h>

extern char *fileName;
extern struct programData data;
extern struct threadargs threadParams[NUM_OF_THREADS];

void runner(void *param)
{
    int threadId = ((struct threadargs *)param)->id;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    printf("Thread %d begins\n", threadId);

    FILE *infile;
    if (fileName != NULL)
    {
        char modifiedFileName[128];
        getFileName(modifiedFileName, threadId);
        printf("Thread with id: %d is opening arg file: %s\n", threadId, modifiedFileName);

        infile = fopen(modifiedFileName, "r");
    }

    //sleep(1);
    //waitForExecution[threadId] = 1;

    if (infile != NULL)
    {
        while (!feof(infile))
        {
            // Get Burst Duration
            int burstTime = getCPUBurstDuration(infile);

            // Send burst duration to queue
            // write code here by deleting this line -----!

            // wait for mutex conditional variable
            pthread_cond_wait(&threadParams[threadId].cond, &lock);

            // Get Sleep Duration
            int sleepTime = getSleepDuration(infile);
            sleep(0.01 * sleepTime); // Sleep in ms!!!!!
        }
    }
    else
    {
        int i = 0;
        while (i < data.duration) // this needs  to be improved if an infile is read!!!!!
        {
            // Get Burst Duration
            int burstTime = getCPUBurstDuration(infile);

            // Send burst duration to queue
            // write code here by deleting this line -----!

            // wait for mutex conditional variable
            pthread_cond_wait(&threadParams[threadId].cond, &lock);

            // Get Sleep Duration
            int sleepTime = getSleepDuration(infile);
            sleep(0.01 * sleepTime); // Sleep in ms!!!!!

            i++;
        }
    }
    pthread_exit(0);
}

int getCPUBurstDuration(FILE *fp)
{
    int burstTime = 0;
    if (fp == NULL)
    {
        burstTime = getRandomNum(data.minCPU, data.maxCPU, 100);
    }
    else
    {
        // READ burst time from file and assign it to burstTime
        fscanf(fp, "%*s %d", &burstTime);
    }
    return burstTime;
}

int getSleepDuration(FILE *fp)
{
    int sleepTime = 0;
    if (fp == NULL)
    {
        sleepTime = getRandomNum(data.minIO, data.maxIO, 100);
    }
    else
    {
        // READ burst time from file and assign it to burstTime
        fscanf(fp, "%*s %d", &sleepTime);
    }
    return sleepTime;
}