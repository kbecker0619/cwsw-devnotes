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

#ifndef CWSW_EVTHNDLRASSOC_H
#define CWSW_EVTHNDLRASSOC_H

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
#include "cwsw_event.h"		/* event */

// ----	Module Headers --------------------------
#include "cwsw_evhandler.h"


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

typedef struct eEvQ_EvHndlrAssocTable {
	pEvQ_EvHandlerAssoc	pEvtHndlrTbl;
	int32_t				szEvtHandlerTbl;
} tEvQ_EvHndlrAssocTable;

typedef tEvQ_EvHndlrAssocTable * ptEvQ_EvHndlrAssocTable;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

extern tErrorCodes_EvQ Cwsw_EvQX__InitEventHandlerTable(ptEvQ_EvHndlrAssocTable EvtHndlrTbl, pEvQ_EvHandlerAssoc HndlrArray, int32_t szHndlrArray);


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_EVTHNDLRASSOC_H */
