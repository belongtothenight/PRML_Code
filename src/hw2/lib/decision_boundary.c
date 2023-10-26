#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "normal_distribution.h"
#include "decision_boundary.h"

float cal_prob(norm_dist* pND, float x){
    return (float)(1 / (pND->sigma * sqrt(2 * acos(-1))) * exp(-pow(x - pND->mu, 2) / (2 * pow(pND->sigma, 2))));
}

float cal_portion_integral(norm_dist* pND, intersection* pIST, float start, float end){
    float integral = 0.0f;
    // for (int i = start; i < end; i++){
    //     integral += pND->integral_step * (y_arr[i] + y_arr[i + 1]) / 2;
    // }
    for (float x = start; x <= end; x += pIST->step){
        integral += pIST->step * (cal_prob(pND, x) + cal_prob(pND, x + pIST->step)) / 2;
    }
    return integral;
}

void cal_intersection(norm_dist* pND1, norm_dist* pND2, intersection* pIntersection){
    for (float x = pND1->x_min; x <= pND1->x_max; x += pIntersection->step){
        float y1 = cal_prob(pND1, x);
        float y2 = cal_prob(pND2, x);
        if (y2 > y1){
            pIntersection->y1 = y1;
            pIntersection->x1 = x;
            break;
        }
    }
    for (float x = pND2->x_max; x >= pND2->x_min; x -= pIntersection->step){
        float y1 = cal_prob(pND1, x);
        float y2 = cal_prob(pND2, x);
        if (y1 > y2){
            pIntersection->y2 = y2;
            pIntersection->x2 = x;
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
    cal_intersection(pND1, pND2, pIntersection);
    // 4. calculate the average x value of the two normal distributions
    pIntersection->avg_x = (pIntersection->x1 + pIntersection->x2) / 2;
    // 5. calculate the portion integral of the two normal distributions
    //! TODO: fix the bug here, probability is somehow 0 for some reason
    //! Fix: P(x|w1) + P(x|w2)
    printf("cal1 x1: %f, x2: %f\n\r", pIntersection->avg_x, pND1->x_max);
    printf("cal1: %f\n\r", cal_portion_integral(pND1, pIntersection, pIntersection->avg_x, pND1->x_max)); // P(x|w2)
    printf("cal2 x1: %f, x2: %f\n\r", pIntersection->avg_x, pND2->x_max);
    printf("cal2: %f\n\r", cal_portion_integral(pND2, pIntersection, pIntersection->avg_x, pND2->x_max)); // P(w2)
    printf("cal3 x1: %f, x2: %f\n\r", pND2->x_min, pIntersection->avg_x);
    printf("cal3: %f\n\r", cal_portion_integral(pND2, pIntersection, pND2->x_min, pIntersection->avg_x)); // P(x|w1)
    printf("cal4 x1: %f, x2: %f\n\r", pND1->x_min, pIntersection->avg_x);
    printf("cal4: %f\n\r", cal_portion_integral(pND1, pIntersection, pND1->x_min, pIntersection->avg_x)); // P(w1)
    pIntersection->min_error += cal_portion_integral(pND1, pIntersection, pIntersection->avg_x, pND1->x_max) / cal_portion_integral(pND2, pIntersection, pIntersection->avg_x, pND2->x_max);
    pIntersection->min_error += cal_portion_integral(pND2, pIntersection, pND2->x_min, pIntersection->avg_x) / cal_portion_integral(pND1, pIntersection, pND1->x_min, pIntersection->avg_x);
    
    return;
}
