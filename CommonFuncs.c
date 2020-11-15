#include "CommonFuncs.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <time.h>

void init()
{
    srand(time(0));
}

int getRandomNum(int min, int max, int interval)
{
    int randomNum = (rand() % (max - min + 1)) + min;
    randomNum = (randomNum / 100) * 100;
    return randomNum;
}

void getFileName(char name[], int id)
{
    strcpy(name, fileName);
    int nameLength = strlen(name);
    name[nameLength] = '0' + id;
    name[nameLength + 1] = '.';
    name[nameLength + 2] = 't';
    name[nameLength + 3] = 'x';
    name[nameLength + 4] = 't';
    name[nameLength + 5] = '\0';
}

void writeOutput(FILE* fp, int totExecTime, int burstTime, int threadId){
    char formattedTime[11];
    char strExecTime[11];
    sprintf(strExecTime, "%d", totExecTime);
    for(int i = 0 ; i < 10 ; i++){
        if(i < 10 - strlen(strExecTime))
            formattedTime[i] = '0';
        else
            formattedTime[i] = strExecTime[i - 10 + strlen(strExecTime)];
    }
    formattedTime[10] = '\0';
    fprintf(fp, "%s %d %d\n", formattedTime, burstTime, threadId);
}