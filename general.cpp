#include "general.h"

void InitRandom()
{
    srand((unsigned int)time(0));
}

int Random(int a, int b) //randrange(a,b)
{
    return int(a + (b-a)*double(rand())/RAND_MAX);
}

