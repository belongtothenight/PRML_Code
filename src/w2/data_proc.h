#ifndef DATA_PROC_H
#define DATA_PROC_H

#define MAX_SIZE            40
#define SPLIT_PARTS         5
#define NORMAL_SPLIT_PARTS  6
#define UNIT                "mm"

typedef struct{
    int size;
    float data_element[MAX_SIZE];
    float min;
    float max;
    float mean;
    float variance_biased;
    float variance_unbiased;
    float mu;
    float sigma;
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
} dataset;

void initialize_data(dataset* pData);
void read_csv(char* pFilename, dataset* pData);
void combine_data(dataset* pMaleData, dataset* pFemaleData, dataset* pAllData);
void print_data(dataset* pData, char* pName);
void get_min(dataset* pData);
void get_max(dataset* pData);
void get_mean(dataset* pData);
void get_variance(dataset* pData);
void get_sigma(dataset* pData);
void get_split_points(dataset* pData);
void get_split_points_center(dataset *pData);
void get_split_data(dataset* pData);
void split_data_checker(dataset* pData);
void get_normal_split_points(dataset* pData);
void get_normal_split_points_center(dataset* pData);
void get_normal_split_data(dataset* pData);
void get_stats(dataset* pData);

#endif // DATA_PROC_H
