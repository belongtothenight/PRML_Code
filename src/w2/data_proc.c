#include <stdio.h>
#include <stdlib.h>
#include "data_proc.h"

void initialize_data(pinky_knuckle_cm* pData){
    pData->size = 0;
    for (int i = 0; i < MAX_SIZE; i++){
        pData->diameter[i] = 0;
    }
    pData->min = 0;
    pData->max = 0;
    pData->mean = 0;
    pData->variance = 0;
    for (int i = 0; i < SPLIT_PARTS + 1; i++){
        pData->split_points[i] = 0;
    }
    pData->split_step = 0;
    for (int i = 0; i < SPLIT_PARTS; i++){
        pData->split_count[i] = 0;
    }
    for (int i = 0; i < SPLIT_PARTS; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            pData->split_data[i][j] = 0;
        }
    }
    return;
}

void read_csv(char* pFilename, pinky_knuckle_cm* pData){
    FILE *fp;
    fp = fopen(pFilename, "r");
    if (fp == NULL){
        printf("Error opening file\n\r");
        exit(1);
    } else {
        printf("Opened %s successfully\n\r", pFilename);
    }
    int read = 0;
    int records = 0;
    do{
        read = fscanf(fp, "%f", &pData->diameter[records]);
        records++;
    } while (!feof(fp));
    pData->size = records - 1;
    fclose(fp);
    return;
}

void combine_data(pinky_knuckle_cm* pMaleData, pinky_knuckle_cm* pFemaleData, pinky_knuckle_cm* pAllData){
    for (int i = 0; i < pMaleData->size; i++){
        pAllData->diameter[i] = pMaleData->diameter[i];
    }
    for (int i = 0; i < pFemaleData->size; i++){
        pAllData->diameter[i + pMaleData->size] = pFemaleData->diameter[i];
    }
    pAllData->size = pMaleData->size + pFemaleData->size;
    return;
}

void print_data(pinky_knuckle_cm* pData, char* pName){
    printf("Printing %s data:===============================\n\r", pName);
    printf("Size:         %d\n\r", pData->size);
    printf("Diameter:     ");
    for (int i = 0; i < pData->size; i++){
        printf("%f ", pData->diameter[i]);
    }
    printf("%s.\n\r", UNIT);
    printf("Min:          %f %s.\n\r", pData->min, UNIT);
    printf("Max:          %f %s.\n\r", pData->max, UNIT);
    printf("Mean:         %f %s.\n\r", pData->mean, UNIT);
    printf("Variance:     %f %s.\n\r", pData->variance, UNIT);
    printf("Split points: ");
    for (int i = 0; i < SPLIT_PARTS + 1; i++){
        printf("%f ", pData->split_points[i]);
    }
    printf("%s.\n\r", UNIT);
    printf("Split step:   %f %s.\n\r", pData->split_step, UNIT);
    printf("Split count:  ");
    for (int i = 0; i < SPLIT_PARTS; i++){
        printf("%d ", pData->split_count[i]);
    }
    printf("\n\r");
    return;
}

void get_min(pinky_knuckle_cm* pData){
    float min = pData->diameter[0];
    for (int i = 1; i < pData->size; i++){
        if (pData->diameter[i] < min){
            min = pData->diameter[i];
        }
    }
    pData->min = min;
    return;
}

void get_max(pinky_knuckle_cm* pData){
    float max = pData->diameter[0];
    for (int i = 1; i < pData->size; i++){
        if (pData->diameter[i] > max){
            max = pData->diameter[i];
        }
    }
    pData->max = max;
    return;
}

void get_mean(pinky_knuckle_cm* pData){
    float sum = 0;
    for (int i = 0; i < pData->size; i++){
        sum += pData->diameter[i];
    }
    pData->mean = sum / pData->size;
    return;
}

void get_variance(pinky_knuckle_cm* pData){
    float sum = 0;
    for (int i = 0; i < pData->size; i++){
        sum += (pData->diameter[i] - pData->mean) * (pData->diameter[i] - pData->mean);
    }
    pData->variance = sum / (pData->size - 1);
    return;
}

void get_split_points(pinky_knuckle_cm* pData){
    float step = (pData->max - pData->min) / SPLIT_PARTS;
    for (int i = 0; i < SPLIT_PARTS + 1; i++){
        pData->split_points[i] = pData->min + i * step;
    }
    pData->split_step = step;
    return;
}

void get_split_data(pinky_knuckle_cm* pData){
    // use split_points to split data into SPLIT_PARTS parts
    for (int i = 0; i < SPLIT_PARTS; i++){
        for (int j = 0; j < pData->size; j++){
            if (pData->diameter[j] >= pData->split_points[i] && pData->diameter[j] < pData->split_points[i + 1]){
                pData->split_data[i][pData->split_count[i]] = pData->diameter[j];
                pData->split_count[i]++;
            }
        }
    }
    return;
}

void get_stats(pinky_knuckle_cm* pData){
    get_min(pData);
    get_max(pData);
    get_mean(pData);
    get_variance(pData);
    get_split_points(pData);
    get_split_data(pData);
    return;
}
