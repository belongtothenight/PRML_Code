#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "iter.h"
#include "config_read.h"
#include "../../libc/distance.h"
#include "../../libc/intersection.h"

void iter_history_print(iter_history_t* iter_history){
    printf("iter_history->cnt: %d ->iter: %d ->x: %lf ->y: %lf ->cost: %lf ->relative_cost: %lf\n", iter_history->cnt, iter_history->iter[iter_history->cnt], iter_history->x[iter_history->cnt], iter_history->y[iter_history->cnt], iter_history->cost[iter_history->cnt], iter_history->cost[iter_history->cnt] / iter_history->max_cost);
    return;
}

void iter_history_init(iter_history_t* iter_history, config_t* config, config_line_t (*config_lines)[]){
    iter_history->cnt = 0;
    for (int i = 0; i < MAX_POINT_CNT; i++){
        iter_history->x[i] = 0;
        iter_history->y[i] = 0;
        iter_history->cost[i] = 0;
        iter_history->iter[i] = 0;
    }
    iter_history->max_cost = 0;
    iter_history->iter_min = 0;
    iter_history->iter_min_set = false;
    iter_history->x[iter_history->cnt] = config->initial_x;
    iter_history->y[iter_history->cnt] = config->initial_y;
    iter_history->cost[iter_history->cnt] = iter_history_calculate_cost(iter_history, config, &(*config_lines));
    iter_history->iter[iter_history->cnt] = iter_history->cnt;
    iter_history->max_cost = iter_history->cost[iter_history->cnt];
    return;
}

double iter_history_calculate_cost(iter_history_t* iter_history, config_t* config, config_line_t (*config_lines)[]){
    // add distance to all lines in this function and return it.
    double cost = 0;
    for (int i = 0; i < config->line_cnt; i++){
        cost += distance_2Dpoint2line(iter_history->x[iter_history->cnt], iter_history->y[iter_history->cnt], (*config_lines)[i].line_param1, (*config_lines)[i].line_param2, (*config_lines)[i].line_param3);
    }
    return cost;
}

void iter_history_iterate(iter_history_t* iter_history, config_t* config, config_line_t (*config_lines)[]){
    // each iteration should move the point to the selected line's direction
    double a1 = 0;
    double b1 = 0;
    double c1 = 0;
    double a2 = 0;
    double b2 = 0;
    double c2 = 0;
    d2_point_t d2_point; // intersection point
    double step_normalize_coeff = 0;
    double next_x = 0;
    double next_y = 0;
    int    iter = iter_history->iter[iter_history->cnt] + 1;
    for (int i = 0; i < config->line_cnt; i++){
        iter_history->cnt++;
        a1 = (*config_lines)[i].line_param1;
        b1 = (*config_lines)[i].line_param2;
        c1 = -(*config_lines)[i].line_param3;
        a2 = -(*config_lines)[i].line_param2;
        b2 = (*config_lines)[i].line_param1;
        c2 = -(iter_history->x[iter_history->cnt - 1] * a2 + iter_history->y[iter_history->cnt - 1] * b2);
        d2_intersection(a1, b1, c1, a2, b2, c2, &d2_point);
        if (config->dynamic_step == false){
            step_normalize_coeff = config->initial_step / sqrt(pow(d2_point.x - iter_history->x[iter_history->cnt - 1], 2) + pow(d2_point.y - iter_history->y[iter_history->cnt - 1], 2));
        } else {
            step_normalize_coeff = config->initial_step;
        }
        next_x = iter_history->x[iter_history->cnt - 1] + (d2_point.x - iter_history->x[iter_history->cnt - 1]) * step_normalize_coeff;
        next_y = iter_history->y[iter_history->cnt - 1] + (d2_point.y - iter_history->y[iter_history->cnt - 1]) * step_normalize_coeff;
        iter_history->x[iter_history->cnt] = next_x;
        iter_history->y[iter_history->cnt] = next_y;
        iter_history->cost[iter_history->cnt] = iter_history_calculate_cost(iter_history, config, &(*config_lines));
        iter_history->iter[iter_history->cnt] = iter;
        if (config->debug_mode == true){
            printf("a1: %lf ->b1: %lf ->c1: %lf ->a2: %lf ->b2: %lf ->c2: %lf ->d2_point.x: %lf ->d2_point.y: %lf ->next_x: %lf ->next_y: %lf\n", a1, b1, c1, a2, b2, c2, d2_point.x, d2_point.y, next_x, next_y);
        }
        if (((next_x > config->plot_x_min) && (next_y > config->plot_y_min) && (next_x < config->plot_x_max) && (next_y < config->plot_y_max)) || (iter_history->iter_min_set == true)){
            if (iter_history->iter_min_set == false){
                iter_history->iter_min = iter_history->cnt;
                iter_history->iter_min_set = true;
                printf("entering plot view at cnt: %d\n", iter_history->iter_min);
                if (config->debug_mode) {
                    printf("iter_history->iter_min_set: %d\n", iter_history->iter_min_set);
                }
            }
        }
    }
}
