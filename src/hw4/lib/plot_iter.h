/**
 * @file plot_iter.h
 * @brief Create a gnuplot drawing API for iter.h
*/

#ifndef PLOT_ITER_H
#define PLOT_ITER_H

#include <stdio.h>
#include "config_read.h"

/**
 * @brief Open a gnuplot pipe
 * @param config Pointer to config_t struct
 * @retval FILE* The file pointer to the opened gnuplot pipe
*/
FILE* plot_open(config_t* config);

/**
 * @brief Add line p1*x + p2*y = p3 to gnuplot
 * @param gnuplot The file pointer to the gnuplot pipe
 * @param p1 The first parameter of the line
 * @param p2 The second parameter of the line
 * @param p3 The third parameter of the line
 * @retval void
*/
void add_line(FILE* gnuplot, config_line_t* config_line);

/**
 * @brief Update the plot
 * @param gnuplot The file pointer to the gnuplot pipe
 * @param config Pointer to config_t struct
 * @param config_lines Pointer to config_line_t struct
 * @retval void
*/
void plot_update(FILE* gnuplot, config_t* config, config_line_t (*config_lines)[]);

/**
 * @brief Close the gnuplot pipe
 * @param gnuplot The file pointer to the gnuplot pipe
 * @retval void
*/
void plot_close(FILE* gnuplot);

#endif // PLOT_ITER_H
