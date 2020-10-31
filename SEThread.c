#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "SEThread.h"
#include "PSThread.h"
//#include "lists/list.h"
//#include "lists/WordList.h"

//pthread_t tids[NUM_OF_THREADS];
//pthread_attr_t attrs[NUM_OF_THREADS];
//struct threadargs threadParams[NUM_OF_THREADS];

char *fileName;
struct programData data;
struct threadargs threadParams[NUM_OF_THREADS];

//int waitForExecution[NUM_OF_THREADS];
//char *fileName = NULL;
//struct programData data;

int main(int argc, char *argv[])
{
    int threadCount = atoi(argv[1]);
    data.minCPU = atoi(argv[2]);
    data.maxCPU = atoi(argv[3]);
    data.minIO = atoi(argv[4]);
    data.maxIO = atoi(argv[5]);
    char *outputName = argv[6];
    data.duration = atoi(argv[7]);
    char *algorithm = argv[8];
    int quantum = atoi(argv[9]);
    if (strcmp(argv[10], "no-infile") == 0)
        data.infile = NULL;
    else
        data.infile = argv[10];

    printf("Thread count:%d, Mincpu:%d, MaxCpu:%d, MinIO:%d, maxIO: %d\n\n", threadCount, data.minCPU, data.maxCPU, data.minIO, data.maxIO);
    printf("Outputname: %s, duration:%d, alg:%s, quantum:%d, infile:%s\n\n", outputName, data.duration, algorithm, quantum, data.infile);

    if (threadCount <= 0)
    {
        printf("Number of argumnets must be between 1 and 5 inclusive...");
        return -1;
    }

    //Create Queue here! with respect to the algorithm!

    // Cretate threads
    for (int i = 0; i < threadCount; i++)
    {
        //waitForExecution[i] = 0;
        pthread_attr_init(&threadParams[i].attr);

        threadParams[i].id = i;
        threadParams[i].cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

        pthread_create(&threadParams[i].tid, &threadParams[i].attr, runner, &threadParams[i]);
        printf("Thread created with id: %d\n", i);
    }

    // Sleep for 1 sec to wait for all threads to add burst to queue
    sleep(1);

    // Open output file to write!
    FILE *fp = fopen(outputName, "w+");
    if (fp == NULL)
    {
        printf("Output file could not be opened!");
    }
    // Write here the SE thread logic

    // do not forget to free the burstnodes you receive from the queue!

    //
    //
    //
    //
    //

    /*int done = 0;
    while (done == 0)
    {
        done = 1;
        for (int i = 0; i < threadCount; i++)
        {
            if (waitForExecution[i] == 0)
                done = 0;
        }
        // for test
        if (done == 1)
        {
            for (int i = 0; i < threadCount; i++)
                printf("Waiting for %d is %d\n", i, waitForExecution[i]);
        }
    }*/

    printf("Completed!");
    /*gettimeofday(&end, NULL);
    printf("Threads completed...\n");

    printf("Threads completed their tasks in time:\n");
    printf("\tIn seconds: %d\n", end.tv_sec - start.tv_sec);
    printf("\tIn microseconds: %ld\n",
           (end.tv_sec * 1000000 + end.tv_usec) -
               (start.tv_sec * 1000000 + start.tv_usec));

    FILE *fp = fopen("output_twc.txt", "w+");

    // Merge solutions
    gettimeofday(&start, NULL);
    struct Node *heads[NUM_OF_THREADS];
    int available[NUM_OF_THREADS];
    int hasBeenRead[NUM_OF_THREADS];
    for (int i = 0; i < threadCount; i++)
    {
        heads[i] = getHeadNode(wordLists[i]);
        available[i] = 1;
        hasBeenRead[i] = 0;
    }

    int remianingLists = threadCount;
    int smallestFound;
    char *smallest = malloc(1024 * sizeof(char));
    int count;
    while (remianingLists > 0)
    {
        // find smallest word in available buffers
        smallestFound = -1;
        for (int i = 0; i < threadCount; i++)
        {
            if (available[i])
            {
                if (smallestFound < 0)
                {
                    strcpy(smallest, (const char *)heads[i]->word);
                    smallestFound = 1;
                }
                else
                {
                    if (strcmp((const char *)smallest, (const char *)heads[i]->word) > 0)
                    {
                        strcpy(smallest, (const char *)heads[i]->word);
                    }
                }
            }
        }

        count = 0;
        for (int i = 0; i < threadCount; i++)
        {
            if (available[i])
            {
                if (strcmp((const char *)smallest, (const char *)heads[i]->word) == 0)
                {
                    hasBeenRead[i] = 1;
                    count = count + heads[i]->count;
                }
            }
        }

        // write to file
        if (fp != NULL)
        {
            fprintf( fp, "%s %d\n", smallest, count);
        }

        // read from the buffers that are used for output
        for (int i = 0; i < threadCount; i++)
        {
            if (available[i] && hasBeenRead[i] > 0)
            {
                heads[i] = heads[i]->next;
                hasBeenRead[i] = 0;
                if (heads[i] == NULL)
                {
                    available[i] = 0;
                    remianingLists--;
                }
            }
        }
    }
    gettimeofday(&end, NULL);

    printf("Algorithm completed for threads:\n");
    printf("\tIn seconds: %d\n", end.tv_sec - start.tv_sec);
    printf("\tIn microseconds: %ld\n",
           (end.tv_sec * 1000000 + end.tv_usec) -
               (start.tv_sec * 1000000 + start.tv_usec));

    // Clear up
    fclose(fp);
    free(smallest);
    for (int i = 0; i < threadCount; i++)
    {
        destroyWordLinkedList(wordLists[i]);
    }
    gettimeofday(&endTime, NULL);

    printf("Program run for:\n");
    printf("\tIn seconds: %d\n", endTime.tv_sec - startTime.tv_sec);
    printf("\tIn microseconds: %ld\n",
           (endTime.tv_sec * 1000000 + endTime.tv_usec) -
               (startTime.tv_sec * 1000000 + startTime.tv_usec));*/

    fclose(fp);
    return 0;
}