/** @file cwsw_evqueue_ex.h
 *	@brief	One-sentence short description of file.
 *
 *	Description:
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 15, 2020
 *	Author: kevin
 */

#ifndef CWSW_EVQUEUE_EX_H
#define CWSW_EVQUEUE_EX_H

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------

// ----	Project Headers -------------------------
#include "cwsw_evthndlrassoc.h"		/* this class extends the event handler association component (cannot be built without it) */
#include "cwsw_evqueue.h"			/* this class extends the event queue component (cannot be built without it) */

// ----	Module Headers --------------------------


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

/** @defgroup	tEvQ_QueueCtrlEx	tEvQ_QueueCtrlEx: Extended Event Queue.
 *	@brief		Extends an Event Queue by adding Event Handlers.
 */

/**
 * 	@ingroup tEvQ_QueueCtrlEx
 */
typedef struct sEvQ_QueueCtrlEx {
	tEvQ_QueueCtrl			EvQ_Ctrl;
	ptEvQ_EvHndlrAssocTable	pEvHndlrs;
} tEvQ_QueueCtrlEx;

/**
 * 	@ingroup tEvQ_QueueCtrlEx
 */
typedef tEvQ_QueueCtrlEx *ptEvQ_QueueCtrlEx;


// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

extern tErrorCodes_EvQ		Cwsw_EvQX__InitEvQ(	ptEvQ_QueueCtrlEx 		pEvQX,
												ptEvQ_EvTable			ptblEv,
												ptEvQ_Event				pEvBuff,
												size_t					szEvBuf,
												ptEvQ_EvHndlrAssocTable	ptblEvH,
												ptEvQ_EvHandlerAssoc	pAssocArr,
												size_t					szAssocArr);

extern tErrorCodes_EvQ		Cwsw_EvQX__FlushEvents(ptEvQ_QueueCtrlEx pEvQX);
extern tErrorCodes_EvQ		Cwsw_EvQX__GetEvent(ptEvQ_QueueCtrlEx pEvQX, ptEvQ_Event pEv);
extern tErrorCodes_EvQ		Cwsw_EvQX__PostEvent(ptEvQ_QueueCtrlEx pEvQX, tEvQ_Event ev);
extern tErrorCodes_EvQ		Cwsw_EvQX__SetEvHandler(ptEvQ_QueueCtrlEx pEvQX, tEvQ_EventID evId, pEvQ_EvHandlerFunc pHndlrFunc);
extern pEvQ_EvHandlerFunc	Cwsw_EvQX__GetEvHandler(ptEvQ_QueueCtrlEx pEvQX, tEvQ_EventID evId);
extern tErrorCodes_EvQ		Cwsw_EvQX__HandleNextEvent(ptEvQ_QueueCtrlEx pEvQX, uint32_t ExtraData);


#ifdef	__cplusplus
}
#endif

#endif /* CWSW_EVQUEUE_EX_H */
