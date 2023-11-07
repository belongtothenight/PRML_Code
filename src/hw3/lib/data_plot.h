#ifndef DATA_PLOT_H
#define DATA_PLOT_H

#include <stdio.h>
#include "data_proc.h"

#define PATH_LEN 50

FILE* plot_save_open(char* filename);
void plot_save_close(FILE* gnuplot);
FILE* plot_open(char* filename, float xmin, float xmax, float ymin, float ymax);
void plot_close(FILE* gnuplot);

void plot_shape(int index, data_t *data);

#endif // DATA_PLOT_H
