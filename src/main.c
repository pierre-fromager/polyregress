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

//#define POLY_DEBUG
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
    gj_vector raw_data;
    int datacpt = -1;
    int degree = 0;
    raw_data = malloc(sizeof(double) * RAW_ARR_SIZE);
    populate_data(&raw_data, &datacpt, &degree);
    populate_check(datacpt, degree);
    const int nbPoints = datacpt / 2;
    const size_t psize = sizeof(point_t) * nbPoints;
    const size_t mpcSize = sizeof(double) * datacpt;
    const size_t minfoSize = sizeof(minfo_t);
    minfo_t *minfo;
    minfo = malloc(minfoSize);
    minfo->degree = degree;
    minfo->nbcol = minfo->degree + 2;
    minfo->nbrow = minfo->degree + 1;
    minfo->nbpoints = nbPoints;
    const size_t msize = (minfo->nbcol * minfo->nbrow) * sizeof(double);
    unsigned c, r;
    points_t points;
    gj_vector mpc;
    gj_vector mat;
    gj_mat gjmat;

    points = malloc(psize);
    mpc = malloc(mpcSize);
    mat = malloc(msize);

    points_init(&raw_data, &points, datacpt);
    free(raw_data);
    matcalc_mpc(&mpc, &points, minfo);
    mat_init(&mat, minfo, 0);
#ifdef POLY_DEBUG
    mat_print(&mat, minfo);
#endif
    mat_set_row(&mat, 0, &mpc, minfo);
    for (c = 0; c < minfo->nbrow; ++c)
        mat_set_col(&mat, c, &mpc, minfo, c);
    free(mpc);
    matcalc_rhs(&mat, &points, minfo);
    free(points);
#ifdef POLY_DEBUG
    mat_print(&mat, minfo);
#endif
    const size_t gjmatRowSize = sizeof(double) * minfo->nbrow;
    const size_t gjmatColSize = sizeof(double) * minfo->nbcol;
    gjmat = malloc(gjmatRowSize);
    for (r = 0; r < minfo->nbrow; r++)
    {
        gjmat[r] = malloc(gjmatColSize);
        mat_get_row(&mat, minfo, r, &gjmat[r]);
    }
    gj_echelonize(&gjmat, minfo);
    for (r = 0; r < minfo->nbrow; r++)
        mat_set_row(&mat, r, &gjmat[r], minfo);
    for (r = 0; r < minfo->nbrow; r++)
        free(gjmat[r]);
    free(gjmat);
#ifdef POLY_DEBUG
    mat_print(&mat, minfo);
    printf("\n");
#endif
    solution_print(&mat, minfo, gjmatColSize);
    free(minfo);
    free(mat);
    return 0;
}
