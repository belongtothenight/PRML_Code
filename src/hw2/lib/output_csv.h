/**
 * @file output_csv.h
 * @brief Output csv functions
*/

#include "data_proc.h"
#include "normal_distribution.h"
#include "decision_boundary.h"

#ifndef OUTPUT_CSV_H
#define OUTPUT_CSV_H

/**
 * @brief Output the dataset to a csv file
 * @param pFilename Filename to save the csv file
 * @param pDS Pointer to the dataset
 * @param pND Pointer to the normal distribution
*/
void output_csv(char *pFilename, dataset *pDS, norm_dist *pND);

/**
 * @brief Output the decision boundary to a csv file
 * @param pFilename Filename to save the csv file
 * @param pIntersection Pointer to the intersection
*/
void output_decision_boundary_csv(char *pFilename, intersection *pIntersection);

#endif // OUTPUT_CSV_H
