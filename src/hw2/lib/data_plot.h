/**
 * @file data_plot.h
 * @brief Plotting functions for data
 */

#include <stdio.h>
#include <stdlib.h>
#include "data_proc.h"
#include "decision_boundary.h"

#ifndef DATA_PLOT_H
#define DATA_PLOT_H

#define GNUPLOT_TERMINAL "wxt enhanced" ///< "qt" for qt terminal, "wxt" for wxt terminal

/******************************************************************************************/
// help functions 

/**
 * @brief Open gnuplot
 * @param pFilename Filename to save the plot
*/
FILE* plot_open(char* pFilename);

/**
 * @brief Close gnuplot
 * @param gnuplot gnuplot file pointer
*/
void plot_close(FILE* gnuplot);

/**
 * @brief Open gnuplot for saving
*/
FILE* plot_save_open();

/**
 * @brief Close gnuplot for saving
 * @param gnuplot gnuplot file pointer
*/
void plot_save_close(FILE *gnuplot);

/******************************************************************************************/
// plot functions

/**
 * @brief Plot data
 * @param pData Pointer to the dataset
 * @param pFilename Filename to save the plot
*/
void test_plot(dataset* pData, char* pFilename);

// save data to file

/**
 * @brief Save data to file
 * @param pData Pointer to the dataset
 * @param pFilename Filename to save the data
*/
void save_data_div5_cnt(dataset *pData, char *pFilename);

/**
 * @brief Save data to file
 * @param pFilename Filename to save the data
 * @param x_min Minimum value of x
 * @param x_max Maximum value of x
 * @param mu Mean of the data
 * @param sigma Standard deviation of the data
*/
void save_data_div5_norm(char* pFilename, float x_min, float x_max, float mu, float sigma);

/**
 * @brief Save vertical line data to file
 * @param pFilename Filename to save the data
 * @param x x value
 * @param y1 y minimum value
 * @param y2 y maximum value
*/
void save_data_vertical_line(char* pFilename, float x, float y1, float y2);

// plot div5

/**
 * @brief Plot data
 * @param pData Pointer to the dataset
 * @param pFilename Filename to save the plot
 * @param pTMP1 Temporary file name
 * @param pTMP2 Temporary file name
*/
void plot_data_div5(dataset* pData, char* pFilename, char* pTMP1, char* pTMP2);

/**
 * @brief Plot data
 * @param pData1 Pointer to the dataset 1
 * @param pData2 Pointer to the dataset 2
 * @param pITS Pointer to the intersection
 * @param pFilename Filename to save the plot
 * @param pTMP1 Temporary file name
 * @param pTMP2 Temporary file name
 * @param pTMP3 Temporary file name
*/
void plot_stacked_data_div5(dataset* pData1, dataset* pData2, intersection* pITS, char* pFilename, char* pTMP1, char* pTMP2, char* pTMP3);

#endif // DATA_PLOT_H
