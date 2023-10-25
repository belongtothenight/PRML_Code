#include "normal_distribution.h"

#ifndef DECISION_BOUNDARY_H
#define DECISION_BOUNDARY_H

typedef struct{
    int idx1; // index of the first normal distribution
    int idx2; // index of the second normal distribution
    float y1; // y value of the first normal distribution
    float y2; // y value of the second normal distribution
    float x1; // x value of the first normal distribution
    float x2; // x value of the second normal distribution
    float avg_x; // average x value of the two normal distributions
    float min_error; // minimum error
} intersection;

// Calculate the portion integral of normal distribution
float cal_portion_integral(norm_dist* pND, float* y_arr, int start, int end);

// Calculate the intersection of two normal distributions
void cal_intersection(norm_dist* pND1, norm_dist* pND2, float* y_arr1, float* y_arr2, intersection* pIntersection);

// Find the minimum error by using intersaction as boundary
void get_intersection(input_struct* pIS1, norm_dist* pND1, input_struct* pIS2, norm_dist* pND2, intersection* pIntersection);

#endif // DECISION_BOUNDARY_H
