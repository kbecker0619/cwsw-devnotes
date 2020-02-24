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
#include "cwsw_svc.h"
#include "cwsw_eventsim.h"

// ----	Module Headers --------------------------
// the point of this project
#include "cwsw_evhandler.h"
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


#include "evq_events.h"
static void
do_evdispatch(void)
{
	tedlos_init();
	tedlos_do();
}

int
main(void)
{
	tEventPayload ev = { 0 };

	if(!Get(Cwsw_Lib, Initialized))	// totally unnecessary test, simply to demonstrate Get() API
	{
		PostEvent(evNotInit, ev);
		(void)Init(Cwsw_Lib);		// since the CWSW lib can be called by any module, initialize it 1st
		cwsw_assert(Get(Cwsw_Lib, Initialized), "Confirm initialization");
	}

	(void)Init(Cwsw_Services);
	(void)Init(Cwsw_EvQ);		// Cwsw_EvQ__Init()

	/* contrived example, not recommended, to exercise other features of the component */
	cwsw_assert(1 == Cwsw_Critical_Protect(0), "Confirm critical section nesting count");
	cwsw_assert(0 == Cwsw_Critical_Release(0), "Confirm balanced critical region usage");
	cwsw_assert(2 == Init(Cwsw_Lib), "Confirm reinitialization return code");

	do_evdispatch();

	PostEvent(evTerminateRequested, ev);
    return (EXIT_SUCCESS);
}
