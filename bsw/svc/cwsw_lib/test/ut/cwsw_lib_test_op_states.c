/** @file cwsw_lib_test_op_states.c
 *	@brief	One-sentence short description of file.
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Apr 21, 2019
 *	@author KBECKE35
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
#include "cwsw_lib_test_op_states.h"


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

/** Initialize the CUnit Operating States suite for the CWSW Library component.
 *  For this edition of this UT suite, all we're looking for is to confirm that
 *  the library has not yet been initialized.
 *
 *	@return 0 for success.
 *  @return non-0 for failure.
 */
int
init_suite_lib_op_states(void)
{
    /* at this time, there are no test environment things to set up, nor are
     * there UUT environment things to set up. Simply do a nop.
     */
    return CUE_SUCCESS;
}

/** Perform final cleanup of the Operating States suite for the CWSW Library component.
 *  For this edition of this UT suite, there is no actual cleanup activity
 *  required, we are only confirming that the library indicates it's been
 *  initialized.
 *
 *	@return 0 for success.
 *  @return non-0 for failure.
 */
int
clean_suite_lib_op_states(void)
{
    /* at this time, there are no UT environment nor UUT environment post-conditions that need to
     * be affirmed, or activities that need to be done. Simply return success.
     */
    return CUE_SUCCESS;
}


/** Confirm presence of an API to determine initialization status of the component.
 *	The mere fact that this function compiles, proves that there is an interface
 *  to return the initialization status of the component.
 *
 *  @xreq{SR_LIB_0001}
 */
void
test_sr_lib_0001(void)
{
    UNUSED(Get(Cwsw_Lib, Initialized));
    CU_PASS("Get Initialization Status API Exists");
}


/** @test Confirm presence of an API to initialize the component.
 *  @xreq{SR_LIB_0000}
 */
void
test_sr_lib_0000(void)
{
    int initstat = Init(Cwsw_Lib);
    /* check for either no problem, or reinitialization w/ no problem */
    CU_ASSERT((0 == initstat) || (2 == initstat));
}


/** Confirm component's internal state is set correctly in init function.
 *  @xreq{SR_LIB_0002}
 */
void
test_sr_lib_0002(void)
{
    extern bool cwsw_lib_initialized;
    extern int cwsw_lib_cs_protection_count;

    cwsw_lib_initialized = false;			/* forcibly override any previous initialization */
    cwsw_lib_cs_protection_count = 1234;	/* random, meaningless value that is not 0 */
    CU_ASSERT_EQUAL(Init(Cwsw_Lib), 0);
    CU_ASSERT_EQUAL(cwsw_lib_initialized, true);
    CU_ASSERT_EQUAL(cwsw_lib_cs_protection_count, 0);
}


/** Confirm that all but init function indicate error condition if called before init.
 *  @xreq{SR_LIB_0003}
 */
void
test_sr_lib_0003(void)
{
    extern bool cwsw_lib_initialized;

    cwsw_lib_initialized = false;        /* forcibly override any previous initialization */
    CU_FAIL("Test to be created yet");
}


/** Confirm that all but init function refuse to work if called before init.
 *  @xreq{SR_LIB_0004}
 */
void
test_sr_lib_0004(void)
{
    CU_FAIL("Test to be created yet");
}
