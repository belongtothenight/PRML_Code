#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_proc.h"
#include "output_format.h"

void initialize_data(dataset* pData){
    pData->size = 0;
    for (int i = 0; i < MAX_SIZE; i++){
        pData->data_element[i] = 0;
    }
    pData->min = 0;
    pData->max = 0;
    pData->mean = 0;
    pData->variance_biased = 0;
    pData->variance_unbiased = 0;
    pData->mu = 0;
    pData->sigma = 0;
    for (int i = 0; i < SPLIT_PARTS + 1; i++){
        pData->split_points[i] = 0;
    }
    pData->split_step = 0;
    for (int i = 0; i < SPLIT_PARTS; i++){
        pData->split_count[i] = 0;
    }
    for (int i = 0; i < SPLIT_PARTS; i++){
        pData->split_points_center[i] = 0;
    }
    for (int i = 0; i < SPLIT_PARTS; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            pData->split_data[i][j] = 0;
        }
    }
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 1; i++){
        pData->normal_split_points[i] = 0;
    }
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 2; i++){
        pData->normal_split_points_center[i] = 0;
    }
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 2; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            pData->normal_split_data[i][j] = 0;
        }
    }
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 2; i++){
        pData->normal_split_count[i] = 0;
    }
    return;
}

void read_csv(char* pFilename, dataset* pData){
    output_format Format;
    get_format(&Format);
    FILE *fp;
    fp = fopen(pFilename, "r");
    if (fp == NULL){
        printf("%sERROR%s: Failed to open file %s.\n\r", Format.foreground.red, Format.style.reset, pFilename);
        exit(1);
    } else {
        printf("%sSUCCESS%s: File %s opened.\n\r", Format.foreground.green, Format.style.reset, pFilename);
    }
    int read = 0;
    int records = 0;
    do{
        read = fscanf(fp, "%f", &pData->data_element[records]);
        records++;
    } while (!feof(fp));
    pData->size = records - 1;
    fclose(fp);
    printf("%sSUCCESS%s: File %s closed.\n\r", Format.foreground.green, Format.style.reset, pFilename);
    return;
}

void combine_data(dataset* pMaleData, dataset* pFemaleData, dataset* pAllData){
    for (int i = 0; i < pMaleData->size; i++){
        pAllData->data_element[i] = pMaleData->data_element[i];
    }
    for (int i = 0; i < pFemaleData->size; i++){
        pAllData->data_element[i + pMaleData->size] = pFemaleData->data_element[i];
    }
    pAllData->size = pMaleData->size + pFemaleData->size;
    return;
}

void print_data(dataset* pData, char* pName){
    printf("\n\rPrinting %s data:===============================\n\r", pName);
    printf("Size:                       %d\n\r", pData->size);
    printf("Min:                        %f %s.\n\r", pData->min, UNIT);
    printf("Max:                        %f %s.\n\r", pData->max, UNIT);
    printf("Mean:                       %f %s.\n\r", pData->mean, UNIT);
    printf("Variance_biased:            %f %s.\n\r", pData->variance_biased, UNIT);
    printf("Variance_unbiased:          %f %s.\n\r", pData->variance_unbiased, UNIT);
    printf("Mu:                         %f %s.\n\r", pData->mu, UNIT);
    printf("Sigma:                      %f %s.\n\r", pData->sigma, UNIT);
    printf("Split points:               ");
    for (int i = 0; i < SPLIT_PARTS + 1; i++){
        printf("%f ", pData->split_points[i]);
    }
    printf("%s.\n\r", UNIT);
    printf("Split step:                 %f %s.\n\r", pData->split_step, UNIT);
    printf("Split points center:        ");
    for (int i = 0; i < SPLIT_PARTS; i++){
        printf("%f ", pData->split_points_center[i]);
    }
    printf("%s.\n\r", UNIT);
    printf("Split count:                ");
    for (int i = 0; i < SPLIT_PARTS; i++){
        printf("%d ", pData->split_count[i]);
    }
    printf("\n\r");
    printf("Normal split points center: ");
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 2; i++){
        printf("%f ", pData->normal_split_points_center[i]);
    }
    printf("%s.\n\r", UNIT);
    printf("Normal split points:        ");
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 1; i++){
        printf("%f ", pData->normal_split_points[i]);
    }
    printf("%s.\n\r", UNIT);
    printf("Norm split cnt:             ");
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 2; i++){
        printf("%d ", pData->normal_split_count[i]);
    }
    printf("\n\r");
    return;
}

void get_min(dataset* pData){
    float min = pData->data_element[0];
    for (int i = 1; i < pData->size; i++){
        if (pData->data_element[i] < min){
            min = pData->data_element[i];
        }
    }
    pData->min = min;
    return;
}

void get_max(dataset* pData){
    float max = pData->data_element[0];
    for (int i = 1; i < pData->size; i++){
        if (pData->data_element[i] > max){
            max = pData->data_element[i];
        }
    }
    pData->max = max;
    return;
}

void get_mean(dataset* pData){
    float sum = 0;
    for (int i = 0; i < pData->size; i++){
        sum += pData->data_element[i];
    }
    pData->mean = sum / pData->size;
    pData->mu = pData->mean;
    return;
}

void get_variance(dataset* pData){
    // sigma^2
    float sum = 0;
    for (int i = 0; i < pData->size; i++){
        sum += (pData->data_element[i] - pData->mean) * (pData->data_element[i] - pData->mean);
    }
    pData->variance_biased = sum / (pData->size);
    pData->variance_unbiased = sum / (pData->size - 1);
    return;
}

void get_sigma(dataset* pData){
    float sum = 0;
    for (int i = 0; i < pData->size; i++){
        sum += (pData->data_element[i] - pData->mean) * (pData->data_element[i] - pData->mean);
    }
    pData->sigma = sqrt(sum / (pData->size));
    return;
}

void get_split_points(dataset* pData){
    float step = (pData->max - pData->min) / SPLIT_PARTS;
    for (int i = 0; i < SPLIT_PARTS + 1; i++){
        pData->split_points[i] = pData->min + i * step;
    }
    pData->split_step = step;
    return;
}

void get_split_points_center(dataset* pData){
    float step = pData->split_step;
    for (int i = 0; i < SPLIT_PARTS; i++){
        pData->split_points_center[i] = pData->split_points[0] + 0.5 * step + i * step;
    }
    return;
}

void get_split_data(dataset* pData){
    // use split_points to split data into SPLIT_PARTS parts
    for (int j = 0; j < pData->size; j++){
        for (int i = 0; i < SPLIT_PARTS; i++){
            if (pData->data_element[j] >= pData->split_points[i] && pData->data_element[j] < pData->split_points[i + 1]){
                pData->split_data[i][pData->split_count[i]] = pData->data_element[j];
                pData->split_count[i]++;
            }
        }
        if (pData->data_element[j] == pData->split_points[SPLIT_PARTS]){
            pData->split_data[SPLIT_PARTS - 1][pData->split_count[SPLIT_PARTS - 1]] = pData->data_element[j];
            pData->split_count[SPLIT_PARTS - 1]++;
        }
    }
    return;
}

void split_data_checker(dataset* pData){
    output_format Format;
    get_format(&Format);
    int sum = 0;
    for (int i = 0; i < SPLIT_PARTS; i++){
        sum += pData->split_count[i];
    }
    if (sum != pData->size){
        printf("%sFAIL%s: Split data check failed!\n\r", Format.foreground.red, Format.style.reset);
        exit(1);
    } else {
        printf("%sPASS%s: Split data check!\n\r", Format.foreground.green, Format.style.reset);
    }
    return;
}

void get_normal_split_points(dataset* pData){
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 1; i++){
        pData->normal_split_points[i] = pData->mean + (i - 3) * pData->variance_unbiased;
    }
    return;
}

void get_normal_split_points_center(dataset* pData){
    float normal_step = pData->variance_unbiased;
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 2; i++){
        pData->normal_split_points_center[i] = pData->normal_split_points[0] - 0.5 * normal_step + i * normal_step;
    }
    return;
}

void get_normal_split_data(dataset* pData){
    // use normal distribution to split data into normal_split_data parts
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 1; i++){
        for (int j = 0; j < pData->size; j++){
            if (pData->data_element[j] >= pData->normal_split_points[i] && pData->data_element[j] < pData->normal_split_points[i + 1]){
                pData->normal_split_data[i][pData->normal_split_count[i]] = pData->data_element[j];
                pData->normal_split_count[i+1]++;
            }
        }
    }
    for (int i = 0; i < pData->size; i++){
        if (pData->data_element[i] < pData->normal_split_points[0]){
            pData->normal_split_data[0][pData->normal_split_count[0]] = pData->data_element[i];
            pData->normal_split_count[0]++;
        } else if (pData->data_element[i] >= pData->normal_split_points[NORMAL_SPLIT_PARTS]){
            pData->normal_split_data[NORMAL_SPLIT_PARTS+1][pData->normal_split_count[NORMAL_SPLIT_PARTS+1]] = pData->data_element[i];
            pData->normal_split_count[NORMAL_SPLIT_PARTS+1]++;
        } else {
            continue;
        }
    }
    return;
}

void get_stats(dataset* pData){
    get_min(pData);
    get_max(pData);
    get_mean(pData);
    get_variance(pData);
    get_sigma(pData);
    get_split_points(pData);
    get_split_points_center(pData);
    get_split_data(pData);
    split_data_checker(pData);
    get_normal_split_points(pData);
    get_normal_split_points_center(pData);
    get_normal_split_data(pData);
    return;
}
