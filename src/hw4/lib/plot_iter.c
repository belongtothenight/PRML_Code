#include <stdio.h>
#include <stdlib.h>
#include "plot_iter.h"
#include "config_read.h"
#include "iter.h"
#include "../../libc/output_format.h"

FILE* iter_file_open(config_t* config){
    output_format format;
    get_format(&format);
    FILE* iter_tmp = fopen(config->iter_tmp, "w");
    if (iter_tmp == NULL) {
        printf("%sCannot open file: %s\n", format.status.error, config->iter_tmp);
        exit(1);
    } else {
        printf("%sFile opened: %s\n", format.status.success, config->iter_tmp);
    }
    return iter_tmp;
}

void iter_file_flush(FILE* iter_tmp, iter_history_t* iter_history, config_t* config){
    for (int i = iter_history->cnt - config->line_cnt + 1; i <= iter_history->cnt; i++){
        fprintf(iter_tmp, "%lf %lf\n", iter_history->x[i], iter_history->y[i]);
    }
    return;
}

FILE* iter_plot_open(config_t* config){
    output_format format;
    get_format(&format);
    // open gnuplot
    FILE* gnuplot = popen("gnuplot -persist", "w");
    if (gnuplot == NULL) {
        printf("%sCannot open gnuplot, please check your environment.\n", format.status.error);
        exit(1);
    } else {
        printf("%sgnuplot opened.\n", format.status.success);
    }
    fprintf(gnuplot, "set terminal qt persist font \"%s,%d\" size %d,%d\n", config->font, config->font_size, config->plot_x_size, config->plot_y_size);
    fprintf(gnuplot, "set title \"iteration points\"\n");
    fprintf(gnuplot, "set xlabel \"x axis\"\n");
    fprintf(gnuplot, "set ylabel \"y axis\"\n");
    fprintf(gnuplot, "set xrange [%d:%d]\n", config->plot_x_min, config->plot_x_max);
    fprintf(gnuplot, "set yrange [%d:%d]\n", config->plot_y_min, config->plot_y_max);
    return gnuplot;
}

void add_line(FILE* gnuplot, config_t* config, config_line_t (*config_lines)[]){
    for (int i = 0; i < config->line_cnt; i++) {
        fprintf(gnuplot, "%s(x) = %lf - %lf * x\n", &(*config_lines)[i].line_symbol, (*config_lines)[i].line_param3/(*config_lines)[i].line_param2, (*config_lines)[i].line_param1/(*config_lines)[i].line_param2);
    }
    return;
}

void iter_plot_update(FILE* gnuplot, config_t* config, config_line_t (*config_lines)[], iter_history_t* iter_history, FILE* iter_tmp){
    // Add points
    fflush(iter_tmp);
    // Add lines and points to gnuplot
    fprintf(gnuplot, "plot ");
    for (int i = 0; i < config->line_cnt; i++) {
        fprintf(gnuplot, "%s(x) title \"%s %.1lfx+%.1lfy=%.1lf\" with lines lw 3", &(*config_lines)[i].line_symbol, &(*config_lines)[i].line_title, (*config_lines)[i].line_param1, (*config_lines)[i].line_param2, (*config_lines)[i].line_param3);
        if (i != config->line_cnt - 1) fprintf(gnuplot, ", ");
    }
    fprintf(gnuplot, ", \"%s\" with points pt 7 ps 0.5 lc rgb \"red\" title \"iteration points\"\n", config->iter_tmp);
    fprintf(gnuplot, "\n");
    fflush(gnuplot);
    return;
}

void iter_plot_reset(FILE* gnuplot, config_t* config){
    fprintf(gnuplot, "reset\n");
    fprintf(gnuplot, "set terminal pngcairo enhanced font \"%s,%d\" size %d,%d\n", config->font, config->font_size, config->plot_x_size, config->plot_y_size);
    fprintf(gnuplot, "set output \"%s.%s\"\n", config->iter_img, config->plot_filetype);
    fprintf(gnuplot, "set title \"iteration points\"\n");
    fprintf(gnuplot, "set xlabel \"x axis\"\n");
    fprintf(gnuplot, "set ylabel \"y axis\"\n");
    fprintf(gnuplot, "set xrange [%d:%d]\n", config->plot_x_min, config->plot_x_max);
    fprintf(gnuplot, "set yrange [%d:%d]\n", config->plot_y_min, config->plot_y_max);
    return;
}

void iter_plot_close(FILE* gnuplot){
    fflush(gnuplot);
    fprintf(gnuplot, "exit\n");
    pclose(gnuplot);
    printf("gnuplot closed.\n");
    return;
}
