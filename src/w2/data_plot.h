#include <stdio.h>
#include <stdlib.h>
#include "data_proc.h"

#ifndef DATA_PLOT_H
#define DATA_PLOT_H

/* "qt" for qt terminal, "wxt" for wxt terminal */
#define GNUPLOT_TERMINAL "wxt"
#define TMP_DATA_FILE1   "./output/div5_p1_tmp_data1.dat"
#define TMP_DATA_FILE2   "./output/div5_p1_tmp_data2.dat"

/******************************************************************************************/
// help functions 
FILE* plot_open(char* pFilename);
void plot_close(FILE* gnuplot);
FILE* plot_save_open();
void plot_save_close(FILE *gnuplot);

/******************************************************************************************/
// plot functions
void test_plot(pinky_knuckle_cm* pData, char* pFilename);

// plot div5
void save_data_div5_cnt(pinky_knuckle_cm *pData, char *pFilename);
void save_data_div5_norm(char* pFilename, float x_min, float x_max, float mu, float sigma);
void save_data_div5_vert_grid(char* pFilename, float y_min, float y_max);
void plot_data_div5(pinky_knuckle_cm* pData, char* pFilename);

#endif // DATA_PLOT_H
