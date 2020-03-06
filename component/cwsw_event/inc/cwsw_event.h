/** @file
 *
 *	Description:
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 24, 2020
 *	Author: KBECKE35
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
#include "cwsw_lib.h"

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

typedef enum eErrorCodes_EvQ tErrorCodes_EvQ;

/** @defgroup tEvQ_Event	Event for Event Queue usage.
 *	@brief	Base class for Event Queue component.
 */

/** Event object.
 *	Relies on the project-specific definition of a Event ID container type.
 *
 *	@ingroup tEvQ_Event
 */
typedef struct sEvQ_Event {
	tEvQ_EventID	evId;		//!< Scalar number, unambiguous identifier for "this" event.
	uint32_t		evData;		//!< Supplemental data to augment the context of the event.
} tEvQ_Event, *pEvQ_Event;


/** @defgroup sEvq_EvTable	Table of events for Event Queue usage.
 *	@brief In order to have a queue, you must have a storage container for those items; this is the storage for the events in the event queue.
 */

/**	Table of Events for projects that use the CWSW Event Queue.
 *	By design, the project must allocate the actual table of events; the project may want to locate
 *	the event buffer in a different memory segment than the control struct itself.
 *
 *	@ingroup sEvq_EvTable
 */
typedef struct sEvq_EvTable {
	pEvQ_Event		pEvBuffer;	//!< Pointer to event table
	int32_t			szEvTbl;	//!< Size of embedded table. Signed int to allow for `-1`.
} tEvQ_EvTable, *pEvQ_EvTable;

/** "Handle" for the position of a specific event in the event-handler table.
 *	Intention is to use value `-1` to indicate invalid reference.
 */
typedef int32_t	tEvQ_EvtHandle;		/* would prefer to use `ssize_t`, but that's a POSIX type, not a C type */


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

// ---- Discrete Functions -------------------------------------------------- {

extern tErrorCodes_EvQ	Cwsw_Evt__InitEventTable(pEvQ_EvTable pEvQTable, pEvQ_Event pTable, size_t TableSize);		/* initialize a table of events */
extern pEvQ_Event		Cwsw_Evt__GetEventPtr(pEvQ_EvTable pEvTbl, tEvQ_EvtHandle hnd);
extern tErrorCodes_EvQ	Cwsw_Evt__GetEvent(pEvQ_Event pEv, pEvQ_EvTable pEvTb, tEvQ_EvtHandle hnd);
extern tErrorCodes_EvQ	Cwsw_Evt__PutEvent(pEvQ_EvTable pEvTb, tEvQ_EvtHandle hnd, pEvQ_Event pEv);

#define Cwsw_EvT__InitEvent(pEv)	memset(pEv, 0, sizeof(tEvQ_Event))

// ---- /Discrete Functions ------------------------------------------------- }

// ---- Targets for Get/Set APIs -------------------------------------------- {

/** "Chapter Designator" for Get/Set API.
 *	Intentionally unused symbol, designed to get you to the correct starting
 *	point, when you want to find macros for the Get/Set API; simply highlight
 *	the Module argument in your IDE (e.g, Eclipse, NetBeans, etc.), and select
 *	Go To Definition.
 */
enum { Cwsw_EvT = 0 };	/* Component ID for Event Table */

/** Target symbol for Get(Cwsw_EvT, xxx) interface */
#define Cwsw_EvT__Get(resource)		Cwsw_EvT__Get_ ## resource()

/** Target for Get(Cwsw_EvT, Initialized) interface. */
extern bool Cwsw_EvT__Get_Initialized(void);

/** target for Init(Cwsw_EvT) API */
extern uint16_t			Cwsw_Evt__Init(void);		/* initialize event _component_ */

extern void				Cwsw_EvT__Deinit(void);

// ---- /Targets for Get/Set APIs ------------------------------------------- }


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_EVENT_H */
