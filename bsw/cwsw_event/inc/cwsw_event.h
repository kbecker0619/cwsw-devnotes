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

#ifndef BSW_EVQ_INC_CWSW_EVENT_H_
#define BSW_EVQ_INC_CWSW_EVENT_H_

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stddef.h>				/* size_t */

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
enum { kEvQ_Ev_None };

/** Error codes returned by Event Queue API.
 *	@ingroup sEvq_EvTable
 */
enum eErrorCodes_EvQ {
	kErr_EvQ_NoError = kErr_Lib_NoError,
	kErr_EvQ_NotInitialized,	//!< Event Queue component not initialized.
	kErr_EvQ_BadParm,			//!< Bad Parameter; e.g., NULL pointer-to-event.
	kErr_EvQ_BadCtrl,			//!< Bad or invalid control struct.
	kErr_EvQ_BadQueue,			//!< Bad or invalid event queue.
	kErr_EvQ_BadEvent,			//!< Bad or invalid event.
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
	pEvQ_Event		pEvTable;	//!< Pointer to event table
	size_t			EvTblSize;	//!< Size of embedded table
} tEvQ_EvTable, *pEvQ_EvTable;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

extern uint16_t			Cwsw_Evt__Init(void);		/* initialize event _component_ */
extern tErrorCodes_EvQ	Cwsw_Evt__InitEventTable(pEvQ_EvTable pEvQTable, pEvQ_Event pTable, size_t TableSize);		/* initialize a table of events */
extern int32_t			Cwsw_Evt__FindEvent(pEvQ_EvTable pEvQTable, tEvQ_EventID evId);

#ifdef	__cplusplus
}
#endif

#endif /* BSW_EVQ_INC_CWSW_EVENT_H_ */
