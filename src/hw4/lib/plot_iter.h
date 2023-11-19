/**
 * @file plot_iter.h
 * @brief Create a gnuplot drawing API for iter.h
*/

#ifndef PLOT_ITER_H
#define PLOT_ITER_H

#include <stdio.h>
#include "config_read.h"
#include "iter.h"

/**
 * @brief Open a temporary file to store iteration history
 * @param config Pointer to config_t struct
 * @retval FILE* The file pointer to the opened file
*/
FILE* iter_file_open(config_t* config);

/**
 * @brief Flush the iteration history to file
 * @param iter_file The file pointer to the iteration history file
 * @param iter_history Pointer to iter_history_t struct
 * @param config Pointer to config_t struct
 * @retval void
*/
void iter_file_flush(FILE* iter_file, iter_history_t* iter_history, config_t* config);

/**
 * @brief Open a gnuplot pipe
 * @param config Pointer to config_t struct
 * @retval FILE* The file pointer to the opened gnuplot pipe
*/
FILE* plot_open(config_t* config);

/**
 * @brief Add all lines p1*x + p2*y = p3 to gnuplot
 * @param gnuplot The file pointer to the gnuplot pipe
 * @param config Pointer to config_t struct
 * @param config_lines Pointer to config_line_t structs
 * @retval void
*/
void add_line(FILE* gnuplot, config_t* config, config_line_t (*config_lines)[]);

/**
 * @brief Update the plot
 * @param gnuplot The file pointer to the gnuplot pipe
 * @param config Pointer to config_t struct
 * @param config_lines Pointer to config_line_t struct
 * @param iter_history Pointer to iter_history_t struct
 * @param iter_file The file pointer to the iteration history file
 * @retval void
*/
void plot_update(FILE* gnuplot, config_t* config, config_line_t (*config_lines)[], iter_history_t* iter_history, FILE* iter_file);

/**
 * @brief Close the gnuplot pipe
 * @param gnuplot The file pointer to the gnuplot pipe
 * @retval void
*/
void plot_close(FILE* gnuplot);

#endif // PLOT_ITER_H
