#include <stdio.h>
#include <stdlib.h>
#include "data_plot.h"
#include "data_proc.h"

/*
REF
1. https://stackoverflow.com/questions/57614573/plotting-a-coordinate-system-with-gnuplot
*/

FILE* plot_open(char* pFilename){
    // open gnuplot interactive session and save to png file simultaneously
    FILE* gnuplot = popen("gnuplot --persist", "w");
    if (gnuplot == NULL){
        printf("gnuplot not found...\n");
        exit(1);
    }
    fprintf(gnuplot, "set terminal %s\n", GNUPLOT_TERMINAL);
    fprintf(gnuplot, "set terminal push\n");
    fprintf(gnuplot, "set terminal pngc\n");
    // fprintf(gnuplot, "set terminal pngcairo\n");
    fprintf(gnuplot, "set output '%s'\n", pFilename);
    // formatting
    fprintf(gnuplot, "set xzeroaxis;\n");
    fprintf(gnuplot, "set yzeroaxis;\n");
    fprintf(gnuplot, "set border 0\n");
    fprintf(gnuplot, "set xtics axis\n");
    fprintf(gnuplot, "set ytics axis\n");
    fprintf(gnuplot, "set ticscale 0;\n");
    fprintf(gnuplot, "set xtics add (\"\" 0)\n");
    fprintf(gnuplot, "set ytics add (\"\" 0)\n");
    fprintf(gnuplot, "set arrow 1 from 0,0 to graph 1, first 0 filled head\n");
    fprintf(gnuplot, "set arrow 2 from 0,0 to first 0, graph 1 filled head\n");
    fprintf(gnuplot, "set arrow 3 from 0,0 to graph 0, first 0 filled head\n");
    fprintf(gnuplot, "set arrow 4 from 0,0 to first 0, graph 0 filled head\n");
    return gnuplot;
}

void plot_close(FILE* gnuplot){
    fprintf(gnuplot, "set terminal pop\n");
    fprintf(gnuplot, "replot\n");
    fflush(gnuplot);
    pclose(gnuplot);
    return;
}

void test_plot(pinky_knuckle_cm* pData, char* pFilename){
    FILE* gnuplot = plot_open(pFilename);
    fprintf(gnuplot, "set title 'Pinky Knuckle Diameter'\n");
    fprintf(gnuplot, "set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 pi -1 ps 1.5\n");
    fprintf(gnuplot, "set pointintervalbox 3\n");
    // plot data till 'e'nd of data
    fprintf(gnuplot, "plot '-'\n");
    float x = 0;
    for (int i = 0; i < pData->size; i++){
        fprintf(gnuplot, "%g %g\n", x, pData->diameter[i]);
        printf("Plot %g %g\n", x, pData->diameter[i]);
        x++;
    }
    fprintf(gnuplot, "e with linespoints ls 1\n");
    //
    plot_close(gnuplot);
    return;
}

void plot_data_vs_normal(pinky_knuckle_cm* pData, char* pFilename){
    FILE* gnuplot = plot_open(pFilename);
    fprintf(gnuplot, "set title 'Pinky Knuckle Diameter'\n");
    fprintf(gnuplot, "set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 pi -1 ps 1.5\n");
    fprintf(gnuplot, "set pointintervalbox 3\n");
    // plot data till 'e'nd of data
    fprintf(gnuplot, "plot '-'\n");
    float x = 0;
    for (int i = 0; i < pData->size; i++){
        fprintf(gnuplot, "%g %g\n", x, pData->diameter[i]);
        printf("Plot %g %g\n", x, pData->diameter[i]);
        x++;
    }
    fprintf(gnuplot, "e with linespoints ls 1\n");
    //
    plot_close(gnuplot);
    return;
    return;
}
