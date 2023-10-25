#include "output_format.h"

#ifndef NORMAL_DISTRIBUTION_H
#define NORMAL_DISTRIBUTION_H

#define INTEGRAL_BAR 0.95

typedef struct{
    float mu;
    float sigma;
    float integral_step;
    float x_min;
    float x_max;
    int arr_length;
    float integral;
}norm_dist;

typedef struct{
    float *pX_arr;
    float *pY_arr;
    char *tmp_file_1;
    char *tmp_file_2;
} input_struct;

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
void norm_dist_integral(norm_dist* pNd, float* y_arr);

// CDF check function
void norm_dist_integral_check(norm_dist* pNd);

// Print the input struct
void print_input_struct(input_struct* pIs);

// Pack all the functions above
void cal_norm_dist(norm_dist* pNd, float mu, float sigma, float x_min, float x_max, float integral_step, input_struct* pInput_struct);

#endif // NORMAL_DISTRIBUTION_H
