
#include "gaussjordan.h"

static void gj_swap(gj_vector *mat, unsigned i, unsigned k, minfo_t *minfo)
{
    mat_swap_row(mat, i, k, minfo);
}

static void gj_divide(gj_vector *mat, unsigned i, unsigned j, minfo_t *minfo)
{
    unsigned q;
    for (q = j + 1; q < minfo->nbcol; q++)
    {
        const double v = mat_get_value(mat, i, q, minfo) / mat_get_value(mat, i, j, minfo);
        mat_set_value(mat, i, q, minfo, v);
    }
    mat_set_value(mat, i, j, minfo, 1);
}

static void gj_eliminate(gj_vector *mat, unsigned i, unsigned j, minfo_t *minfo)
{
    unsigned k, q;
    for (k = 0; k < minfo->nbrow; k++)
        if (k != i && mat_get_value(mat, k, j, minfo) != 0)
        {
            for (q = j + 1; q < minfo->nbcol; q++)
            {
                const double v = mat_get_value(mat, k, q, minfo) - mat_get_value(mat, k, j, minfo) * mat_get_value(mat, i, q, minfo);
                mat_set_value(mat, k, q, minfo, v);
            }
            mat_set_value(mat, k, j, minfo, 0);
        }
}

void gj_echelonize(gj_vector *mat, minfo_t *minfo)
{
    unsigned i, j, k;
    i = j = 0;
    while (i < minfo->nbrow && j < minfo->nbcol)
    {
        k = i;
        while (k < minfo->nbrow && mat_get_value(mat, k, j, minfo) == 0)
            k += 1;
        if (k < minfo->nbrow)
        {
            if (k != i)
                gj_swap(mat, i, k, minfo);

            if (mat_get_value(mat, i, j, minfo) != 1)
                gj_divide(mat, i, j, minfo);

            gj_eliminate(mat, i, j, minfo);
            i += 1;
        }
        j += 1;
    }
}