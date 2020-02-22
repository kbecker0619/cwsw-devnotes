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
#include "cwsw_lib.h"		/* kCwsw_Lib_NoError */
#include "cwsw_clock.h"		/* tCwswClockTics */


// ----	Module Headers --------------------------


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

enum eClkSvc_ErrorCodes {
	kSwTmr_Err_NoError = kCwsw_Lib_NoError,
	kSwTmr_Err_NotInitialized,
	kSwTmr_Err_BadParm,			//!< Bad Parameter; e.g., NULL pointer-to-event.

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

typedef enum eClkSvc_ErrorCodes tClkSvc_ErrorCodes;

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

extern tClkSvc_ErrorCodes Cwsw_SwTmr__Init(pCwswSwTimer pTimer, tCwswClockTics armtm, int16_t ev);
extern void Cwsw_SwTmr__SetState(pCwswSwTimer pTimer, tSwTimerState newstate);



#ifdef	__cplusplus
}
#endif

#endif /* CWSW_SWTIMER_H */
