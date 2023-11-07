#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../libc/common_macro.h"
#include "../libc/output_format.h"
#include "./lib/read_csv.h"
#include "./lib/data_proc.h"

// *NOTE: Configure the following two arrays to match the number of shapes and their filenames.
// int num_rows[NUM_SHAPES] = {5, 7, 5, 5, 7, 7};

// !NOTE: Do not modify the following parameters.
csv_t shape;
data_t data;
output_format format;

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("%sUsage: %s [<filename>...]\n", format.status.error, argv[0]);
        exit(1);
    }
    get_format(&format);

    for (int i = 1; i < argc; i++){
        char *filename = argv[i];
        printf("Setting csv_t struct for %s...\n", filename);
        clear_data(&data);
        set_csv(&shape, filename);
        set_data(&data, shape.num_rows, shape.num_cols);
        read_csv(&shape, &data);
        print_csv(&shape);
        print_data(&data);
    }
    return 0;
}
