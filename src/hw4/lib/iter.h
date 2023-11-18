/**
 * @file iter.h
 * @brief Iterate through points and fine the point closest to the intersection of lines
*/

#ifndef ITER_H
#define ITER_H

#include <stdio.h>
#include "config_read.h"

#define MAX_POINT_CNT 1000000   ///< Maximum number of points

/**
 * @brief Structure for iterate history
 * @param cnt Number of coordinates
 * @param x X coordinate list
 * @param y Y coordinate list
 * @param cost Cost list of the coordinate (learning curve)
 * @param iter Iteration number list
*/
typedef struct {
    int cnt;
    double x[MAX_POINT_CNT];
    double y[MAX_POINT_CNT];
    double cost[MAX_POINT_CNT];
    int iter[MAX_POINT_CNT];
} iter_history_t;

/**
 * @brief Print iteration history
 * @param iter_history Pointer to iter_history_t struct
 * @retval void
*/
void iter_history_print(iter_history_t* iter_history);

/**
 * @brief Initialize iteration history
 * @param iter_history Pointer to iter_history_t struct
 * @param config Pointer to config_t struct
 * @param config_lines Pointer to config_line_t struct list
 * @retval void
*/
void iter_history_init(iter_history_t* iter_history, config_t* config, config_line_t* (*config_lines)[]);

/**
 * @brief Calculate latest point cost
 * @param iter_history Pointer to iter_history_t struct
 * @param config_lines Pointer to config_line_t struct list
 * @param line_index Index of the line
 * @retval distance
*/
double iter_history_calculate_cost(iter_history_t* iter_history, config_line_t* (*config_lines)[]);

/**
 * @brief Iterate through points and fine the point closest to the intersection of lines
 * @param iter_history Pointer to iter_history_t struct
 * @param config Pointer to config_t struct
 * @param config_lines Pointer to config_line_t struct list
 * @retval void
*/
void iter_history_iterate(iter_history_t* iter_history, config_t* config, config_line_t (*config_lines)[]);

#endif // ITER_H
