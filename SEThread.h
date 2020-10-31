#define NUM_OF_THREADS 5

char *fileName = NULL;
struct programData data;
struct threadargs threadParams[NUM_OF_THREADS];

struct programData
{
    int minCPU;
    int maxCPU;
    int minIO;
    int maxIO;
    int duration;
    char *infile;
} programData;