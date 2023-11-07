#include <stdio.h>
#include <stdlib.h>
#include "../../libc/output_format.h"
#include "data_plot.h"
#include "data_proc.h"

FILE* plot_save_open(char* filename){
    output_format format;
    get_format(&format);
    FILE* data = popen("gnuplot", "w");
    if (data == NULL){
        printf("%sError: Cannot open %s.\n", format.status.error, filename);
        exit(1);
    } else {
        printf("%sSaving %s.dat ...\n", format.status.success, filename);
    }
    fprintf(data, "set table '%s.dat'\n", filename);
    fprintf(data, "plot '-'\n");
    return data;
}

void plot_save_close(FILE* gnuplot){
    fprintf(gnuplot, "e\n");
    fprintf(gnuplot, "unset table\n");
    fflush(gnuplot);
    pclose(gnuplot);
    return;
}

FILE* plot_open(char* filename, float xmin, float xmax, float ymin, float ymax){
    output_format format;
    get_format(&format);
    FILE* gnuplot = popen("gnuplot", "w");
    if (gnuplot == NULL){
        printf("%sError: Cannot open gnuplot.\n", format.status.error);
        exit(1);
    } else {
        printf("%sPlotting %s.png ...\n", format.status.success, filename);
    }
    fprintf(gnuplot, "set terminal pngcairo enhanced font \"Arial,25\" size 1080,1080\n");
    fprintf(gnuplot, "set output \"%s.png\"\n", filename);
    fprintf(gnuplot, "set xrange [%f:%f]\n", xmin, xmax);
    fprintf(gnuplot, "set yrange [%f:%f]\n", ymin, ymax);
    fprintf(gnuplot, "set size ratio -1\n");
    fprintf(gnuplot, "set xlabel 'x_1'\n");
    fprintf(gnuplot, "set ylabel 'x_2'\n");
    return gnuplot;
}

void plot_close(FILE* gnuplot){
    fprintf(gnuplot, "reset\n");
    fflush(gnuplot);
    pclose(gnuplot);
    return;
}

void plot_shape(int index, data_t *data){
    char baseDir[PATH_LEN] = "../hw3/output";
    float empty_range[2];
    // Original Coordinates - Save
    char filename_orig_save[PATH_LEN];
    sprintf(filename_orig_save, "%s/shape_%d", baseDir, index);
    FILE* gnuplot_data1 = plot_save_open(filename_orig_save);
    for (int i = 0; i < data->num_rows; i++){
        fprintf(gnuplot_data1, "%f %f\n", data->coord_original[i][0], data->coord_original[i][1]);
    }
    plot_save_close(gnuplot_data1);
    // Original Coordinates - Plot
    char filename_orig_plot[PATH_LEN], title_orig_plot[PATH_LEN];
    sprintf(filename_orig_plot, "%s/shape_%d", baseDir, index);
    sprintf(title_orig_plot, "Shape R_%d", index);
    empty_range[0] = (data->orignal_range[1] - data->orignal_range[0]) * 0.1;
    empty_range[1] = (data->orignal_range[3] - data->orignal_range[2]) * 0.1;
    FILE* gnuplot1 = plot_open(filename_orig_plot, data->orignal_range[0]-empty_range[0], data->orignal_range[1]+empty_range[0], data->orignal_range[2]-empty_range[1], data->orignal_range[3]+empty_range[1]);
    fprintf(gnuplot1, "set title '%s'\n", title_orig_plot);
    fprintf(gnuplot1, "plot '%s.dat' notitle with lines lw 5\n", filename_orig_save);
    plot_close(gnuplot1);
    // Pan Coordinates - Save
    char filename_pan_save[PATH_LEN];
    sprintf(filename_pan_save, "%s/shape_%d_pan", baseDir, index);
    FILE* gnuplot_data2 = plot_save_open(filename_pan_save);
    for (int i = 0; i < data->num_rows; i++){
        fprintf(gnuplot_data2, "%f %f\n", data->coord_pan[i][0], data->coord_pan[i][1]);
    }
    plot_save_close(gnuplot_data2);
    // Pan Coordinates - Plot
    char filename_pan_plot[PATH_LEN], title_pan_plot[PATH_LEN];
    sprintf(filename_pan_plot, "%s/shape_%d_pan", baseDir, index);
    sprintf(title_pan_plot, "Shape R_%d", index);
    empty_range[0] = (data->pan_range[1] - data->pan_range[0]) * 0.1;
    empty_range[1] = (data->pan_range[3] - data->pan_range[2]) * 0.1;
    FILE* gnuplot2 = plot_open(filename_pan_plot, data->pan_range[0]-empty_range[0], data->pan_range[1]+empty_range[0], data->pan_range[2]-empty_range[1], data->pan_range[3]+empty_range[1]);
    fprintf(gnuplot2, "set title '%s shifted (%g,%g)'\n", title_pan_plot, data->pan_diff[0], data->pan_diff[1]);
    fprintf(gnuplot2, "plot '%s.dat' notitle with lines lw 5\n", filename_pan_save);
    plot_close(gnuplot2);
    // Zoom Coordinates - Save
    char filename_zoom_save[PATH_LEN];
    sprintf(filename_zoom_save, "%s/shape_%d_zoom", baseDir, index);
    FILE* gnuplot_data3 = plot_save_open(filename_zoom_save);
    for (int i = 0; i < data->num_rows; i++){
        fprintf(gnuplot_data3, "%f %f\n", data->coord_zoom[i][0], data->coord_zoom[i][1]);
    }
    plot_save_close(gnuplot_data3);
    // Zoom Coordinates - Plot
    char filename_zoom_plot[PATH_LEN], title_zoom_plot[PATH_LEN];
    sprintf(filename_zoom_plot, "%s/shape_%d_zoom", baseDir, index);
    sprintf(title_zoom_plot, "Shape R_%d", index);
    empty_range[0] = (data->zoom_range[1] - data->zoom_range[0]) * 0.1;
    empty_range[1] = (data->zoom_range[3] - data->zoom_range[2]) * 0.1;
    FILE* gnuplot3 = plot_open(filename_zoom_plot, data->zoom_range[0]-empty_range[0], data->zoom_range[1]+empty_range[0], data->zoom_range[2]-empty_range[1], data->zoom_range[3]+empty_range[1]);
    fprintf(gnuplot3, "set title '%s scaled %g'\n", title_zoom_plot, data->zoom);
    fprintf(gnuplot3, "plot '%s.dat' notitle with lines lw 5\n", filename_zoom_save);
    plot_close(gnuplot3);
    // Rotate Coordinates - Save
    char filename_rotate_save[PATH_LEN];
    sprintf(filename_rotate_save, "%s/shape_%d_rotate", baseDir, index);
    FILE* gnuplot_data4 = plot_save_open(filename_rotate_save);
    for (int i = 0; i < data->num_rows; i++){
        fprintf(gnuplot_data4, "%f %f\n", data->coord_rotate[i][0], data->coord_rotate[i][1]);
    }
    plot_save_close(gnuplot_data4);
    // Rotate Coordinates - Plot
    char filename_rotate_plot[PATH_LEN], title_rotate_plot[PATH_LEN];
    sprintf(filename_rotate_plot, "%s/shape_%d_rotate", baseDir, index);
    sprintf(title_rotate_plot, "Shape R_%d", index);
    empty_range[0] = (data->rotate_range[1] - data->rotate_range[0]) * 0.1;
    empty_range[1] = (data->rotate_range[3] - data->rotate_range[2]) * 0.1;
    FILE* gnuplot4 = plot_open(filename_rotate_plot, data->rotate_range[0]-empty_range[0], data->rotate_range[1]+empty_range[0], data->rotate_range[2]-empty_range[1], data->rotate_range[3]+empty_range[1]);
    fprintf(gnuplot4, "set title '%s rotated %g'\n", title_rotate_plot, data->rotate);
    fprintf(gnuplot4, "plot '%s.dat' notitle with lines lw 5\n", filename_rotate_save);
    plot_close(gnuplot4);
}
