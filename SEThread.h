#ifndef SETHREAD_H
#define SETHREAD_H

#include <stdio.h>
#define NUM_OF_THREADS 5

struct programData
{
    int minCPU;
    int maxCPU;
    int minIO;
    int maxIO;
    int duration;
    char *infile;
    int quantum;
};

struct BurstNode{
    int id;
    int burstTime;
    struct BurstNode* next;
};

#endif