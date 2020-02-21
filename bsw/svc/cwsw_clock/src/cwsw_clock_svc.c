/** @file
 *	@brief	CWSW Clock Module
 *
 *	Description:
 *	Requires support of a hardware time module.
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Sep 1, 2016
 *	Author: Kevin L. Becker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
#include "projcfg.h"

// ----	Module Headers --------------------------
#include "cwsw_clock.h"


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Global Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Module-level Variables ------------------------------------------------
// ============================================================================

static tEvQ_QueueCtrl	*posevq = NULL;
static int16_t			ev_os_heartbeat = 0;


// ============================================================================
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/**	Clock tic.
 *	Here in Lin/dows, since we're not interrupt-driven, this function requires
 *	being called as absolutely fast as possible.
 *
 *	If the address of of an OS event queue is provided, we post an OS event on
 *	every change; we assume this is a 1 ms resolution.
 *
 *	In a real live system, it would return the number of milliseconds since a
 *	system reset.
 */
tCwswClockTics maxct = 0;
tCwswClockTics
Cwsw_ClockSvc(void)
{
	static tCwswClockTics thistic, lasttic = 0;
	static tCwswClockTics thisct;

	thistic = clock();	// MinGW on Windows has a 1-ms resolution
	if(thistic != lasttic)
	{
		if(lasttic)
		{
			thisct = (thistic - lasttic);
			if(thisct > maxct)	{ maxct = thisct; }
		}
		lasttic = thistic;
		if(posevq)
		{
			(void)Cwsw_EvQ__PostEvent(posevq, ev_os_heartbeat);
		}
	}
	return thistic;
}


/**	Initialize Clock Services module.
 *
 *	@param pevq	Address of control structure for CWSW Event Queues.
 *	@param evhb	Event to post when it's time to issue a timer tic.
 *
 *	While the name format complies with the init signature for sister CWSW
 *	components, but this function requires 2 parameters, so we can't use the
 *	`Init(component)` API.
 *
 *	@note	We need to know about CWSW event queues, but because we want to
 *	support a system that might use a different event queue for OS events than
 *	it does for application events, we'll use a generic container for the event
 *	parameter.
 */
void
Cwsw_ClockSvc__Init(tEvQ_QueueCtrl	*pevq, int16_t evhb)
{
	posevq = pevq;				// remember the address of the OS event queue
	ev_os_heartbeat = evhb;		// and also remember the event we're to post.
}
