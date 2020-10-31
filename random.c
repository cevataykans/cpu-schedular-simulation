#include "random.h"
#include <sys/time.h>
#include <stdio.h>

void init()
{
    srand(time(NULL));
}

int getRandomNum(int min, int max)
{
    int randomNum = (rand() % (max - min + 1)) - min;
    return randomNum;
}

int getRandomNum(int min, int max, int interval)
{
    int randomNum = (rand() % (max - min + 1)) - min;
    randomNum = (randomNum % 100) * 100;
    return randomNum;
}