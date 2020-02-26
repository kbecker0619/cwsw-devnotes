/** @file
 *	@brief	MVP (Minimum Viable Product) main for CWSW Event component.
 *
 *	Description:
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 26, 2020
 *	Author: KBECKE35
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include "projcfg.h"

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------
#include "cwsw_event.h"


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
// ----	Private Functions -----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

int
main(void)
{
	do {	/*  rote run-through of EVENT methods */
		tEvQ_Event my_table_of_events[10] = {0};
		tEvQ_EvTable myq = {0};

		cwsw_assert(Init(Cwsw_Evt) == kErr_Lib_NoError, "test component init");

		cwsw_assert(
			kErr_EvQ_BadParm == Cwsw_Evt__InitEventTable(NULL, my_table_of_events, TABLE_SIZE(my_table_of_events)),
			"Confirm bad Event Queue parameter");
		cwsw_assert(
			kErr_EvQ_BadParm == Cwsw_Evt__InitEventTable(&myq, NULL, TABLE_SIZE(my_table_of_events)),
			"Confirm bad Event Queue parameter");

		cwsw_assert(
			kErr_EvQ_NoError == Cwsw_Evt__InitEventTable(&myq, my_table_of_events, TABLE_SIZE(my_table_of_events)),
			"Confirm good parms");

	} while(0);

}
