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
#include <stddef.h>		/* size_t */

// ----	Project Headers -------------------------
#include "projcfg.h"

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
	do {	/* event table initialization */
		tEvQ_Event my_table_of_events[] = {
			{ 0, 100 },
		};
		tEvQ_EvTable evTbl = {0};

		cwsw_assert(Init(Cwsw_Evt) == kErr_Lib_NoError, "test component init");

		cwsw_assert(
			kErr_EvQ_BadParm == Cwsw_Evt__InitEventTable(NULL, my_table_of_events, TABLE_SIZE(my_table_of_events)),
			"Confirm bad Event Queue parameter");
		cwsw_assert(
			kErr_EvQ_BadParm == Cwsw_Evt__InitEventTable(&evTbl, NULL, TABLE_SIZE(my_table_of_events)),
			"Confirm bad Event Queue parameter");

		cwsw_assert(
			kErr_EvQ_NoError == Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events)),
			"Confirm good parms");

	} while(0);

	do {	/* event-finding API */
		int32_t evtblidx;

		tEvQ_Event my_table_of_events[] = {
			{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
			{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
		};
		tEvQ_EvTable evTbl = {0};

		cwsw_assert(
			kErr_EvQ_NoError == Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events)),
			"Confirm event table initialization");

	} while(0);
}
