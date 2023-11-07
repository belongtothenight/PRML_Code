#include <stdio.h>
#include "data_proc.h"
#include "../../libc/output_format.h"

void set_data(data_t *data, int num_rows, int num_cols){
    data->num_rows = num_rows;
    data->num_cols = num_cols;
}
