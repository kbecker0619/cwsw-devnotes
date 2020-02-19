/** @file cwsw_svc.c
 *	@brief	One-sentence short description of file.
 *
 *	Description:
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 19, 2020
 *	Author: KBECKE35
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdbool.h>

// ----	Project Headers -------------------------
#include "cwsw_board.h"

// ----	Module Headers --------------------------
#include "cwsw_svc.h"


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

static bool initialized = false;


// ============================================================================
// ----	Private Functions -----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

uint16_t
Cwsw_Services__Init(void)
{
	if(!Get(Cwsw_Lib, Initialized))
	{
		if(!Init(Cwsw_Lib))		{ return Cwsw_Lib; }
	}

	// cwsw_board does not make assumptions about the MCU architecture; initialize it ourselves
	if(!Get(Cwsw_Arch, Initialized))
	{
		if(!Init(Cwsw_Arch))	{return Cwsw_Arch; }
	}

	if(!Get(Cwsw_Board, Initialized))	// because some services may depend on the BSP, initialize it
	{
		if(!Init(Cwsw_Board))	{ return Cwsw_Board; }
	}

	#if defined(__GNUC__)	/* --- GNU Environment ------------------------------ */
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpedantic"
	#endif

	dbg_printf(
			"\tModule ID %i\t%s\t\n"
			"\tEntering %s()\n\n",
			Cwsw_Services, __FILE__,
			__FUNCTION__);

	#if defined(__GNUC__)	/* --- GNU Environment ------------------------------ */
	#pragma GCC diagnostic pop
	#endif

	initialized = true;
	return 0;
}
