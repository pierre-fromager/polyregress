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
#include <math.h>
#include "gaussjordan.h"
#include "matrix.h"
#include "points.h"
#include "solution.h"

#define MSG_USG_0 "Usage degree x0 y0 x1 y1 .. xn yn:\n"
#define MSG_USG_1 "echo \"4 1 0 2 2 3 1 4 4 5 2\" | %s - \n"
#define MSG_ERR_POINTS "Error: data not in form of x,y pairs.\n"
#define MSG_ERR_DEGREE "Warning: polynomial degree %d > nb points %d.\n"

#define DELIM " "
#define DSIZE 10

#define LINE_BUF_SIZE 128
#define RAW_ARR_SIZE 2048
//#define POLY_DEBUG

static void calc_mpc(gj_vector *mpc, points_t *points, minfo_t *minfo);
static void calc_rhs(gj_vector *mat, points_t *points, minfo_t *minfo);
static void populate_data(gj_vector *rawArray, int *datacpt, int *degree);
static void check_populate(int datacpt, int degree);

static void calc_mpc(gj_vector *mpc, points_t *points, minfo_t *minfo)
{
    unsigned cr, cl;
    double s;
    (*mpc)[0] = minfo->nbpoints;
    const unsigned rs = (2 * minfo->degree) + 1;
    for (cr = 1; cr < rs; cr++)
    {
        s = 0;
        for (cl = 0; cl < minfo->nbpoints; cl++)
            s += pow((*points)[cl].x, cr);
        (*mpc)[cr] = s;
    }
}

static void calc_rhs(gj_vector *mat, points_t *points, minfo_t *minfo)
{
    unsigned c, r, rhs;
    rhs = 0;
    for (c = 0; c < minfo->nbpoints; ++c)
        rhs += (*points)[c].y;
    mat_set_value(mat, 0, minfo->nbcol - 1, minfo, rhs);
    rhs = 0;
    for (c = 0; c < minfo->nbpoints; ++c)
        rhs += (*points)[c].x * (*points)[c].y;
    mat_set_value(mat, 1, minfo->nbcol - 1, minfo, rhs);
    for (r = 2; r < minfo->nbrow; r++)
    {
        rhs = 0;
        for (c = 0; c < minfo->nbpoints; c++)
            rhs += pow((*points)[c].x, r) * (*points)[c].y;
        mat_set_value(mat, r, minfo->nbcol - 1, minfo, rhs);
    }
}

static void populate_data(gj_vector *rawArray, int *datacpt, int *degree)
{
    char bufin[LINE_BUF_SIZE];
    while (fgets(bufin, LINE_BUF_SIZE, stdin))
    {
        char *value = strtok(bufin, DELIM);
        while (value)
        {
            if ((*datacpt) == -1)
                (*degree) = atoi(value);
            else
                (*rawArray)[(*datacpt)] = atof(value);
            value = strtok(NULL, DELIM);
            (*datacpt)++;
        }
    }
}

static void check_populate(int datacpt, int degree)
{
    if (datacpt % 2 != 0)
    {
        printf(MSG_ERR_POINTS);
        exit(EXIT_FAILURE);
    }

    if (degree + 1 > datacpt / 2)
    {
        printf(MSG_ERR_DEGREE, degree, datacpt / 2);
        exit(EXIT_FAILURE);
    }
}

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
    check_populate(datacpt, degree);
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
    calc_mpc(&mpc, &points, minfo);
    mat_init(&mat, minfo, 0);

    mat_set_row(&mat, 0, &mpc, minfo);
    for (c = 0; c < minfo->nbrow; ++c)
        mat_set_col(&mat, c, &mpc, minfo, c);
    free(mpc);

    calc_rhs(&mat, &points, minfo);
    free(points);
#ifdef POLY_DEBUG    
    mat_print(&mat, minfo);
#endif
    const size_t gjmatRowSize = sizeof(double) * minfo->nbrow;
    const size_t gjmatColSize = sizeof(double) * minfo->nbcol;
    // 1D to 2D array
    gjmat = malloc(gjmatRowSize);
    for (r = 0; r < minfo->nbrow; r++)
    {
        gjmat[r] = malloc(gjmatColSize);
        for (c = 0; c < minfo->nbcol; c++)
            gjmat[r][c] = mat_get_value(&mat, r, c, minfo);
    }
    gj_echelonize(&gjmat, minfo);
    // 2D to 1D array
    for (r = 0; r < minfo->nbrow; r++)
        for (c = 0; c < minfo->nbcol; c++)
            mat_set_value(&mat, r, c, minfo, gjmat[r][c]);

    for (r = 0; r < minfo->nbrow; r++)
        free(gjmat[r]);
    free(gjmat);
#ifdef POLY_DEBUG
    mat_print(&mat, minfo);
    printf("\n");
#endif
    //print_sol(&mat, minfo, gjmatColSize);
    solution_print(&mat, minfo, gjmatColSize);

    free(minfo);
    free(mat);
    return 0;
}
