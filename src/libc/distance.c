#include <stdio.h>
#include <math.h>
#include "distance.h"
// Ref: https://machinelearningmastery.com/distance-measures-for-machine-learning/

float distance_straightline(float x1, float y1, float x2, float y2){
    return (fabs(x1 - x2) + fabs(y1 - y2));
}

float distance_hamming(float x1, float y1, float x2, float y2){
    return (fabs(x1 - x2) + fabs(y1 - y2))/2;
}

float distance_euclidean(float x1, float y1, float x2, float y2){
    printf("Not implemented yet.\n");
}

float distance_manhattan(float x1, float y1, float x2, float y2){
    printf("Not implemented yet.\n");
}

float distance_minkowski(float x1, float y1, float x2, float y2){
    printf("Not implemented yet.\n");
}
