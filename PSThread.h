#include <pthread.h>
#include "SEThread.h"
#include <stdio.h>

void runner(void *param);
int getBurstDuration(FILE *fp);
int getSleepDuration(FILE *fp);

//extern int waitForExecution[NUM_OF_THREADS];
extern char *fileName;
extern struct programData data;
extern struct threadargs threadParams[];

struct threadargs
{
    int id;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_cond_t cond;

} threadargs;