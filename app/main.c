/** @file
 *	@brief	Primary Unit Test file for the CWSW Lib component.
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Oct 15, 2019
 *	@author kbecker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdio.h>
#include <stdlib.h>			/* EXIT_SUCCESS */
#include <limits.h>			/* INT_MAX */

// ----	Project Headers -------------------------
#include "projcfg.h"
#include "cwsw_lib.h"
#include "cwsw_arch.h"
#include "cwsw_board.h"
#include "cwsw_eventsim.h"

// ----	Module Headers --------------------------
// the point of this project
#include "cwsw_evqueue.h"
#include "cwsw_evhandler.h"


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
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

void
EventHandler__evNotInit(tEventPayload EventData)
{
	UNUSED(EventData);
}

void
EventHandler__evTerminateRequested(tEventPayload EventData)
{
	UNUSED(EventData);
	(void)puts("Goodbye Cruel World!");
}


/** Dummy symbol to resolve task API call in main. */
#define Cwsw_Lib__Task()	do { } while(0)


static void
handle_not_init(tEvQ_Event ev, uint32_t evInt)
{

}

tEvQ_QueueCtrl	evqCtrl = {0};

/* for this trial, simply load the event queue with a bunch of events. at the moment, i'm not worried
 * about their semantic meanings.
 * note that initializing them this way does NOT properly initialize the write pointer, so the 1st
 * <n> PostEvent() calls will overwrite the existing events.
 */
tEvQ_Event		evqueue[10] = {1, 2, 3, 4, 5, 6};


#include "evq_events.h"
static void
do_evdispatch(void)
{
	tEvQ_EvQueue pQ = evqueue;
	tEvH_EvHandler evhandlers[kNumProjectEvqEvents] = { { 0 } };
	pEvH_EvHandlerFunc pf = NULL;

	if(kEvQ_Err_NoError != Cwsw_EvQ__InitEvQ(&evqCtrl, pQ, TABLE_SIZE(evqueue)))	return;
	evqCtrl.Queue_Count = 6;	// preload w/ the values already initialized (in the definition statement)

	(void)Cwsw_EvQ__RegisterHandler(evhandlers, TABLE_SIZE(evhandlers), evBtnCommit, handle_not_init);
	pf = Cwsw_EvQ__GetHandler(evhandlers, TABLE_SIZE(evhandlers), evBtnCommit);
	if(pf)
	{
		pf(evBtnCommit, 0);	/* todo: launch this in an independent thread (e.g., protothread) */
	}

//	(void)Cwsw_EvQ
//	tEvQ_Event thisevent = evNoEvent;

//		(void)Cwsw_EvQ__PostEvent(&evqCtrl, evButtonCommit);
//
//		do
//		{
//			Cwsw_EvQ__PostEvent(&evqCtrl, evNotInit);
//			Cwsw_EvQ__GetEvent(&evqCtrl, &thisevent);
//			pf = Cwsw_EvQ__GetHandler(&evhandlers, thisevent, TABLE_SIZE(evhandlers));
//			if(pf)
//			{
//				pf(thisevent, 0);	/* todo: launch this in an independent thread (e.g., protothread) */
//			}
//		} while(evTerminateRequested != thisevent);
}


int
main(void)
{
	tEventPayload ev = { 0 };

	if(!Get(Cwsw_Lib, Initialized))
	{
		PostEvent(evNotInit, ev);
		(void)Init(Cwsw_Lib);
		cwsw_assert(Get(Cwsw_Lib, Initialized), "Confirm initialization");
	}

	(void)Init(Cwsw_Arch);	// Cwsw_Arch__Init()
	(void)Init(Cwsw_Board);	// Cwsw_Board__Init()
	(void)Init(Cwsw_EvQ);	// Cwsw_EvQ__Init()

	/* contrived example, not recommended, to exercise other features of the component */
	cwsw_assert(1 == Cwsw_Critical_Protect(0), "Confirm critical section nesting count");
	cwsw_assert(0 == Cwsw_Critical_Release(0), "Confirm balanced critical region usage");
	cwsw_assert(2 == Init(Cwsw_Lib), "Confirm reinitialization return code");

	do_evdispatch();

	Task(Cwsw_Lib);

	PostEvent(evTerminateRequested, ev);
    return (EXIT_SUCCESS);
}
