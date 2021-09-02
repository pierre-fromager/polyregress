
#include "matcalc.h"

void matcalc_mpc(gj_vector *mpc, points_t *points, minfo_t *minfo)
{
    unsigned cr, cl;
    double s;
    *(*mpc) = minfo->nbpoints;
    const unsigned rs = (2 * minfo->degree) + 1;
    for (cr = 1; cr < rs; cr++)
    {
        s = 0;
        for (cl = 0; cl < minfo->nbpoints; cl++)
            s += pow((*points)[cl].x, (double)cr);
        *(*mpc + cr) = s;
    }
}

void matcalc_rhs(gj_vector *mat, points_t *points, minfo_t *minfo)
{
    unsigned c, r;
    double rhs;
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
            rhs += pow((*points)[c].x, (double)r) * (*points)[c].y;
        mat_set_value(mat, r, minfo->nbcol - 1, minfo, rhs);
    }
}