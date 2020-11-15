#include "SEThread.h"

extern char *fileName;

void init();
int getRandomNum(int min, int max, int interval);
void getFileName(char name[], int id);
void writeOutput(FILE* fp, int totExecTime, int burstTime, int threadId);