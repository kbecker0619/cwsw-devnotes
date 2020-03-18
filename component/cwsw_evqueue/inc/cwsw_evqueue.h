/** @file
 *	@brief	Event Queue component definitions and methods.
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 1, 2018
 *	Author: kbecker
 */

#ifndef CWSW_EVQUEUE_H
#define CWSW_EVQUEUE_H

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <limits.h>

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------
#include "cwsw_event.h"			/* tEvQ_Event, tErrorCodes_EvQ */
#include "cwsw_eventtable.h"	/* ptEvQ_EvTable */


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

/** @defgroup	tEvQ_QueueCtrl	tEvQ_QueueCtrl: Event Queue component.
 *	@brief		Takes a table of events and adds management routines to it.
 * 	@ingroup	tEvQ_QueueCtrlEx
 */

/**	Event Queue control structure.
 *	@ingroup tEvQ_QueueCtrl
 */
typedef struct sEvQueue {
	ptEvQ_EvTable	pEventTable;	//!< reference to event table.
	int32_t		 	Queue_Count;	//!< number of items in the queue.
	int32_t			idxWrite;		//!< queue write pointer.
	int32_t			idxRead;		//!< queue read pointer.
} tEvQ_QueueCtrl;

/** Reference to an Event Queue.
 *	@ingroup tEvQ_QueueCtrl
 */
typedef tEvQ_QueueCtrl *ptEvQ_QueueCtrl;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

// ---- Discrete Functions -------------------------------------------------- {

extern uint16_t			Cwsw_EvQ__Init(void);
extern tErrorCodes_EvQ	Cwsw_EvQ__InitEvQ(ptEvQ_QueueCtrl EvQueueCtrl, ptEvQ_EvTable pEvQueue);
extern bool 			Cwsw_EvQ__Get_Initialized(void);
extern tErrorCodes_EvQ	Cwsw_EvQ__FlushEvents(ptEvQ_QueueCtrl pEvQueueCtrl);
extern tErrorCodes_EvQ	Cwsw_EvQ__PostEvent(ptEvQ_QueueCtrl pEvQueueCtrl, tEvQ_Event ev);
extern tErrorCodes_EvQ	Cwsw_EvQ__GetEvent(ptEvQ_QueueCtrl pEvQ, pEvQ_Event pEv);

// ---- /Discrete Functions ------------------------------------------------- }

// ---- Targets for Get/Set APIs -------------------------------------------- {

/** "Chapter Designator" for Get/Set API.
 *	Intentionally unused symbol, designed to get you to the correct starting
 *	point, when you want to find macros for the Get/Set API; simply highlight
 *	the Module argument in your IDE (e.g, Eclipse, NetBeans, etc.), and select
 *	Go To Definition.
 */
enum { Cwsw_EvQ };		/* Component ID for Event Queue */

/** Target symbol for Get(Cwsw_EvQ, xxx) interface */
#define Cwsw_EvQ__Get(resource)		Cwsw_EvQ__Get_ ## resource()

#define PostEvQ(EvQ, ev)			Cwsw_EvQ__Post(EvQ, ev)
#define Cwsw_EvQ__Post(EvQ, event)	Cwsw_EvQ__PostEvent(&EvQ, event)

// ---- /Targets for Get/Set APIs ------------------------------------------- }


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_EVQUEUE_H */
