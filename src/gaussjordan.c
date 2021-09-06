
#include "gaussjordan.h"

void gauss_divide(pr_vector_t *mat, unsigned i, unsigned j, minfo_t *minfo)
{
    unsigned q;
    for (q = j + 1; q < minfo->nbcol; q++)
    {
        const pr_item_t v = mat_get_value(mat, i, q, minfo) / mat_get_value(mat, i, j, minfo);
        mat_set_value(mat, i, q, minfo, v);
    }
    mat_set_value(mat, i, j, minfo, 1.0);
}

void gauss_eliminate(pr_vector_t *mat, unsigned i, unsigned j, minfo_t *minfo)
{
    unsigned k, q;
    for (k = 0; k < minfo->nbrow; k++)
        if (k != i && mat_get_value(mat, k, j, minfo) != 0)
        {
            for (q = j + 1; q < minfo->nbcol; q++)
            {
                const pr_item_t v = mat_get_value(mat, k, q, minfo) - mat_get_value(mat, k, j, minfo) * mat_get_value(mat, i, q, minfo);
                mat_set_value(mat, k, q, minfo, v);
            }
            mat_set_value(mat, k, j, minfo, 0.0);
        }
}

void gauss_echelonize(pr_vector_t *mat, minfo_t *minfo)
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
                mat_swap_row(mat, i, k, minfo);
            if (mat_get_value(mat, i, j, minfo) != 1)
                gauss_divide(mat, i, j, minfo);
            gauss_eliminate(mat, i, j, minfo);
            i += 1;
        }
        j += 1;
    }
}