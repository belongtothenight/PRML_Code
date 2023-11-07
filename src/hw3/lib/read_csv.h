#ifndef READ_CSV_H
#define READ_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data_proc.h"

typedef struct {
    char *filename; // path to csv file
    int num_rows;
    int num_cols;
    bool read_flag;
} csv_t;

void set_csv(csv_t *csv, char *filename);

void read_csv(csv_t *csv, data_t *data);

void print_csv(csv_t *csv);

#endif // READ_CSV_H
