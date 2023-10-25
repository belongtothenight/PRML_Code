#include <stdio.h>
#include <stdlib.h>
#include "data_proc.h"
#include "decision_boundary.h"

#ifndef DATA_PLOT_H
#define DATA_PLOT_H

/* "qt" for qt terminal, "wxt" for wxt terminal */
#define GNUPLOT_TERMINAL "wxt enhanced"

/******************************************************************************************/
// help functions 
FILE* plot_open(char* pFilename);
void plot_close(FILE* gnuplot);
FILE* plot_save_open();
void plot_save_close(FILE *gnuplot);

/******************************************************************************************/
// plot functions
void test_plot(dataset* pData, char* pFilename);

// save data to file
void save_data_div5_cnt(dataset *pData, char *pFilename);
void save_data_div5_norm(char* pFilename, float x_min, float x_max, float mu, float sigma);
void save_data_vertical_line(char* pFilename, float x, float y1, float y2);

// plot div5
void plot_data_div5(dataset* pData, char* pFilename, char* pTMP1, char* pTMP2);
void plot_stacked_data_div5(dataset* pData1, dataset* pData2, intersection* pITS, char* pFilename, char* pTMP1, char* pTMP2, char* pTMP3);

#endif // DATA_PLOT_H
