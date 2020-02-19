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

// ----	Project Headers -------------------------
#include "projcfg.h"

// ----	Module Headers --------------------------


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

#if (BUILD_FOR_UNIT_TEST)
#define CWSW_CLOCK_H__REVSTRING "$Revision: 09052016 $"
#endif


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

/*	building on windows, for windows, we can take advantage of MinGW's
 *	time.h...
 */
typedef clock_t tCwswClockTics;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

#if (XPRJ_Debug)
#define Cwsw_Clock()	(tCwswClockTics)(clock())

#else
extern tCwswClockTics Cwsw_Clock(void);

#endif

/**	Return the number of ms between start and stop times.
 * 	@note We are assuming here that there is 1 clock tic per ms; this is what is
 * 	true for MinGW and so of course that means the whole world does it the same
 * 	way.
 */
#define Cwsw_ElapsedTimeMs(start, stop)	(tCwswClockTics)(stop - start)

/**	@returns the time left in said timer.
 *	Negative values indicate expiration of timer.
 *	@param timer - the timer to be looked at.
 *	@note In usage, do not compare one time directly to another.
 *	Doing this will not properly handle timer tic rollover.
 *	Instead, subtract one time from another, and compare the result to zero.
 */
#define Cwsw_GetTimeLeft(timer)		Cwsw_ElapsedTimeMs(Cwsw_Clock(), timer)


/**	Set the duration of a timer.
 *	@param timer - a reference to the specified timer.
 *	@param duration - the duration of the timer. Negative values are not possible.
 */
#define Cwsw_SetTimerVal(ptimer, duration)		do { *ptimer = Cwsw_Clock() + (duration); } while(0)


/**	Determine if timer "a" has expired (i.e., matured) or not.
 *	@param   a - name of timer
 *	@return  Boolean where TRUE indicates the timer has indeed expired.
 */
//  Expansion of HAS_TIMER_EXPIRED(TIMER_NAME)
//! @{
#define HAS_TIMER_EXPIRED(a)            _HAS_TIMER_EXPIRED(a)
#define _HAS_TIMER_EXPIRED(a)           (GET(a) <= 0)
//! @}

/**
 * Has a timer expired?
 * This definition provided to accommodate UML notation.
 */
#define TM(tmr)                         HAS_TIMER_EXPIRED(tmr)


#ifdef	__cplusplus
}
#endif

#endif /* SMT_CLOCK_H_ */
