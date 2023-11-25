/**
 * @file plot_iter.h
 * @brief Create a gnuplot drawing API for iter.h
*/

#ifndef PLOT_ITER_H
#define PLOT_ITER_H

#include <stdio.h>
#include <stdlib.h>
#include "config_read.h"
#include "iter.h"

#define MAX_DOTTED_LINE_CORD_CNT (1000000)   ///< Maximum number of dotted lines

/**
 * @brief Structure for dotted line coorindates
 * @param x X coordinate list
 * @param y Y coordinate list
 * @param cnt Number of coordinates
*/
typedef struct {
    double x[MAX_DOTTED_LINE_CORD_CNT];
    double y[MAX_DOTTED_LINE_CORD_CNT];
    int cnt;
} dotted_line_cord_t;

/**
 * @brief Generate dotted line coordinates
 * @param config Pointer to config_t struct
 * @param config_lines Pointer to config_line_t struct list
 * @param dotted_line_cord Pointer to dotted_line_cord_t struct
 * @param iter_dt_tmp The file pointer to the iteration dotted line temporary file
 * @retval void
*/
void dotted_line_cord_generate(config_t* config, config_line_t (*config_lines)[], dotted_line_cord_t* dotted_line_cord, FILE* iter_dt_tmp);

/**
 * @brief Open a temporary file to store iteration history
 * @param config Pointer to config_t struct
 * @param file_num The number of the file to open
 * @retval FILE* The file pointer to the opened file
*/
FILE* iter_file_open(config_t* config, int file_num);

/**
 * @brief Flush the iteration history to file
 * @param iter_tmp The file pointer to the iteration history file
 * @param iter_history Pointer to iter_history_t struct
 * @param config Pointer to config_t struct
 * @retval void
*/
void iter_file_flush(FILE* iter_tmp, iter_history_t* iter_history, config_t* config);

/**
 * @brief Open a gnuplot pipe
 * @param config Pointer to config_t struct
 * @retval FILE* The file pointer to the opened gnuplot pipe
*/
FILE* iter_plot_open(config_t* config);

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
 * @param iter_point_tmp The file pointer to the iteration history file
 * @param iter_dt_tmp The file pointer to the iteration dotted line temporary file
 * @retval void
*/
void iter_plot_update(FILE* gnuplot, config_t* config, config_line_t (*config_lines)[], iter_history_t* iter_history, FILE* iter_point_tmp, FILE* iter_dt_tmp);

/**
 * @brief Reset the plot to export to file
 * @param gnuplot The file pointer to the gnuplot pipe
 * @param config Pointer to config_t struct
 * @retval void
*/
void iter_plot_reset(FILE* gnuplot, config_t* config);

/**
 * @brief Close the gnuplot pipe
 * @param gnuplot The file pointer to the gnuplot pipe
 * @retval void
*/
void iter_plot_close(FILE* gnuplot);

#endif // PLOT_ITER_H
