#ifndef DATA_PROC_H
#define DATA_PROC_H

#define MAX_LINE_LENGTH 32
#define COORDINATE_DIM  2

typedef struct {
    int num_rows;
    int num_cols;
    float coord_original[MAX_LINE_LENGTH][COORDINATE_DIM];
    float coord_pan[MAX_LINE_LENGTH][COORDINATE_DIM];
    float coord_zoom[MAX_LINE_LENGTH][COORDINATE_DIM];
    float coord_rotate[MAX_LINE_LENGTH][COORDINATE_DIM];
} data_t;

void clear_data(data_t *data);

void set_data(data_t *data, int num_rows, int num_cols);

void print_data(data_t *data);

#endif // DATA_PROC_H
