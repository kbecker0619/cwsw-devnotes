/** @file cwsw_evhandler.h
 *
 *	Description:
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 8, 2020
 *	Author: KBECKE35
 */

#ifndef BSW_EVQ_INC_CWSW_EVHANDLER_H_
#define BSW_EVQ_INC_CWSW_EVHANDLER_H_

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
#include "projcfg.h"
#include "cwsw_evqueue.h"	/* tEvQ_Event, et. al. */
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
 * 	@param evInt	Supplemental information for the event.
 */
typedef void (*pEvQ_EvHandlerFunc)(tEvQ_Event evId, uint32_t extra);

/**	Association of event handler to a specific event.
 */
typedef struct sEvHandlerAssoc {
	tEvQ_EventID		evId;
	pEvQ_EvHandlerFunc	pEvHandler;
} tEvQ_EvHandlerAssoc, *pEvQ_EvHandlerAssoc;

/** "Handle" for the position of a specific event in the event-handler table.
 */
typedef int32_t	tEvQ_EvtHandle;		/* would prefer to use `ssize_t`, but that's a POSIX type, not a C type */


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

tEvQ_ErrorCode 		Cwsw_EvQ__RegisterHandler(pEvQ_EvHandlerAssoc pEvHndlrTbl, size_t evtblsz, tEvQ_EventID ev, pEvQ_EvHandlerFunc pf);
pEvQ_EvHandlerFunc	Cwsw_EvQ__GetHandler(pEvQ_EvHandlerAssoc pEvHndlr, size_t evtblsz, tEvQ_EventID ev);


#ifdef	__cplusplus
}
#endif

#endif /* BSW_EVQ_INC_CWSW_EVHANDLER_H_ */
