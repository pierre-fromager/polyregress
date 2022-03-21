
#ifndef __TEST_POLYREGRESS_SUITE_MATCALC_H__
#define __TEST_POLYREGRESS_SUITE_MATCALC_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <points.h>
#include <matcalc.h>

#define SUITE_MATCAL_DEGREE 4 
#define SUITE_MATCAL_NB_POINTS 5

void test_polyregress_matcalc_add_suite(void);
void reset_test_matcalc(void);

void test_polyregress_matcalc_matcalc_mpc(void);
void test_polyregress_matcalc_matcalc_rhs(void);

#endif
