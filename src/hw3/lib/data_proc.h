#ifndef DATA_PROC_H
#define DATA_PROC_H

#define MAX_LINE_LENGTH  32
#define COORDINATE_DIM   2
#define MAX_RECORDS      10
#define MAX_CATEGORY     6
#define STR_LEN_FOR_HASH 999
#define HASH_STR_LEN     256

typedef struct {
    int num_rows;
    int num_cols;
    double coord_original[MAX_LINE_LENGTH][COORDINATE_DIM];
    double coord_pan[MAX_LINE_LENGTH][COORDINATE_DIM];
    double coord_zoom[MAX_LINE_LENGTH][COORDINATE_DIM];
    double coord_rotate[MAX_LINE_LENGTH][COORDINATE_DIM];
    float orignal_range[COORDINATE_DIM*2];
    float pan_range[COORDINATE_DIM*2];
    float pan_diff[COORDINATE_DIM];
    float zoom_range[COORDINATE_DIM*2];
    float zoom;
    float rotate_range[COORDINATE_DIM*2];
    float rotate;
} data_t;

typedef struct{
    char line[MAX_RECORDS][HASH_STR_LEN]; // concatenated data string
    char hash[MAX_RECORDS][HASH_STR_LEN];
    int category[MAX_RECORDS];
    int category_count[MAX_CATEGORY];
} history_t;

double remove_neg_zero(double x);

// Clear all data in data_t struct.
void clear_data(data_t *data);

// Give initial values to history_t struct.
void set_history(history_t *history);

void sort_data(data_t *data, int mode);

// Pan the data in data_t struct to x and y. (bottom-left corner)
void pan_data(data_t *data, double x, double y, int mode);

// Zoom the data in data_t struct to specified length. (max length normalization)
// *NOTE: If you want to keep the original location of the data, you should pan the data first.
void zoom_data(data_t *data, double max_length);

void get_range(data_t *data);

// Rotate the data in data_t struct to specified angle. (clockwise)
void rotate_data(data_t *data, double angle_degree);

// Use openssl to hash the zoomed coordinate in data_t struct.
void hash_data(data_t *data, history_t *history, int index, int mode);

// Compare the hash of the zoomed data with previous data.
// If use hash value and num_rows to compare. (try rotating)
// If after rotating hash value is still not the same, different shape.
void classify_data(data_t *data, history_t *history, int index);

void print_data(data_t *data);

void print_history(history_t *history);

#endif // DATA_PROC_H
