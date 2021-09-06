
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

typedef struct point_s
{
    pr_item_t x;
    pr_item_t y;
} point_t;

typedef point_t *points_t;

void points_init(pr_vector_t *data, points_t *points, mi_item_t nbPoints);

#endif // _POLYREG_POINTS_