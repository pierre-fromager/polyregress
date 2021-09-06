/**
 * @file main.c
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief   polyregress.py portage
 *          Data fitting
 *          Find polynome factors from cloud of points
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * @todo https://www.zend.com/generating-php-extension-skeleton
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "gaussjordan.h"
#include "matrix.h"
#include "points.h"
#include "populate.h"
#include "matcalc.h"
#include "solution.h"

#define POLY_DEBUG
#define MSG_USG_0 "Usage degree x0 y0 x1 y1 .. xn yn:\n"
#define MSG_USG_1 "echo \"4 1 0 2 2 3 1 4 4 5 2\" | %s - \n"
#define DSIZE 10
#define RAW_ARR_SIZE 2048

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(MSG_USG_0);
        printf(MSG_USG_1, argv[0]);
        exit(EXIT_FAILURE);
    }
    pr_vector_t raw_data;
    mi_item_t datacpt, degree;
    degree = datacpt = 0;
    raw_data = malloc(sizeof(pr_item_t) * RAW_ARR_SIZE);
    populate_data(&raw_data, &datacpt, &degree, stdin);
    populate_check(datacpt, degree);
    const mi_item_t nb_points = datacpt / 2;
    minfo_t *minfo;
    minfo = malloc(sizeof(minfo_t));
    minfo->degree = degree;
    minfo->set_dim = mat_set_dim;
    minfo->set_dim(minfo);
    minfo->nbpoints = nb_points;
    mi_item_t c;
    points_t points;
    pr_vector_t mpc;
    pr_vector_t mat;

    points = malloc(sizeof(point_t) * nb_points);
    mpc = malloc(sizeof(pr_item_t) * datacpt);
    mat = malloc((minfo->nbcol * minfo->nbrow) * sizeof(pr_item_t));

    points_init(&raw_data, &points, datacpt);
    free(raw_data);

    matcalc_mpc(&mpc, &points, minfo);
    mat_init(&mat, minfo, 0.0);
#ifdef POLY_DEBUG
    mat_print(&mat, minfo, stdout);
#endif
    mat_set_row(&mat, 0, &mpc, minfo);
    for (c = 0; c < minfo->nbrow; ++c)
        mat_set_col(&mat, c, &mpc, minfo, c);
    free(mpc);

    matcalc_rhs(&mat, &points, minfo);
    free(points);

#ifdef POLY_DEBUG
    mat_print(&mat, minfo, stdout);
#endif
    gauss_echelonize(&mat, minfo);
#ifdef POLY_DEBUG
    mat_print(&mat, minfo, stdout);
    printf("\n");
#endif
    solution_print(&mat, minfo, stdout);

    free(minfo);
    free(mat);
    return 0;
}
