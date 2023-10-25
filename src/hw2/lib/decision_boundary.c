#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "normal_distribution.h"
#include "decision_boundary.h"

float cal_portion_integral(norm_dist* pND, float* y_arr, int start, int end){
    float integral = 0.0f;
    for (int i = start; i < end; i++){
        integral += pND->integral_step * (y_arr[i] + y_arr[i + 1]) / 2;
    }
    return integral;
}

void cal_intersection(norm_dist* pND1, norm_dist* pND2, float* y_arr1, float* y_arr2, intersection* pIntersection){
    for (int i = 0; i < pND1->arr_length; i++){
        if (y_arr2[i] > y_arr1[i]){
            pIntersection->idx1 = i;
            pIntersection->y1 = y_arr1[i];
            pIntersection->x1 = pND1->x_min + i * pND1->integral_step;
            break;
        }
    }
    for (int i = pND2->arr_length-1; i >= 0; i--){
        if (y_arr1[i] > y_arr2[i]){
            pIntersection->idx2 = i;
            pIntersection->y2 = y_arr2[i];
            pIntersection->x2 = pND2->x_min + i * pND2->integral_step;
            break;
        }
    }
    return;
}

void get_intersection(input_struct* pIS1, norm_dist* pND1, input_struct* pIS2, norm_dist* pND2, intersection* pIntersection){
    pIntersection->min_error = 0.0f;
    bool is_nd1_larger = false;
    // 1. find which normal distribution has larger mu
    if (pND1->mu > pND2->mu){
        is_nd1_larger = true;
    }
    // 2. exchange the two normal distributions by swapping pointers based on the result of 1.
    if (is_nd1_larger){
        norm_dist* pND_temp = pND1;
        pND1 = pND2;
        pND2 = pND_temp;
        input_struct* pIS_temp = pIS1;
        pIS1 = pIS2;
        pIS2 = pIS_temp;
    }
    // 3. calculate the intersection of the two normal distributions
    cal_intersection(pND1, pND2, pIS1->pY_arr, pIS2->pY_arr, pIntersection);
    // 4. calculate the portion integral of the two normal distributions
    pIntersection->min_error += cal_portion_integral(pND1, pIS1->pY_arr, pIntersection->idx1, pND1->arr_length-1) / pND1->integral;
    pIntersection->min_error += cal_portion_integral(pND2, pIS2->pY_arr, 0, pIntersection->idx2) / pND2->integral;
    // 5. calculate the average x value of the two normal distributions
    pIntersection->avg_x = (pIntersection->x1 + pIntersection->x2) / 2;
    return;
}
