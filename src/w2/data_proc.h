#ifndef DATA_PROC_H
#define DATA_PROC_H

#define MAX_SIZE            40
#define SPLIT_PARTS         5
#define NORMAL_SPLIT_PARTS  6
#define UNIT                "mm"

typedef struct{
    int size;
    float diameter[MAX_SIZE];
    float min;
    float max;
    float mean;
    float variance;
    //
    float split_points[SPLIT_PARTS + 1];
    float split_step;
    float split_points_center[SPLIT_PARTS];
    float split_data[SPLIT_PARTS][MAX_SIZE];
    int split_count[SPLIT_PARTS];
    //
    float normal_split_points[NORMAL_SPLIT_PARTS+1]; // m_p_3std, m_p_2std, m_p_1std, m, m_m_1std, m_m_2std, m_m_3std
    float normal_split_points_center[NORMAL_SPLIT_PARTS + 2];
    float normal_split_data[NORMAL_SPLIT_PARTS+2][MAX_SIZE];
    int normal_split_count[NORMAL_SPLIT_PARTS+2];
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
void get_split_points_center(pinky_knuckle_cm *pData);
void get_split_data(pinky_knuckle_cm* pData);
void get_normal_split_points(pinky_knuckle_cm* pData);
void get_normal_split_points_center(pinky_knuckle_cm* pData);
void get_normal_split_data(pinky_knuckle_cm* pData);
void get_stats(pinky_knuckle_cm* pData);

#endif // DATA_PROC_H
