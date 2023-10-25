#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_plot.h"
#include "data_proc.h"
#include "output_format.h"
#include "decision_boundary.h"

/*
REF
1. https://stackoverflow.com/questions/57614573/plotting-a-coordinate-system-with-gnuplot
2. \\ path to normal distribution
*/

FILE* plot_open(char* pFilename){
    // open gnuplot interactive session and save to png file simultaneously
    output_format Format;
    get_format(&Format);
    FILE* gnuplot = popen("gnuplot --persist", "w");
    if (gnuplot == NULL){
        printf("%sERROR%s: gnuplot not found...\n\r", Format.foreground.red, Format.style.reset);
        exit(1);
    }
    fprintf(gnuplot, "set terminal %s font \"sans,12\"\n", GNUPLOT_TERMINAL);
    fprintf(gnuplot, "set terminal push\n");
    fprintf(gnuplot, "set terminal pngc\n");
    // fprintf(gnuplot, "set terminal pngcairo\n");
    fprintf(gnuplot, "set output '%s'\n", pFilename);
    // formatting
    fprintf(gnuplot, "set xzeroaxis;\n");
    fprintf(gnuplot, "set yzeroaxis;\n");
    // fprintf(gnuplot, "set border 0\n");
    fprintf(gnuplot, "set xtics axis\n");
    fprintf(gnuplot, "set ytics axis\n");
    fprintf(gnuplot, "set ticscale 0;\n");
    fprintf(gnuplot, "set xtics add (\"\" 0)\n");
    fprintf(gnuplot, "set ytics add (\"\" 0)\n");
    // fprintf(gnuplot, "set arrow 1 from 0,0 to graph 1, first 0 filled head\n");
    // fprintf(gnuplot, "set arrow 2 from 0,0 to first 0, graph 1 filled head\n");
    // fprintf(gnuplot, "set arrow 3 from 0,0 to graph 0, first 0 filled head\n");
    // fprintf(gnuplot, "set arrow 4 from 0,0 to first 0, graph 0 filled head\n");
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
    output_format Format;
    get_format(&Format);
    FILE* gnuplot;
    gnuplot = popen("gnuplot --persist", "w");
    if (gnuplot == NULL){
        printf("%sERROR%s: gnuplot not found...\n\r", Format.foreground.red, Format.style.reset);
        exit(1);
    }
    return gnuplot;
}

void plot_save_close(FILE* gnuplot){
    output_format Format;
    get_format(&Format);
    if (gnuplot != NULL){
        pclose(gnuplot);
        printf("%sSUCCESS%s: gnuplot closed.\n\r", Format.foreground.green, Format.style.reset);
    } else {
        printf("%sERROR%s: Error closing gnuplot\n\r", Format.foreground.red, Format.style.reset);
    }
    return;
}

void test_plot(dataset* pData, char* pFilename){
    FILE* gnuplot = plot_open(pFilename);
    fprintf(gnuplot, "set title 'Pinky Knuckle Diameter'\n");
    fprintf(gnuplot, "set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 pi -1 ps 1.5\n");
    fprintf(gnuplot, "set pointintervalbox 3\n");
    // plot data till 'e'nd of data
    fprintf(gnuplot, "plot '-'\n");
    float x = 0;
    for (int i = 0; i < pData->size; i++){
        fprintf(gnuplot, "%g %g\n", x, pData->data_element[i]);
        printf("Plot %g %g\n", x, pData->data_element[i]);
        x++;
    }
    fprintf(gnuplot, "e with linespoints ls 1\n");
    //
    plot_close(gnuplot);
    return;
}

void save_data_div5_cnt(dataset* pData, char* pFilename){
    output_format Format;
    get_format(&Format);
    FILE* gnuplot = plot_save_open(pFilename);
    fprintf(gnuplot, "set table '%s'\n", pFilename);
    fprintf(gnuplot, "plot '-'\n");
    float x = 0;
    float y = 0;
    for (int i = 0; i < SPLIT_PARTS; i++){
        x = (float)(pData->split_points_center[i]);
        y = (float)(pData->split_count[i]/(float)pData->size);
        fprintf(gnuplot, "%g %g\n", x, y);
        printf("Plot %g %g\n", x, y);
    }
    fprintf(gnuplot, "e\n");
    fprintf(gnuplot, "unset table\n");
    pclose(gnuplot);
    printf("%sSUCCESS%s: Data written to file %s.\n\r", Format.foreground.green, Format.style.reset, pFilename);
    return;
}

void save_data_div5_norm(char* pFilename, float x_min, float x_max, float mu, float sigma){
    // https://gist.github.com/JavierJia/e10f7c7d8ce3c42a6e469316a5738f0f
    output_format Format;
    get_format(&Format);
    FILE* gnuplot = plot_save_open();
    fprintf(gnuplot, "set xrange [%g:%g]\n", x_min, x_max);
    fprintf(gnuplot, "invsqrt2pi = 0.398942280401433\n");
    fprintf(gnuplot, "normal(x,mu,sigma)=sigma<=0?1/0:invsqrt2pi/sigma*exp(-0.5*((x-mu)/sigma)**2)\n");
    fprintf(gnuplot, "set table '%s'\n", pFilename);
    fprintf(gnuplot, "plot normal(x,%g,%g) with lines lw 2\n", mu, sigma);
    fprintf(gnuplot, "unset table\n");
    plot_save_close(gnuplot);
    printf("%sSUCCESS%s: Data written to file %s.\n\r", Format.foreground.green, Format.style.reset, pFilename);
    return;
}

void save_data_vertical_line(char* pFilename, float x, float y1, float y2){
    output_format Format;
    get_format(&Format);
    FILE* gnuplot = plot_save_open();
    fprintf(gnuplot, "set table '%s'\n", pFilename);
    fprintf(gnuplot, "plot '-'\n");
    fprintf(gnuplot, "%g %g\n", x, y1);
    fprintf(gnuplot, "%g %g\n", x, y2);
    fprintf(gnuplot, "e\n");
    fprintf(gnuplot, "unset table\n");
    plot_save_close(gnuplot);
    printf("%sSUCCESS%s: Data written to file %s.\n\r", Format.foreground.green, Format.style.reset, pFilename);
    return;
}

void plot_data_div5(dataset* pData, char* pFilename, char* pTMP1, char* pTMP2){
    // plot data vs normal distribution with 8 parts
    // https://stackoverflow.com/questions/8855332/line-chart-and-bar-chart-in-gnuplot
    // http://www.gnuplot.info/docs_4.2/node295.html
    float x_min = pData->split_points[0]-(pData->split_step/2);
    float x_max = pData->split_points[SPLIT_PARTS]+(pData->split_step/2);
    float y_min = 0;
    float y_max = 1;
    //
    save_data_div5_cnt(pData, pTMP1);
    save_data_div5_norm(pTMP2, x_min, x_max, pData->mu, pData->sigma);
    FILE* gnuplot = plot_open(pFilename);
    fprintf(gnuplot, "set title 'Pinky Knuckle Diameter'\n");
    fprintf(gnuplot, "set xrange [%g:%g]\n", x_min, x_max);
    fprintf(gnuplot, "set yrange [%g:%g]\n", y_min, y_max);
    fprintf(gnuplot, "set xlabel 'Pinky Knuckle Diameter (%s)'\n", UNIT);
    fprintf(gnuplot, "set ylabel 'Probability'\n");
    fprintf(gnuplot, "set boxwidth 0.6 relative\n");
    fprintf(gnuplot, "set style fill solid\n");
    fprintf(gnuplot, "set xtics ('%g' %g, '%g' %g, '%g' %g, '%g' %g, '%g' %g)\n", pData->split_points_center[0], pData->split_points_center[0], pData->split_points_center[1], pData->split_points_center[1], pData->split_points_center[2], pData->split_points_center[2], pData->split_points_center[3], pData->split_points_center[3], pData->split_points_center[4], pData->split_points_center[4]);
    fprintf(gnuplot, "plot '%s' title 'data' with boxes, '%s' title 'normal distribution' with lines lw 3\n", pTMP1, pTMP2);
    plot_close(gnuplot);
    return;
}

void plot_stacked_data_div5(dataset* pData1, dataset* pData2, intersection* pITS, char* pFilename, char* pTMP1, char* pTMP2, char* pTMP3){
    float x_min1 = pData1->split_points[0]-(pData1->split_step/2);
    float x_max1 = pData1->split_points[SPLIT_PARTS]+(pData1->split_step/2);
    float x_min2 = pData2->split_points[0]-(pData2->split_step/2);
    float x_max2 = pData2->split_points[SPLIT_PARTS]+(pData2->split_step/2);
    float x_min = (x_min1 < x_min2) ? x_min1 : x_min2;
    float x_max = (x_max1 > x_max2) ? x_max1 : x_max2;
    float y_min = 0;
    float y_max = 1;
    //
    save_data_div5_norm(pTMP1, x_min, x_max, pData1->mu, pData1->sigma);
    save_data_div5_norm(pTMP2, x_min, x_max, pData2->mu, pData2->sigma);
    save_data_vertical_line(pTMP3, pITS->avg_x, y_min, y_max);
    FILE* gnuplot = plot_open(pFilename);
    fprintf(gnuplot, "set title 'Pinky Knuckle Diameter Male vs. Female'\n");
    fprintf(gnuplot, "set xrange [%g:%g]\n", x_min, x_max);
    fprintf(gnuplot, "set yrange [%g:%g]\n", y_min, y_max);
    fprintf(gnuplot, "set xlabel 'Pinky Knuckle Diameter (%s)'\n", UNIT);
    fprintf(gnuplot, "set ylabel 'Probability'\n");
    fprintf(gnuplot, "plot '%s' title 'male' with lines lw 3, '%s' title 'femlae' with lines lw 3, '%s' title 'decision boundary' with lines lw 3\n", pTMP1, pTMP2, pTMP3);
    plot_close(gnuplot);
    return;
}
