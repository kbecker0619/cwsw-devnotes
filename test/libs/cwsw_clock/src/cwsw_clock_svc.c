/** @file
 *	@brief	CWSW Clock Module
 *
 *	Description:
 *	Requires support of a hardware time module.
 *
 *	\copyright
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
//#include "cwsw_clock.h"


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

static pEvQ_QueueCtrl	pOsEvQ = NULL;
static tEvQ_Event		ev_os_heartbeat = {0};

/** Offset between value returned by clock(), and the number of tics since initialization.
 */
static tCwswClockTics	clockoffset = 0;


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
 *	If a valid OS event queue is referenced, we post an OS event on
 *	every change; we assume this is a 1 ms resolution.
 *
 *	@returns Number of clock tics since initialization.
 */
tCwswClockTics maxct = 0;
tCwswClockTics
Cwsw_ClockSvc__Task(void)
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
		if(pOsEvQ)
		{
			ev_os_heartbeat.evData = thistic;
			(void)Cwsw_EvQ__PostEvent(pOsEvQ, ev_os_heartbeat);
		}
	}
	return thistic - clockoffset;
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
Cwsw_ClockSvc__Init(pEvQ_QueueCtrl pEvQ, int16_t HeatbeatEvId)
{
	pOsEvQ = pEvQ;							// remember the address of the OS event queue.
	ev_os_heartbeat.evId = HeatbeatEvId;	// and also remember the event we're to post.

	clockoffset = clock();
}


tClkSvc_ErrorCode
Cwsw_ClockSvc__SetTimer(pCwswClockTics pTimer, tCwswClockTics duration)
{
	if(pTimer)
	{
		if(duration > 0)
		{
			*pTimer = clock() + duration;	// raw clock reading, rather than ClockSvc(), 'cuzza
			return kErr_ClkSvc_NoError;
		}
		return kerr_ClkSvc_BadParm;
	}
	return kerr_ClkSvc_BadParm;
}
