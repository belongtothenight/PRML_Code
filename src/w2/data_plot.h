#include <stdio.h>
#include <stdlib.h>
#include "data_proc.h"

#ifndef DATA_PLOT_H
#define DATA_PLOT_H

/* "qt" for qt terminal, "wxt" for wxt terminal */
#define GNUPLOT_TERMINAL "wxt"
#define TMP_DATA_FILE1   "./output/tmp_data1.dat"
#define TMP_DATA_FILE2   "./output/tmp_data2.dat"

FILE* plot_open(char* pFilename);
void plot_close(FILE* gnuplot);
FILE* plot_save_open();
void plot_save_close(FILE *gnuplot);
void test_plot(pinky_knuckle_cm* pData, char* pFilename);
void save_data_as_text(pinky_knuckle_cm *pData, char *pFilename);
void save_line_as_text(char* pFilename, float x_min, float x_max, float mu, float sigma);
void plot_data_vs_normal(pinky_knuckle_cm* pData, char* pFilename);

#endif // DATA_PLOT_H
