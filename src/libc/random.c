#include <stdio.h>
#include <stdlib.h>
#include "random.h"

double random_double(double min, double max){
    double range = max - min;
    double div = RAND_MAX / range;
    return min + (rand() / div);
}
