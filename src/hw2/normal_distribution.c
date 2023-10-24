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
    pNd->cdf = 0;
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
    printf("cdf:           %f\n\r", pNd->cdf);
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

float norm_dist_cdf(norm_dist* pNd, float x){

}

void norm_dist_cdf_check(norm_dist* pNd){

}
