/** @file
 *	@brief	Project-specific definitions related to event queues.
 *
 *	Note:
 *	To configure the Event Queue component, copy this file to the application-specific configuration
 *	folder, and remove the ".template" portion of the file name.
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 2, 2018
 *	Author: kbecker
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


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

/**	The base type for the events used in the Event Queue.
 *	With the present container, there can be a maximum of 255 distinct events
 *	per event queue (it is possible for each event queue to have a distinct
 *	list of events, or, one or more event queues could use the same list of
 *	defined events.
 *
 *	Value 0 is reserved for queue management (and, because the State Machine
 *	Engine uses this event queue, it also uses value 0 for its own purposes).
 *
 *	If you use a different base type, it should be an unsigned integral type.
 */
typedef unsigned char tEvQ_Event;


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
