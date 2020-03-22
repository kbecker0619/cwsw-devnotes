/** @file tedlos.c
 *	@brief	The Event-Dispatching Loop OS.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Feb 19, 2020
 *	@author: kbecker
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

enum eAppStates {
	// this state machine applies only during the time that the scheduler is active; it does not
	//	track the earlier stages of initialization, nor the states that will take effect after the
	//	scheduler has been stopped.
	kAppState_NoState,
	kAppState_Init,
	kAppState_Normal,
	kAppState_PrepSleep,
	kAppState_Sleep,
	kAppState_Awake,
};


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

typedef enum eAppStates tAppState;


// ============================================================================
// ----	Global Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Module-level Variables ------------------------------------------------
// ============================================================================

static bool initialized = false;

// control structure for the OS event queue
static tEvQ_QueueCtrl evqcTedlos = {0};

// the event queue itself
static tEvQ_Event evqTedlos[10] = { 0 };

// the handlers for each identified OS event
static tEvQ_EvHandlerAssoc evcbTedlos[kNumOsEvqEvents] = { 0 };


// application heartbeat timer; intended for a 1-ms nominal rate, though in this implementation, its monotonicity is suspect
tCwswSwTimer tmrOsTic = {0};


tAppState appstate = kAppState_NoState;


// timer objects	{
// application lifecycle timer
//static tCwswClockTics timeleft = 0;
// reload value
enum {app_duration = 5000 };	/* roughly 5 seconds */

//	}

// ============================================================================
// ----	Private Functions -----------------------------------------------------
// ============================================================================

/*	This is the main app-owned message pump, and is called by the Clock Services component.
 *	This callback should have an absolute minimum of things to do:
 *	- manage all timers
 *	- nothing else (because, in this design, we are fully reactive, and nothing happens unless an
 *	  event prompts it to happen, and our "tasks" are driven by timers
 */
void
Os1msTic(tEvQ_Event ev, uint32_t evInt)
{
	// update all SW timers
	Cwsw_SwTmr__ManageTimer(&tmrOsTic);
}

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

typedef struct eTedlosTaskDescriptor {
	pCwswSwTimer		pTmrTask;
	tCwswClockTics		tm_init;
	tCwswClockTics		tm_rearm;
	pEvQ_QueueCtrl		pEvqCtrl;	// assume this is always going to be the init task, but we specify it here because it's a project-specific thing
	int16_t				evid;
	pEvQ_EvHandlerFunc	pf;			//
} tTedlosTaskDescriptor, *pTedlosTaskDescriptor;

//	10ms Task, Init	@{
tCwswSwTimer tmrTask10msInit;
void
cb10Ms_Init(tEvQ_Event ev, uint32_t evInt)
{
	UNUSED(ev);
	UNUSED(evInt);
}
//	@}

//tTedlosTaskDescriptor TableOfInitTasks;
tTedlosTaskDescriptor TableOfInitTasks[] = {
	//		timer			init	reload		evq				evid					evcb
	{	&tmrTask10msInit,	  10,	  10,	&evqcTedlos,	evOs_Tmr10MsTaskInit,	cb10Ms_Init	},
};

void
InitTask(tEvQ_Event ev, uint32_t evInt)
{
	// Start all init tasks. they, in turn, will start their respective application-mode tasks
	size_t ct = TABLE_SIZE(TableOfInitTasks);
	while(ct--)
	{
		pTedlosTaskDescriptor tmp = &TableOfInitTasks[ct];
		(void)Cwsw_SwTmr__Init(tmp->pTmrTask, tmp->tm_init, tmp->tm_rearm, tmp->pEvqCtrl, 0, tmp->evid);
//		(void)Cwsw_EvQ__RegisterHandler(tmp->pf, TABLE_SIZE(evcbTedlos), tmp->evid, Os1msTic);

	}
}

void tedlos_init(void)
{
	// initialize clock services.
	//	since at present, clk-srv only understands one base-rate event, we'll associate it with
	//	tedlos' own private queue.
	Cwsw_ClockSvc__Init(&evqcTedlos, evOsTmrHeartbeat);

	/* initialize the app-specific OS timer tic
	 *	since we want this timer tic callback to be extremely simple, and not to be involved in mode
	 *	management or other distractionary things, we will then set up the initialize task
	 */
	do {
		// initialize event queue used for tedlos
		if(kErr_EvQ_NoError != Cwsw_EvQ__InitEvQ(&evqcTedlos, evqTedlos, TABLE_SIZE(evqTedlos)))	return;

		// initialize the handlers.
		(void)Cwsw_EvQ__RegisterHandler(evcbTedlos, TABLE_SIZE(evcbTedlos), evOsTmrHeartbeat, Os1msTic);

		// set up the app-level timer tic task
//		Cwsw_SwTmr__Init(&tmrOsTic, 10, 10, &evqcTedlos, 0);
		Cwsw_SwTmr__SetState(&tmrOsTic, kSwTimerEnabled);
	} while(0);

	// set the application state and start the init task
	appstate = kAppState_Init;

	initialized = true;
}

void
tedlos_do(void)
{
	tEvQ_Event thisevent = { evOsNullEvent, 0};
	pEvQ_EvHandlerFunc pf = NULL;

	if(!initialized)	{ return; }

	do {
		// execute clock pump. only required (?) for Lin/dows.
		tCwswClockTics tmrtic = Cwsw_ClockSvc__Task();

		// retrieve event. if one exists, and if it has a handler, dispatch
		(void)Cwsw_EvQ__GetEvent(&evqcTedlos, &thisevent);
		if(thisevent.evId)
		{
			pf = Cwsw_EvQ__GetHandler(evcbTedlos, TABLE_SIZE(evcbTedlos), thisevent.evId);
			if(pf)
			{
				pf(thisevent, tmrtic);	/* todo: launch this in an independent thread (e.g., protothread) */
			}
		}
	} while(thisevent.evId != evQuitRqst);
}
