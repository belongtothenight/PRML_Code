#include <stdio.h>
#include <stdlib.h>
#include "data_proc.h"
#include "data_plot.h"
#include "normal_distribution.h"

#define MALE_DATA        "./dataset/data_male.csv"
#define FEMALE_DATA      "./dataset/data_female.csv"
#define TEST_IMAGE       "./output/test_image.png"
#define DIV5_MALE_IMG    "./output/div5_p1.png"
#define TMP_DATA_FILE1   "./output/div5_p1_tmp_data1.dat"
#define TMP_DATA_FILE2   "./output/div5_p1_tmp_data2.dat"
#define DIV5_FEMALE_IMG  "./output/div5_p2.png"
#define TMP_DATA_FILE3   "./output/div5_p2_tmp_data3.dat"
#define TMP_DATA_FILE4   "./output/div5_p2_tmp_data4.dat"
#define DIV5_ALL_IMG     "./output/div5_p3.png"
#define TMP_DATA_FILE5   "./output/div5_p3_tmp_data5.dat"
#define TMP_DATA_FILE6   "./output/div5_p3_tmp_data6.dat"
#define INTEGRAL_STEP 0.0001
#define TMP_DATA_FILE7   "./output/div5_p1_tmp_norm_dist_x.dat"
#define TMP_DATA_FILE8   "./output/div5_p1_tmp_norm_dist_y.dat"

int main(void) {
    printf("Program started!\n");
    dataset male_data;
    dataset female_data;
    dataset all_data;

    // initialize data to 0
    initialize_data(&male_data);
    initialize_data(&female_data);
    initialize_data(&all_data);

    // read data
    read_csv(MALE_DATA, &male_data);
    read_csv(FEMALE_DATA, &female_data);
    // combine data
    combine_data(&male_data, &female_data, &all_data);
    printf("All dataset size: %d.\n\r", all_data.size);

    // get stats
    get_stats(&male_data);
    get_stats(&female_data);
    get_stats(&all_data);

    print_data(&male_data, "Male");
    print_data(&female_data, "Female");
    print_data(&all_data, "All");

    // calculate normal distribution
    norm_dist norm_dist_data;
    get_norm_dist(&norm_dist_data, male_data.mu, male_data.sigma, male_data.min, male_data.max, INTEGRAL_STEP);
    print_norm_dist(&norm_dist_data);
    float* pNorm_dist_x_arr = get_norm_dist_x_arr(&norm_dist_data);
    pour_arr_to_file(pNorm_dist_x_arr, norm_dist_data.arr_length, TMP_DATA_FILE7);
    float* pNorm_dist_y_arr = get_norm_dist_y_arr(&norm_dist_data, pNorm_dist_x_arr);
    pour_arr_to_file(pNorm_dist_y_arr, norm_dist_data.arr_length, TMP_DATA_FILE8);

    // plot data
    // test_plot(&male_data, TEST_IMAGE);
    // plot_data_div5(&male_data, DIV5_MALE_IMG, TMP_DATA_FILE1, TMP_DATA_FILE2);
    // plot_data_div5(&female_data, DIV5_FEMALE_IMG, TMP_DATA_FILE3, TMP_DATA_FILE4);
    // plot_data_div5(&all_data, DIV5_ALL_IMG, TMP_DATA_FILE5, TMP_DATA_FILE6);

    // free memory
    free(pNorm_dist_x_arr);
    free(pNorm_dist_y_arr);

    printf("Program ended!\n\r");
    return 0;
}
