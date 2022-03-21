
#include <test/suite_matrix.h>

static pr_vector_t mat, col, row;
static minfo_t *minfo;

void reset_test_matrix()
{
    minfo->degree = 4;
    minfo->set_dim = mat_set_dim;
    minfo->set_dim(minfo);
}

static int suite_setup(void)
{
    minfo = malloc(sizeof(minfo_t));
    reset_test_matrix();
    mat = malloc((minfo->nbcol * minfo->nbrow) * sizeof(pr_item_t));
    col = malloc(minfo->nbrow * sizeof(pr_item_t));
    row = malloc(minfo->nbcol * sizeof(pr_item_t));
    return 0;
}

static int suite_teardown(void)
{
    free(col);
    free(row);
    free(minfo);
    free(mat);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_polyregress_matrix_mat_set_dim, "mat_set_dim"},
    {test_polyregress_matrix_mat_storage, "mat_storage"},
    {test_polyregress_matrix_mat_set_value, "mat_set_value"},
    {test_polyregress_matrix_mat_get_value, "mat_get_value"},
    {test_polyregress_matrix_mat_get_row, "mat_get_row"},
    {test_polyregress_matrix_mat_get_col, "mat_get_col"},
    {test_polyregress_matrix_mat_set_row, "mat_set_row"},
    {test_polyregress_matrix_mat_swap_row, "mat_swap_row"},
    {test_polyregress_matrix_mat_set_col, "mat_set_col"},
    {test_polyregress_matrix_mat_fill_vect, "mat_fill_vect"},
    {test_polyregress_matrix_mat_init, "mat_init"},
    {test_polyregress_matrix_mat_print_vect, "mat_print_vect"},
    {test_polyregress_matrix_mat_print, "mat_print"},
    {0, 0},
};

void test_polyregress_matrix_add_suite()
{
    const char *suite_name = "matrix";
    const char *suite_err_fmt = "Error adding suite %s : %s\n";
    const char *test_err_fmt = "Error adding test '%s' : %s\n";
    CU_pSuite suite = CU_add_suite(suite_name, suite_setup, suite_teardown);
    if (!suite)
    {
        CU_cleanup_registry();
        printf(suite_err_fmt, suite_name, CU_get_error_msg());
        _exit(3);
    }

    int i;
    for (i = 0; test_functions[i].name; i++)
    {
        if (!CU_add_test(suite, test_functions[i].name, test_functions[i].function))
        {
            CU_cleanup_registry();
            printf(test_err_fmt, test_functions[i].name, CU_get_error_msg());
            _exit(3);
        }
    }
}

void test_polyregress_matrix_mat_set_dim()
{
    reset_test_matrix();
    minfo->degree = 0;
    minfo->nbcol = 0;
    minfo->nbrow = 0;
    minfo->set_dim = mat_set_dim;
    minfo->set_dim(minfo);
    CU_ASSERT_EQUAL(minfo->nbcol, minfo->degree + 2);
    CU_ASSERT_EQUAL(minfo->nbrow, minfo->degree + 1);
    minfo->degree = 4;
    minfo->nbcol = 0;
    minfo->nbrow = 0;
    minfo->set_dim(minfo);
    CU_ASSERT_EQUAL(minfo->nbcol, minfo->degree + 2);
    CU_ASSERT_EQUAL(minfo->nbrow, minfo->degree + 1);
}

void test_polyregress_matrix_mat_storage()
{
    reset_test_matrix();
    mi_item_t stor_ix;
    stor_ix = mat_storage(0, 0, minfo);
    CU_ASSERT_EQUAL(stor_ix, 0);
    stor_ix = mat_storage(minfo->nbrow, minfo->nbcol, minfo);
    CU_ASSERT_NOT_EQUAL(stor_ix, minfo->nbrow * minfo->nbcol);
    CU_ASSERT_EQUAL(stor_ix, 36);
}

void test_polyregress_matrix_mat_set_value()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_matrix();
    pr_item_t val;
    mat_init(&mat, minfo, 0.0);
    mat_set_value(&mat, 0, 0, minfo, 1.0);
    val = mat_get_value(&mat, 0, 0, minfo);
    CU_ASSERT_EQUAL(val, 1.0);
    val = mat_get_value(&mat, 0, 1, minfo);
    CU_ASSERT_EQUAL(val, 0.0);
}

void test_polyregress_matrix_mat_get_value()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_matrix();
    pr_item_t val;
    mat_init(&mat, minfo, 10.0);
    const mi_item_t last_col_number = minfo->nbcol - 1;
    const mi_item_t last_row_number = minfo->nbrow - 1;
    mat_set_value(&mat, last_row_number, last_col_number, minfo, 0.0);
    val = mat_get_value(&mat, last_row_number, last_col_number, minfo);
    CU_ASSERT_EQUAL(val, 0.0);
    val = mat_get_value(&mat, last_row_number, last_col_number - 1, minfo);
    CU_ASSERT_EQUAL(val, 10.0);
}

void test_polyregress_matrix_mat_get_row()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_matrix();
    mi_item_t icol;
    const pr_item_t expected_val = 5.0;
    mat_init(&mat, minfo, expected_val);
    mat_get_row(&mat, minfo, 0, &row);
    for (icol = 0; icol < minfo->nbcol; icol++)
    {
        CU_ASSERT_EQUAL(*(row + icol), expected_val);
        CU_ASSERT_EQUAL(row[icol], expected_val);
    }
}

void test_polyregress_matrix_mat_get_col()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_matrix();
    mi_item_t irow;
    const pr_item_t expected_val = 2.0;
    mat_init(&mat, minfo, expected_val);
    mat_get_col(&mat, minfo, 0, &col);
    for (irow = 0; irow < minfo->nbrow; irow++)
    {
        CU_ASSERT_EQUAL(*(col + irow), expected_val);
        CU_ASSERT_EQUAL(col[irow], expected_val);
    }
}

void test_polyregress_matrix_mat_set_row()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_matrix();
    mi_item_t icol;
    const mi_item_t row_number = 0;
    const pr_item_t expected_val = 1.0;
    mat_init(&mat, minfo, 0.0);
    mat_fill_vect(&row, minfo->nbcol, expected_val);
    for (icol = 0; icol < minfo->nbcol; icol++)
        CU_ASSERT_NOT_EQUAL(mat_get_value(&mat, row_number, icol, minfo), expected_val);
    mat_set_row(&mat, 0, &row, minfo);
    for (icol = 0; icol < minfo->nbcol; icol++)
        CU_ASSERT_EQUAL(mat_get_value(&mat, row_number, icol, minfo), expected_val);
}

void test_polyregress_matrix_mat_swap_row()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_matrix();
    mi_item_t icol;
    const mi_item_t row_number = 0;
    const pr_item_t expected_val = 1.0;
    const pr_item_t initial_val = 0.0;
    mat_init(&mat, minfo, initial_val);
    mat_fill_vect(&row, minfo->nbcol, expected_val);
    for (icol = 0; icol < minfo->nbcol; icol++)
        CU_ASSERT_NOT_EQUAL(mat_get_value(&mat, row_number, icol, minfo), expected_val);
    mat_set_row(&mat, row_number, &row, minfo);
    for (icol = 0; icol < minfo->nbcol; icol++)
        CU_ASSERT_EQUAL(mat_get_value(&mat, row_number, icol, minfo), expected_val);
    mat_swap_row(&mat, row_number, row_number + 1, minfo);
    for (icol = 0; icol < minfo->nbcol; icol++)
        CU_ASSERT_EQUAL(mat_get_value(&mat, row_number, icol, minfo), initial_val);
    for (icol = 0; icol < minfo->nbcol; icol++)
        CU_ASSERT_EQUAL(mat_get_value(&mat, row_number + 1, icol, minfo), expected_val);
}

void test_polyregress_matrix_mat_set_col()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_matrix();
    mi_item_t irow;
    const mi_item_t col_number = 0;
    const mi_item_t col_offset = 0;
    const pr_item_t expected_val = 1.0;
    const pr_item_t initial_val = 0.0;
    mat_init(&mat, minfo, initial_val);
    for (irow = 0; irow < minfo->nbrow; irow++)
        CU_ASSERT_EQUAL(mat_get_value(&mat, irow, col_number, minfo), initial_val);
    mat_fill_vect(&col, minfo->nbrow, expected_val);
    mat_set_col(&mat, col_number, &col, minfo, col_offset);
    for (irow = 0; irow < minfo->nbrow; irow++)
        CU_ASSERT_EQUAL(mat_get_value(&mat, irow, col_number, minfo), expected_val);
}

void test_polyregress_matrix_mat_fill_vect()
{
    reset_test_matrix();
    pr_vector_t vect;
    const mi_item_t vlen = 1024;
    const mi_item_t vlen_half = vlen / 2;
    const pr_item_t initial_val = 0.0;
    const pr_item_t expected_val = 1.0;
    vect = malloc(sizeof(pr_item_t) * vlen);
    mat_fill_vect(&vect, vlen, initial_val);
    CU_ASSERT_EQUAL(*(vect + 0), initial_val);
    CU_ASSERT_EQUAL(*(vect + vlen - 1), initial_val);
    mat_fill_vect(&vect, vlen_half, expected_val);
    CU_ASSERT_EQUAL(*(vect + 0), expected_val);
    CU_ASSERT_EQUAL(*(vect + vlen_half - 1), expected_val);
    free(vect);
}

void test_polyregress_matrix_mat_init()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_matrix();
    mi_item_t icol, irow;
    const pr_item_t initial_val = 3.0;
    mat_init(&mat, minfo, initial_val);
    for (irow = 0; irow < minfo->nbrow; irow++)
        for (icol = 0; icol < minfo->nbcol; icol++)
            CU_ASSERT_EQUAL(mat_get_value(&mat, irow, icol, minfo), initial_val);
}

void test_polyregress_matrix_mat_print_vect()
{
    CU_PASS("Skip printf");
}
void test_polyregress_matrix_mat_print()
{
    CU_PASS("Skip printf");
}
