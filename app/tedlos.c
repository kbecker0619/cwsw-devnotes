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
static tEvQ_Event	evqueue[10] = {1, 2, 3, 4, 5, 6};

// the handlers for each identified OS event
void HandleEvent1(tEvQ_Event ev, uint32_t evInt);
void HandleEvent2(tEvQ_Event ev, uint32_t evInt);
void HandleEvent3(tEvQ_Event ev, uint32_t evInt);
static tEvH_EvHandler evhandlers[kNumOsEvqEvents] = {
		{1, HandleEvent1 },
		{2, HandleEvent2 },
		{3, HandleEvent3 }
	};


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

void HandleTimerTic(tEvQ_Event ev, uint32_t evInt)
{

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
	(void)Cwsw_EvQ__RegisterHandler(evhandlers, TABLE_SIZE(evhandlers), evTmrHeartbeat, HandleTimerTic);


	initialized = true;
}

void tedlos_do(void)
{
	pEvH_EvHandlerFunc pf = NULL;

	if(!initialized)	{ return; }


	pf = Cwsw_EvQ__GetHandler(evhandlers, TABLE_SIZE(evhandlers), evTmrHeartbeat);
	if(pf)
	{
		pf(evTmrHeartbeat, 0);	/* todo: launch this in an independent thread (e.g., protothread) */
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
