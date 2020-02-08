/** @file
 *	@brief	One-sentence short description of file.
 *
 *	Description:
 *
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
#include "evq_events.h"		/* project must supply this header */


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
 * 	This is the stupidest brute-force search possible; it does a linear search until it finds a
 * 	match to the specified event. This algorithm works best if the lower-priority events are placed
 * 	at the beginning of the table.
 *
 * 	Note this could be radically optimized, if you assume that the given event is the index into the
 * 	event-dispatcher table.
 *
 * @param pEvHndlr		Pointer to the event-handler table (presumed to be index 0, or at least as much room left in the table as specified size).
 * @param evtblsz		Size of event-handler table.
 * @param ev			Event to search for.
 * @return				Index in the table where event was found, or -1 if not found
 */
static tEvH_EvtHandle
get_ev_handle(tEvH_EvHandler *pEvHndlr, size_t evtblsz, tEvQ_Event ev)
{
	ssize_t handle = 0;
	if(!pEvHndlr)					return -1;
	if(evtblsz == 0)				return -1;
	if(ev < 1)						return -1;
	if(ev >= kNumProjectEvqEvents)	return -1;

	// for this edition, we're using the event as an index into our table, rather than any sort of
	//	more sophisticated means.
	handle = (ssize_t)ev;
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
 * 	@param pEvHndlr	Pointer to the event-handler table.
 * 	@param evtlbsz	Size of event-handler table, in number of elements.
 *	@param ev		Event to associate. Note that the container type is defined by the project, and
 * 					might not be of the same signedness as the list of events (e.g., if the list of
 * 					events is implemented as an enumeration type, the signedness may be unsigned or
 * 					signed; the container type for `tEvQ_Event` may be either signed or unsigned.
 * 					It is a project responsibility to match the compatibility types between the list
 * 					of events and the container in which they're held, if that is important (such as
 * 					for MISRA analysis).
 *	@param pf	Address of the function to be associated with the event. A "disassociation" can be
 * 				accomplished by passing NULL.
 *	@return		#kEvQ_Err_BadParm if any problem is noticed, #kEvQ_Err_NoError on success.
 *
 *	@note 	To accommodate compile-time configuration, it is not required to use this handler
 *			registration at run time; you can set up a table of type tEvH_EvHandler[] and pre-fill
 *			it out.
 */
tEvQ_ErrorCode
Cwsw_EvQ__RegisterHandler(tEvH_EvHandler *pEvHndlr, size_t evtblsz, tEvQ_Event ev, pEvH_EvHandlerFunc pf)
{
	tEvH_EvtHandle idx;

	if(!pEvHndlr) 					return kEvQ_Err_BadParm;
	if(!evtblsz)	  				return kEvQ_Err_BadParm;

	// in our system, event value `0` is a special event, and so we don't want to allow for it to
	//	be associated with a handler.
	// also, since the container type for enums can be signed int on some systems, make sure the
	//	minimum value is 0 or higher.
	if(ev < 1)		  				return kEvQ_Err_BadParm;
	if(ev >= kNumProjectEvqEvents)	return kEvQ_Err_BadParm;

	idx = get_ev_handle(pEvHndlr, evtblsz, ev);
	if(idx < 1)						return kEvQ_Err_BadEvent;

//	pEvHndlr += idx * sizeof(tEvH_EvHandler);

	pEvHndlr[idx].ev = ev;
	pEvHndlr[idx].pEvHandler = pf;
	return kEvQ_Err_NoError;
}


/**	Register a bunch of event handlers.
 *	Given a list of events, and a corresponding list of handlers, associate the handlers with their
 *	events.
 *
 *	We attempt to iterate through the complete list of events or handlers (whichever list is
 *	shorter); if any of them fail, we remember that at least one failed and return #kEvQ_Err_BadParm
 *
 	@param [out]	pEvHndlr		Pointer to the event-handler table.
 *	@param [in]		evhndlrtblsz	Size of event-handler table, in number of elements.
 *	@param [in]		pev				Pointer to a list of events, one per element.
 *	@param [in]		evtblsz			Size of event table, in number of entries.
 *	@param [in]		pf				Pointer to a list of event handlers, one per element.
 *	@param [in]		hndlrtblsz	Size of event-handler table, in number of entries.
 *	@return	#kEvQ_Err_BadParm if any problem is noticed, #kEvQ_Err_NoError on success.
 *
 *	@note	While it may seem odd to provide a matched and paired set of events and their handlers,
 *			in order to update another list of events paired with their handlers, but there may be
 *			situations where independent lists derived from different sources may need to be merged
 *			into a handler table within this application.
 */
tEvQ_ErrorCode
Cwsw_EvQ_ResgisterHandlers(tEvH_EvHandler *pEvHndlr, size_t evhndlrtblsz,
						   tEvQ_Event *pev, size_t evtblsz,
						   pEvH_EvHandlerFunc *pf, size_t hndlrtblsz)
{
	tEvQ_ErrorCode allerrs, thiserr;
	UNUSED(allerrs);
	UNUSED(thiserr);
	if( !pEvHndlr		||	/* check input addesses */
		!pev			||
		!pf				||	/* end of input addresses checked and found valid (enough) */
		!evhndlrtblsz	||
		!evtblsz		||
		!hndlrtblsz)
	{
		tEvH_EvtHandle idx;
		size_t loopsize = MIN(evhndlrtblsz, MIN(evtblsz, hndlrtblsz));
		int volatile loopidx = loopsize;
		while(loopidx--)
		{
			// get the handle of our event
			idx = get_ev_handle(pEvHndlr, evtblsz, pev[loopidx]);
			UNUSED(idx);
		}

	}
//	if(idx < 1)  				return kEvQ_Err_BadParm;
//
//	pEvHndlr += idx * sizeof(tEvH_EvHandler);

	return 0;
}


pEvH_EvHandlerFunc
Cwsw_EvQ__GetHandler(tEvH_EvHandler *pEvHndlr, size_t evtblsz, tEvQ_Event ev)
{
	ssize_t idx = 0;

	if(!pEvHndlr)					return NULL;
	if(!evtblsz)					return NULL;
	if(ev < 1)						return NULL;
	if(ev >= kNumProjectEvqEvents)	return NULL;

	idx = get_ev_handle(pEvHndlr, evtblsz, ev);
	if(idx < 1)						return NULL;

	return pEvHndlr[idx].pEvHandler;
}


