/** @file
 *	@brief	Methods for Event Table component.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 7, 2020
 *	Author: Kevin
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <limits.h>				/* INT_MAX */

// ----	Project Headers -------------------------
#include "projcfg.h"
#include "cwsw_lib.h"			/* Cwsw_Critical_Protect() */

// ----	Module Headers --------------------------
#include "cwsw_eventtable.h"


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

/**	Initialize an Event Table object.
 *	Note the actual "buffer" (table of events) is not touched;
 *	only the metadata used to manage the table is initialized.
 *
 *	@param [out]	pEvQTable	Event Table object to be initialized.
 *	@param [in]		pTable		Table of events.
 *	@param [in]		TableSize	Size of the event table, in number of elements (not bytes).
 *								Rejection occurs if > INT_MAX.
 *	@return	Event Queue error code, where value `0` is success.
 *
 *	@ingroup sEvq_EvTable
 */
tErrorCodes_EvQ
Cwsw_Evt__InitEventTable(
	pEvQ_EvTable pEvQTable,	// Event Queue table.
	pEvQ_Event pTable,		// table of events.
	size_t TableSize)		// size of the event table. the benefit of passing as unsigned, is that we don't have to worry about negative values.
{
	if(!pEvQTable)			return kErr_EvQ_BadParm;
	if(!pTable)				return kErr_EvQ_BadParm;
	if(TableSize > INT_MAX)	return kErr_EvQ_BadParm;

	pEvQTable->pEvBuffer	= pTable;
	pEvQTable->szEvTbl		= (int32_t)TableSize;	// yes, we do accept a size of 0 elements
	return kErr_EvQ_NoError;
}


/**	Return the address of a specified event in the event buffer.
 *
 *	@param [in]		pEvTbl	Event table control structure.
 *	@param [in]		hnd		base-0 handle, used as an index into the event buffer.
 *	@return	address of the specified event.
 */
pEvQ_Event
Cwsw_Evt__GetEventPtr(pEvQ_EvTable pEvTbl, tEvQ_EvtHandle hnd)
{
	if(!pEvTbl)					return NULL;	// bad Event Table object.
	if(!pEvTbl->pEvBuffer)		return NULL;	// bad event buffer object.
	if(hnd >= pEvTbl->szEvTbl)	return NULL;	// bad handle (index).
	return &pEvTbl->pEvBuffer[hnd];
}


/**	Get a specified event from the event buffer.
 *
 *	@param pEv		[out]	destination.
 *	@param pEvTb	[in]	table of events.
 *	@param hnd		[in]	"handle" (index) into the event buffer of the event to retrieve.
 *	@return	Event Queue error code.
 *	@ingroup sEvq_EvTable
 */
tErrorCodes_EvQ
Cwsw_Evt__GetEvent(pEvQ_Event pEv, pEvQ_EvTable pEvTb, tEvQ_EvtHandle hnd)
{
	pEvQ_Event pfound;

	if(!pEv)					return kErr_EvQ_BadParm;
	if(!pEvTb)					return kErr_EvQ_BadParm;
	if(hnd >= pEvTb->szEvTbl)	return kErr_EvQ_BadTable;

	pfound = Cwsw_Evt__GetEventPtr(pEvTb, hnd);
	if(pfound)
	{
		int crit = Cwsw_Critical_Protect(0);
		(void)memcpy(pEv, pfound, sizeof(tEvQ_Event));
		crit = Cwsw_Critical_Release(crit);
		return kErr_EvQ_NoError;
	}
	return kErr_EvQ_BadEvent;
}


/**
 *
 *	@param pEvTb
 *	@param hnd
 *	@param pEv
 *	@return
 *	@ingroup sEvq_EvTable
 */
tErrorCodes_EvQ
Cwsw_Evt__PutEvent(pEvQ_EvTable pEvTb, tEvQ_EvtHandle hnd, pEvQ_Event pEv)
{
	pEvQ_Event pfound;

	if(!pEv)					return kErr_EvQ_BadParm;
	if(!pEvTb)					return kErr_EvQ_BadParm;
	if(hnd >= pEvTb->szEvTbl)	return kErr_EvQ_BadTable;

	pfound = Cwsw_Evt__GetEventPtr(pEvTb, hnd);
	if(pfound)
	{
		int crit = Cwsw_Critical_Protect(0);
		(void)memcpy(pfound, pEv, sizeof(tEvQ_Event));
		crit = Cwsw_Critical_Release(crit);
		return kErr_EvQ_NoError;
	}
	return kErr_EvQ_BadEvBuffer;
}

