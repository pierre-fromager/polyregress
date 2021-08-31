
#include "matrix.h"

static unsigned mat_storage(int row, int col, minfo_t *minfo)
{
    return (row * minfo->nbcol) + col;
}

void mat_set_value(gj_vector *mat, int row, int col, minfo_t *minfo, double value)
{
    *(*mat + mat_storage(row, col, minfo)) = value;
}

double mat_get_value(gj_vector *mat, int row, int col, minfo_t *minfo)
{
    return *(*mat + mat_storage(row, col, minfo));
}

void mat_get_row(gj_vector *mat, minfo_t *minfo, int row, gj_vector *rowvect)
{
    memcpy(*rowvect, *mat + mat_storage(row, 0, minfo), sizeof(double) * minfo->nbcol);
}

void mat_get_col(gj_vector *mat, minfo_t *minfo, int col, gj_vector *colvect)
{
    unsigned rows;
    for (rows = 0; rows < minfo->nbrow; rows++)
        (*colvect)[rows] = mat_get_value(mat, rows, col, minfo);
}

void mat_set_row(gj_vector *mat, int row, gj_vector *vect, minfo_t *minfo)
{
    memcpy(*mat + mat_storage(row, 0, minfo), *vect, sizeof(double) * minfo->nbcol);
}

void mat_swap_row(gj_vector *mat, int i, int k, minfo_t *minfo)
{
    gj_vector ritmp, rktmp;
    const size_t asize = sizeof(double) * minfo->nbcol;
    ritmp = malloc(asize);
    rktmp = malloc(asize);
    mat_get_row(mat, minfo, i, &ritmp);
    mat_get_row(mat, minfo, k, &rktmp);
    mat_set_row(mat, k, &ritmp, minfo);
    mat_set_row(mat, i, &rktmp, minfo);
    free(ritmp);
    free(rktmp);
}

void mat_set_col(gj_vector *mat, int col, gj_vector *vect, minfo_t *minfo, unsigned offset)
{
    unsigned rows;
    for (rows = 0; rows < minfo->nbrow; rows++)
        mat_set_value(mat, rows, col, minfo, (*vect)[rows + offset]);
}

void mat_print(gj_vector *mat, minfo_t *minfo)
{
    unsigned rows;
    gj_vector rv;
    printf("\n");
    rv = malloc(sizeof(double) * minfo->nbcol);
    for (rows = 0; rows < minfo->nbrow; rows++)
    {
        mat_get_row(mat, minfo, rows, &rv);
        mat_print_vect(rv, minfo->nbcol);
    }
    free(rv);
}

void mat_fill_vect(gj_vector vect, unsigned size, double value)
{
    unsigned i;
    for (i = 0; i < size; i++)
        *(vect + i) = value;
}

void mat_print_vect(gj_vector vect, unsigned size)
{
    unsigned i;
    for (i = 0; i < size; i++)
        printf("%7.5lf \t", vect[i]);
    printf("\n");
}

void mat_init(gj_vector *mat, minfo_t *minfo, double value)
{
    unsigned i;
    gj_vector rowvect;
    rowvect = malloc(sizeof(double) * minfo->nbcol);
    mat_fill_vect(rowvect, minfo->nbcol, value);
    for (i = 0; i < minfo->nbrow; i++)
        mat_set_row(mat, i, &rowvect, minfo);
    free(rowvect);
}
