/** @file
 *	@brief	Methods for the Event Queue Extended component.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Feb 8, 2020
 *	Author: KBECKE35
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------
#include "cwsw_evhandler.h"
#include "cwsw_event_proj.h"		/* project must supply this header */


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

// ============================================================================
// ----	Private Functions -----------------------------------------------------
// ============================================================================

/** Find the "handle" (index, in this implementation) of an event in an event table.
 * 	~This is the stupidest brute-force search possible; it does a linear search until it finds a
 * 	match to the specified event. This algorithm works best if the lower-priority events are placed
 * 	at the beginning of the table.~
 * 	This implementation uses the Event ID as an index into the handler table; we're trading ease-of-
 * 	implementation + fast lookup speed, for sparse tables.
 *
 * @param pEvHndlrTbl	Pointer to the event-handler table (presumed to be index 0, or at least as much room left in the table as specified size).
 * @param evtblsz		Size of event-handler table.
 * @param evId			Event to search for.
 * @return				Index in the table where event was found, or -1 if not found
 */
static tEvQ_EvtHandle
get_ev_handle(ptEvQ_EvHandlerAssoc pEvHndlrTbl, size_t evtblsz, tEvQ_EventID evId)
{
	tEvQ_EvtHandle		handle = 0;
	if(!pEvHndlrTbl)	return -1;	// no table specified
	if(evtblsz <= 0)	return -1;	// table has invalid size
	if(evId < 1)			return -1;	// invalid event
	if(evId >= evtblsz)	return -1;	// invalid event

	// for this edition, we're using the event as an index into our table, rather than any sort of
	//	more sophisticated means. Due to this, we're ignoring the event-handler table args.
	UNUSED(pEvHndlrTbl);
	handle = (tEvQ_EvtHandle)evId;
	return handle;
}


// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/** Register an event handler.
 * 	Because we intend for this to be a library, we will not provide our own look up table; this
 * 	must be passed as a parameter, with the full understanding that we will be using index notation
 * 	(rather than pointer notation) to index into it.
 *
 * 	@param pEvHndlrTbl	[out]	Pointer to the event-handler table.
 * 	@param evtblsz		[in]	Size of event-handler table, in number of elements.
 *	@param evId			[in]	Event to associate. Note that the container type is defined by the project, and
 * 						might not be of the same signedness as the list of events (e.g., if the list of
 * 						events is implemented as an enumeration type, the signedness may be unsigned or
 * 						signed; the container type for `tEvQ_Event` may be either signed or unsigned.
 * 						It is a project responsibility to match the compatibility types between the list
 * 						of event IDs and the container in which they're held, if that is important (such
 * 						as it might be for MISRA analysis).
 *	@param pf			Address of the function to be associated with the event. A "disassociation" can be
 * 						accomplished by passing NULL.
 *
 *	@return		#kErr_EvQ_BadParm if any problem is noticed, #kErr_EvQ_NoError on success.
 *
 *	@note 	To accommodate compile-time configuration, it is not required to use this handler
 *			registration at run time; you can set up a table of type tEvQ_EvHandlerAssoc[] and pre-fill
 *			it out to create compile-time registrations.
 */
tErrorCodes_EvQ
Cwsw_EvQ__RegisterHandler(
	ptEvQ_EvHandlerAssoc pEvHndlrTbl,
	size_t evtblsz,
	tEvQ_EventID evId,
	pEvQ_EvHandlerFunc pf)
{
	tEvQ_EvtHandle idx;

	if(!pEvHndlrTbl) 		return kErr_EvQ_BadParm;
	if(!evtblsz)	  		return kErr_EvQ_BadParm;

	// since the container type for enums can be signed int on some systems, make sure the
	//	minimum value is 0 or higher.
	// in our system, event value `0` is a special event, and so we don't want to allow for it to
	//	be associated with a handler.
	if(evId < 1)		  	return kErr_EvQ_BadParm;
	if(evId >= evtblsz)		return kErr_EvQ_BadParm;

	idx = get_ev_handle(pEvHndlrTbl, evtblsz, evId);
	if(idx < 1)				return kErr_EvQ_BadEvent;

//	pEvHndlr += idx * sizeof(tEvH_EvHandler);

	pEvHndlrTbl[idx].evId = evId;
	pEvHndlrTbl[idx].pEvHandler = pf;
	return kErr_EvQ_NoError;
}


/**	Get the current event handler.
 *
 *	@param pEvHndlr	[in]
 *	@param evtblsz	[in]
 *	@param evId		[in]
 * @return	address of handler; NULL if non or disabled.
 *
 * @todo: implement "enabled/disabled" status.
 */
pEvQ_EvHandlerFunc
Cwsw_EvQ__GetHandler(ptEvQ_EvHandlerAssoc pEvHndlr, size_t evtblsz, tEvQ_EventID evId)
{
	tEvQ_EvtHandle idx = 0;

	if(!pEvHndlr)		return NULL;
	if(!evtblsz)		return NULL;
	if(evId < 1)		return NULL;
	if(evId >= evtblsz)	return NULL;

	// todo: get enabled/disabled status; if disabled, return NULL
	idx = get_ev_handle(pEvHndlr, evtblsz, evId);
	if(idx < 1)			return NULL;

	return pEvHndlr[idx].pEvHandler;
}
