/**
 * @file main.c
 * @brief Main function of hw3 - 2 dimensional shape classification.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../libc/common_macro.h"
#include "../libc/output_format.h"
#include "./lib/read_csv.h"
#include "./lib/data_proc.h"
#include "./lib/data_plot.h"

csv_t shape;            ///< csv_t struct
data_t data;            ///< data_t struct
history_t history;      ///< history_t struct
output_format format;   ///< output_format struct

/**
 * @brief main function
 * @param argc argument count
 * @param argv argument vector
 * @return 0
 */
int main(int argc, char *argv[]){
    get_format(&format);
    if (argc < 2){
        printf("%sUsage: %s [<filename>...]\n", format.status.error, argv[0]);
        exit(1);
    }
    set_history(&history);

    for (int i = 1; i < argc; i++){
        char *filename = argv[i];
        printf("Setting csv_t struct for %s...\n", filename);
        clear_data(&data);
        set_csv(&shape, filename);
        read_csv(&shape, &data);
        print_csv(&shape);
        pan_data(&data, 0, 0, 1);
        zoom_data(&data, 1);
        classify_data(&data, &history, i-1);
        print_data(&data);
        // print_history(&history);
        get_range(&data);
        plot_shape(i, &data);
    }
    print_history(&history);
    return 0;
}
