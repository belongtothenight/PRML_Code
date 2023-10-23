#include "data_proc.h"

#ifndef DATA_PLOT_H
#define DATA_PLOT_H

/* "qt" for qt terminal, "wxt" for wxt terminal */
#define GNUPLOT_TERMINAL "wxt"

FILE* plot_open();
void plot_close(FILE* gnuplot);
void test_plot(pinky_knuckle_cm* pData, char* pFilename);
void plot_data_vs_normal(pinky_knuckle_cm* pData, char* pFilename);

#endif // DATA_PLOT_H
