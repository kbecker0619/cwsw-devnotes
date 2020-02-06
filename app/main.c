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

#include "projcfg.h"

// ----	System Headers --------------------------
#include <stdio.h>
#include <stdlib.h>			/* EXIT_SUCCESS */
#include <limits.h>			/* INT_MAX */

// ----	Project Headers -------------------------
#include "cwsw_lib.h"
#include "cwsw_arch.h"
#include "cwsw_board.h"
#include "cwsw_eventsim.h"

// ----	Module Headers --------------------------
// the point of this project
#include "cwsw_evqueue.h"


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

	do {
		tEvQueueCtrl evqCtrl = {0};
		tEvQ_Event evqueue[5] = {0};
		tEvQ_Event thisevent = evNoEvent;

		tEvQ_EvQueue pQ = evqueue;
		if(kEvQ_Err_NoError == Cwsw_EvQ__InitEvQ(&evqCtrl, pQ, sizeof evqueue))
		{
			Cwsw_EvQ__PostEvent(&evqCtrl, evNotInit);
			Cwsw_EvQ__GetEvent(&evqCtrl, &thisevent);

		}

	} while(0);

	Task(Cwsw_Lib);

	PostEvent(evTerminateRequested, ev);
    return (EXIT_SUCCESS);
}
