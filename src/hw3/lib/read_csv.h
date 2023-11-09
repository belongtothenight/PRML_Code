/**
 * @file read_csv.h
 * @brief Read csv file related utilities
*/

#ifndef READ_CSV_H
#define READ_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data_proc.h"

/**
 * @brief csv_t struct
 * @details csv_t struct for csv file reading
*/
typedef struct {
    char *filename; ///< path to csv file
    int num_rows;   ///< number of rows
    int num_cols;   ///< number of columns
    bool read_flag; ///< read flag
} csv_t;

/**
 * @brief Set csv_t struct
 * @details Set csv_t struct element filename
 * @param csv csv_t struct
 * @param filename path to csv file
*/
void set_csv(csv_t *csv, char *filename);

/**
 * @brief Read csv file
 * @details Read csv file with csv_t settings and store data to data_t struct
 * @param csv csv_t struct
 * @param data data_t struct
*/
void read_csv(csv_t *csv, data_t *data);

/**
 * @brief Print csv file
 * @details Print csv_t settings
 * @param csv csv_t struct
*/
void print_csv(csv_t *csv);

#endif // READ_CSV_H
