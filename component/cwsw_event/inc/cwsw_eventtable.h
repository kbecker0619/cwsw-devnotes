/** @file
*	@brief	This module defines the table of events that is contained within an Event Queue object.
 *
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 7, 2020
 *	Author: Kevin
 */

#ifndef CWSW_EVENTTABLE_H
#define CWSW_EVENTTABLE_H

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
//#include "projcfg.h"

// ----	Module Headers --------------------------
#include "cwsw_event.h"


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

/** @defgroup	tEvq_EvTable	tEvq_EvTable: Table of events for Event Queue usage
 *	@brief		In order to have a queue, you must have a storage container for those items; this is the storage for the events in the event queue.
 *	@ingroup	tEvQ_QueueCtrl
 */

/**	Table of Events for projects that use the CWSW Event Queue.
 *	By design, the project must allocate the actual table of events; the project may want to locate
 *	the event buffer in a different memory segment than the control struct itself.
 *
 *	@ingroup tEvq_EvTable
 */
typedef struct sEvq_EvTable {
	pEvQ_Event		pEvBuffer;	//!< Pointer to event table
	int32_t			szEvTbl;	//!< Size of embedded table. Signed int to allow for `-1`.
} tEvQ_EvTable;

/** Reference to an Event Table.
 *	@ingroup tEvq_EvTable
 */
typedef tEvQ_EvTable *ptEvQ_EvTable;

/** "Handle" for the position of a specific event in the event-handler table.
 *	Intention is to use value `-1` to indicate invalid reference.
 *	@ingroup tEvq_EvTable
 */
typedef int32_t	tEvQ_EvtHandle;		/* would prefer to use `ssize_t`, but that's a POSIX type, not a C type */


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

// ---- Discrete Functions -------------------------------------------------- {

/** Initialize an instance of an Event. Because this is C and not C++, we cannot use constructors to do this.
 *	@param pEv	[out]	event to be initialized.
 */
#define 				Cwsw_EvT__InitEvent(pEv)	(void)memset(pEv, 0, sizeof(tEvQ_Event))
extern tErrorCodes_EvQ	Cwsw_Evt__InitEventTable(ptEvQ_EvTable pEvQTable, pEvQ_Event pTable, size_t TableSize);		/* initialize a table of events */
extern pEvQ_Event		Cwsw_Evt__GetEventPtr(ptEvQ_EvTable pEvTbl, tEvQ_EvtHandle hnd);
extern tErrorCodes_EvQ	Cwsw_Evt__GetEvent(pEvQ_Event pEv, ptEvQ_EvTable pEvTb, tEvQ_EvtHandle hnd);
extern tErrorCodes_EvQ	Cwsw_Evt__PutEvent(ptEvQ_EvTable pEvTb, tEvQ_EvtHandle hnd, pEvQ_Event pEv);


// ---- /Discrete Functions ------------------------------------------------- }

// ---- Targets for Get/Set APIs -------------------------------------------- {

// ---- /Targets for Get/Set APIs ------------------------------------------- }


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_EVENTTABLE_H */
