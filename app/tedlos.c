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
 * note that initializing them this way does NOT properly initialize the write pointer, so the 1st
 * <n> PostEvent() calls will overwrite the existing events.
 */
static tEvQ_Event		evqueue[10] = {1, 2, 3, 4, 5, 6};

// the handlers for each identified OS event
void HandleEvent1(tEvQ_Event ev, uint32_t evInt);
void HandleEvent2(tEvQ_Event ev, uint32_t evInt);
void HandleEvent3(tEvQ_Event ev, uint32_t evInt);
static tEvH_EvHandler evhandlers[kNumOsEvqEvents] = {
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
// retrieval method
/**	Target for TM(app_duration) API */
#define GET_timeleft()	Get(Cwsw_Clock, timeleft)

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


enum eSwTimerState {
	kSwTimerDisabled,
	kSwTimerEnabled,
	kSwTimerPaused
};
typedef enum eSwTimerState tSwTimerState;
struct sSwTimer {
	tCwswClockTics		tm;
	tCwswClockTics		reloadtm;
	int16_t				ev;			// generic container so any event class can be used; 0 for no event
	pEvH_EvHandlerFunc	pTmrFunc;	// allows for a different ev + handler than "normal" event associations
	tSwTimerState		tmrstate;
};
typedef struct sSwTimer tCwswSwTimer, *pCwswSwTimer;

tCwswSwTimer tmrHb = {0};


int	/* does not allow for an initial timeout different than rearm time */
timer__init(pCwswSwTimer pTimer, tCwswClockTics armtm, int16_t ev, pEvH_EvHandlerFunc pTmrFunc)
{
	if(pTimer)
	{
		pTimer->tm = armtm;
		pTimer->reloadtm = armtm;
		pTimer->ev = ev;
		pTimer->pTmrFunc = pTmrFunc;
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


void HandleTimerTic(tEvQ_Event ev, uint32_t evInt)
{
	if(!timeleft)
	{
		Set(Cwsw_Clock, timeleft, app_duration);
	}
	if(TM(timeleft))
	{
		// update all SW timers

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
	timer__init(&tmrHb, 100, 0, NULL);
	timer_state_set(&tmrHb, kSwTimerEnabled);

	initialized = true;
}

void tedlos_do(void)
{
	tEvQ_Event thisevent = evOsNullEvent;
	pEvH_EvHandlerFunc pf = NULL;

	if(!initialized)	{ return; }

	do {
		// execute clock pump. only required (?) for Lin/dows.
		tCwswClockTics tmrtic = Cwsw_ClockSvc(); UNUSED(tmrtic);

		// retrieve event. if one exists, and if it has a handler, dispatch
		(void)Cwsw_EvQ__GetEvent(&evqCtrl, &thisevent);
		if(thisevent)
		{
			if(thisevent != evOsTmrHeartbeat)
			{
				printf("%d", thisevent);
			}
			pf = Cwsw_EvQ__GetHandler(evhandlers, TABLE_SIZE(evhandlers), thisevent);
			if(pf)
			{
				pf(thisevent, tmrtic);	/* todo: launch this in an independent thread (e.g., protothread) */
			}
		}
	} while(thisevent != evQuitRqst);
}
