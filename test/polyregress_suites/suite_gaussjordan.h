
#ifndef __TEST_POLYREGRESS_SUITE_GAUSSJORDAN_H__
#define __TEST_POLYREGRESS_SUITE_GAUSSJORDAN_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../src/gaussjordan.h"

void test_polyregress_gaussjordan_add_suite(void);

void test_polyregress_gaussjordan_gj_echelonize(void);

#endif
