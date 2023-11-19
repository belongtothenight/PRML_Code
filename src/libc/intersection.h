/**
 * @file intersection.h
 * @brief Intersection of two sets
*/

#ifndef INTERSECTION_H
#define INTERSECTION_H

/**
 * @brief Intersection of two dimentional lines
 * @param x x coordinate
 * @param y y coordinate
*/
typedef struct {
    double x;
    double y;
} d2_point_t;

/**
 * @brief Intersection of two dimentional lines
 * @param a1 a1x + b1y = c1
 * @param b1 a1x + b1y = c1
 * @param c1 a1x + b1y = c1
 * @param a2 a2x + b2y = c2
 * @param b2 a2x + b2y = c2
 * @param c2 a2x + b2y = c2
 * @param d2_point pointer to the intersection point
*/
void d2_intersection(double a1, double b1, double c1, double a2, double b2, double c2, d2_point_t *d2_point);

#endif // INTERSECTION_H
