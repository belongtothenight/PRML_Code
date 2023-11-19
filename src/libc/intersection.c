#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "intersection.h"

void d2_intersection(double a1, double b1, double c1, double a2, double b2, double c2, d2_point_t *d2_point){
    // a1*x + b1*y = c1
    // a2*x + b2*y = c2
    // x = (c1*b2 - c2*b1) / (a1*b2 - a2*b1)
    // y = (c2*a1 - c1*a2) / (a1*b2 - a2*b1)
    d2_point->x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
    d2_point->y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
    return;
}
