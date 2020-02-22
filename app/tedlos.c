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
#include "cwsw_swtimer.h"

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

// application heartbeat timer; intended for a 1-ms nominal rate, though in this implementation, its monotonicity is suspect
tCwswSwTimer tmrOsTic = {0};


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


enum eAppStates {
	// this state machine applies only during the time that the scheduler is active; it does not
	//	track the earlier stages of initialization, nor the states that will take effect after the
	//	scheduler has been stopped.
	kAppState_Init,
	kAppState_Normal,
	kAppState_PrepSleep,
	kAppState_Sleep,
	kAppState_Awake,
};


/*	This is the main app-owned message pump, and is called by the Clock Services component.
 *	This callback should have an absolute minimum of things to do:
 *	- manage all timers
 *	- nothing else (because, in this design, we are fully reactive, and nothing happens unless an
 *	  event prompts it to happen, and our "tasks" are driven by timers
 */
void
Os1msTic(tEvQ_Event ev, uint32_t evInt)
{
	if(!timeleft)
	{
		Set(Cwsw_Clock, timeleft, app_duration);
	}
	if(Get(Cwsw_Clock, timeleft) <= 0)
	{
		// update all SW timers
		Cwsw_SwTmr__ManageTimer(&tmrOsTic, &evqCtrl);

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
	// initialize clock services.
	//	since at present, clk-srv only understands one base-rate event, we'll associate it with
	//	tedlos' own private queue.
	Cwsw_ClockSvc__Init(&evqCtrl, evOsTmrHeartbeat);

	// initialize event queue used for tedlos
	if(kErr_EvQ_NoError != Cwsw_EvQ__InitEvQ(&evqCtrl, evqueue, TABLE_SIZE(evqueue)))	return;

	// initialize the handlers.
	(void)Cwsw_EvQ__RegisterHandler(evhandlers, TABLE_SIZE(evhandlers), evOsTmrHeartbeat, Os1msTic);

	// for this test / build only
	evqCtrl.Queue_Count = 6;	// preload w/ the values already initialized (in the definition statement)

	// initialize HB timer for a 100-ms HB
	Cwsw_SwTmr__Init(&tmrOsTic, 100, 0);
	Cwsw_SwTmr__SetState(&tmrOsTic, kSwTimerEnabled);

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
