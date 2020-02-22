/** @file
 *	@brief	CWSW Clock Module
 *
 *	Description:
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Sep 5, 2016
 *	Author: Kevin L. Becker
 */

#ifndef SMT_CLOCK_H_
#define SMT_CLOCK_H_

#ifdef	__cplusplus
extern "C" {
#endif

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <time.h>
#include <stdint.h>

// ----	Project Headers -------------------------
#include "projcfg.h"
#include "cwsw_evqueue.h"	/* tEvQ_Event, et. al. */

// ----	Module Headers --------------------------


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

enum eErrorCodes_ClkSvc {
	kErr_ClkSvc_NoError = kErr_Lib_NoError,
	kerr_ClkSvc_NotInitialized,
	kerr_ClkSvc_BadParm,
};


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

typedef enum eErrorCodes_ClkSvc tClkSvc_ErrorCode;


/*	building on windows, for windows, we can take advantage of MinGW's
 *	time.h...
 */
typedef clock_t tCwswClockTics, *pCwswClockTics;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

// ---- Discrete Functions -------------------------------------------------- {

extern tCwswClockTics Cwsw_ClockSvc__Task(void);
extern void Cwsw_ClockSvc__Init(pEvQ_QueueCtrl pEvQ, int16_t HeatbeatEvId);

/**	Set the duration of a timer.
 *	@param timer - a reference to the specified timer.
 *	@param duration - the duration of the timer. Negative values are not possible.
 */
extern tClkSvc_ErrorCode Cwsw_ClockSvc__SetTimer(pCwswClockTics pTimer, tCwswClockTics duration);

/**	Return the number of ms between start and stop times.
 * 	@note Assumptions:
 * 	- We are assuming there is 1 clock tic per ms; this is what is true for MinGW and so of course
 * 	  that means the whole world does it the same way.
 * 	- The math only works for 2s-complement encodings; 1s-complement and sign-magnitude will need to
 * 	  find another way.
 */
#define Cwsw_ElapsedTimeMs(start, stop)	(tCwswClockTics)(stop - start)

/**	Get the time left in a specified timer.
 *
 *	@param timer - the timer to be inspected.
 *
 * 	@returns the time left in said timer.
 *	Negative values indicate expiration of timer.
 *
 *	@note In usage, do not compare one time directly to another.
 *	Doing this will not properly handle timer tic rollover.
 *	Instead, subtract one time from another, and compare the result to zero.
 */
#define Cwsw_GetTimeLeft(timer)		Cwsw_ElapsedTimeMs(Cwsw_ClockSvc__Task(), timer)

// ---- /Discrete Functions ------------------------------------------------- }

// ---- Targets for Get/Set APIs -------------------------------------------- {
/** "Chapter Designator" for Get/Set API.
 *	Intentionally unused symbol, designed to get you to the correct starting
 *	point, when you want to find macros for the Get/Set API; simply highlight
 *	the Module argument in your IDE (e.g, Eclipse, NetBeans, etc.), and select
 *	Go To Definition.
 */
enum { Cwsw_Clock = 5 };	/* Component ID for Clock Services */

/**	Target for Set(Cwsw_Clock, timer, duration) API
 */
#define Cwsw_Clock__Set(timer, timeout)		Cwsw_ClockSvc__SetTimer(&timer, timeout)

/** Target for Get(Cwsw_Clock, timer) API
 */
#define Cwsw_Clock__Get(timer)				Cwsw_GetTimeLeft(timer)


/**	Determine if timer "a" has expired (i.e., matured) or not.
 *	@param   a - name of timer
 *	@return  Boolean where TRUE indicates the timer has indeed expired.
 */
//  Expansion of HAS_TIMER_EXPIRED(TIMER_NAME)
//! @{
#define HAS_TIMER_EXPIRED(a)            	_HAS_TIMER_EXPIRED(a)
#define _HAS_TIMER_EXPIRED(a)           	(GET(a) <= 0)
//! @}

/**	Has a timer expired?
 *	This definition provided to accommodate UML notation.
 */
#define TM(tmr)                         	HAS_TIMER_EXPIRED(tmr)

// ---- /Targets for Get/Set APIs ------------------------------------------- }


#ifdef	__cplusplus
}
#endif

#endif /* SMT_CLOCK_H_ */
