#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../libc/common_macro.h"
#include "../libc/output_format.h"
#include "./lib/read_csv.h"
#include "./lib/data_proc.h"
#include "./lib/data_plot.h"

// *NOTE: Configure the following two arrays to match the number of shapes and their filenames.
// int num_rows[NUM_SHAPES] = {5, 7, 5, 5, 7, 7};

// !NOTE: Do not modify the following parameters.
csv_t shape;
data_t data;
history_t history;
output_format format;

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
