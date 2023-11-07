#ifndef DISTANCE_H
#define DISTANCE_H

#include <math.h>

float distance_straightline(float x1, float y1, float x2, float y2);

float distance_hamming(float x1, float y1, float x2, float y2);

float distance_euclidean(float x1, float y1, float x2, float y2);

float distance_manhattan(float x1, float y1, float x2, float y2);

float distance_minkowski(float x1, float y1, float x2, float y2);

# endif
