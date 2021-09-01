
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUCurses.h>
#include <CUnit/CUnit.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include "polyregress_suites/suite_gaussjordan.h"
#include "polyregress_suites/suite_points.h"
#include "polyregress_suites/suite_matcalc.h"

int main(int argc, char *argv[])
{
	enum
	{
		OPT_INTERFACE_BASIC = 'b',
		OPT_INTERFACE_CONSOLE = 'c',
		OPT_INTERFACE_NCURSES = 'C',
		OPT_HELP = 'h',
		OPT_INTERFACE = 'i',
	};

	static int option_index = 0;
	static struct option long_options[] = {
		{"help", 0, 0, OPT_HELP},
		{"interface", 1, 0, OPT_INTERFACE},
		{0, 0, 0, 0},
	};

	enum interface
	{
		interface_basic,
		interface_console,
		interface_ncurses,
	} interface = interface_basic;

	struct
	{
		enum interface interface;
		const char *name;
	} interfaces[] = {
		{interface_basic, "basic"},
		{interface_console, "console"},
		{interface_ncurses, "ncurses"},
		{0, 0},
	};

	int opt;
	do
	{
		opt = getopt_long(argc, argv, "bcChi:", long_options, &option_index);
		switch (opt)
		{
		case -1:
			break;
		case OPT_INTERFACE:
		{
			int i, found = 0;
			for (i = 0; interfaces[i].name && !found; i++)
			{
				if (!strcmp(interfaces[i].name, optarg))
				{
					interface = interfaces[i].interface;
					found = 1;
				}
			}
			if (!found)
			{
				printf("Interface should be one of ");
				for (i = 0; interfaces[i].name; i++)
					printf(
						"'%s'%s",
						interfaces[i].name,
						interfaces[i + 1].name ? ", " : "\n");
				return 1;
			}
		}
		break;
		case OPT_INTERFACE_BASIC:
			interface = interface_basic;
			break;
		case OPT_INTERFACE_CONSOLE:
			interface = interface_console;
			break;
		case OPT_INTERFACE_NCURSES:
			interface = interface_ncurses;
			break;
		case OPT_HELP:
			return 0;
		default:
			return 1;
		}
	} while (opt > -1);
	if (CU_initialize_registry() != CUE_SUCCESS)
	{
		printf(
			"Failed to initialize CUnit because %s\n",
			CU_get_error_msg());
		return 2;
	}

	test_polyregress_gaussjordan_add_suite();
	test_polyregress_points_add_suite();
	test_polyregress_matcalc_add_suite();

	switch (interface)
	{
	case interface_basic:
		//CU_basic_set_mode(CU_BRM_SILENT);
		CU_basic_set_mode(CU_BRM_VERBOSE);
		CU_basic_run_tests();
		break;

	case interface_console:
		CU_console_run_tests();
		break;

	case interface_ncurses:
		CU_curses_run_tests();
		break;
	default:
		break;
	}
	CU_cleanup_registry();
	return CU_get_error();
}
