/** @file tedlos.c
 *	@brief	The Event-Dispatching Loop OS.
 *
 *	Description:
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 19, 2020
 *	Author: KBECKE35
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdint.h>
#include <stdbool.h>

// ----	Project Headers -------------------------
#include "cwsw_clock.h"
#include "cwsw_evhandler.h"

// ----	Module Headers --------------------------
#include "tedlos.h"


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

static bool initialized = false;

// control structure for the OS event queue
static tEvQ_QueueCtrl	evqCtrl = {0};

// the event queue itself
/* for this trial, simply load the event queue with a bunch of events. at the moment, i'm not worried
 * about their semantic meanings.
 * note that initializing them this way does NOT properly initialize the queue-control write pointer,
 * so the 1st <n> PostEvQ() calls will overwrite the existing events.
 */
static tEvQ_Event		evqueue[10] = {
	{1, 1},
	{2, 2},
	{3, 3},
	{4, 4},
	{5, 5},
	{6, 6}
};

// the handlers for each identified OS event
void HandleEvent1(tEvQ_Event ev, uint32_t evInt);
void HandleEvent2(tEvQ_Event ev, uint32_t evInt);
void HandleEvent3(tEvQ_Event ev, uint32_t evInt);
static tEvQ_EvHandlerAssoc evhandlers[kNumOsEvqEvents] = {
		{0, NULL },
		{1, HandleEvent1 },
		{2, HandleEvent2 },
		{3, HandleEvent3 }
	};

// timer objects	{
// application lifecycle timer
static tCwswClockTics timeleft = 0;
// reload value
enum {app_duration = 5000 };	/* roughly 5 seconds */

//	}

// ============================================================================
// ----	Private Functions -----------------------------------------------------
// ============================================================================

void HandleEvent1(tEvQ_Event ev, uint32_t evInt)
{
	UNUSED(ev);
	UNUSED(evInt);
}

void HandleEvent2(tEvQ_Event ev, uint32_t evInt)
{
	UNUSED(ev);
	UNUSED(evInt);
}

void HandleEvent3(tEvQ_Event ev, uint32_t evInt)
{
	UNUSED(ev);
	UNUSED(evInt);
}


// constant section
enum eSwTimerState {
	kSwTimerDisabled,
	kSwTimerEnabled,
	kSwTimerPaused
};
// type section
typedef enum eSwTimerState tSwTimerState;
struct sSwTimer {
	tCwswClockTics		tm;
	tCwswClockTics		reloadtm;
	int16_t				evid;		// generic container so any event class can be used; 0 for no event
	tSwTimerState		tmrstate;	// allows for a different ev + handler than "normal" event associations
};
typedef struct sSwTimer tCwswSwTimer, *pCwswSwTimer;

// application heartbeat timer; intended for a 1-ms nominal rate, though in this implementation, its monotonicity is suspect
tCwswSwTimer tmrHb = {0};


int	/* does not allow for an initial timeout different than rearm time */
timer__init(pCwswSwTimer pTimer, tCwswClockTics armtm, int16_t ev)
{
	if(pTimer)
	{
		pTimer->tm = armtm;
		pTimer->reloadtm = armtm;
		pTimer->evid = ev;
		pTimer->tmrstate = kSwTimerDisabled;
	}
	return 0;	// todo: return badptr
}

void
timer_state_set(pCwswSwTimer pTimer, tSwTimerState newstate)
{
	if(pTimer)
	{
		pTimer->tmrstate = newstate;
	}
}


void Cwsw_SwTmr__ManageTimer(pCwswSwTimer pTimer)
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
					tEvQ_Event ev = {pTimer->evid, exptm};
					(void)PostEvQ(evqCtrl, ev);
				}
			}
		}
	}
}


void HandleTimerTic(tEvQ_Event ev, uint32_t evInt)
{
	if(!timeleft)
	{
		Set(Cwsw_Clock, timeleft, app_duration);
	}
	if(Get(Cwsw_Clock, timeleft) <= 0)
	{
		// update all SW timers
		Cwsw_SwTmr__ManageTimer(&tmrHb);

		// do whatever else should be done in the OS scheduling loop

		// rearm timer
		Set(Cwsw_Clock, timeleft, app_duration);
	}
}

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

void tedlos_init(void)
{
	if(kEvQ_Err_NoError != Cwsw_EvQ__InitEvQ(&evqCtrl, evqueue, TABLE_SIZE(evqueue)))	return;

	// for this test / build only
	evqCtrl.Queue_Count = 6;	// preload w/ the values already initialized (in the definition statement)

	// initialize the handlers
	(void)Cwsw_EvQ__RegisterHandler(evhandlers, TABLE_SIZE(evhandlers), evOsTmrHeartbeat, HandleTimerTic);

	// since nobody's initialized the clock yet, do it here. note it may be significant to do it
	//	in the module, as we may want to pass the evq control structure of the module.
	Cwsw_ClockSvc__Init(&evqCtrl, evOsTmrHeartbeat);

	// initialize HB timer for a 100-ms HB
	timer__init(&tmrHb, 100, 0);
	timer_state_set(&tmrHb, kSwTimerEnabled);

	initialized = true;
}

void tedlos_do(void)
{
	tEvQ_Event thisevent = { evOsNullEvent, 0};
	pEvQ_EvHandlerFunc pf = NULL;

	if(!initialized)	{ return; }

	do {
		// execute clock pump. only required (?) for Lin/dows.
		tCwswClockTics tmrtic = Cwsw_ClockSvc__Task();

		// retrieve event. if one exists, and if it has a handler, dispatch
		(void)Cwsw_EvQ__GetEvent(&evqCtrl, &thisevent);
		if(thisevent.evId)
		{
			pf = Cwsw_EvQ__GetHandler(evhandlers, TABLE_SIZE(evhandlers), thisevent.evId);
			if(pf)
			{
				pf(thisevent, tmrtic);	/* todo: launch this in an independent thread (e.g., protothread) */
			}
		}
	} while(thisevent.evId != evQuitRqst);
}
