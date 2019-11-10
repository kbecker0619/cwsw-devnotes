/** @file cwsw_lib_test.c
 *	@brief	Primary Unit Test file for the CWSW Lib component.
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Nov 11, 2018
 *	Author: kbecker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>         // INT_MAX, INT_MIN

// ----	Project Headers -------------------------
#include <CUnit/Basic.h>
#include "cwsw_eventsim.h"

// ----	Module Headers --------------------------
#include "cwsw_lib.h"
#include "cwsw_lib_test_op_states.h"
#include "cwsw_lib_test_task_support.h"
#include "cwsw_lib_test_crit_section.h"


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Global Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Module-level Variables ------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

int
main(void)
{
	CU_pSuite pSuite = NULL;
	bool cu_setup_ok = false;

	/* Initialize the CUnit test registry for Operating States test suite */
	if(CUE_SUCCESS == CU_initialize_registry())
	{
		cu_setup_ok = true;
	}

	/* CWSW Library Operating States suite */
	do
	{
		CU_pTest tests[5] = {0};

		/* Add a suite to the registry.
		 * within the CWSW suite, we are using, generally, one suite per section of the requirements
		 * document, with a separate compilation unit for each suite. within the suite, distinct unit
		 * test files are used per requirement, or else, a distinct design element.
		 */
		if(cu_setup_ok)
		{
			pSuite = CU_add_suite(
					"CWSW Library Component, Operating States",
					init_suite_lib_op_states,
					clean_suite_lib_op_states);
			if(NULL == pSuite)
			{
				cu_setup_ok = false;
				break;
			}
		}

		/* add tests to Operating States test suite */
		tests[0] = CU_add_test(pSuite, "SR_LIB_0000: Initialization API", 					test_sr_lib_0000);
		tests[1] = CU_add_test(pSuite, "SR_LIB_0001: Initialization Status API", 			test_sr_lib_0001);
		tests[2] = CU_add_test(pSuite, "SR_LIB_0002: Initialization API Responsibilities",	test_sr_lib_0002);
		tests[3] = CU_add_test(pSuite, "SR_LIB_0003: Indication when uninitialized",		test_sr_lib_0003);
		tests[4] = CU_add_test(pSuite, "SR_LIB_0004: Behavior when uninitialized",			test_sr_lib_0004);
		if( !tests[0] ||
            !tests[1] ||
            !tests[2] ||
            !tests[3] ||
            !tests[4]
            )
		{
			cu_setup_ok = false;
			break;
		}

		/* sr-lib-0004 & sr-lib-0005 are not yet ready for testing */
		(void)CU_set_test_active(tests[3], CU_FALSE);
		(void)CU_set_test_active(tests[4], CU_FALSE);
	} while(0);

	/* CWSW Library Tasking Support test suite */
	do
	{
		CU_pTest tests[1] = {0};
		if(cu_setup_ok)
		{
			pSuite = CU_add_suite(
					"CWSW Library Component, Tasking Support",
					init_suite_lib_task_support,
					clean_suite_lib_task_support);
			if(NULL == pSuite)
			{
				cu_setup_ok = false;
				break;
			}

			/* add tests to Operating States test suite */
			tests[0] = CU_add_test(pSuite, "SR_LIB_0200: Tasking Support API", test_sr_lib_0200);
			if(!tests[0])
			{
				cu_setup_ok = false;
				break;
			}

			/* sr_lib_0201 is not yet ready for testing */
			(void)CU_set_test_active(tests[0], CU_FALSE);
		}
	} while(0);

	/* CWSW Library Protected Regions test suite */
	do {
		CU_pTest tests[11] = {0};
		if(cu_setup_ok)
		{
			pSuite = CU_add_suite(
					"CWSW Library Component, Protected Regions Support",
					init_suite_lib_crit_section,
					clean_suite_lib_crit_section);
			if(NULL == pSuite)
			{
				cu_setup_ok = false;
				break;
			}

			/* add tests to Operating States test suite */
			tests[ 0] = CU_add_test(pSuite, "SR_LIB_0301: Critical Section API, Enter",									test_sr_lib_0301);
			tests[ 1] = CU_add_test(pSuite, "SR_LIB_0302: Critical Section API, Leave",									test_sr_lib_0302);
			tests[ 2] = CU_add_test(pSuite, "SR_LIB_0303: Critical Section Counter: Inactive",							test_sr_lib_0303_floor);
			tests[ 3] = CU_add_test(pSuite, "SR_LIB_0303: Critical Section Counter: Increment to Max Nesting Depth",	test_sr_lib_0303_ceiling);
			tests[ 4] = CU_add_test(pSuite, "SR_LIB_0304: Critical Section Counter: Decrement from Max Nesting Depth",	test_sr_lib_0304_ceiling);
			tests[ 5] = CU_add_test(pSuite, "SR_LIB_0304: Critical Section Counter: Decrement to Inactive",				test_sr_lib_0304_floor);
			tests[ 6] = CU_add_test(pSuite, "SR_LIB_0306: Critical Section Counter: Invalid Value",						test_sr_lib_0306);
			tests[ 7] = CU_add_test(pSuite, "SR_LIB_0307: Critical Section Counter: Enter when Inactive",				test_sr_lib_0307);
			tests[ 8] = CU_add_test(pSuite, "SR_LIB_0308: Critical Section Counter: Enter when Active",					test_sr_lib_0308);
			tests[ 9] = CU_add_test(pSuite, "SR_LIB_0309: Critical Section Counter: Leave when Active",					test_sr_lib_0309);
			tests[10] = CU_add_test(pSuite, "SR_LIB_0310: Critical Section Counter: Leave when Active",					test_sr_lib_0310);
			if(   !tests[ 0]
			   || !tests[ 1]
			   || !tests[ 2]
			   || !tests[ 3]
			   || !tests[ 4]
			   || !tests[ 5]
			   || !tests[ 6]
			   || !tests[ 7]
			   || !tests[ 8]
			   || !tests[ 9]
			   || !tests[10]
			   )
			{
				cu_setup_ok = false;
				break;
			}
		}
	} while(0);

	/* Run all tests using the CUnit Basic interface */
	if(cu_setup_ok)
	{
		CU_basic_set_mode(CU_BRM_VERBOSE);
		CU_basic_run_tests();
	}

	CU_cleanup_registry();
	return CU_get_error();
}
