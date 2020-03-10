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
	pEvtHndlrTbl->szEvtHandlerTbl	= (int32_t)szHndlrArray;	// yes, we do accept a size of 0 elements
	return kErr_EvQ_NoError;
}
