/** @file cwsw_swtimer.c
 *
 *	Description:
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 21, 2020
 *	Author: KBECKE35
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
#include "cwsw_evqueue.h"

// ----	Module Headers --------------------------
#include "cwsw_swtimer.h"


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

// ============================================================================
// ----	Private Functions -----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/**	Initialize the SW Timer. Leaves the timer initialized, but disabled.
 *  does not allow for an initial timeout different than rearm time.
 *
 *  todo: pass event queue control struct as an additional argument.
 *  todo: pass the rearm time as an additional argument.
 */
tErrorCodes_SwTmr
Cwsw_SwTmr__Init(
	// timer-related parameters
	pCwswSwTimer	pTimer,
	tCwswClockTics	tm_init,
	tCwswClockTics	tm_rearm,
	// timer-maturation parameters
	pEvQ_QueueCtrl	pEvqCtrl,
	size_t			qsz,		//
	int16_t			evid)
{
	if(pTimer)
	{
		pTimer->tm = tm_init;
		pTimer->reloadtm = tm_rearm;
		pTimer->pEvqCtrl = pEvqCtrl;
		pTimer->evid = evid;
		pTimer->tmrstate = kSwTimerDisabled;
		return kErr_SwTmr_NoError;
	}
	return kErr_SwTmr_BadParm;
}


void
Cwsw_SwTmr__SetState(pCwswSwTimer pTimer, tSwTimerState newstate)
{
	if(pTimer)
	{
		pTimer->tmrstate = newstate;
	}
}


/**	Manage one SW timer.
 *	If timer has a "re-arm" value set, automatically restart the timer with that value.
 *	If the timer has an event associated, post it to the designated event queue.
 *
 *	@param pTimer	SW Timer to manage.
 *	@param pEvqCtrl	Event queue to post event to.
 *
 *	To be worked out yet:
 *	- original intent was to avoid tying this module explicitly to the event queue component, but we
 *	  also want to have an async response to a timer maturation; there is no other way (in my system)
 *	  to do this.
 *	- given the previous point, without an event, the other way to provide notification that a timer
 *	  event has fired, would be in the return value, but as we look forward, i don't think that's
 *	  the best way.
 *	- given the previous points, there's no reason _not_ to set up the timer with an associated
 *	  event.
 *	- and, given the previous points, it may make usage much easier if we just move the reference to
 *	  the event queue right into the timer definition. the method used here, does allow for
 *	  "dynamic" switching of the event queue, but i cannot at this time envision a usage for this
 *	  which would have any hope of satisfying security or functional safety goals.
 */
void
Cwsw_SwTmr__ManageTimer(pCwswSwTimer pTimer)
{
	if(pTimer)
	{
		if(pTimer->tmrstate == kSwTimerEnabled)
		{
			if(Get(Cwsw_Clock, pTimer->tm) <= 0)
			{
				// save target value to pass as argument to reaction task
				tCwswClockTics exptm = pTimer->tm;

				// rearm timer
				if(pTimer->reloadtm > 0)
				{
					Cwsw_ClockSvc__SetTimer(&pTimer->tm, pTimer->reloadtm);
				}

				// schedule callback
				if(pTimer->evid)
				{
					tEvQ_ErrorCode err;
					tEvQ_Event ev = {pTimer->evid, exptm};
					err = Cwsw_EvQ__PostEvent(pTimer->pEvqCtrl, ev);	// don't need to check for valid queue ctrl, 'cuz it does its own checking
					if(err)
					{
						err = ~0;
					}
				}
			}
		}	// else if paused: ...
		// note: "pause" doesn't tread water; it does not make the timeout value keep pace with the
		//	current time. upon resumption, it is highly probable that the timer will immediately
		//	mature.
	}
}


