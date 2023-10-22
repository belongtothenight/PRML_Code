#ifndef DATA_PROC_H
#define DATA_PROC_H

#define MAX_SIZE     40
#define SPLIT_PARTS  5
#define UNIT         "mm"

typedef struct{
    int size;
    float diameter[MAX_SIZE];
    float min;
    float max;
    float mean;
    float variance;
    float split_points[SPLIT_PARTS + 1];
    float split_step;
    float split_data[SPLIT_PARTS][MAX_SIZE];
    int split_count[SPLIT_PARTS];
} pinky_knuckle_cm;

void initialize_data(pinky_knuckle_cm* pData);
void read_csv(char* pFilename, pinky_knuckle_cm* pData);
void combine_data(pinky_knuckle_cm* pMaleData, pinky_knuckle_cm* pFemaleData, pinky_knuckle_cm* pAllData);
void print_data(pinky_knuckle_cm* pData, char* pName);
void get_min(pinky_knuckle_cm* pData);
void get_max(pinky_knuckle_cm* pData);
void get_mean(pinky_knuckle_cm* pData);
void get_variance(pinky_knuckle_cm* pData);
void get_split_points(pinky_knuckle_cm* pData);
void get_split_data(pinky_knuckle_cm* pData);
void get_stats(pinky_knuckle_cm* pData);

#endif
