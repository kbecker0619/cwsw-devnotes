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
typedef void (*pEvH_EvHandlerFunc)(tEvQ_Event ev, uint32_t evInt);

/**	Association of event handler to a specific event.
 */
struct evhandler {
	tEvQ_Event			ev;
	pEvH_EvHandlerFunc	pEvHandler;
};
typedef struct evhandler tEvH_EvHandler;

/** Association of event handler to event.
 *	This type is intended to be used against a table of type #tEvH_EvHandler.
 */
typedef tEvH_EvHandler pEvH_EvHandler;

/** "Handle" for the position of a specific event in the event-handler table.
 */
typedef int tEvH_EvtHandle;	/* would prefer to use `ssize_t`, but that's a POSIX type, not a C type */


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

tEvQ_ErrorCode 	Cwsw_EvQ__RegisterHandler(tEvH_EvHandler *pEvHndlr, size_t evtblsz, tEvQ_Event ev, pEvH_EvHandlerFunc pf);
pEvH_EvHandlerFunc	Cwsw_EvQ__GetHandler(tEvH_EvHandler *pEvHndlr, size_t evtblsz, tEvQ_Event ev);


#ifdef	__cplusplus
}
#endif

#endif /* BSW_EVQ_INC_CWSW_EVHANDLER_H_ */
