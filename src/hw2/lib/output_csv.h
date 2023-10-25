#include "data_proc.h"
#include "normal_distribution.h"

#ifndef OUTPUT_CSV_H
#define OUTPUT_CSV_H

void output_csv(char *pFilename, dataset *pDS, norm_dist *pND);

void output_decision_boundary_csv(char *pFilename, intersection *pIntersection);

#endif // OUTPUT_CSV_H
