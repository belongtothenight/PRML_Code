#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../libc/common_macro.h"
#include "../libc/output_format.h"
#include "./lib/read_csv.h"
#include "./lib/data_proc.h"

#define NUM_SHAPES 6

// *NOTE: Configure the following two arrays to match the number of shapes and their filenames.
char *filenames[NUM_SHAPES] = {
    "E:/GitHub/PRML_Code/src/dataset/shape1.csv",
    "E:/GitHub/PRML_Code/src/dataset/shape2.csv",
    "E:/GitHub/PRML_Code/src/dataset/shape3.csv",
    "E:/GitHub/PRML_Code/src/dataset/shape4.csv",
    "E:/GitHub/PRML_Code/src/dataset/shape5.csv",
    "E:/GitHub/PRML_Code/src/dataset/shape6.csv"
};
int num_rows[NUM_SHAPES] = {5, 7, 5, 5, 7, 7};

// !NOTE: Do not modify the following parameters.
csv_t shapes[NUM_SHAPES];
data_t datas[NUM_SHAPES];
output_format format;

int main(void){    
    get_format(&format);
    for(int i = 0; i < NUM_SHAPES; i++){
        printf("Setting csv_t struct for %s...\n", filenames[i]);
        set_csv(&shapes[i], filenames[i], num_rows[i]);
        read_csv(&shapes[i], &datas[i]);
        print_csv(&shapes[i]);
    }
    return 0;
}
