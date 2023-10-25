#include <stdio.h>
#include <stdlib.h>
#include "data_proc.h"
#include "normal_distribution.h"
#include "output_format.h"
#include "decision_boundary.h"

void output_csv(char *pFilename, dataset *pDS, norm_dist *pND){
    output_format Format;
    get_format(&Format);
    FILE* fp = fopen(pFilename, "w");
    if (fp == NULL){
        printf("%sERROR%s: file %s not found...\n\r", Format.foreground.red, Format.style.reset, pFilename);
        exit(1);
    }
    fprintf(fp, "Stats (%s)\n", UNIT);
    fprintf(fp, "Size, %d\n", pDS->size);
    fprintf(fp, "Min, %f\n", pDS->min);
    fprintf(fp, "Max, %f\n", pDS->max);
    fprintf(fp, "Variance_biased, %f\n", pDS->variance_biased);
    fprintf(fp, "Variance_unbiased, %f\n", pDS->variance_unbiased);
    fprintf(fp, "Mu, %f\n", pND->mu);
    fprintf(fp, "Sigma, %f\n", pND->sigma);
    fprintf(fp, "Split points, %g, %g, %g, %g, %g, %g\n", pDS->split_points[0], pDS->split_points[1], pDS->split_points[2], pDS->split_points[3], pDS->split_points[4], pDS->split_points[5]);
    fprintf(fp, "Split step, %g\n", pDS->split_step);
    fprintf(fp, "Split points center, %g, %g, %g, %g, %g\n", pDS->split_points_center[0], pDS->split_points_center[1], pDS->split_points_center[2], pDS->split_points_center[3], pDS->split_points_center[4]);
    fprintf(fp, "Split count, %d, %d, %d, %d, %d\n", pDS->split_count[0], pDS->split_count[1], pDS->split_count[2], pDS->split_count[3], pDS->split_count[4]);
    fprintf(fp, "Normal split points, %g, %g, %g, %g, %g, %g, %g\n", pDS->normal_split_points[0], pDS->normal_split_points[1], pDS->normal_split_points[2], pDS->normal_split_points[3], pDS->normal_split_points[4], pDS->normal_split_points[5], pDS->normal_split_points[6]);
    fprintf(fp, "Normal split points center, %g, %g, %g, %g, %g, %g, %g, %g\n", pDS->normal_split_points_center[0], pDS->normal_split_points_center[1], pDS->normal_split_points_center[2], pDS->normal_split_points_center[3], pDS->normal_split_points_center[4], pDS->normal_split_points_center[5], pDS->normal_split_points_center[6], pDS->normal_split_points_center[7]);
    fprintf(fp, "Normal split count, %d, %d, %d, %d, %d, %d, %d, %d\n", pDS->normal_split_count[0], pDS->normal_split_count[1], pDS->normal_split_count[2], pDS->normal_split_count[3], pDS->normal_split_count[4], pDS->normal_split_count[5], pDS->normal_split_count[6], pDS->normal_split_count[7]);
    fprintf(fp, "\n");
    fprintf(fp, "Normal distribution (%s)\n", UNIT);
    fprintf(fp, "Mu, %f\n", pND->mu);
    fprintf(fp, "Sigma, %f\n", pND->sigma);
    fprintf(fp, "Integral step, %f\n", pND->integral_step);
    fprintf(fp, "X min, %f\n", pND->x_min);
    fprintf(fp, "X max, %f\n", pND->x_max);
    fprintf(fp, "Arr length, %d\n", pND->arr_length);
    fprintf(fp, "Integral, %f\n", pND->integral);

    fclose(fp);
    printf("%sSUCCESS%s: Data written to file %s.\n\r", Format.foreground.green, Format.style.reset, pFilename);
    return;
}

void output_decision_boundary_csv(char *pFilename, intersection *pIntersection){
    output_format Format;
    get_format(&Format);
    FILE* fp = fopen(pFilename, "w");
    if (fp == NULL){
        printf("%sERROR%s: file %s not found...\n\r", Format.foreground.red, Format.style.reset, pFilename);
        exit(1);
    }
    fprintf(fp, "Intersection\n");
    fprintf(fp, "Index 1, %d\n", pIntersection->idx1);
    fprintf(fp, "Index 2, %d\n", pIntersection->idx2);
    fprintf(fp, "Y 1, %f\n", pIntersection->y1);
    fprintf(fp, "Y 2, %f\n", pIntersection->y2);
    fprintf(fp, "X 1, %f\n", pIntersection->x1);
    fprintf(fp, "X 2, %f\n", pIntersection->x2);
    fprintf(fp, "Average X, %f\n", pIntersection->avg_x);
    fprintf(fp, "Minimum error, %f\n", pIntersection->min_error);

    fclose(fp);
    printf("%sSUCCESS%s: Data written to file %s.\n\r", Format.foreground.green, Format.style.reset, pFilename);
    return;
}
