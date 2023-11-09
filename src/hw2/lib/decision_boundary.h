/**
 * @file decision_boundary.h
 * @brief Decision boundary functions
*/

#include "normal_distribution.h"

#ifndef DECISION_BOUNDARY_H
#define DECISION_BOUNDARY_H

/**
 * @brief The input_struct struct
 * @details This struct is used to store the input data
 */
typedef struct{
    float step;         ///< step size
    float y1;           ///< y value of the first normal distribution
    float y2;           ///< y value of the second normal distribution
    float x1;           ///< x value of the first normal distribution
    float x2;           ///< x value of the second normal distribution
    float avg_x;        ///< average x value of the two normal distributions
    float min_error;    ///< minimum error
} intersection;

/// Calculate probability of certain x value
float cal_prob(norm_dist* pND, float x);

/// Calculate the portion integral of normal distribution
float cal_portion_integral(norm_dist* pND, intersection* pIST, float start, float end);

/// Calculate the intersection of two normal distributions
void cal_intersection(norm_dist* pND1, norm_dist* pND2, intersection* pIntersection);

/// Find the minimum error by using intersaction as boundary
void get_intersection(input_struct* pIS1, norm_dist* pND1, input_struct* pIS2, norm_dist* pND2, intersection* pIntersection);

#endif // DECISION_BOUNDARY_H
