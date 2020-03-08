/** @file cwsw_evqueue.h
 *
 *	Description:
 *
 *	Copyright (c) 2018 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 1, 2018
 *	Author: kbecker
 *
 *	Current:
 *	$Revision: $
 *	$Date: $
 */

#ifndef CWSW_EVQUEUE_H_
#define CWSW_EVQUEUE_H_

#ifdef	__cplusplus
extern "C" {
#endif

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

#include "projcfg.h"

// ----	System Headers --------------------------
#include <stdint.h>				/* uint16_t */
#include <stdbool.h>			/* bool */
#include <stddef.h>				/* size_t */
#include <limits.h>

// ----	Project Headers -------------------------
#include "cwsw_lib.h"

// ----	Module Headers --------------------------
#include "cwsw_event.h"			/* tEvQ_Event */
#include "cwsw_eventtable.h"	/* pEvQ_EvTable */

// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

/** @defgroup tEvQ_QueueCtrl	Event Queue object.
 *	@brief TBD.
 */

/** Error codes returned by Event Queue API.
 *	@ingroup tEvQ_QueueCtrl
 */
typedef enum eErrorCodes_EvQ tEvQ_ErrorCode;

/**	Event Queue control structure.
 *	@ingroup tEvQ_QueueCtrl
 */
typedef struct sEvQueue {
	pEvQ_EvTable	pEventTable;	//!< reference to event table.
	int32_t		 	Queue_Count;	//!< number of items in the queue.
	int32_t			idxWrite;		//!< queue write pointer.
	int32_t			idxRead;		//!< queue read pointer.
} tEvQ_QueueCtrl;

/** Reference to an Event Queue.
 *	@ingroup tEvQ_QueueCtrl
 */
typedef tEvQ_QueueCtrl *pEvQ_QueueCtrl;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

// ---- Discrete Functions -------------------------------------------------- {

extern uint16_t			Cwsw_EvQ__Init(void);
extern tEvQ_ErrorCode	Cwsw_EvQ__InitEvQ(pEvQ_QueueCtrl EvQueueCtrl, pEvQ_EvTable pEvQueue);
extern bool 			Cwsw_EvQ__Get_Initialized(void);
extern tEvQ_ErrorCode	Cwsw_EvQ__FlushEvents(pEvQ_QueueCtrl pEvQueueCtrl);
extern tEvQ_ErrorCode	Cwsw_EvQ__PostEvent(pEvQ_QueueCtrl pEvQueueCtrl, tEvQ_Event ev);
extern tEvQ_ErrorCode	Cwsw_EvQ__GetEvent(pEvQ_QueueCtrl pEvQ, pEvQ_Event pEv);

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

#endif /* CWSW_EVQUEUE_H_ */
