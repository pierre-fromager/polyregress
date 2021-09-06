
#include "suite_points.h"

pr_vector_t datapoints;
point_t *points;
mi_item_t nb_points;

const pr_item_t suite_points_data[] = {1.0, 0.0, 2.0, 2.0, 3.0, 1.0, 4.0, 4.0, 5.0, 2.0};
const pr_item_t exptected_suite_points_x[SUITE_POINTS_NB_POINTS] = {1, 2, 3, 4, 5};
const pr_item_t exptected_suite_points_y[SUITE_POINTS_NB_POINTS] = {0, 2, 1, 4, 2};

static int suite_setup(void)
{
    nb_points = SUITE_POINTS_NB_POINTS * 2;
    size_t datapoints_asize = (sizeof(pr_item_t) * nb_points);
    datapoints = malloc(datapoints_asize);
    memcpy(datapoints, &suite_points_data, datapoints_asize);
    points = malloc(sizeof(point_t) * SUITE_POINTS_NB_POINTS);
    return 0;
}

static int suite_teardown(void)
{
    free(points);
    free(datapoints);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_polyregress_points_points_init, "points_init"},
    {0, 0},
};

void test_polyregress_points_add_suite()
{
    const char *suite_name = "points";
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

void test_polyregress_points_points_init()
{
    mi_item_t pts_cpt;
    points_init(&datapoints, &points, nb_points);
    for (pts_cpt = 0; pts_cpt < SUITE_POINTS_NB_POINTS; pts_cpt++)
    {
        CU_ASSERT_EQUAL(points[pts_cpt].x, exptected_suite_points_x[pts_cpt]);
        CU_ASSERT_EQUAL(points[pts_cpt].y, exptected_suite_points_y[pts_cpt]);
    }
}
