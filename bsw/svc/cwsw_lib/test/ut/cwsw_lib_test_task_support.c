/** @file cwsw_lib_test_task_support.c
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Apr 22, 2019
 *	Author: KBECKE35
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
#include <CUnit/Basic.h>
#include "cwsw_eventsim.h"

// ----	Module Headers --------------------------
#include "cwsw_lib.h"
#include "cwsw_lib_test_task_support.h"


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

/** Initialize the CUnit Tasking Support suite for the CWSW Library component.
 *
 *	@return 0 for success.
 *  @return non-0 for failure.
 */
int
init_suite_lib_task_support(void)
{
	return CUE_SUCCESS;
}

/** Perform final cleanup of the Tasking Support suite for the CWSW Library component.
 *  For this edition of this UT suite, there is no actual cleanup activity
 *  required.
 *
 *	@return 0 for success.
 *  @return non-0 for failure.
 */
int
clean_suite_lib_task_support(void)
{
	return CUE_SUCCESS;
}


/** Dummy task function to satisfy tasking API. */
void
SR_LIB_0200__Task(void)
{
    /* intentionally empty */
}

/** Confirm presence of an API to support component tasks.
 *  @xreq{SR_LIB_0200}
 */
void
test_sr_lib_0200(void)
{
    /* if this compiles, we've satisfied the requirement (as of the current
     * revision of the requirements document)
     */
    Task(SR_LIB_0200);
    CU_PASS("Tasking API Exists");
}
