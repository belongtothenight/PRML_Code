#include <stdio.h>
#include <stdlib.h>
#include "./lib/data_proc.h"
#include "./lib/data_plot.h"
#include "./lib/normal_distribution.h"
#include "./lib/output_csv.h"
#include "./lib/decision_boundary.h"

#define TEST_DATA         "./dataset/data_1.csv"
#define TEST_IMAGE        "./output/test_image.png"
#define DIV5_TEST_IMG     "./output/div5_pt.png"
#define TMP_DATA_FILE1    "./output/div5_pt_tmp_data1.dat"
#define TMP_DATA_FILE2    "./output/div5_pt_tmp_data2.dat"
#define INTEGRAL_STEP     0.000001
// #define INTEGRAL_STEP     0.0001
#define INTERSECTION_STEP 0.000001
#define TMP_DATA_FILE7    "./output/div5_pt_tmp_norm_dist_x.dat"
#define TMP_DATA_FILE8    "./output/div5_pt_tmp_norm_dist_y.dat"
#define OUTPUT_CSV_FILE1  "./output/div5_pt_output.csv"

int main(void) {
    printf("Program started!\n");
    dataset test_data;

    // initialize data to 0
    initialize_data(&test_data);

    // read data
    read_csv(TEST_DATA, &test_data);

    // get stats
    get_stats(&test_data);
    print_data(&test_data, "Test");

    // calculate male normal distribution
    norm_dist norm_dist_data_test;
    input_struct input_struct_data_male;
    input_struct_data_male.tmp_file_1 = TMP_DATA_FILE7;
    input_struct_data_male.tmp_file_2 = TMP_DATA_FILE8;
    cal_norm_dist(&norm_dist_data_test, test_data.mu, test_data.sigma, test_data.min, test_data.max, INTEGRAL_STEP, &input_struct_data_male, "Test");

    // output data to csv
    output_csv(OUTPUT_CSV_FILE1, &test_data, &norm_dist_data_test);

    // plot data
    plot_data_div5(&test_data, DIV5_TEST_IMG, TMP_DATA_FILE1, TMP_DATA_FILE2);

    // free memory
    free_norm_dist(&input_struct_data_male, "Test");

    printf("Program ended!\n\r");
    return 0;
}
