/** @file
 *
 *	@brief	Definition of the Event object.
 *	The Event object is the base type upon which the Event Queue and its extended forms is built.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Feb 24, 2020
 *	@author: kbecker
 */

#ifndef CWSW_EVENT_H
#define CWSW_EVENT_H

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stddef.h>				/* size_t */
#include <string.h>				/* memset */

// ----	Project Headers -------------------------
#include "projcfg.h"
#include "cwsw_lib.h"			/* kErr_Lib_NoError */

// ----	Module Headers --------------------------
#include "cwsw_event_proj.h"	/* project-specific compile-time configuration */


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

/** Reserved event value. In the CWSW Event Queue system, this indicates "no event." */
enum { kEvQ_Ev_None = 0 };

/** Error codes returned by Event Queue API.
 *	@ingroup sEvq_EvTable
 */
enum eErrorCodes_EvQ {
	kErr_EvQ_NoError = kErr_Lib_NoError,
	kErr_EvQ_NotInitialized,	//!< Event Queue component not initialized.
	kErr_EvQ_BadParm,			//!< Bad Parameter; e.g., NULL pointer-to-event.
	kErr_EvQ_BadEvQ,			//!< Bad or invalid EvQ control struct (tEvQ_QueueCtrl).
	kErr_EvQ_BadEvTable,		//!< Bad or invalid event table (tEvQ_EvTable).
	kErr_EvQ_BadEvBuffer,		//!< Bad or invalid buffer for events (tEvQ_Event[]).
	kErr_EvQ_BadEvent,			//!< Bad or invalid event.
	kErr_EvQ_QueueEmpty,		//!< Queue empty, cannot get event from queue.
	kErr_EvQ_QueueFull,			//!< Queue full, cannot add new event to queue.
};


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

/** @defgroup tEvQ_Event	Event data type for Event Queue usage.
 *	@brief	Base class for Event Queue component.
 */

typedef enum eErrorCodes_EvQ tErrorCodes_EvQ;

/** Event object.
 *	Relies on the project-specific definition of a Event ID container type.
 *
 *	@ingroup tEvQ_Event
 */
typedef struct sEvQ_Event {
	tEvQ_EventID	evId;		//!< Scalar number, unambiguous identifier for "this" event.
	uint32_t		evData;		//!< Supplemental data to augment the context of the event.
} tEvQ_Event;

/** Reference to one row in a buffer of events.
 *	Also used to point at the base of an event buffer.
 *
 *	@ingroup tEvQ_Event
 */
typedef tEvQ_Event *pEvQ_Event;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

// ---- Discrete Functions -------------------------------------------------- {

// ---- /Discrete Functions ------------------------------------------------- }

// ---- Targets for Get/Set APIs -------------------------------------------- {

/** "Chapter Designator" for Get/Set API.
 *	Intentionally unused symbol, designed to get you to the correct starting
 *	point, when you want to find macros for the Get/Set API; simply highlight
 *	the Module argument in your IDE (e.g, Eclipse, NetBeans, etc.), and select
 *	Go To Definition.
 */
enum { Cwsw_EvT };		/* Component ID for Event Table */

/** Target symbol for Get(Cwsw_EvT, xxx) interface.
 *	@ingroup tEvQ_Event
 */
#define Cwsw_EvT__Get(resource)		Cwsw_EvT__Get_ ## resource()

/** Target for Get(Cwsw_EvT, Initialized) interface.
 *	@ingroup tEvQ_Event
 */
extern bool Cwsw_EvT__Get_Initialized(void);

/** target for Init(Cwsw_EvT) API.
 *	@ingroup tEvQ_Event
 */
extern uint16_t			Cwsw_Evt__Init(void);		/* initialize event _component_ */

extern void				Cwsw_EvT__Deinit(void);

// ---- /Targets for Get/Set APIs ------------------------------------------- }


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_EVENT_H */
