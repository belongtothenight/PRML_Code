#include <stdio.h>
#include <stdlib.h>
#include "plot_iter.h"
#include "config_read.h"
#include "../../libc/output_format.h"

FILE* plot_open(config_t* config){
    output_format format;
    get_format(&format);
    FILE* gnuplot = _popen("gnuplot -persist", "w");
    if (gnuplot == NULL) {
        printf("%sCannot open gnuplot, please check your environment.\n", format.status.error);
        exit(1);
    } else {
        printf("%sgnuplot opened.\n", format.status.success);
    }
    fprintf(gnuplot, "set terminal qt persist font \"Arial,25\" size 1080,1080\n");
    fprintf(gnuplot, "set output \"%s.png\"\n", config->output_file);
    fprintf(gnuplot, "set xlabel \"x axis\"\n");
    fprintf(gnuplot, "set ylabel \"y axis\"\n");
    return gnuplot;
}

void add_line(FILE* gnuplot, config_line_t* config_line){
    fprintf(gnuplot, "%s(x) = %lf - %lf * x\n", config_line->line_symbol, config_line->line_param3/config_line->line_param2, config_line->line_param1/config_line->line_param2);
    return;
}

void plot_update(FILE* gnuplot, config_t* config, config_line_t (*config_lines)[]){
    fprintf(gnuplot, "plot ");
    for (int i = 0; i < config->line_cnt; i++) {
        fprintf(gnuplot, "%s(x) title \"%s %.1lfx+%.1lfy=%.1lf\" with lines lw 3", &(*config_lines)[i].line_symbol, &(*config_lines)[i].line_title, (*config_lines)[i].line_param1, (*config_lines)[i].line_param2, (*config_lines)[i].line_param3);
        if (i != config->line_cnt - 1) fprintf(gnuplot, ", ");
    }
    fprintf(gnuplot, "\n");
    fflush(gnuplot);
    return;
}

void plot_close(FILE* gnuplot){
    fprintf(gnuplot, "exit\n");
    fflush(gnuplot);
    pclose(gnuplot);
    printf("gnuplot closed.\n");
    return;
}
