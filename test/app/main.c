/** @file
 *	@brief	demo main() for CWSW Event Queue and EvQ Extended.
 *
 *	\copyright
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

// ----	Project Headers -------------------------
/* configuration items */
#include "cwsw_eventsim.h"
/* component headers used here */
#include "cwsw_evqueue_ex.h"
#include "cwsw_evthndlrassoc.h"		/* tEvQ_EvHandlerAssoc */
#include "tedlosevents.h"			/* OS events for this demo */
#include "cwsw_svc.h"

// ----	Module Headers --------------------------
// the point of this project
//#include "tedlos.h"


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


//#include "evq_events.h"
static void
do_evdispatch(void)
{
//	tedlos_init();
//	tedlos_do();
}


void
MyEvHandler(tEvQ_Event ev, uint32_t extra)
{
	UNUSED(ev);
	UNUSED(extra);
}

static void
basic_lib_api(void)
{
	tEventPayload ev = { 0 };

	if(!Get(Cwsw_Lib, Initialized))	// totally unnecessary test, simply to demonstrate Get() API
	{
		PostEvent(evNotInit, ev);
		(void)Init(Cwsw_Lib);		// since the CWSW lib can be called by any module, initialize it 1st
		cwsw_assert(Get(Cwsw_Lib, Initialized), "Confirm initialization");
	}

	(void)Init(Cwsw_Services);
//	(void)Init(Cwsw_EvQ);			// Cwsw_EvQ__Init()

	/* contrived example, not recommended, to exercise other features of the component */
	cwsw_assert(1 == Cwsw_Critical_Protect(0), "Confirm critical section nesting count");
	cwsw_assert(0 == Cwsw_Critical_Release(0), "Confirm balanced critical region usage");
	cwsw_assert(2 == Init(Cwsw_Lib), "Confirm reinitialization return code");
}

static void
basic_ev_api(void)
{
/*  rote run-through of EVENT methods */
	tEvQ_Event my_table_of_events[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_EvTable evTbl = {0};

	cwsw_assert(Init(Cwsw_Evt) == kErr_Lib_NoError, "test component init");

	cwsw_assert(
		kErr_EvQ_BadParm == Cwsw_Evt__InitEventTable(NULL, my_table_of_events, TABLE_SIZE(my_table_of_events)),
		"Confirm bad Event Queue parameter");
	cwsw_assert(
		kErr_EvQ_BadParm == Cwsw_Evt__InitEventTable(&evTbl, NULL, TABLE_SIZE(my_table_of_events)),
		"Confirm bad Event Queue parameter");
	cwsw_assert(
		kErr_EvQ_NoError == Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events)),
		"Confirm good parms");
	cwsw_assert(kRT_TBL_VALID == evTbl.validity, "Unexpected table validity");

	cwsw_assert(
		kErr_EvQ_NoError == Cwsw_Evt__InitEventTable(&evTbl, my_table_of_events, TABLE_SIZE(my_table_of_events)),
		"Confirm event table initialization");

	Deinit(Cwsw_EvT);
}

static void
basic_evq_api(void)
{
	/* event queue methods */
	// predefine a buffer already filled with events.
	// Note: to try to help keep things straight, we're going to call the actual buffer that
	//	contains the events, a "buffer." the "Event Table" will be the buffer control structure.
	tEvQ_Event tblEventBuff[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	tEvQ_Event tblEventBuf2[] = {
		{ 9, 415 }, { 8, 414 }, { 7, 207 }, { 6, 206 }, { 5, 205 },
		{ 4, 204 }, { 3, 103 }, { 2, 102 }, { 1, 101 }, { 0, 100 },
	};
	tEvQ_EvTable evTbl = {0};	// for this step, rely on init() function, not compile-time setup

	static tEvQ_QueueCtrl evq = {0};

	if(!Init(Cwsw_EvQ))
	{
		// step 1: initialize event table
		if(!Cwsw_Evt__InitEventTable(&evTbl, tblEventBuff, TABLE_SIZE(tblEventBuff)))
		{
			tEvQ_Event myevent = {0};

			// step 2: now that the Event Table is initialized, init the Event Queue
			cwsw_assert(
					kErr_EvQ_NoError == Cwsw_EvQ__InitEvQ(&evq, &evTbl, tblEventBuff, TABLE_SIZE(tblEventBuff)),
					"Unexpected failure to initialize queue");

			// for this test only, modify an internal queue attribute to account for the initialization
			//	done in the event buffer above.
			evq.Queue_Count = 10;

			// retrieve an event
			cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQ__GetEvent(&evq, &myevent), "Unexpected initialization problem.");
				cwsw_assert(0 == myevent.evId, "Unexpected event.");
				cwsw_assert(100 == myevent.evData, "Unexpected event data.");
			cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQ__GetEvent(&evq, &myevent), "confirm happy path");
				cwsw_assert(1 == myevent.evId, "Unexpected event.");
				cwsw_assert(101 == myevent.evData, "Unexpected event data.");
			cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQ__FlushEvents(&evq), "confirm happy path");
			cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQ__PostEvent(&evq, myevent), "confirm happy path");
			cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQ__GetEvent(&evq, &myevent), "confirm happy path");
				cwsw_assert(1 == myevent.evId, "Unexpected event.");
				cwsw_assert(101 == myevent.evData, "Unexpected event data.");
			cwsw_assert(kErr_EvQ_QueueEmpty == Cwsw_EvQ__GetEvent(&evq, &myevent), "confirm happy path");
		}
		// step 1: initialize event table
		if(!Cwsw_Evt__InitEventTable(&evTbl, tblEventBuf2, TABLE_SIZE(tblEventBuf2)))
		{
			tEvQ_Event myev = {0};

			// step 2: now that the Event Table is initialized, init the Event Queue
			cwsw_assert(
					kErr_EvQ_NoError == Cwsw_EvQ__InitEvQ(&evq, &evTbl, tblEventBuf2, TABLE_SIZE(tblEventBuf2)),
					"unexpected failure to initialize queue");
			// for this test only, modify an internal queue attribute to account for the initialization
			//	done in the event buffer above.
			evq.Queue_Count = 10;

			// retrieve an event
			cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQ__GetEvent(&evq, &myev), "Unexpected initialization problem.");
				cwsw_assert(9 == myev.evId, "Unexpected event.");
				cwsw_assert(415 == myev.evData, "Unexpected event data.");
			cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQ__GetEvent(&evq, &myev), "confirm happy path");
				cwsw_assert(8 == myev.evId, "Unexpected event.");
				cwsw_assert(414 == myev.evData, "Unexpected event data.");
			cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQ__FlushEvents(&evq), "confirm happy path");
			cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQ__PostEvent(&evq, myev), "confirm happy path");
			cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQ__GetEvent(&evq, &myev), "confirm happy path");
				cwsw_assert(8 == myev.evId, "Unexpected event.");
				cwsw_assert(414 == myev.evData, "Unexpected event data.");
			cwsw_assert(kErr_EvQ_QueueEmpty == Cwsw_EvQ__GetEvent(&evq, &myev), "confirm happy path");
		}
	}
}

static void
basic_evh_api(void)
{
	/* event handler */
	tEvQ_EvHandlerAssoc mytbl[kNumOsEvqEvents] = { {0} };
	tEvQ_EvHndlrAssocTable tblMyHandlers = {0};
	pEvQ_EvHandlerFunc myfunc;

	(void)Cwsw_EvHA__InitEventHandlerTable(&tblMyHandlers, mytbl, TABLE_SIZE(mytbl));
	Cwsw_EvHA__SetEvHandler(&tblMyHandlers, 1, MyEvHandler);
	myfunc = Cwsw_EvHA__GetEvHandler(&tblMyHandlers, 1);
	if(myfunc)
	{
		tEvQ_Event ev = {13, 137};
		myfunc(ev, __LINE__);
	}
}

static void
basic_evqx_api(void)
{
	/* extended event queue */
	// set up the standard queue
	//	1. event array
	tEvQ_Event tblxEvtBuff[] = {
		{ 0, 100 }, { 1, 101 }, { 2, 102 }, { 3, 103 }, { 4, 204 },
		{ 5, 205 }, { 6, 206 }, { 7, 207 }, { 8, 414 }, { 9, 415 },
	};
	//	2. event table
	tEvQ_EvTable tblxEv = {tblxEvtBuff, TABLE_SIZE(tblxEvtBuff), kCT_TBL_VALID};

	// now set up the event handler table
	//	1. event association array
	tEvQ_EvHandlerAssoc tblxEvHndlr[kNumOsEvqEvents] = { {0} };
	//	2. event handler assocation table
	tEvQ_EvHndlrAssocTable tblxMyHandlers = {tblxEvHndlr, TABLE_SIZE(tblxEvHndlr), kCT_TBL_VALID};

	// finally, set up evqx
	//							evq		ct	w	r
	tEvQ_QueueCtrlEx MyQX = {{&tblxEv, 0,	0,	0}, &tblxMyHandlers};

	do {	/* EvQ API */
		tEvQ_Event myev = {0};
		// the above setup demonstrate compile-time setup.
		// now do the same thing via the init function
		tErrorCodes_EvQ rc = Cwsw_EvQX__InitEvQ(&MyQX,
												&tblxEv,
												tblxEvtBuff,
												TABLE_SIZE(tblxEvtBuff),
												&tblxMyHandlers,
												tblxEvHndlr,
												TABLE_SIZE(tblxEvHndlr) );
		UNUSED(rc);

		// retrieve an event
		MyQX.EvQ_Ctrl.Queue_Count = 10;
		cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQX__GetEvent(&MyQX, &myev), "Unexpected initialization problem.");
			cwsw_assert(0 == myev.evId, "Unexpected event.");
			cwsw_assert(100 == myev.evData, "Unexpected event data.");
		cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQX__GetEvent(&MyQX, &myev), "confirm happy path");
			cwsw_assert(1 == myev.evId, "Unexpected event.");
			cwsw_assert(101 == myev.evData, "Unexpected event data.");
		cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQX__FlushEvents(&MyQX), "unexpected problem during queue flush");
		cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQX__PostEvent(&MyQX, myev), "confirm happy path");
		cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQX__GetEvent(&MyQX, &myev), "confirm happy path");
			cwsw_assert(1 == myev.evId, "Unexpected event.");
			cwsw_assert(101 == myev.evData, "Unexpected event data.");
		cwsw_assert(kErr_EvQ_QueueEmpty == Cwsw_EvQX__GetEvent(&MyQX, &myev), "confirm happy path");
	} while(0);

	do {	/* Event Handler API */
		tEvQ_Event myev = {evQuitRqst, __LINE__};
		pEvQ_EvHandlerFunc myfunc;
		cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQX__SetEvHandler(&MyQX, evQuitRqst, MyEvHandler), "unexpected association failure");
		cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQX__PostEvent(&MyQX, myev), "unexpected event post problem");
		cwsw_assert(kErr_EvQ_NoError == Cwsw_EvQX__PostEvent(&MyQX, myev), "unexpected event post problem");
		myfunc = Cwsw_EvQX__GetEvHandler(&MyQX, evQuitRqst);
		if(myfunc)
		{
			tEvQ_Event ev = {13, 137};
			myfunc(ev, __LINE__);
		}
	} while(0);

	(void)Cwsw_EvQX__HandleNextEvent(&MyQX, __LINE__);
}


int
main(void)
{
	tEventPayload ev = { 0 };
	basic_lib_api();
	basic_ev_api();
	basic_evq_api();
	basic_evh_api();
	basic_evqx_api();

	do_evdispatch();

	PostEvent(evTerminateRequested, ev);
    return (EXIT_SUCCESS);
}
