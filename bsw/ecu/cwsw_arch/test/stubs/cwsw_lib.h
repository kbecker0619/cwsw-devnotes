/** @file cwsw_lib.h
 *	@brief	Stubbed version of "real" header, sufficient to support cwsw_arch development & unit test.
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Oct 17, 2019
 *	Author: KBECKE35
 */

#ifndef BSW_ECU_CWSW_ARCH_TEST_STUBS_CWSW_LIB_H_
#define BSW_ECU_CWSW_ARCH_TEST_STUBS_CWSW_LIB_H_

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdint.h>		/* standard integer type definitions */
#include <stdbool.h>	/* bool */
#include <stdio.h>		/* __FILE__, printf(), etc. */

// ----	Project Headers -------------------------
#include "projcfg.h"

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

// ==== Discrete Functions ================================================== {
/** Module initialization function. */
#define Cwsw_Lib__Init()    (0)


// ==== /Discrete Functions ================================================= }

// ==== Targets for Get/Set APIs ============================================ {
// ==== /Targets for Get/Set APIs =========================================== }

// ====	definitions common to all environments ============================== {


/**	Eliminate compiler and static-checker warnings about an unused function
 *	parameter. Note for C89 code, any invocation must follow your variables definitions.
 */
#if !defined(UNUSED)
#define UNUSED(x) (void)x
#endif


/*  Initialize API description for the CWSW Library components (all of them) */
/**	@defgroup	cwsw_lib_init_group		Initialize API
 * 	@ingroup	cwsw_lib_object_group
 */
/**	Abstract module initialization. This is the exposed, 1st-level API.
 *
 *	The intention is, all modules use the same signature for their init
 *	function, so use this API to make it more obvious to the code maintainer
 *	that we're using a standardized (template) init function.
 *
 *	@ingroup	cwsw_lib_init_group
 *
 *	@xreq{SR_LIB_0002}	(Primary)
 *	@{
 */
#define Init(instance)						_INIT(instance)

/**	This is the 2nd level of a 2-level expansion; this is done because it is
 *	possible to pass a macro to the 1st-level (external) API, and we want the
 *	macro to be fully expanded when the concatenation is done. We don't expect
 *	to pass nested macro definitions.
 *
 *	@xreq{SR_LIB_0002}	(Supports)
 */
#define _INIT(instance)						instance ## __Init()

// ====	/definitions common to all environments ============================= }


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_LIB_H_ */
