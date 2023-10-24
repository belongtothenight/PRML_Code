#include "output_format.h"

#ifndef NORMAL_DISTRIBUTION_H
#define NORMAL_DISTRIBUTION_H

typedef struct{
    float mu;
    float sigma;
    float integral_step;
    float x_min;
    float x_max;
    int arr_length;
    float cdf;
}norm_dist;

// Initialize a normal distribution struct
void get_norm_dist(norm_dist* pNd, float mu, float sigma, float x_min, float x_max, float integral_step);

// Print the normal distribution struct
void print_norm_dist(norm_dist* pNd);

// Malloc two float arrays for x values of the normal distribution
float* get_norm_dist_x_arr(norm_dist* pNd);

// Malloc float arrays for y values of the normal distribution
float* get_norm_dist_y_arr(norm_dist* pNd, float* x_arr);

// Pour x y values into a file
void pour_arr_to_file(float* arr, int arr_length, char* file_name);

// Calculate CDF of the normal distribution
float norm_dist_cdf(norm_dist* pNd, float x);

// CDF check function
void norm_dist_cdf_check(norm_dist* pNd);

#endif // NORMAL_DISTRIBUTION_H
