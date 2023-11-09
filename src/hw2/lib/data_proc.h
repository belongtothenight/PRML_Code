/**
 * @file data_proc.h
 * @brief Data processing functions for hw2
*/

#ifndef DATA_PROC_H
#define DATA_PROC_H

#define MAX_SIZE            1000    ///< Maximum number of data
#define SPLIT_PARTS         5       ///< Number of split parts
#define NORMAL_SPLIT_PARTS  6       ///< Number of normal split parts
#define UNIT                "mm"    ///< Unit of the data

/**
 * @brief Data struct for hw2
 * @details This struct contains all the data for hw2.
*/
typedef struct{
    int size;                                                   ///< Number of data
    float data_element[MAX_SIZE];                               ///< Data array
    float min;                                                  ///< Minimum value
    float max;                                                  ///< Maximum value
    float mean;                                                 ///< Mean value
    float variance_biased;                                      ///< Biased variance
    float variance_unbiased;                                    ///< Unbiased variance
    float mu;                                                   ///< Mean of the normal distribution
    float sigma;                                                ///< standard deviation
    //
    float split_points[SPLIT_PARTS + 1];                        ///< Split points
    float split_step;                                           ///< Split step
    float split_points_center[SPLIT_PARTS];                     ///< Split points center
    float split_data[SPLIT_PARTS][MAX_SIZE];                    ///< Split data
    int split_count[SPLIT_PARTS];                               ///< Split data count
    //
    float normal_split_points[NORMAL_SPLIT_PARTS+1];            ///< m_p_3std, m_p_2std, m_p_1std, m, m_m_1std, m_m_2std, m_m_3std
    float normal_split_points_center[NORMAL_SPLIT_PARTS + 2];   ///< Normal split points center
    float normal_split_data[NORMAL_SPLIT_PARTS+2][MAX_SIZE];    ///< Normal split data
    int normal_split_count[NORMAL_SPLIT_PARTS+2];               ///< Normal split data count
} dataset;

/**
 * @brief Initialize data struct
 * @details This function initializes the data struct.
 * @param pData Pointer to the data struct
*/
void initialize_data(dataset* pData);

/**
 * @brief Read csv file
 * @details This function reads the csv file and stores the data in the data struct.
 * @param pFilename Pointer to the file name
 * @param pData Pointer to the data struct
*/
void read_csv(char* pFilename, dataset* pData);

/**
 * @brief Combine data
 * @details Combines two data sets into one.
 * @param pMaleData Pointer to first data set
 * @param pFemaleData Pointer to second data set
 * @param pAllData Pointer to combined data set
*/
void combine_data(dataset* pMaleData, dataset* pFemaleData, dataset* pAllData);

/**
 * @brief Print data
 * @details This function prints the data in the data struct.
 * @param pData Pointer to the data struct
 * @param pName Pointer to the name of the data set
*/
void print_data(dataset* pData, char* pName);

/**
 * @brief Get minimum
 * @details This function gets the minimum value of the data set.
 * @param pData Pointer to the data struct
*/
void get_min(dataset* pData);

/**
 * @brief Get maximum
 * @details This function gets the maximum value of the data set.
 * @param pData Pointer to the data struct
*/
void get_max(dataset* pData);

/**
 * @brief Get mean
 * @details This function gets the mean value of the data set.
 * @param pData Pointer to the data struct
*/
void get_mean(dataset* pData);

/**
 * @brief Get biased variance
 * @details This function gets the biased variance of the data set.
 * @param pData Pointer to the data struct
*/
void get_variance(dataset* pData);

/**
 * @brief Get unbiased variance
 * @details This function gets the unbiased variance of the data set.
 * @param pData Pointer to the data struct
*/
void get_sigma(dataset* pData);

/**
 * @brief Get split points that split the data into 5 parts
 * @details This function gets the split points that split the data into 5 parts.
 * @param pData Pointer to the data struct
*/
void get_split_points(dataset* pData);

/**
 * @brief Get split points center (5 parts)
 * @details This function gets the split points center.
 * @param pData Pointer to the data struct
*/
void get_split_points_center(dataset *pData);

/**
 * @brief Get split data (5 parts)
 * @details This function gets the split data.
 * @param pData Pointer to the data struct
*/
void get_split_data(dataset* pData);

/**
 * @brief Get split data count (5 parts)
 * @details This function gets the split data count.
 * @param pData Pointer to the data struct
*/
void split_data_checker(dataset* pData);

/**
 * @brief Get normal split points that split the data into 6 parts
 * @details This function gets the normal split points that split the data into 6 parts.
 * @param pData Pointer to the data struct
*/
void get_normal_split_points(dataset* pData);

/**
 * @brief Get normal split points center (6 parts)
 * @details This function gets the normal split points center.
 * @param pData Pointer to the data struct
*/
void get_normal_split_points_center(dataset* pData);

/**
 * @brief Get normal split data (6 parts)
 * @details This function gets the normal split data.
 * @param pData Pointer to the data struct
*/
void get_normal_split_data(dataset* pData);

/**
 * @brief Get normal split data count (6 parts)
 * @details This function gets the normal split data count.
 * @param pData Pointer to the data struct
*/
void get_stats(dataset* pData);

#endif // DATA_PROC_H
