/**
 * @file data_proc.h
 * @brief Data processing functions
*/

#ifndef DATA_PROC_H
#define DATA_PROC_H

#define MAX_LINE_LENGTH  32     ///< max number of points in a line
#define COORDINATE_DIM   2      ///< x, y
#define MAX_RECORDS      10     ///< max number of records in history
#define MAX_CATEGORY     6      ///< max number of categories
#define STR_LEN_FOR_HASH 999    ///< max length of string for hashing
#define HASH_STR_LEN     256    ///< max length of hash string

/**
 * @brief Data struct
 * @details Store the data of a line
*/
typedef struct {
    int num_rows;                                               ///< number of rows
    int num_cols;                                               ///< number of columns
    double coord_original[MAX_LINE_LENGTH][COORDINATE_DIM];     ///< original coordinate
    double coord_pan[MAX_LINE_LENGTH][COORDINATE_DIM];          ///< pan coordinate
    double coord_zoom[MAX_LINE_LENGTH][COORDINATE_DIM];         ///< zoom coordinate
    double coord_rotate[MAX_LINE_LENGTH][COORDINATE_DIM];       ///< rotate coordinate
    float orignal_range[COORDINATE_DIM*2];                      ///< original range
    float pan_range[COORDINATE_DIM*2];                          ///< pan range
    float pan_diff[COORDINATE_DIM];                             ///< pan difference
    float zoom_range[COORDINATE_DIM*2];                         ///< zoom range
    float zoom;                                                 ///< zoom
    float rotate_range[COORDINATE_DIM*2];                       ///< rotate range
    float rotate;                                               ///< rotate
} data_t;

/**
 * @brief Shape history struct
 * @details Store the history of the shape
*/
typedef struct{
    char line[MAX_RECORDS][HASH_STR_LEN];   ///< concatenated data string
    char hash[MAX_RECORDS][HASH_STR_LEN];   ///< hashed data string
    int category[MAX_RECORDS];              ///< category of the data
    int category_count[MAX_CATEGORY];       ///< category count
} history_t;

/**
 * @brief Remove negative zero
 * @details If x is negative zero (-0.0000), return 0.0
*/
double remove_neg_zero(double x);

/**
 * @brief Clear all data in data_t struct
 * @details Clear all data in data_t struct
 * @param data data_t struct
*/
void clear_data(data_t *data);

/**
 * @brief Give initial values to history_t struct
 * @details Give initial values to history_t struct
 * @param history history_t struct
*/
void set_history(history_t *history);

/**
 * @brief Sort the data in data_t struct
 * @details Sort the data in data_t struct
 * @param data data_t struct
 * @param mode 1: zoomed data 2: rotated data
*/
void sort_data(data_t *data, int mode);

/**
 * @brief Pan the data in data_t struct to x and y. (bottom-left corner)
 * @details Pan the data in data_t struct to x and y. (bottom-left corner)
 * @param data data_t struct
 * @param x x
 * @param y y
 * @param mode 1: zoomed data 2: rotated data
*/
void pan_data(data_t *data, double x, double y, int mode);

/**
 * @brief Zoom the data in data_t struct to specified length. (max length normalization)
 * @details Zoom the data in data_t struct to specified length. (max length normalization) NOTE: If you want to keep the original location of the data, you should pan the data first.
 * @param data data_t struct
 * @param max_length max length
*/
void zoom_data(data_t *data, double max_length);

/**
 * @brief Get the range of the data in data_t struct.
 * @details Get the range of the data in data_t struct.
 * @param data data_t struct
*/
void get_range(data_t *data);

/**
 * @brief Rotate the data in data_t struct to specified angle. (clockwise)
 * @details Rotate the data in data_t struct to specified angle. (clockwise)
 * @param data data_t struct
 * @param angle_degree angle in degree
*/
void rotate_data(data_t *data, double angle_degree);

/**
 * @brief Use openssl to hash the zoomed coordinate in data_t struct.
 * @details Use openssl to hash the zoomed or rotated coordinate in data_t struct.
 * @param data data_t struct
 * @param history history_t struct
 * @param index index of the data in history
 * @param mode 1: zoomed data 2: rotated data
*/
void hash_data(data_t *data, history_t *history, int index, int mode);

/**
 * @brief Classify the data in data_t struct.
 * @details Classify the data in data_t struct.
 * @param data data_t struct
 * @param history history_t struct
 * @param index index of the data in history
*/
void classify_data(data_t *data, history_t *history, int index);

/**
 * @brief Print the data in data_t struct.
 * @details Print the data in data_t struct.
 * @param data data_t struct
*/
void print_data(data_t *data);

/**
 * @brief Print the history in history_t struct.
 * @details Print the history in history_t struct.
 * @param history history_t struct
*/
void print_history(history_t *history);

#endif // DATA_PROC_H
