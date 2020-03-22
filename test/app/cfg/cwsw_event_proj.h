/** @file
 *	@brief	Project-specific definitions related to event queues.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Mar 2, 2018
 *	@author: kbecker
 */

#ifndef CWSW_EVQ_PROJ_H_
#define CWSW_EVQ_PROJ_H_

#ifdef	__cplusplus
extern "C" {
#endif

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdint.h>

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

/** Compile-time calibration to enable guards on either side of the Event Queue
 *	buffer. This is a debugging aid used to detect buffer underrun or overrun.
 *
 *	Disable guard band: Default; symbol not defined, or defined as 0 or false.
 *	Enable guard band:	Symbol defined with a value of 1 or true.
 */
#define ENABLE_EVQ_GUARDS		1

/** Global list of events for the event queue.
 *	Note that this implementation assumes a contiguous list with no gaps in numeric values. This
 *	implementation uses the event value as an index into a table, and sizes all tables according to
 *	the value of kNumProjectEvqEvents.
 */
enum eTestProjectEvents {
	evNullEvent = 0,	/**< reserved value, used for initialization */
	evBtnPressed,		/**< debounced press event */
	evBtnCommit,
	evBtReleased,
	evUiUpdate,
	kNumProjectEvqEvents
};


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

/**	The base type for the event IDs used in the Event Queue.
 *	With the present container, there can be a maximum of 255 distinct event IDs
 *	per event queue. It is possible for each event queue to have a distinct
 *	list of events, or, one or more event queues could use the same list of
 *	defined events.
 *
 *	Value 0 is reserved for queue management (and, because the State Machine
 *	Engine uses this event queue, it also uses value 0 for its own purposes).
 *
 *	If you use a different base type, it should be an unsigned integral type.
 */
typedef unsigned char tEvQ_EventID;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_EVQ_PROJ_H_ */
