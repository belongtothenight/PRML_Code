#include <stdio.h>
#include "data_proc.h"
#include "../../libc/output_format.h"

void clear_data(data_t *data){
    for (int i = 0; i < data->num_rows; i++){
        for (int j = 0; j < data->num_cols; j++){
            data->coord_original[i][j] = 0.0;
            data->coord_pan[i][j] = 0.0;
            data->coord_zoom[i][j] = 0.0;
            data->coord_rotate[i][j] = 0.0;
        }
    }
    data->num_rows = 0;
    data->num_cols = 0;
}

void set_data(data_t *data, int num_rows, int num_cols){
    data->num_rows = num_rows;
    data->num_cols = num_cols;
}

void print_data(data_t *data){
    printf("num_rows: %d\n", data->num_rows);
    printf("num_cols: %d\n", data->num_cols);
    printf("coord_original:\n");
    for (int i = 0; i < data->num_rows; i++){
        printf("  %f, %f\n", data->coord_original[i][0], data->coord_original[i][1]);
    }
}
