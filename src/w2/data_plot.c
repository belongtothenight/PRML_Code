#include <stdio.h>
#include <stdlib.h>
#include "data_plot.h"
#include "data_proc.h"

void test_plot(pinky_knuckle_cm* pData, char* pFilename){
    // open gnuplot interactive session and save to png file simultaneously
    FILE *gnuplot = popen("gnuplot --persist", "w");
    if (gnuplot == NULL){
        printf("gnuplot not found...\n");
        exit(1);
    }
    // fprintf(gnuplot, "set terminal %s persist\n", GNUPLOT_TERMINAL);
    fprintf(gnuplot, "set terminal %s\n", GNUPLOT_TERMINAL);
    fprintf(gnuplot, "set terminal push\n");
    fprintf(gnuplot, "set terminal png\n");
    fprintf(gnuplot, "set output '%s'\n", pFilename);
    fprintf(gnuplot, "set title 'Pinky Knuckle Diameter'\n");
    // plot data till 'e'nd of data
    fprintf(gnuplot, "plot '-'\n");
    for (int i = 0; i < pData->size; i++){
        fprintf(gnuplot, "%f\n", pData->diameter[i]);
    }
    fprintf(gnuplot, "e\n");
    fprintf(gnuplot, "set terminal pop\n");
    fprintf(gnuplot, "replot\n");
    fflush(gnuplot);
    pclose(gnuplot);
    return;
}
