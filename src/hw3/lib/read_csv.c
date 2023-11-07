#include <stdio.h>
#include <stdlib.h>
#include "read_csv.h"
#include "data_proc.h"
#include "../../libc/output_format.h"

void set_csv(csv_t *csv, char *filename, int num_rows){
    output_format format;
    get_format(&format);
    csv->filename = filename;
    csv->num_rows = num_rows;
    csv->num_cols = COORDINATE_DIM;
    csv->read_flag = false;
    printf("%scsv_t struct has been set.\n", format.status.success);
}

void read_csv(csv_t *csv, data_t *data){
    output_format format;
    get_format(&format);
    FILE *fp = fopen(csv->filename, "r");
    if (fp == NULL){
        printf("%sFailed to open %s.\n", format.status.error, csv->filename);
        exit(1);
    } else {
        printf("%s%s has been opened.\n", format.status.success, csv->filename);
    }

    for (int i = 0; i < csv->num_rows; i++){
        fscanf(fp, "%f,%f", &data->coord_original[i][0], &data->coord_original[i][1]);
    }
    csv->read_flag = true;
}

void print_csv(csv_t *csv){
    printf("filename: %s\n", csv->filename);
    printf("num_rows: %d\n", csv->num_rows);
    printf("num_cols: %d\n", csv->num_cols);
    printf("read_flag: %d\n", csv->read_flag);
}