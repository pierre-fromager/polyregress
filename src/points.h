
/**
 * @file points.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Points elementary structures and operations
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYREG_POINTS_
#define _POLYREG_POINTS_

#include "matrix.h"

typedef union point_s {
    double point[2];
    struct
    {
        double x;
        double y;
    };
} point_t;

typedef point_t *points_t;

void points_init(gj_vector *data, points_t *points, int nbPoints);

#endif // _POLYREG_POINTS_