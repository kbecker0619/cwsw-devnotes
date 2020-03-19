/** @file
 *	@brief	Event Queue component definitions and methods.
 *
 *	Description:
 *
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 1, 2018
 *	Author: kbecker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdbool.h>
#include <stddef.h>		/* ssize_t */

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------
#include "cwsw_evqueue.h"


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

static bool initialized = false;


// ============================================================================
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/** Initialize the Event Queue component.
 *
 *	This function is intended to be called during the application-initialization
 *	phase, and is only the 1st initialization function that needs to be called.
 *
 *	Because this component is a superclass of an Event Table, we'll ensure that subcomponent is
 *	also initialized.
 *
 *	@returns	Error code, where 0 is no error.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
uint16_t
Cwsw_EvQ__Init(void)
{
	uint16_t ret = kErr_EvQ_NoError;
	if( (XPRJ_Win_MinGW_Debug) || (XPRJ_Debug_Linux_GCC) || (XPRJ_Win_MSVC_Debug) )
	{
		#if defined(__GNUC__)	/* --- GNU Environment ------------------------------ */
		#pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Wpedantic"
		#endif

		dbg_printf(
				"\tModule ID %i\t%s\t\n"
				"\tEntering %s()\n\n",
				Cwsw_EvQ, __FILE__,
				__FUNCTION__);

		#if defined(__GNUC__)	/* --- GNU Environment ------------------------------ */
		#pragma GCC diagnostic pop
		#endif
	}
	else
	{
	}

	if(!Get(Cwsw_EvT, Initialized))
	{
		ret = Init(Cwsw_Evt);
	}

	if(!ret)
	{
		initialized = true;
	}
	return ret;
}


/**	Target for Get(Cwsw_EvQ, Initialized) API.
 *
 *	@returns	true if component is initialized.
 *	@returns	false if the component is not initialized.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
bool
Cwsw_EvQ__Get_Initialized(void)
{
	return initialized;
}


/** Initialize an Event Queue (meaning specifically, the control structure for an event queue).
 *
 *	Each queue in your system needs initialization: The management functions
 *	need to know the size of this event buffer, and where the buffer is located.
 *
 * 	@param[out]	pEvQ	Reference to the Event Queue.
 *	@param[in] pEvTable	Pointer to the event table object.
 *						This is an independent object, not embedded into the EvQ control structure.
 * @return				Error code, where 0 (#kErr_EvQ_NoError) is no error.
 *
 *	It is the responsibility of the caller to ensure the validity of the buffer
 *	and control struct.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
tErrorCodes_EvQ
Cwsw_EvQ__InitEvQ(
		ptEvQ_QueueCtrl	pEvQ,		//!< Event Queue member of the EvQX object.
		ptEvQ_EvTable	pEvTable,	//!< Event Table member of the EvQ object.
		ptEvQ_Event		pEvBuff,	//!< Event Table buffer; actual storage for queued events.
		size_t			szEvBuf		//!< Size of Event Table buffer, in number of elements.
	)
{
	tErrorCodes_EvQ rc = kErr_EvQ_NotInitialized;

	// check preconditions, in order of priority
	if(!initialized)	{ return kErr_EvQ_NotInitialized; }		// has component init happened?
	if(!pEvQ)			{ return kErr_EvQ_BadEvQ; }				// is evq control structure valid?
	if(!pEvTable)		{ return kErr_EvQ_BadTable; }			// is event table valid?
	if(!pEvBuff)		{ return kErr_EvQ_BadEvBuffer; }		// is event buffer valid?
	if(!szEvBuf)		{ return kErr_EvQ_BadEvBuffer; }		// is event buffer valid? (while the event component itself allows zero-size tables, we don't)

	rc = Cwsw_Evt__InitEventTable(pEvTable, pEvBuff, szEvBuf);
	if(!rc)
	{
		pEvQ->pEventTable	= pEvTable;
		pEvQ->Queue_Count	= 0;
		pEvQ->idxRead		= 0;
		pEvQ->idxWrite		= 0;
	}

	return kErr_EvQ_NoError;
}


/**	Clear (empty) the event queue.
 *
 *  While there might be a number of reasons why the developer may want to
 *  empty the current queue of all pending events, one important opportunity is
 *  at module initialization.
 *
 *  @param[in,out]	pEvQ	Pointer to the current event buffer control structure
 *
 *	@returns		Error code, enumeration of type tEvQ_ErrorCode.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
tErrorCodes_EvQ
Cwsw_EvQ__FlushEvents(ptEvQ_QueueCtrl pEvQ)
{
	// check preconditions, in order of priority
	if(!initialized)					{ return kErr_EvQ_NotInitialized; }
	if(!pEvQ) 							{ return kErr_EvQ_BadEvQ; }
	if(!pEvQ->pEventTable)				{ return kErr_EvQ_BadTable; }
	if(!pEvQ->pEventTable->pEvBuffer)	{ return kErr_EvQ_BadEvBuffer; }
	if(!pEvQ->pEventTable->szEvTbl)		{ return kErr_EvQ_BadEvBuffer; }

	pEvQ->idxRead = 0;
	pEvQ->idxWrite = 0;
	pEvQ->Queue_Count = 0;

	return kErr_EvQ_NoError;
}


/**	Posts an event into the queue.
 *
 *	@param[in,out]	pEvQ	Pointer to the current control structure.
 *	@param[in]		ev		Event to add to the queue.
 *
 *	@returns Error code, enumeration of type tEvQ_ErrorCode.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
tErrorCodes_EvQ
Cwsw_EvQ__PostEvent(ptEvQ_QueueCtrl pEvQ, tEvQ_Event ev)
{
	tErrorCodes_EvQ rc = kErr_EvQ_NoError;
	bool isthereroom;

	// check preconditions, in order of priority
	if(!initialized)					{ return kErr_EvQ_NotInitialized; }
	if(!pEvQ)							{ return kErr_EvQ_BadEvQ; }
	if(!pEvQ->pEventTable)				{ return kErr_EvQ_BadTable; }
	if(!pEvQ->pEventTable->pEvBuffer)	{ return kErr_EvQ_BadEvBuffer;}
	if(!pEvQ->pEventTable->szEvTbl)		{ return kErr_EvQ_BadEvBuffer; }
//	if(NULL == pEv)						{ return kErr_EvQ_BadParm; }	<<== reserved for if we convert to pointer-to-event

	isthereroom = (pEvQ->Queue_Count < pEvQ->pEventTable->szEvTbl);
	if(!isthereroom)					{ return kErr_EvQ_QueueFull; }

	if(!ev.evId)						{ return kErr_EvQ_BadEvent; }

	do {
		tEvQ_EvtHandle idx = 0;
		int crit = Cwsw_Critical_Protect(0);

		// get the index of the current event to write, increment to point to the next write
		//	we don't ever expect to have an index > INT_MAX
		idx = pEvQ->idxWrite++;

		// still updating for the next write, correct for buffer wrap-around
		if(pEvQ->idxWrite > pEvQ->pEventTable->szEvTbl)
		{
			pEvQ->idxWrite = 0;
		}

		// add the item to the queue
		rc = Cwsw_Evt__PutEvent(pEvQ->pEventTable, idx, &ev);

		// adjust the count
		++pEvQ->Queue_Count;

		crit = Cwsw_Critical_Release(crit);
	} while(0);

	return rc;
}


/** Get an event from the Event Queue.
 * 	Destructive read from the event buffer.
 *	Always writes to the event parameter, except if queue is presently empty.
 *
 *	@param pEvQ	[in,out]	Event Queue. Control metadata is updated during this method's operation.
 *	@param pEv	[out]		Event retrieved. Cleared if event buffer is empty.
 *
 *	@return	EvQ Error Code, where `0` is no problem observed.
 *
 *	@ingroup tEvQ_QueueCtrl
 */
tErrorCodes_EvQ
Cwsw_EvQ__GetEvent(ptEvQ_QueueCtrl pEvQ, ptEvQ_Event pEv)
{
	tErrorCodes_EvQ rc = kEvQ_Ev_None;
	tEvQ_EvtHandle idx = 0;
	int crit = 0;

	// check preconditions, in order of priority
	if(!initialized)					{ return kErr_EvQ_NotInitialized; }
	if(!pEvQ)							{ return kErr_EvQ_BadEvQ; }
	if(!pEvQ->pEventTable)				{ return kErr_EvQ_BadTable; }
	if(!pEvQ->pEventTable->pEvBuffer)	{ return kErr_EvQ_BadEvBuffer;}
	if(!pEvQ->pEventTable->szEvTbl)		{ return kErr_EvQ_BadEvBuffer; }
	if(!pEv)							{ return kErr_EvQ_BadParm; }
	if(!pEvQ->Queue_Count)				{ return kErr_EvQ_QueueEmpty; }

	Cwsw_EvT__InitEvent(pEv);

	crit = Cwsw_Critical_Protect(0);	// protect the evq control structure.

	// get the index of the current event to read, increment to point to the next read
	//	we don't ever expect to have an index > INT_MAX
	idx = pEvQ->idxRead++;

	// still updating for the next read, correct for buffer wrap-around
	if(pEvQ->idxRead > pEvQ->pEventTable->szEvTbl)
	{
		pEvQ->idxRead = 0;
	}

	// retrieve the event
	rc = Cwsw_Evt__GetEvent(pEv, pEvQ->pEventTable, idx);

	// decrement the count
	--pEvQ->Queue_Count;
	crit = Cwsw_Critical_Release(crit);

	// return the event
	return rc;
}

