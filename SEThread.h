#define NUM_OF_THREADS 5

extern char *fileName;
extern struct programData data;
extern struct threadargs threadParams[NUM_OF_THREADS];

struct programData
{
    int minCPU;
    int maxCPU;
    int minIO;
    int maxIO;
    int duration;
    char *infile;
} programData;