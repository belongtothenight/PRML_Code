#include <stdio.h>
#include <stdlib.h>
#include "plot_iter.h"
#include "config_read.h"
#include "iter.h"
#include "../../libc/output_format.h"
#include "../../libc/random.h"

void dotted_line_cord_generate(config_t* config, config_line_t (*config_lines)[], dotted_line_cord_t* dotted_line_cord, FILE* iter_dt_tmp){
    // Generate dotted line coordinates
    printf("Generating dotted line coordinates...\n");
    int total_cnt = ((config->plot_x_max - config->plot_x_min) / config->iter_dotted_line_step) * config->iter_dotted_line_num_per_x * config->line_cnt;
    printf("Total dotted line cnt: %d\n", total_cnt);
    dotted_line_cord->cnt = 0;
    double y;
    if (config->debug_mode) {
        printf("plot_x_min: %lf\n", config->plot_x_min);
        printf("plot_x_max: %lf\n", config->plot_x_max);
        printf("iter_dotted_line_step: %lf\n", config->iter_dotted_line_step);
        printf("line_cnt: %d\n", config->line_cnt);
        printf("iter_dotted_line_num_per_x: %d\n", config->iter_dotted_line_num_per_x);
    }
    for (double i = config->plot_x_min; i <= config->plot_x_max; i += config->iter_dotted_line_step) {
        for (int j = 0; j < config->line_cnt; j++) {
            // y = (p3 - p1 * x) / p2
            y = ((*config_lines)[j].line_param3 - (*config_lines)[j].line_param1 * i) / (*config_lines)[j].line_param2;
            for (int k = 0; k < config->iter_dotted_line_num_per_x; k++) {
                dotted_line_cord->x[dotted_line_cord->cnt] = i;
                dotted_line_cord->y[dotted_line_cord->cnt] = y + random_double(-config->iter_dotted_line_range, config->iter_dotted_line_range);
                dotted_line_cord->cnt++;
                if (config->debug_mode) {
                    printf("Generated %d/%d %.2lf%% x: %.2lf y: %.2lf i: %.2lf j: %d k: %d\n", dotted_line_cord->cnt, total_cnt, (double)dotted_line_cord->cnt / total_cnt * 100, i, y, i, j, k);
                } else {
                    printf("Generated %d/%d %.2lf%% x: %.2lf y: %.2lf i: %.2lf j: %d k: %d\r", dotted_line_cord->cnt, total_cnt, (double)dotted_line_cord->cnt / total_cnt * 100, i, y, i, j, k);
                }
                if (dotted_line_cord->cnt > total_cnt + MAX_LINE_CNT * config->iter_dotted_line_num_per_x) {
                    printf("\ndotted line cnt exceeds total cnt\n");
                    exit(1);
                }
            }
        }
    }
    // Write to file
    printf("\nWriting to file...\n");
    if (config->debug_mode) printf("dotted line cnt: %d\n", dotted_line_cord->cnt);
    for (int i = 0; i < dotted_line_cord->cnt; i++) {
        fprintf(iter_dt_tmp, "%lf %lf\n", dotted_line_cord->x[i], dotted_line_cord->y[i]);
        if (config->debug_mode) {
            printf("Writing to file: %d/%d %.2lf%% x: %lf y: %lf\n", i+1, dotted_line_cord->cnt, (double)(i+1) / dotted_line_cord->cnt * 100, dotted_line_cord->x[i], dotted_line_cord->y[i]);
        } else {
            printf("Writing to file: %d/%d %.2lf%% x: %lf y: %lf\r", i+1, dotted_line_cord->cnt, (double)(i+1) / dotted_line_cord->cnt * 100, dotted_line_cord->x[i], dotted_line_cord->y[i]);
        }
    }
    return;
}

FILE* iter_file_open(config_t* config, int file_num){
    output_format format;
    get_format(&format);
    char* filepath;
    if (file_num == 1) {
        filepath = config->iter_point_tmp;
    } else if (file_num == 2) {
        filepath = config->iter_dt_tmp;
    } else {
        printf("%sInvalid file number: %d\n", format.status.error, file_num);
        exit(1);
    }
    FILE* iter_tmp = fopen(filepath, "w");
    if (iter_tmp == NULL) {
        printf("%sCannot open file: %s\n", format.status.error, filepath);
        exit(1);
    } else {
        printf("%sFile opened: %s\n", format.status.success, filepath);
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
        printf("%sgnuplot opened for iter plot.\n", format.status.success);
    }
    fprintf(gnuplot, "set terminal qt persist font \"%s,%d\" size %d,%d\n", config->font, config->font_size, config->plot_x_size, config->plot_y_size);
    fprintf(gnuplot, "set title \"iteration points\"\n");
    fprintf(gnuplot, "set xlabel \"x axis\"\n");
    fprintf(gnuplot, "set ylabel \"y axis\"\n");
    fprintf(gnuplot, "set xrange [%lf:%lf]\n", config->plot_x_min, config->plot_x_max);
    fprintf(gnuplot, "set yrange [%lf:%lf]\n", config->plot_y_min, config->plot_y_max);
    return gnuplot;
}

void add_line(FILE* gnuplot, config_t* config, config_line_t (*config_lines)[]){
    for (int i = 0; i < config->line_cnt; i++) {
        fprintf(gnuplot, "%s(x) = %lf - %lf * x\n", &(*config_lines)[i].line_symbol, (*config_lines)[i].line_param3/(*config_lines)[i].line_param2, (*config_lines)[i].line_param1/(*config_lines)[i].line_param2);
    }
    return;
}

void iter_plot_update(FILE* gnuplot, config_t* config, config_line_t (*config_lines)[], iter_history_t* iter_history, FILE* iter_point_tmp, FILE* iter_dt_tmp){
    // Add temporary files to gnuplot
    fflush(iter_point_tmp);
    fflush(iter_dt_tmp);
    // Add lines and points to gnuplot
    fprintf(gnuplot, "plot ");
    if (config->plot_iter_with_line) {
        for (int i = 0; i < config->line_cnt; i++) {
            fprintf(gnuplot, "%s(x) title \"%s %.1lfx+%.1lfy=%.1lf\" with lines lw 3", &(*config_lines)[i].line_symbol, &(*config_lines)[i].line_title, (*config_lines)[i].line_param1, (*config_lines)[i].line_param2, (*config_lines)[i].line_param3);
            if (i != config->line_cnt - 1) fprintf(gnuplot, ", ");
        }
        fprintf(gnuplot, ", ");
    }
    if (config->plot_iter_with_dotted_line) {
        fprintf(gnuplot, "\"%s\" with points pt 7 ps 0.5 lc rgb \"blue\" title \"dotted line points\"", config->iter_dt_tmp);
        fprintf(gnuplot, ", ");
    }
    fprintf(gnuplot, "\"%s\" with points pt 7 ps 0.5 lc rgb \"red\" title \"iteration points\"", config->iter_point_tmp);
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
    fprintf(gnuplot, "set xrange [%lf:%lf]\n", config->plot_x_min, config->plot_x_max);
    fprintf(gnuplot, "set yrange [%lf:%lf]\n", config->plot_y_min, config->plot_y_max);
    return;
}

void iter_plot_close(FILE* gnuplot){
    fflush(gnuplot);
    fprintf(gnuplot, "exit\n");
    pclose(gnuplot);
    printf("gnuplot closed.\n");
    return;
}
