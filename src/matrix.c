
#include "matrix.h"

minfo_ptr_t mat_set_dim(minfo_t *self)
{
    self->nbcol = self->degree + 2;
    self->nbrow = self->degree + 1;
    return self;
}

static size_t mat_row_asize(minfo_t *minfo)
{
    return sizeof(pr_item_t) * minfo->nbcol;
}

unsigned mat_storage(unsigned row, unsigned col, minfo_t *minfo)
{
    return (row * minfo->nbcol) + col;
}

void mat_set_value(pr_vector_t *mat, unsigned row, unsigned col, minfo_t *minfo, pr_item_t value)
{
    *(*mat + mat_storage(row, col, minfo)) = value;
}

pr_item_t mat_get_value(pr_vector_t *mat, unsigned row, unsigned col, minfo_t *minfo)
{
    return *(*mat + mat_storage(row, col, minfo));
}

void mat_get_row(pr_vector_t *mat, minfo_t *minfo, unsigned row, pr_vector_t *rowvect)
{
    memcpy(*rowvect, *mat + mat_storage(row, 0, minfo), mat_row_asize(minfo));
}

void mat_get_col(pr_vector_t *mat, minfo_t *minfo, unsigned col, pr_vector_t *colvect)
{
    unsigned rows;
    for (rows = 0; rows < minfo->nbrow; rows++)
        *(*colvect + rows) = mat_get_value(mat, rows, col, minfo);
}

void mat_set_row(pr_vector_t *mat, unsigned row, pr_vector_t *vect, minfo_t *minfo)
{
    memcpy(*mat + mat_storage(row, 0, minfo), *vect, mat_row_asize(minfo));
}

void mat_swap_row(pr_vector_t *mat, unsigned i, unsigned k, minfo_t *minfo)
{
    pr_vector_t ritmp, rktmp;
    const size_t asize = mat_row_asize(minfo);
    ritmp = malloc(asize);
    rktmp = malloc(asize);
    mat_get_row(mat, minfo, i, &ritmp);
    mat_get_row(mat, minfo, k, &rktmp);
    mat_set_row(mat, k, &ritmp, minfo);
    mat_set_row(mat, i, &rktmp, minfo);
    free(ritmp);
    free(rktmp);
}

void mat_set_col(pr_vector_t *mat, unsigned col, pr_vector_t *vect, minfo_t *minfo, unsigned offset)
{
    unsigned rows;
    for (rows = 0; rows < minfo->nbrow; rows++)
        mat_set_value(mat, rows, col, minfo, *(*vect + rows + offset));
}

void mat_print(pr_vector_t *mat, minfo_t *minfo, FILE *stream)
{
    unsigned rows;
    pr_vector_t rv;
    fprintf(stream, "\n");
    rv = malloc(mat_row_asize(minfo));
    for (rows = 0; rows < minfo->nbrow; rows++)
    {
        mat_get_row(mat, minfo, rows, &rv);
        mat_print_vect(&rv, minfo->nbcol, stream);
    }
    free(rv);
}

void mat_fill_vect(pr_vector_t *vect, unsigned size, pr_item_t value)
{
    unsigned i;
    for (i = 0; i < size; i++)
        *(*vect + i) = value;
}

void mat_print_vect(pr_vector_t *vect, unsigned size, FILE *stream)
{
    unsigned i;
    for (i = 0; i < size; i++)
        fprintf(stream, "%7.5lf \t", *(*vect + i));
    fprintf(stream, "\n");
}

void mat_init(pr_vector_t *mat, minfo_t *minfo, pr_item_t value)
{
    unsigned i;
    pr_vector_t rowvect;
    rowvect = malloc(mat_row_asize(minfo));
    mat_fill_vect(&rowvect, minfo->nbcol, value);
    for (i = 0; i < minfo->nbrow; i++)
        mat_set_row(mat, i, &rowvect, minfo);
    free(rowvect);
}
