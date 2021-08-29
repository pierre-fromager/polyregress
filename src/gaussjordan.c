
#include "gaussjordan.h"

static void gj_swap(gj_mat *mat, unsigned i, unsigned k)
{
    gj_vector tmp = (*mat)[i];
    (*mat)[i] = (*mat)[k];
    (*mat)[k] = tmp;
}

static void gj_divide(gj_mat *mat, unsigned i, unsigned j, unsigned m)
{
    unsigned q;
    for (q = j + 1; q < m; q++)
        (*mat)[i][q] /= (*mat)[i][j];
    (*mat)[i][j] = 1;
}

static void gj_eliminate(gj_mat *mat, unsigned i, unsigned j, unsigned n, unsigned m)
{
    unsigned k, q;
    for (k = 0; k < n; k++)
        if (k != i && (*mat)[k][j] != 0)
        {
            for (q = j + 1; q < m; q++)
                (*mat)[k][q] -= (*mat)[k][j] * (*mat)[i][q];
            (*mat)[k][j] = 0;
        }
}

void gj_echelonize(gj_mat *mat, minfo_t *minfo)
{
    unsigned i, j, k;
    i = j = 0;
    while (i < minfo->nbrow && j < minfo->nbcol)
    {
        k = i;
        while (k < minfo->nbrow && (*mat)[k][j] == 0)
            k += 1;
        if (k < minfo->nbrow)
        {
            if (k != i)
                gj_swap(mat, i, k);
            if ((*mat)[i][j] != 1)
                gj_divide(mat, i, j, minfo->nbcol);
            gj_eliminate(mat, i, j, minfo->nbrow, minfo->nbcol);
            i += 1;
        }
        j += 1;
    }
}