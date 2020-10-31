#include "CommonFuncs.h"
#include <sys/time.h>
#include <stdio.h>
#include "string.h"

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