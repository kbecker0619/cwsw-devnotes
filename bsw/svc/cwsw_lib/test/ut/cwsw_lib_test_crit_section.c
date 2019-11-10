/** @file cwsw_lib_test_crit_section.c
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Apr 22, 2019
 *	@author KBECKE35
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <limits.h>

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

/**	Initialize the CUnit Operating States suite for the CWSW Library component.
 *	For this edition of this UT suite, all we're looking for is to confirm that
 *	the library has not yet been initialized.
 *
 *	@return 0 for success.
 *	@return non-0 for failure.
 */
int
init_suite_lib_crit_section(void)
{
	/* at this time, there are no test environment things to set up, nor are
	 * there UUT environment things to set up. Simply do a nop.
	 */
	return CUE_SUCCESS;
}

/**	Perform final cleanup of the Operating States suite for the CWSW Library component.
 *	For this edition of this UT suite, there is no actual cleanup activity
 *	required, we are only confirming that the library indicates it's been
 *	initialized.
 *
 *	@return 0 for success.
 *	@return non-0 for failure.
 */
int
clean_suite_lib_crit_section(void)
{
	/* at this time, there are no UT environment nor UUT environment post-conditions that need to
	 * be affirmed, or activities that need to be done. Simply return success.
	 */
	return CUE_SUCCESS;
}


/**	Confirm presence of an API to support component tasks.
 *	@xreq{SR_LIB_0301}  API for entering critical sections.		(Primary)
 *	@xreq{SR_LIB_0300}  API for managing critical sections.		(Support)
 */
void
test_sr_lib_0301(void)
{
	/* if this compiles, we've satisfied the requirement (as of the current
	 * revision of the requirements document)
	 */
	int protct = Cwsw_Critical_Protect(0); UNUSED(protct);
	CU_PASS("Tasking API Exists");
}


/**	Confirm presence of an API to support component tasks.
 *	This test confirms the "leave" API that is complementary to the "enter" API
 *	tested as part of sr-lib-0301.
 *	@xreq{SR_LIB_0302}  API for leaving critical section.		(Primary)
 *	@xreq{SR_LIB_0300}  API for managing critical sections.		(Support)
 */
void
test_sr_lib_0302(void)
{
	/* if this compiles, we've satisfied the requirement (as of the current
	 * revision of the requirements document)
	 */
	int protct = Cwsw_Critical_Release(0); UNUSED(protct);
	CU_PASS("Tasking API Exists");
}


/**	Confirm behavior of critical-section nesting counter incrementation:
 *	begin @ floor of counter range.
 *
 *	@xreq{SR_LIB_0303}	Increment nesting counter upon entry.	(Primary)
 *	@xreq{SR_LIB_0305}	Data range of nesting counter.			(Primary, Shared)
 */
void
test_sr_lib_0303_floor(void)
{
	extern int cwsw_lib_cs_protection_count;
	int localct = INT_MAX;	/* just want some value non-zero, unlikely to be seen */

	cwsw_lib_cs_protection_count = 0;	/* sr-lib-0305: data range floor is 0 */
	localct = Cwsw_Critical_Protect(0);
	CU_ASSERT_EQUAL(cwsw_lib_cs_protection_count, 1);
	CU_ASSERT_EQUAL(localct, 1);
}


/**	Confirm behavior of critical-section nesting counter incrementation:
 *	test at upper end of range.
 *	Since the data range is specified to be one-sided, there is no concern
 *	about "crossover" such as passing from negative to positive values.
 *
 *	@xreq{SR_LIB_0303}	Increment nesting counter upon entry.	(Primary)
 *	@xreq{SR_LIB_0305}	Data range of nesting counter.			(Primary, Shared)
 */
void
test_sr_lib_0303_ceiling(void)
{
	extern int cwsw_lib_cs_protection_count;
	int localct = 1234;	/* just want some value non-zero, unlikely to be seen */

	cwsw_lib_cs_protection_count = INT_MAX - 1;	/* sr_lib_0305: data range ceiling is INT_MAX, after incrementation */
	localct = Cwsw_Critical_Protect(0);
	CU_ASSERT_EQUAL(cwsw_lib_cs_protection_count, INT_MAX);
	CU_ASSERT_EQUAL(localct, INT_MAX);
}


/**	Confirm behavior of critical-range nesting counter decrementation: begin @
 *	max value of counter range.
 *
 *	@xreq{SR_LIB_0304}	Decrement nesting counter upon entry 	(Primary)
 *	@xreq{SR_LIB_0305}	Data range of nesting counter.			(Primary, Shared)
 */
void
test_sr_lib_0304_ceiling(void)
{
	extern int cwsw_lib_cs_protection_count;
	int localct = 1234;	/* just want some value non-zero, unlikely to be seen */

	cwsw_lib_cs_protection_count = INT_MAX;	/* sr-lib-0305: data range ceiling is INT_MAX */
	localct = Cwsw_Critical_Release(0);
	CU_ASSERT_EQUAL(cwsw_lib_cs_protection_count, INT_MAX - 1);
	CU_ASSERT_EQUAL(localct, INT_MAX - 1);
}


/**	Confirm behavior of critical-section nesting counter decrementation: when
 *	the counter is just above the floor.
 *
 *	@xreq{SR_LIB_0304}	Decrement nesting counter upon entry 	(Primary)
 *	@xreq{SR_LIB_0305}	Data range of nesting counter.			(Primary, Shared)
 */
void
test_sr_lib_0304_floor(void)
{
	extern int cwsw_lib_cs_protection_count;
	int localct = 1234;	/* just want some value non-zero, unlikely to be seen */

	cwsw_lib_cs_protection_count = 1;
	localct = Cwsw_Critical_Release(0);
	CU_ASSERT_EQUAL(cwsw_lib_cs_protection_count, 0);
	CU_ASSERT_EQUAL(localct, 0);
}


/** Confirm invalid critical-section nesting counter handling.
 *	Because of the way we have defined the data range, the only way to have an
 *	invalid data range fault is if the counter is negative.
 *
 *  @note: This test will invoke assertion behavior: calling `enter` when the
 *	counter is already at max will result in a data-range fault. The requirement
 *	is stated in terms of the range of the counter, not the value of the counter
 *	when the enter or leave APIs are called.
 *
 *	@note Because of the assertion built into the UUT, be aware that this
 *	function will invoke cwsw_assert().
 *
 *	@xreq{SR_LIB_0306}	Behavior when nesting counter invalid.	(Primary)
 *	@xreq{SR_LIB_0305}	Data range of nesting counter.			(Primary, Shared)
 */
void
test_sr_lib_0306(void)
{
	extern int cwsw_lib_cs_protection_count;
	int localct = 1234;	/* just want some value non-zero, unlikely to be seen */

	cwsw_lib_cs_protection_count = -1;
	localct = Cwsw_Critical_Protect(0);
	CU_ASSERT_EQUAL(cwsw_lib_cs_protection_count, 1);
	CU_ASSERT_EQUAL(localct, 1);
}


/**	Confirm fundamental behavior when entering a critical section for the first
 *	time.
 *	The UUT relies on a Function-Like Macro (FLM) that is configured by the
 *	integration project, to be whatever is suitable for the MCU architecture
 *	and system, for the specified protection level. For the purposes of this
 *	unit test, we are defining a callback that simply allows this UT case to
 *	track "activation."
 *
 *	@xreq{SR_LIB_0307}	Protection Behavior upon 1st activation.
 */
void
test_sr_lib_0307(void)
{
	extern int cwsw_lib_cs_protection_count;    /* cwsw_lib internal nesting counter */
	extern bool crit_section_seen;              /* project-level UT-focused var */
	extern int crit_sec_prot_lvl;               /* project-level UT-focused var */

	cwsw_lib_cs_protection_count = 0;
	crit_section_seen = false;
	crit_sec_prot_lvl = INT_MAX;

	int localct = Cwsw_Critical_Protect(0);

	CU_ASSERT_EQUAL(localct, 1);
	CU_ASSERT_EQUAL(crit_section_seen, true);
	CU_ASSERT_EQUAL(crit_sec_prot_lvl, 0);
}


/**	Confirm fundamental behavior when entering a critical section after it has
 *	been activated at least once before.
 *	The UUT relies on a FLM that is configured by the integration project, to
 *	suit the needs of that project. Our normal recommendation is that it should
 *	be defined as a do-nothing statement; however, for this UT case, we are
 *	defining it in a way that allows us to track when it is called.
 *
 *	@xreq{SR_LIB_0308}	Protection Behavior when Already Protected.
 */
void
test_sr_lib_0308(void)
{
	extern int cwsw_lib_cs_protection_count;    /* cwsw_lib internal nesting counter */
	extern bool crit_section_seen;              /* project-level UT-focused var */
	extern int crit_sec_prot_lvl;               /* project-level UT-focused var */

    cwsw_lib_cs_protection_count = 1;
	crit_section_seen = false;
	crit_sec_prot_lvl = INT_MIN;

	int localct = Cwsw_Critical_Protect(0);

	CU_ASSERT_EQUAL(localct, 2);
	CU_ASSERT_EQUAL(crit_section_seen, false);
	CU_ASSERT_EQUAL(crit_sec_prot_lvl, INT_MIN);
}


/**	Confirm fundamental behavior when leaving a critical section while its
 *	nesting counter is "off the floor."
 *
 *	The UUT relies on a FLM that is configured by the integration project, to
 *	suit the needs of that project. Our normal recommendation is that it should
 *	be defined as a do-nothing statement; however, for this UT case, we are
 *	defining it in a way that allows us to track when it is called.
 *
 *	@xreq{SR_LIB_0309}	Release Behavior with Critical Section nesting active.
 */
void
test_sr_lib_0309(void)
{
	extern int cwsw_lib_cs_protection_count;    /* cwsw_lib internal nesting counter */
	extern bool crit_section_seen;              /* project-level UT-focused var */
	extern int crit_sec_prot_lvl;               /* project-level UT-focused var */

    cwsw_lib_cs_protection_count = 2;
	crit_section_seen = false;
	crit_sec_prot_lvl = INT_MIN;

	int localct = Cwsw_Critical_Release(0);

	CU_ASSERT_EQUAL(localct, 1);
	CU_ASSERT_EQUAL(crit_section_seen, false);
	CU_ASSERT_EQUAL(crit_sec_prot_lvl, INT_MIN);
}


/**	Confirm fundamental behavior when leaving a critical section for the last
 *	time.
 *
 *	The UUT relies on a FLM that is configured by the integration project, to
 *	suit the needs of that project. Our normal recommendation is that it should
 *	be defined as a do-nothing statement; however, for this UT case, we are
 *	defining it in a way that allows us to track when it is called.
 *
 *	@xreq{SR_LIB_0310}	Release Behavior upon last leave.
 */
void
test_sr_lib_0310(void)
{
	extern int cwsw_lib_cs_protection_count;    /* cwsw_lib internal nesting counter */
	extern bool crit_section_seen;              /* project-level UT-focused var */
	extern int crit_sec_prot_lvl;               /* project-level UT-focused var */

    cwsw_lib_cs_protection_count = 1;
	crit_section_seen = false;
	crit_sec_prot_lvl = INT_MIN;

	int localct = Cwsw_Critical_Release(0);

	CU_ASSERT_EQUAL(localct, 0);
	CU_ASSERT_EQUAL(crit_section_seen, true);
	CU_ASSERT_EQUAL(crit_sec_prot_lvl, INT_MAX);
}

