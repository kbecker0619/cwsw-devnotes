/** @file
 *	@brief	Unit test cases for Operational States for the Architecture component.
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
#include <CUnit/Basic.h>

// ----	Project Headers -------------------------
//#include "cwsw_eventsim.h"

// ----	Module Headers --------------------------
#include "cwsw_arch_test_op_states.h"
#include "../../inc/i386/cwsw_arch.h"


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
init_suite_arch_op_states(void)
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
clean_suite_arch_op_states(void)
{
    /* at this time, there are no UT environment nor UUT environment post-conditions that need to
     * be affirmed, or activities that need to be done. Simply return success.
     */
    return CUE_SUCCESS;
}


/**	@test Confirm presence of an API to initialize the component.
 *  @xreq{SR_ARCH_0000}
 */
void
test_sr_arch_0000(void)
{
    int initstat = Cwsw_Arch__Init();
    /* check for either no problem, or reinitialization w/ no problem */
    CU_ASSERT((0 == initstat) || (2 == initstat));
}


/** Confirm presence of an API to determine initialization status of the component.
 *	The mere fact that this function compiles, proves that there is an interface
 *  to return the initialization status of the component.
 *
 *  @xreq{SR_LIB_0001}
 */
void
test_sr_arch_0001(void)
{
    (void)Cwsw_Arch__Get_Initialized();
    CU_PASS("Get Initialization Status API Exists");
}


/** Confirm component's internal state is set correctly in init function.
 *  @xreq{SR_LIB_0002}
 */
void
test_sr_arch_0002(void)
{
    extern bool cwsw_arch_initialized;

    cwsw_arch_initialized = false;			/* forcibly override any previous initialization */
    CU_ASSERT_EQUAL(Cwsw_Arch__Init(), 0);
    CU_ASSERT_EQUAL(cwsw_arch_initialized, true);
}


/** @test Confirm SR-LIB-0003.
 *  Confirm that all but init function indicate error condition if called before init.
 *
 *  @xreq{SR_LIB_0003}
 */
void
test_sr_arch_0003(void)
{
    extern bool cwsw_arch_initialized;

    cwsw_arch_initialized = false;        /* forcibly override any previous initialization */
    CU_FAIL("Test to be created yet");
}


/** Confirm that all but init function refuse to work if called before init.
 *  @xreq{SR_LIB_0004}
 */
void
test_sr_arch_0004(void)
{
    CU_FAIL("Test to be created yet");
}
