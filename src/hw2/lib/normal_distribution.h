/**
 * @file normal_distribution.h
 * @brief Normal distribution functions
*/

#include "output_format.h"

#ifndef NORMAL_DISTRIBUTION_H
#define NORMAL_DISTRIBUTION_H

/**
 * @brief Normal distribution struct
*/
typedef struct{
    float mu;               ///< Mean of the normal distribution
    float sigma;            ///< Standard deviation of the normal distribution
    float integral_step;    ///< Step size of the integral
    float x_min;            ///< Minimum value of x
    float x_max;            ///< Maximum value of x
    int arr_length;         ///< Length of the x y arrays
    float integral;         ///< Integral of the normal distribution
} norm_dist;

/**
 * @brief Input struct
*/
typedef struct{
    float *pX_arr;          ///< Pointer to the x array
    float *pY_arr;          ///< Pointer to the y array
    char *tmp_file_1;       ///< Temporary file name 1
    char *tmp_file_2;       ///< Temporary file name 2
} input_struct;

/// Initialize a normal distribution struct
void get_norm_dist(norm_dist* pNd, float mu, float sigma, float x_min, float x_max, float integral_step);

/// Print the normal distribution struct
void print_norm_dist(norm_dist* pNd, char* name);

/// Malloc two float arrays for x values of the normal distribution
float* get_norm_dist_x_arr(norm_dist* pNd);

/// Malloc float arrays for y values of the normal distribution
float* get_norm_dist_y_arr(norm_dist* pNd, float* x_arr);

/// Pour x y values into a file
void pour_arr_to_file(float* arr, int arr_length, char* file_name);

/// Calculate integral of the normal distribution
void norm_dist_integral(norm_dist* pNd, float* y_arr);

/// Integral check function
void norm_dist_integral_check(norm_dist* pNd);

/// Normal distribution y value check function
void norm_dist_y_check(norm_dist* pNd, float* y_arr);

/// Print the input struct
void print_input_struct(input_struct* pIs, char* name);

/// Pack all the functions above
void cal_norm_dist(norm_dist* pNd, float mu, float sigma, float x_min, float x_max, float integral_step, input_struct* pInput_struct, char* name);

/// Free memory
void free_norm_dist(input_struct* pInput_struct, char* name);

#endif // NORMAL_DISTRIBUTION_H
