/** @file
 *	@brief	One-sentence short description of file.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 9, 2020
 *	Author: Kevin
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------
#include "cwsw_evthndlrassoc.h"


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

/** "Constructor" for an Event Handler association.
 * 	This connects an event ID with its handler.
 *
 *	@param pEvtHndlrTbl
 *	@param pHndlrArray
 *	@param szHndlrArray
 *	@return	Error code, where `0` is success.
 *
 *	@ingroup tEvQ_QueueCtrlEx
 */
tErrorCodes_EvQ
Cwsw_EvQX__InitEventHandlerTable(
	ptEvQ_EvHndlrAssocTable pEvtHndlrTbl,
	pEvQ_EvHandlerAssoc pHndlrArray,
	int32_t szHndlrArray)
{
	if(!pEvtHndlrTbl)			return kErr_EvQ_BadParm;
	if(!pHndlrArray)			return kErr_EvQ_BadParm;
	if(szHndlrArray > INT_MAX)	return kErr_EvQ_BadParm;

	pEvtHndlrTbl->pEvtHndlrTbl		= pHndlrArray;
	pEvtHndlrTbl->szEvtHandlerTbl	= szHndlrArray;		// yes, we do accept a size of 0 elements
	// todo: set validity
	return kErr_EvQ_NoError;
}


static tEvQ_EvtHandle
GetTableHandle(ptEvQ_EvHndlrAssocTable pHndlrTbl, tEvQ_EventID evId)
{
	// for this implementation, the event is used as an index into the LUT
	if(!pHndlrTbl)							return -1;
	// todo: check table validity
	if(evId >= pHndlrTbl->szEvtHandlerTbl)	return -1;
	if(evId < 1)							return -1;
	return (tEvQ_EvtHandle)evId;
}


tErrorCodes_EvQ
Cwsw_EvQX__SetEvHandler(
	ptEvQ_EvHndlrAssocTable pHndlrTbl,	//!< Event Handler Association table.
	tEvQ_EventID evId, 					//!< Event ID to associate.
	pEvQ_EvHandlerFunc pHndlrFunc)		//!< Handler for the identified event. NULL accepted to disassociate an event.
{
	tEvQ_EvtHandle hnd = GetTableHandle(pHndlrTbl, evId);	// validates both association table as well as event id
	if(hnd < 1)	return kErr_EvQ_BadParm;					// not completely accurate, but MVP for now. could return more precise error codes if we did our own examination of the parameters.

	// set event
	pHndlrTbl->pEvtHndlrTbl[hnd].evId = evId;
	// set handler
	pHndlrTbl->pEvtHndlrTbl[hnd].pEvHandler = pHndlrFunc;
	return kErr_EvQ_NoError;
}
