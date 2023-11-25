/**
 * @file random.h
 * @brief Random number generation functions.
 * Ref:
 * 1. https://stackoverflow.com/questions/33058848/generate-a-random-double-between-1-and-1
*/

#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Generate a random double between given min and max.
 * @param min The minimum value of the range.
 * @param max The maximum value of the range.
 * @return A random double between range.
*/
double random_double(double min, double max);

#endif // RANDOM_H
