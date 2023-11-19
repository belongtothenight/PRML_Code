/**
 * @file distance.h
 * @brief Distance calculation functions
 * Ref:
 * 1. 
*/

#ifndef DISTANCE_H
#define DISTANCE_H

#include <math.h>

/**
 * @brief Calculate the straight line distance between two points
 * @param x1 x value of the first point
 * @param y1 y value of the first point
 * @param x2 x value of the second point
 * @param y2 y value of the second point
*/
float distance_straightline(float x1, float y1, float x2, float y2);

/**
 * @brief Calculate 2D distance between a point and a line (ax + by = c)
 * @param x x value of the point
 * @param y y value of the point
 * @param a a value of the line
 * @param b b value of the line
 * @param c c value of the line
*/
double distance_2Dpoint2line(double x, double y, double a, double b, double c);

/**
 * @brief Calculate the hamming distance between two points
 * @param x1 x value of the first point
 * @param y1 y value of the first point
 * @param x2 x value of the second point
 * @param y2 y value of the second point
*/
float distance_hamming(float x1, float y1, float x2, float y2);

/**
 * @brief Calculate the euclidean distance between two points
 * @param x1 x value of the first point
 * @param y1 y value of the first point
 * @param x2 x value of the second point
 * @param y2 y value of the second point
*/
float distance_euclidean(float x1, float y1, float x2, float y2);

/**
 * @brief Calculate the manhattan distance between two points
 * @param x1 x value of the first point
 * @param y1 y value of the first point
 * @param x2 x value of the second point
 * @param y2 y value of the second point
*/
float distance_manhattan(float x1, float y1, float x2, float y2);

/**
 * @brief Calculate the chebyshev distance between two points
 * @param x1 x value of the first point
 * @param y1 y value of the first point
 * @param x2 x value of the second point
 * @param y2 y value of the second point
*/
float distance_minkowski(float x1, float y1, float x2, float y2);

# endif
