#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "SEThread.h"
#include "PSThread.h"
#include "CommonFuncs.h"
#include <unistd.h>
#include "lists/list.h"

char *fileName; // Change
struct programData data;
struct threadargs threadParams[NUM_OF_THREADS];
struct LinkedList *readyQueue;
int done[NUM_OF_THREADS];
pthread_cond_t waitPacket = PTHREAD_COND_INITIALIZER;
pthread_mutex_t test = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
    init();
    int threadCount = atoi(argv[1]);
    data.minCPU = atoi(argv[2]);
    data.maxCPU = atoi(argv[3]);
    data.minIO = atoi(argv[4]);
    data.maxIO = atoi(argv[5]);
    char *outputName = argv[6];
    data.duration = atoi(argv[7]);
    char *algorithm = argv[8];
    data.quantum = atoi(argv[9]);
    if (strcmp(argv[10], "no-infile") == 0)
    {
        data.infile = NULL;
        fileName = NULL;
    }
    else
    {
        data.infile = argv[10];
        fileName = argv[10];
    }

    printf("Thread count:%d, Mincpu:%d, MaxCpu:%d, MinIO:%d, maxIO: %d\n\n", threadCount, data.minCPU, data.maxCPU, data.minIO, data.maxIO);
    printf("Outputname: %s, duration:%d, alg:%s, quantum:%d, infile:%s\n\n", outputName, data.duration, algorithm, data.quantum, data.infile);

    if (threadCount <= 0)
    {
        printf("Number of argumnets must be between 1 and 5 inclusive...");
        return -1;
    }

    // Select algorithm
    struct BurstNode *(*getNextNode)(struct LinkedList *, int *);
    if (strcmp(algorithm, "FCFS") == 0)
        getNextNode = &FCFS;
    else if (strcmp(algorithm, "SJF") == 0)
        getNextNode = &SJF;
    else
        getNextNode = &RR;

    //Create Queue here! with respect to the algorithm!
    readyQueue = createLinkedList();

    // Cretate threads
    for (int i = 0; i < threadCount; i++)
    {
        done[i] = 1;
        //waitForExecution[i] = 0;
        pthread_attr_init(&threadParams[i].attr);

        threadParams[i].id = i;
        threadParams[i].cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

        pthread_create(&threadParams[i].tid, &threadParams[i].attr, runner, &threadParams[i]);
        printf("Thread created with id: %d\n", i);
    }
    printf("All threads are created\n");

    // Open output file to write!
    FILE *fp = fopen(outputName, "w+");
    if (fp == NULL)
    {
        printf("Output file could not be opened!");
        return -1;
    }
    // Write here the SE thread logic
    printf("output file is opened\n");
    int sum = threadCount;
    //int totExecTime = 0; // depreciated!!!
    struct timeval startTime;
    struct timeval exeTime;
    struct timeval curTime;
    int flag;
    int timeFlag = 1;
    int totalResponseTime = 0;
    int responseCount = 0;
    int totalWaitingTime = 0;
    while (sum > 0)
    {
        flag = 0;
        struct BurstNode *curBurst = getNextNode(readyQueue, &flag);
        if (curBurst == NULL)
        {
            pthread_mutex_lock(&test);
            pthread_cond_wait(&waitPacket, &test);
            pthread_mutex_unlock(&test);
            curBurst = getNextNode(readyQueue, &flag);
        }

        if (curBurst->burstTime <= 0)
        {
            sum--;
            continue;
        }

        if (timeFlag > 0)
        {
            gettimeofday(&startTime, NULL);
            exeTime = startTime;
            timeFlag = 0;
        }
        else
        {
            gettimeofday(&exeTime, NULL);
        }

        if (curBurst->first == 1)
        {
            gettimeofday(&curTime, NULL);
            struct timeval entryTime = curBurst->entryTime;
            totalResponseTime += (curTime.tv_sec - entryTime.tv_sec) * 1000000 + (curTime.tv_usec - entryTime.tv_usec);
            responseCount++;
        }

        usleep(curBurst->burstTime * 1000);
        writeOutput(fp, (exeTime.tv_sec - startTime.tv_sec) * 1000000 + (exeTime.tv_usec - startTime.tv_usec), curBurst->burstTime, curBurst->id);

        if (curBurst->last == 1)
        {
            gettimeofday(&curTime, NULL);
            struct timeval entryTime = curBurst->entryTime;
            totalWaitingTime += ( (curTime.tv_sec - entryTime.tv_sec) * 1000000 + (curTime.tv_usec - entryTime.tv_usec) - (curBurst->burstTime) * 1000);
        }

        //writeOutput(fp, (curTime.tv_sec - startTime.tv_sec) * 1000000 + (curTime.tv_usec - startTime.tv_usec), curBurst->burstTime, curBurst->id);
        //totExecTime += curBurst->burstTime; depreciated
        if (curBurst->last == 1) //if (flag == 0)
            pthread_cond_signal(&(threadParams[curBurst->id].cond));

        free(curBurst);
    }

    if (responseCount == 0)
    {
        printf("Response count is 0!\n");
    }
    else
    {
        double averageResponseTime = (double)totalResponseTime / (double)responseCount;
        printf("Average response time is %f\n", averageResponseTime);
        printf("Total waiting time is %d\n", totalWaitingTime);
    }
    fclose(fp);
    return 0;
}