#include <stdio.h>
#include <stdlib.h>
#include "config_read.h"
#include "iter.h"
#include "../../libc/output_format.h"

FILE* cost_file_open(config_t* config){
    output_format format;
    get_format(&format);
    FILE* cost_tmp = fopen(config->cost_tmp, "w");
    if (cost_tmp == NULL) {
        printf("%sCannot open file: %s\n", format.status.error, config->cost_tmp);
        exit(1);
    } else {
        printf("%sFile opened: %s\n", format.status.success, config->cost_tmp);
    }
    return cost_tmp;
}

void cost_file_flush(FILE* cost_tmp, iter_history_t* iter_history, config_t* config){
    for (int i = iter_history->cnt - config->line_cnt + 1; i <= iter_history->cnt; i++){
        fprintf(cost_tmp, "%d %lf\n", i, iter_history->cost[i] / iter_history->max_cost);
    }
    return;
}

FILE* cost_plot_open(config_t* config){
    output_format format;
    get_format(&format);
    // open gnuplot
    FILE* gnuplot = popen("gnuplot -persist", "w");
    if (gnuplot == NULL) {
        printf("%sCannot open gnuplot, please check your environment.\n", format.status.error);
        exit(1);
    } else {
        printf("%sgnuplot opened for cost plot.\n", format.status.success);
    }
    fprintf(gnuplot, "set terminal qt persist font \"%s,%d\" size %d,%d\n", config->font, config->font_size, config->plot_x_size, config->plot_y_size);
    fprintf(gnuplot, "set title \"cost\"\n");
    fprintf(gnuplot, "set xlabel \"iteration (each iter has %d points)\"\n", config->line_cnt);
    fprintf(gnuplot, "set ylabel \"relative cost\"\n");
    return gnuplot;
}

void cost_plot_update(FILE* gnuplot, config_t* config, iter_history_t* iter_history, FILE* cost_tmp){
    // Add points
    fflush(cost_tmp);
    // Add lines and points to gnuplot
    fprintf(gnuplot, "plot \"%s\" with lines title \"cost\"\n", config->cost_tmp);
    fprintf(gnuplot, "set xrange [%d:%d]\n", iter_history->iter_min, iter_history->cnt);
    fflush(gnuplot);
    return;
}

void cost_plot_reset(FILE* gnuplot, config_t* config, iter_history_t* iter_history){
    fprintf(gnuplot, "reset\n");
    fprintf(gnuplot, "set terminal pngcairo enhanced font \"%s,%d\" size %d,%d\n", config->font, config->font_size, config->plot_x_size, config->plot_y_size);
    fprintf(gnuplot, "set output \"%s.%s\"\n", config->cost_img, config->plot_filetype);
    fprintf(gnuplot, "set title \"cost\"\n");
    fprintf(gnuplot, "set xlabel \"iteration (each iter has %d points)\"\n", config->line_cnt);
    fprintf(gnuplot, "set ylabel \"relative cost\"\n");
    fprintf(gnuplot, "set xrange [%d:%d]\n", iter_history->iter_min, iter_history->cnt);
    return;
}

void cost_plot_close(FILE* gnuplot){
    fflush(gnuplot);
    fprintf(gnuplot, "exit\n");
    pclose(gnuplot);
    printf("gnuplot closed.\n");
    return;
}
