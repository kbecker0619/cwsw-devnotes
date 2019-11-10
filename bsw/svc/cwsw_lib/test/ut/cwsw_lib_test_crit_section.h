/** @file cwsw_lib_test_crit_section.h
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Apr 22, 2019
 *	@author KBECKE35
 */

#ifndef UT_CWSW_LIB_TEST_CRIT_SECTION_H_
#define UT_CWSW_LIB_TEST_CRIT_SECTION_H_

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

extern int init_suite_lib_crit_section(void);
extern int clean_suite_lib_crit_section(void);

extern void test_sr_lib_0301(void);
extern void test_sr_lib_0302(void);
extern void test_sr_lib_0303_floor(void);
extern void test_sr_lib_0303_ceiling(void);
extern void test_sr_lib_0304_ceiling(void);
extern void test_sr_lib_0304_floor(void);
extern void test_sr_lib_0306(void);
extern void test_sr_lib_0307(void);
extern void test_sr_lib_0308(void);
extern void test_sr_lib_0309(void);
extern void test_sr_lib_0310(void);


#ifdef	__cplusplus
}
#endif

#endif /* UT_CWSW_LIB_TEST_CRIT_SECTION_H_ */
