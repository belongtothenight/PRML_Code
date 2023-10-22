#include <stdio.h>
#include <stdlib.h>
#include "data_proc.h"
#include "data_plot.h"

#define MALE_DATA    "./dataset/data_male.csv"
#define FEMALE_DATA  "./dataset/data_female.csv"
#define TEST_IMAGE   "./output/test_image.png"

int main(void) {
    printf("Program started!\n");
    pinky_knuckle_cm male_data;
    pinky_knuckle_cm female_data;
    pinky_knuckle_cm all_data;

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

    // plot data
    test_plot(&male_data, TEST_IMAGE);

    printf("Program ended!\n\r");
    return 0;
}
