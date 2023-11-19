/**
 * @file plot_cost.h
 * @brief Function prototypes for plotting cost function
*/

#ifndef PLOT_COST_H
#define PLOT_COST_H

#include <stdio.h>
#include <stdlib.h>
#include "config_read.h"
#include "iter.h"

/**
 * @brief Open a temporary file to store cost function values
 * @param config Configuration struct
 * @return File pointer to the temporary file
*/
FILE* cost_file_open(config_t* config);

/**
 * @brief Flush the cost history to file
 * @param cost_tmp File pointer to the temporary file
 * @param config Configuration struct
 * @param iter_history Iteration history struct
 * @param void
*/
void cost_file_flush(FILE* cost_tmp, iter_history_t* iter_history, config_t* config);

/**
 * @brief Open a gnuplot pipe
 * @param config Pointer to config_t struct
 * @return File pointer to the gnuplot pipe
*/
FILE* cost_plot_open(config_t* config);

/**
 * @brief Update the cost plot
 * @param gnuplot Pipe to gnuplot
 * @param config Pointer to config_t struct
 * @param iter_history Pointer to iter_history_t struct
 * @param cost_tmp Pointer to cost file
 * @return void
*/
void cost_plot_update(FILE* gnuplot, config_t* config, iter_history_t* iter_history, FILE* cost_tmp);

/**
 * @brief Reset the cost plot to export to file
 * @param gnuplot Pipe to gnuplot
 * @param config Pointer to config_t struct
 * @return void
*/
void cost_plot_reset(FILE* gnuplot, config_t* config);

/**
 * @brief Close the cost plot
 * @param gnuplot Pipe to gnuplot
 * @return void
*/
void cost_plot_close(FILE* gnuplot);

#endif // PLOT_COST_H
