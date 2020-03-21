/** @file
 *	@brief	Definitions for the Event Handler component.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 8, 2020
 *	Author: KBECKE35
 */

#ifndef CWSW_EVHANDLER_H
#define CWSW_EVHANDLER_H

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
//#include "projcfg.h"
//#include "cwsw_evqueue.h"		/* tEvQ_Event, et. al. */
#include "cwsw_eventtable.h"

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

/** Event handler, implemented as a function pointer.
 * 	To accommodate the possibility that a common handler could be used for multiple events, pass
 * 	the event as the 1st parameter (so the handler can react accordingly).
 *
 * 	@param ev		Event to handle (typically from Event Queue).
 * 	@param extra	Supplemental information for the event handler.
 *
 * 	@ingroup tEvQ_EvHndlrAssocTable
 */
typedef void (*pEvQ_EvHandlerFunc)(tEvQ_Event ev, uint32_t extra);

/**	Association of event handler to a specific event ID.
 *	@note	This type defines _ONE ROW_ of a table of event-handler associations.
 *
 * 	@ingroup tEvQ_EvHndlrAssocTable
 */
typedef struct sEvHandlerAssoc {
	tEvQ_EventID		evId;
	pEvQ_EvHandlerFunc	pEvHandler;
} tEvQ_EvHandlerAssoc;

/** Reference to an Event Handler Association Table.
 * 	@ingroup tEvQ_EvHndlrAssocTable
 */
typedef tEvQ_EvHandlerAssoc * ptEvQ_EvHandlerAssoc;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

tErrorCodes_EvQ		Cwsw_EvQ__RegisterHandler(ptEvQ_EvHandlerAssoc pEvHndlrTbl, size_t evtblsz, tEvQ_EventID ev, pEvQ_EvHandlerFunc pf);
pEvQ_EvHandlerFunc	Cwsw_EvQ__GetHandler(ptEvQ_EvHandlerAssoc pEvHndlr, size_t evtblsz, tEvQ_EventID ev);


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_EVHANDLER_H */
