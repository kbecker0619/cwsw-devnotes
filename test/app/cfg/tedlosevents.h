/** @file
 *	@brief	events for tedlos
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Feb 8, 2020
 *	@author: kbecker
 */

#ifndef PRJ_EVQ_EVENTS_H
#define PRJ_EVQ_EVENTS_H

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

/** Global list of events for the event queue.
 *	Note that this implementation assumes a contiguous list with no gaps in numeric values. This
 *	implementation uses the event value as an index into a table, and sizes all tables according to
 *	the value of kNumOsEvqEvents.
 */
enum eOsEvqEvents {
	evOsNullEvent = kEvQ_Ev_None,	/**< reserved value, used for initialization */
	evOsTmrHeartbeat,
	evOs_Tmr10MsTaskInit,
	evGarbageEvent2,
	evGarbageEvent3,
	evGarbageEvent4,
	evGarbageEvent5,
	evGarbageEvent6,
	evUiUpdate,
	evQuitRqst,
	kNumOsEvqEvents
};


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

typedef enum eOsEvqEvents tOsEvqEvents, *pOsEvqEvents;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================


#ifdef	__cplusplus
}
#endif

#endif /* EVQ_EVENTS_H_ */
