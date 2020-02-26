/** @file
 *
 *	Description:
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 24, 2020
 *	Author: KBECKE35
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdbool.h>

// ----	Project Headers -------------------------
#include "cwsw_lib.h"

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

static bool initialized = false;


// ============================================================================
// ----	Private Functions -----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/** Initialize the Event "object."
 *	This component doesn't really have any significant need for an initialize method; this function
 *	is here mostly for consistency with other CWSW components.
 */
uint16_t
Cwsw_Evt__Init(void)
{
	initialized = true;
	return kErr_Lib_NoError;
}


/**	Initialize an Event Queue table of events.
 *
 *	@param [out]	pEvQTable	tEvQ_EvTable object to be initialized.
 *	@param [in]		pTable		Table of events.
 *	@param [in]		TableSize	Size of the event table, in number of elements (not bytes).
 *	@return	Event Queue error code, where value `0` is success.
 */
tErrorCodes_EvQ
Cwsw_Evt__InitEventTable(
	pEvQ_EvTable pEvQTable,	// Event Queue table
	pEvQ_Event pTable,		// table of events
	size_t TableSize)		// size of the event table
{
	if(!pEvQTable)	return kErr_EvQ_BadParm;
	if(!pTable)		return kErr_EvQ_BadParm;
	pEvQTable->pEvTable = pTable;
	pEvQTable->EvTblSize = TableSize;	// yes, we do accept a size of 0 elements
	return kErr_EvQ_NoError;
}
