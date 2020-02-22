/** @file cwsw_swtimer.h
 *
 *	Description:
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 21, 2020
 *	Author: KBECKE35
 */

#ifndef CWSW_SWTIMER_H
#define CWSW_SWTIMER_H

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
#include "cwsw_lib.h"		/* kErr_Lib_NoError */
#include "cwsw_clock.h"		/* tCwswClockTics */


// ----	Module Headers --------------------------


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

enum eErrorCodes_SwTmr {
	kErr_SwTmr_NoError = kErr_Lib_NoError,
	kErr_SwTmr_NotInitialized,
	kErr_SwTmr_BadParm,			//!< Bad Parameter; e.g., NULL pointer-to-event.
};

/**	Enabled/disabled states for CWSW SW Timers.
 */
enum eSwTimerState {
	kSwTimerDisabled,
	kSwTimerEnabled,
	kSwTimerPaused
};


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

typedef enum eErrorCodes_SwTmr tErrorCodes_SwTmr;

/**	Enabled/disabled states for CWSW SW Timers.
 */
typedef enum eSwTimerState tSwTimerState;

/**	CWSW SW Timer.
 */
typedef struct sSwTimer {
	tCwswClockTics		tm;
	tCwswClockTics		reloadtm;
	int16_t				evid;		// generic container so any event class can be used; 0 for no event
	tSwTimerState		tmrstate;	// allows for a different ev + handler than "normal" event associations
} tCwswSwTimer, *pCwswSwTimer;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

// ---- Discrete Functions -------------------------------------------------- {

extern tErrorCodes_SwTmr Cwsw_SwTmr__Init(pCwswSwTimer pTimer, tCwswClockTics armtm, int16_t ev);
extern void Cwsw_SwTmr__SetState(pCwswSwTimer pTimer, tSwTimerState newstate);
extern void Cwsw_SwTmr__ManageTimer(pCwswSwTimer pTimer, pEvQ_QueueCtrl pEvqCtrl);

// ---- /Discrete Functions ------------------------------------------------- }

// ---- Targets for Get/Set APIs -------------------------------------------- {

/** "Chapter Designator" for Get/Set API.
 *	Intentionally unused symbol, designed to get you to the correct starting
 *	point, when you want to find macros for the Get/Set API; simply highlight
 *	the Module argument in your IDE (e.g, Eclipse, NetBeans, etc.), and select
 *	Go To Definition.
 */
enum { Cwsw_SwTmr = 6 };	/* Component ID for Event Queue */


// ---- /Targets for Get/Set APIs ------------------------------------------- }


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_SWTIMER_H */
