#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_plot.h"
#include "data_proc.h"

/*
REF
1. https://stackoverflow.com/questions/57614573/plotting-a-coordinate-system-with-gnuplot
2. \\ path to normal distribution
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
    // fprintf(gnuplot, "set border 0\n");
    // fprintf(gnuplot, "set xtics axis\n");
    // fprintf(gnuplot, "set ytics axis\n");
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

FILE* plot_save_open(){
    FILE* gnuplot;
    gnuplot = popen("gnuplot --persist", "w");
    if (gnuplot == NULL){
        printf("gnuplot not found...\n");
        exit(1);
    }
    return gnuplot;
}

void plot_save_close(FILE* gnuplot){
    if (gnuplot != NULL){
        pclose(gnuplot);
        printf("Closed gnuplot successfully\n\r");
    } else {
        printf("Error closing gnuplot\n\r");
    }
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

void save_data_as_text(pinky_knuckle_cm* pData, char* pFilename){
    FILE* gnuplot = plot_save_open(pFilename);
    fprintf(gnuplot, "set table '%s'\n", pFilename);
    fprintf(gnuplot, "plot '-'\n");
    float sum = 0;
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 2; i++){
        sum += pData->normal_split_count[i];
    }
    printf("Sum: %f\n\r", sum);
    float x = 0;
    float y = 0;
    for (int i = 0; i < NORMAL_SPLIT_PARTS + 2; i++){
        x = (float)(pData->normal_split_points_center[i]);
        y = (float)(pData->normal_split_count[i]/sum);
        fprintf(gnuplot, "%g %g\n", x, y);
        printf("Plot %g %g\n", x, y);
    }
    fprintf(gnuplot, "e\n");
    fprintf(gnuplot, "unset table\n");
    pclose(gnuplot);
    printf("Closed %s successfully\n\r", pFilename);
    return;
}

void save_line_as_text(char* pFilename, float x_min, float x_max, float mu, float sigma){
    FILE* gnuplot = plot_save_open();
    fprintf(gnuplot, "set xrange [%g:%g]\n", x_min, x_max);
    fprintf(gnuplot, "invsqrt2pi = 0.398942280401433\n");
    fprintf(gnuplot, "normal(x,mu,sigma)=sigma<=0?1/0:invsqrt2pi/sigma*exp(-0.5*((x-mu)/sigma)**2)\n");
    fprintf(gnuplot, "set table '%s'\n", pFilename);
    fprintf(gnuplot, "plot normal(x,%g,%g) with lines lw 2\n", mu, sqrt(sigma));
    printf("mu: %f\n\r", mu);
    printf("sigma: %f\n\r", sigma);
    fprintf(gnuplot, "unset table\n");
    plot_save_close(gnuplot);
    return;
}

void plot_data_vs_normal(pinky_knuckle_cm* pData, char* pFilename){
    // plot data vs normal distribution with 8 parts
    FILE* gnuplot = plot_open(pFilename);
    float x_min = pData->normal_split_points[0]-pData->variance;
    float x_max = pData->normal_split_points[6]+pData->variance;
    fprintf(gnuplot, "set title 'Pinky Knuckle Diameter'\n");
    fprintf(gnuplot, "set xrange [%g:%g]\n", x_min, x_max);
    //
    save_data_as_text(pData, TMP_DATA_FILE1);
    save_line_as_text(TMP_DATA_FILE2, x_min, x_max, pData->mean, pData->variance);
    fprintf(gnuplot, "plot '%s', '%s'\n", TMP_DATA_FILE1, TMP_DATA_FILE2);
    plot_close(gnuplot);
    return;
}
