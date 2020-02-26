/** @file cwsw_evqueue.h
 *	@brief	One-sentence short description of file.
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
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

// ----	Project Headers -------------------------
#include "cwsw_lib.h"

// ----	Module Headers --------------------------
#include "cwsw_event.h"		/* tEvQ_Event */


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

/** Error codes returned by Event Queue API. */
typedef enum eErrorCodes_EvQ tEvQ_ErrorCode;

//! Event Queue control structure
typedef struct sEvQueue {
	pEvQ_EvTable	pEvent_Queue;	//!< reference to event queue
	uint8_t			Queue_Size;		//!< queue size. this determines the maximum number of events that can be posted at one time.
	uint8_t		 	Queue_Count;	//!< number of items in the queue
	pEvQ_Event      pWrite;			//!< queue write pointer. Defined as a pointer-to-event, rather than an index, to ease reading/writing API, letting complexity fall into queue management code.
	pEvQ_Event      pRead;			//!< queue read pointer. Defined as a pointer-to-event, rather than an index, to ease reading/writing API, letting complexity fall into queue management code.
} tEvQ_QueueCtrl, *pEvQ_QueueCtrl;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

// ---- Discrete Functions -------------------------------------------------- {

/**	Static initialization of the Event Queue.
 *
 *	This function is intended to be called during the application-initialization
 *	phase, and is only the 1st initialization function that needs to be called.
 *
 *	@returns	Error code, where 0 is no error.
 */
extern uint16_t Cwsw_EvQ__Init(void);

/**	Initialize individual event queue.
 *
 *	Each queue in your system needs initialization: The management functions
 *	need to know the size of this event buffer, and where the buffer is located.
 *
 *	@param[in,out]	EvQueueCtrl	The event control structure.
 *	@param[in]		pEvQueue	The location of the event buffer. The pointer is
 * 								constant, though of course the buffer itself is not.
 * 	@param[in]		EvQueueSz	The size of the event buffer.
 *	@returns Error code, enumeration of type tEvQ_ErrorCode.
 *
 *	It is the responsibility of the caller to ensure the validity of the buffer
 *	and control struct.
 */
extern tEvQ_ErrorCode Cwsw_EvQ__InitEvQ(tEvQ_QueueCtrl *EvQueueCtrl, pEvQ_EvTable const pEvQueue, uint8_t const EvQueueSz);

/** Target for Get(Cwsw_EvQueue, Initialized) interface. */
extern bool Cwsw_EvQ__Get_Initialized(void);

/**	Clear (empty) the event queue.
 *
 *  While there might be a number of reasons why the developer may want to
 *  empty the current queue of all pending events, one important opportunity is
 *  at module initialization.
 *
 *  @param[in,out]	pEvQueueCtrl	Pointer to the current event buffer control structure
 *	@returns		Error code, enumeration of type tEvQ_ErrorCode.
 */
extern tEvQ_ErrorCode Cwsw_EvQ__FlushEvents(tEvQ_QueueCtrl * const pEvQueueCtrl);

/**	Posts an event into the queue.
 *
 *	@param[in,out]	pEvQueueCtrl Pointer to the current control structure.
 *	@param[in]		ev Event to add to the queue.
 *	@returns Error code, enumeration of type tEvQ_ErrorCode.
 */
extern tEvQ_ErrorCode Cwsw_EvQ__PostEvent(tEvQ_QueueCtrl *pEvQueueCtrl, tEvQ_Event ev);

/** Retrieve the current event.
 *	Depletes the event count in the queue by one event.
 *
 *	@param pEvQueueCtrl[in,out]	Pointer to the current event buffer control structure.
 *	@param ev[out]				Pointer to the event returned.
 *	@returns Error code, enumeration of type tEvQ_ErrorCode. For an empty queue,
 *			no error is returned.
 */
extern tEvQ_ErrorCode Cwsw_EvQ__GetEvent(pEvQ_QueueCtrl pEvQueueCtrl, tEvQ_Event *pEv);


// ---- /Discrete Functions ------------------------------------------------- }

// ---- Targets for Get/Set APIs -------------------------------------------- {

/** "Chapter Designator" for Get/Set API.
 *	Intentionally unused symbol, designed to get you to the correct starting
 *	point, when you want to find macros for the Get/Set API; simply highlight
 *	the Module argument in your IDE (e.g, Eclipse, NetBeans, etc.), and select
 *	Go To Definition.
 */
enum { Cwsw_EvQ = 4 };	/* Component ID for Event Queue */

/** Target symbol for Get(Cwsw_Board, xxx) interface */
#define Cwsw_EvQ__Get(resource)		Cwsw_EvQ__Get_ ## resource()

#define PostEvQ(EvQ, ev)			Cwsw_EvQ__Post(EvQ, ev)
#define Cwsw_EvQ__Post(EvQ, event)	Cwsw_EvQ__PostEvent(&EvQ, event)

// ---- /Targets for Get/Set APIs ------------------------------------------- }


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_EVQUEUE_H_ */
