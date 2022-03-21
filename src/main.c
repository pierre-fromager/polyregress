/**
 * @file main.c
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief   polyregress.py portage
 *          Data fitting
 *          Find polynome factors from cloud of points
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "arguments.h"
#include "gaussjordan.h"
#include "matrix.h"
#include "points.h"
#include "populate.h"
#include "matcalc.h"
#include "solution.h"

#define DSIZE 10
#define RAW_ARR_SIZE 2048

int main(int argc, char *argv[])
{
    FILE *streamin = stdin;
    FILE *streamout = stdout;
    arguments_t args;
    arguments_process(argc, argv, &args);
    pr_vector_t raw_data;
    mi_item_t datacpt, degree;
    degree = datacpt = 0;
    raw_data = malloc(sizeof(pr_item_t) * RAW_ARR_SIZE);
    populate_data(&raw_data, &datacpt, &degree, streamin, args.separator);
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
    if (args.debug)
        mat_print(&mat, minfo, streamout);
    mat_set_row(&mat, 0, &mpc, minfo);
    for (c = 0; c < minfo->nbrow; ++c)
        mat_set_col(&mat, c, &mpc, minfo, c);
    free(mpc);
    matcalc_rhs(&mat, &points, minfo);
    free(points);
    if (args.debug)
        mat_print(&mat, minfo, streamout);
    gauss_echelonize(&mat, minfo);
    if (args.debug)
        mat_print(&mat, minfo, streamout);
    solution_print(&mat, minfo, streamout);
    free(minfo);
    free(mat);
    return 0;
}
