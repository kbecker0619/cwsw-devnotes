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

/**	Find an event ID in an event table.
 *	Algorithm:
 *	- In this iteration, we are simply using the event ID as an index into the event table;
 *	  this works well for small tables, but is useless if you want sparse tables or if you have a
 *	  lot of events
 *	- RSN (Real Soon Now), we will implement either a linear search, or some sort of divide-and
 *	  conquer, which will actually utilize the ID field of the table rows.
 *
 *	@param [in]	pTbl	Event table.
 *	@param [in]	tblsz	Size of event table.
 *	@param [in]	evId	Event ID to look for.
 * @return
 */
static int32_t	// todo: make this an event "handle", not a direct S32
FindEvent(pEvQ_Event pTbl, size_t tblsz, tEvQ_EventID evId)
{
	if(!pTbl) 			return -1;

	// this check specifically tied to the id-as-index algorithm
	if(evId >= tblsz)	return -1;

	// we could insert here a check that the row's evId is the same as our search criteron, but ... nah.
	return evId;
}


// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/** Initialize the Event "object."
 *	This component doesn't really have any significant need for an initialize method; this function
 *	is here mostly for consistency with other CWSW components.
 *
 *	@ingroup sEvq_EvTable
 */
uint16_t
Cwsw_Evt__Init(void)
{
	initialized = true;
	return kErr_Lib_NoError;
}


/**	Initialize an Event Queue table of events.
 *	Note the actual table of events is not touched; only the metadata used to manage the table is
 *	initialized.
 *
 *	@param [out]	pEvQTable	Event Table object to be initialized.
 *	@param [in]		pTable		Table of events.
 *	@param [in]		TableSize	Size of the event table, in number of elements (not bytes).
 *	@return	Event Queue error code, where value `0` is success.
 *
 *	@ingroup sEvq_EvTable
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


/**	Return the index in the table of events, where an event ID was found.
 *
 *	@param [in]		pEvQTable	Event table control structure.
 *	@param [in]		evId
 *	@return	Index into the table where the event was found, -1 if not found.
 */
int32_t
Cwsw_Evt__FindEvent(pEvQ_EvTable pEvQTable, tEvQ_EventID evId)
{
	if(!pEvQTable)		return -1;
	return FindEvent(pEvQTable->pEvTable, pEvQTable->EvTblSize, evId);
}
