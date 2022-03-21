
#include <test/suite_populate.h>

static pr_vector_t datapoints;
static mi_item_t nb_points, degree;
static FILE *handle;
static const char *points_filename = "test/data/points.txt";

static const mi_item_t expected_degree = 4;
static const mi_item_t expected_nb_points = 10;
static const pr_item_t expected_points[] = {1.0, 0.0, 2.0, 2.0, 3.0, 1.0, 4.0, 4.0, 5.0, 2.0};

static int suite_setup(void)
{
    nb_points = 0;
    degree = 0;
    datapoints = malloc(sizeof(pr_item_t) * 2048);
    return 0;
}

static int suite_teardown(void)
{
    free(datapoints);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_polyregress_populate_populate_data, "populate_data"},
    {test_polyregress_populate_populate_check, "populate_check"},
    {0, 0},
};

void test_polyregress_populate_add_suite()
{
    const char *suite_name = "populate";
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

void test_polyregress_populate_populate_data()
{
    mi_item_t pts_cpt;
    handle = fopen(points_filename, "r");
    if (handle != NULL)
    {
        populate_data(&datapoints, &nb_points, &degree, handle, " ");
        
        CU_ASSERT_EQUAL(degree, expected_degree);
        CU_ASSERT_EQUAL(nb_points, expected_nb_points);
        for (pts_cpt = 0; pts_cpt < expected_nb_points; pts_cpt++)
        {
            CU_ASSERT_EQUAL(*(datapoints + pts_cpt), *(expected_points + pts_cpt));
        }

        fclose(handle);
    }
}

void test_polyregress_populate_populate_check()
{
    CU_PASS("WIP");
}
