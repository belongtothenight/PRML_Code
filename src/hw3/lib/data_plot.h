/**
 * @file data_plot.h
 * @brief Data plot functions
*/

#ifndef DATA_PLOT_H
#define DATA_PLOT_H

#include <stdio.h>
#include "data_proc.h"

#define PATH_LEN 50 ///< Path length

/**
 * @brief Open gnuplot to export data
 * @param filename Filename to save the plot
 * @return gnuplot file pointer
*/
FILE* plot_save_open(char* filename);

//! @cond Doxygen_Suppress
/**
 * @brief Close gnuplot to export data
 * @param gnuplot gnuplot file pointer
*/
void plot_save_close(FILE* gnuplot);
//! @endcond

/**
 * @brief Open gnuplot
 * @param filename Filename to save the plot
 * @param xmin Minimum value of x
 * @param xmax Maximum value of x
 * @param ymin Minimum value of y
 * @param ymax Maximum value of y
 * @return gnuplot file pointer
*/
FILE* plot_open(char* filename, float xmin, float xmax, float ymin, float ymax);

//! @cond Doxygen_Suppress
/**
 * @brief Close gnuplot
 * @param gnuplot gnuplot file pointer
*/
void plot_close(FILE* gnuplot);
//! @endcond

/**
 * @brief Plot data
 * @param index Index of the shape
 * @param data Pointer to the dataset
*/
void plot_shape(int index, data_t *data);

#endif // DATA_PLOT_H
