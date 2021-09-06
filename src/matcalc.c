
#include "matcalc.h"

void matcalc_mpc(pr_vector_t *mpc, points_t *points, minfo_t *minfo)
{
    mi_item_t cr, cl;
    pr_item_t s;
    *(*mpc) = minfo->nbpoints;
    const mi_item_t rs = (2 * minfo->degree) + 1;
    for (cr = 1; cr < rs; cr++)
    {
        s = 0;
        for (cl = 0; cl < minfo->nbpoints; cl++)
            s += pow((*points)[cl].x, (pr_item_t)cr);
        *(*mpc + cr) = s;
    }
}

void matcalc_rhs(pr_vector_t *mat, points_t *points, minfo_t *minfo)
{
    mi_item_t c, r;
    pr_item_t rhs;
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
            rhs += pow((*points)[c].x, (pr_item_t)r) * (*points)[c].y;
        mat_set_value(mat, r, minfo->nbcol - 1, minfo, rhs);
    }
}