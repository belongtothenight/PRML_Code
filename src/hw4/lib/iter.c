#include <stdio.h>
#include <stdlib.h>
#include "iter.h"
#include "config_read.h"
#include "../../libc/distance.h"

void iter_history_print(iter_history_t* iter_history){
    printf("iter_history->cnt: %d\n", iter_history->cnt);
    for (int i = 0; i <= iter_history->cnt; i++){
        printf("iter_history->x[%d]: %lf\n", i, iter_history->x[i]);
        printf("iter_history->y[%d]: %lf\n", i, iter_history->y[i]);
        printf("iter_history->cost[%d]: %lf\n", i, iter_history->cost[i]);
        printf("iter_history->iter[%d]: %d\n", i, iter_history->iter[i]);
    }
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
    iter_history->x[iter_history->cnt] = config->initial_x;
    iter_history->y[iter_history->cnt] = config->initial_y;
    iter_history->cost[iter_history->cnt] = iter_history_calculate_cost(iter_history, config, &(*config_lines));
    iter_history->iter[iter_history->cnt] = iter_history->cnt;
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

}
