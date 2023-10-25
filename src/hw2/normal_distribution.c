#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "normal_distribution.h"
#include "output_format.h"

void get_norm_dist(norm_dist* pNd, float mu, float sigma, float x_min, float x_max, float integral_step){
    pNd->mu = mu;
    pNd->sigma = sigma;
    pNd->integral_step = integral_step;
    pNd->x_min = x_min;
    pNd->x_max = x_max;
    pNd->arr_length = (int)((x_max - x_min) / integral_step + 1);
    pNd->integral = 0;
    return;
}

void print_norm_dist(norm_dist* pNd){
    printf("\n\rNormal distribution:===============================\n\r");
    printf("mu:            %f\n\r", pNd->mu);
    printf("sigma:         %f\n\r", pNd->sigma);
    printf("integral_step: %f\n\r", pNd->integral_step);
    printf("x_min:         %f\n\r", pNd->x_min);
    printf("x_max:         %f\n\r", pNd->x_max);
    printf("arr_length:    %d\n\r", pNd->arr_length);
    printf("integral:      %f\n\r", pNd->integral);
    return;
}

float* get_norm_dist_x_arr(norm_dist* pNd){
    float* x_arr = (float*)malloc(sizeof(float) * pNd->arr_length);
    for(int i = 0; i < pNd->arr_length; i++){
        x_arr[i] = pNd->x_min + i * pNd->integral_step;
    }
    return x_arr;
}

float* get_norm_dist_y_arr(norm_dist* pNd, float* x_arr){
    float* y_arr = (float*)malloc(sizeof(float) * pNd->arr_length);
    float pi = (float)acos(-1);
    for(int i = 0; i < pNd->arr_length; i++){
        y_arr[i] = 1 / (pNd->sigma * sqrt(2 * pi)) * exp(-pow(x_arr[i] - pNd->mu, 2) / (2 * pow(pNd->sigma, 2)));
    }
    return y_arr;
}

void pour_arr_to_file(float* arr, int arr_length, char* file_name){
    output_format Format;
    get_format(&Format);
    FILE* fp = fopen(file_name, "w");
    if (fp == NULL){
        printf("%sERROR%s: Failed to open file %s.\n\r", Format.foreground.red, Format.style.reset, file_name);
        exit(1);
    }
    for(int i = 0; i < arr_length; i++){
        fprintf(fp, "%f\n", arr[i]);
    }
    fclose(fp);
    printf("%sSUCCESS%s: Data written to file %s.\n\r", Format.foreground.green, Format.style.reset, file_name);
    return;
}

void norm_dist_integral(norm_dist* pNd, float* y_arr){
    for(int i = 0; i < pNd->arr_length; i++){
        pNd->integral += pNd->integral_step * (y_arr[i] + y_arr[i + 1]) / 2;
    }
    return;
}

void norm_dist_integral_check(norm_dist* pNd){
    output_format Format;
    get_format(&Format);
    if (pNd->integral < INTEGRAL_BAR){
        printf("%sERROR%s: The integral of the normal distribution is less than %f.\n\r", Format.foreground.red, Format.style.reset, INTEGRAL_BAR);
        // exit(1);
    } else {
        printf("%sSUCCESS%s: The integral of the normal distribution is greater than %f.\n\r", Format.foreground.green, Format.style.reset, INTEGRAL_BAR);
    }
    return;
}

void print_input_struct(input_struct* pIs){
    printf("\n\rInput struct:======================================\n\r");
    printf("pX_arr:     %p\n\r", pIs->pX_arr);
    printf("pY_arr:     %p\n\r", pIs->pY_arr);
    printf("tmp_file_1: %s\n\r", pIs->tmp_file_1);
    printf("tmp_file_2: %s\n\r", pIs->tmp_file_2);
    return;
}

void cal_norm_dist(norm_dist* pNd, float mu, float sigma, float x_min, float x_max, float integral_step, input_struct* pInput_struct){
    get_norm_dist(pNd, mu, sigma, x_min, x_max, integral_step);
    float* pNorm_dist_x_arr = get_norm_dist_x_arr(pNd);
    pour_arr_to_file(pNorm_dist_x_arr, pNd->arr_length, pInput_struct->tmp_file_1);
    float* pNorm_dist_y_arr = get_norm_dist_y_arr(pNd, pNorm_dist_x_arr);
    pour_arr_to_file(pNorm_dist_y_arr, pNd->arr_length, pInput_struct->tmp_file_2);
    norm_dist_integral(pNd, pNorm_dist_y_arr);
    print_norm_dist(pNd);
    print_input_struct(pInput_struct);
    norm_dist_integral_check(pNd);
}
