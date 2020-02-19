/** @file cwsw_svc.h
 *
 *	Description:
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 19, 2020
 *	Author: KBECKE35
 */

#ifndef CWSW_SVC_H_
#define CWSW_SVC_H_

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdint.h>

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
/** Initialization for the Board Support component.
 * 	Target for `Init(Cwsw_Services)` API.
 *
 *	This function's responsibility is to set up the local vars, and manage the
 *	services below it.
 *
 *	This function shall be called before the main scheduler is started.
 *
 *	As general guidance, this should be BSP initialization but before
 *	application initialization functions.
 *
 *	@returns error code, or 0 for no problem (i.e., success).
 */
extern uint16_t Cwsw_Services__Init(void);

// ==== /Discrete Functions ================================================= }

// ==== Targets for Get/Set APIs ============================================ {
/** "Chapter Designator" for Get/Set API.
 *	Intentionally unused symbol, designed to get you to the correct starting
 *	point, when you want to find macros for the Get/Set API; simply highlight
 *	the Module argument in your IDE (e.g, Eclipse, NetBeans, etc.), and select
 *	Go To Definition.
 */
enum { Cwsw_Services = 2 };


/** Target symbol for Get(Cwsw_Services, xxx) interface */
#define Cwsw_Services__Get(resource)			Cwsw_Services__Get_ ## resource()

/** Target symbol for Set(Cwsw_Board, Resource, xxx) interface */
#define Cwsw_Services__Set(resource, value)		Cwsw_Services__Set_ ## resource(value)

// ==== /Targets for Get/Set APIs =========================================== }


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_SVC_H_ */
