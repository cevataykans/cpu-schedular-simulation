#include <pthread.h>

void runner(void *param);

//extern int waitForExecution[NUM_OF_THREADS];
extern char *fileName = NULL;
extern struct programData data;

struct threadargs
{
    int id;
    pthread_t tid;
    pthread_attr_t attr;

} threadargs;