/** @file cwsw_eventsim.h
 *	@brief	Stubbed version of "real" header, sufficient to support cwsw_arch development & unit test.
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Oct 17, 2019
 *	Author: KBECKE35
 */

#ifndef BSW_ECU_CWSW_ARCH_TEST_STUBS_CWSW_EVENTSIM_H_
#define BSW_ECU_CWSW_ARCH_TEST_STUBS_CWSW_EVENTSIM_H_

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdint.h>		/* uint16_t and others */
#include <stdbool.h>

// ----	Project Headers -------------------------
#include "projcfg.h"

// ----	Module Headers --------------------------


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================
#define BSW_ECU_CWSW_ARCH_TEST_STUBS_CWSW_EVENTSIM_H__REVSTRING "$Revision: 0123 $"


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

/**	In the absence of a real event system, this is the payload for our simulated
 *	event.
 *	The 1st field, as I envision it, is reserved for the event ID, but the way I've implemented this
 *	pseudo-system, that is redundant, as the name of the event handler itself is unique to the
 *	event; also, it's very difficult to create a field of enumerated constants before that
 *	enumeration has been defined (one way or the other, there needs to be a forward reference).
 *	Therefore, do with the 1st field what you will.
 *
 *	One suggestion: if you want a generic event handler, you can then put a unique identifier
 *	(as in, the event, cause, reason, etc. code) into the evId field.
 */
typedef struct eEventPayload  {
	uint16_t	evId;		// for unit test, i need to know the event id. this is super-simplistic pseudo-eventing system anyway, solely for purpose of illustrating possibilities
	uint16_t	evExtra;	// 2-byte field to suppress warnings about packing / field alignment on some architectures.
	uint32_t	evInt;
} tEventPayload;

/**	In the absence of a real event system, this is the prototype for an event
 *	handler. Normal instantiation would be for an array of handlers, each of
 *	which "subscribes" to said event.
 */
typedef void (*pEventHandler)(tEventPayload EventData);


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

/**	Directly notify interested parties of a significant event.
 * 	This mechanism is intended to provide a very simple mechanism to send a
 * 	message to an independent part of your software.
 *
 * 	This is an undirected, unqueued "event". It calls the specified event
 * 	handler immediately. Because of this, the recommendation is that the handler
 * 	should be very short, perhaps only setting a flag that is processed by the
 * 	receiver of the event.
 *
 * 	These macros are designed to look to the sender like a simple event posting,
 * 	and to the subscriber (receiver), an event handler or callback.
 *
 * 	Unlike some event systems, we don't specify a handler, because we don't care
 * 	who all subscribes to our data. As implemented now, there is one C *symbol*
 * 	that must be defined; however, it could be a function that forwards the event
 * 	to other handlers, or a macro that iterates through an array, or ...
 */
#if (USE_SIMULATED_EVENTS)
#define PostEvent(ev, evpayload)	_Notify(ev, evpayload)
#define _Notify(ev, evpayload)		EventHandler__ ## ev(evpayload)

#else
#define PostEvent(ev, evpayload)	SUPPRESS_CONST_EXPR;do {UNUSED(evpayload);} while(0);RESTORE_WARNING_CONTEXT

#endif


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_EVENTSIM_H_ */
