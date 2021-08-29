
#include "matrix.h"

void mat_set_value(gj_vector *mat, int row, int col, minfo_t *minfo, double value)
{
    (*mat)[(col * minfo->nbrow) + row] = value;
}

double mat_get_value(gj_vector *mat, int row, int col, minfo_t *minfo)
{
    return (*mat)[(col * minfo->nbrow) + row];
}

void mat_get_row(gj_vector mat, minfo_t *minfo, int row, gj_vector rowvect)
{
    unsigned cols;
    for (cols = 1; cols < minfo->nbcol; cols++)
        rowvect[cols] = mat_get_value(&mat, row, cols, minfo);
}

void mat_get_col(gj_vector *mat, minfo_t *minfo, int col, gj_vector *colvect)
{
    unsigned rows;
    for (rows = 0; rows < minfo->nbrow; rows++)
        (*colvect)[rows] = mat_get_value(mat, rows, col, minfo);
}

void mat_set_row(gj_vector *mat, int row, gj_vector *vect, minfo_t *minfo)
{
    unsigned cols;
    for (cols = 0; cols < minfo->nbcol; cols++)
        mat_set_value(mat, row, cols, minfo, (*vect)[cols]);
}

void mat_set_col(gj_vector *mat, int col, gj_vector *vect, minfo_t *minfo, unsigned offset)
{
    unsigned rows;
    for (rows = 0; rows < minfo->nbrow; rows++)
        mat_set_value(mat, rows, col, minfo, (*vect)[rows + offset]);
}

void mat_print(gj_vector *mat, minfo_t *minfo)
{
    unsigned cols, rows;
    printf("\n");
    for (rows = 0; rows < minfo->nbrow; rows++)
    {
        for (cols = 0; cols < minfo->nbcol; cols++)
            printf("%7.5lf \t", mat_get_value(mat, rows, cols, minfo));
        printf("\n");
    }
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
    unsigned i, j;
    for (j = 0; j < minfo->nbcol; j++)
        for (i = 0; i < minfo->nbrow; i++)
            mat_set_value(mat, i, j, minfo, value);
}
