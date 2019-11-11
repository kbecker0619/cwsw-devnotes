/** @file cwsw_evqueue.c
 *	@brief	One-sentence short description of file.
 *
 *	Description:
 *
 *	Copyright (c) 2018 Kevin L. Becker. All rights reserved.
 *
 *	Original:
 *	Created on: Mar 1, 2018
 *	Author: kbecker
 *
 *	Current:
 *	$Revision: $
 *	$Date: $
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdbool.h>
#include <stddef.h>		/* ssize_t */
#if defined(_CVI_)
typedef signed int ssize_t;
#endif

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
static char const * const cwsw_evqueue_RevString = "$Revision: 0123 $";

static bool initialized = false;


// ============================================================================
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

uint16_t
Cwsw_EvQ__Init(void)
{
	if( (XPRJ_Win_MinGW_Debug) || (XPRJ_Debug_Linux_GCC) || (XPRJ_Win_MSVC_Debug) )
	{
		#if defined(__GNUC__)	/* --- GNU Environment ------------------------------ */
		#pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Wpedantic"
		#endif

		dbg_printf(
				"\tModule ID %i\t%s\t%s\n"
				"\tEntering %s()\n\n",
				Cwsw_EvQ, __FILE__, cwsw_evqueue_RevString,
				__FUNCTION__);

		#if defined(__GNUC__)	/* --- GNU Environment ------------------------------ */
		#pragma GCC diagnostic pop
		#endif
	}
	else
	{
		UNUSED(cwsw_evqueue_RevString);
	}

	initialized = true;
	return kEvQ_Err_NoError;
}

bool
Cwsw_EvQ__Get_Initialized(void)
{
	return initialized;
}


tEvQ_ErrorCodes
Cwsw_EvQ__InitEvQ(
	tEvQueueCtrl *pEvQueueCtrl,
	tEvQ_EvQueue const pEvQueue,
	uint8_t const EvQueueSz)
{
	// check preconditions, in order of priority
	if(!initialized)				{ return kEvQ_Err_NotInitialized; }		// has component init happened?
	if(!pEvQueueCtrl)				{ return kEvQ_Err_BadCtrl; }			// is control structure valid?
	if(!pEvQueue)					{ return kEvQ_Err_BadQueue; }			// is event buffer valid?
	if(!EvQueueSz)					{ return kEvQ_Err_BadQueue; }			// is event buffer valid?

	pEvQueueCtrl->Queue_Size		= EvQueueSz;
	pEvQueueCtrl->Event_Queue_Ptr	= pEvQueue;
	pEvQueueCtrl->Queue_Count		= 0;
	pEvQueueCtrl->Read_Ptr			= pEvQueue;
	pEvQueueCtrl->Write_Ptr			= pEvQueue;

	return kEvQ_Err_NoError;
}


tEvQ_ErrorCodes
Cwsw_EvQ__FlushEvents(tEvQueueCtrl * const pEvQueueCtrl)
{
	// check preconditions, in order of priority
	if(!initialized)					{ return kEvQ_Err_NotInitialized; }
	if(!pEvQueueCtrl) 					{ return kEvQ_Err_BadCtrl; }
	if(!pEvQueueCtrl->Event_Queue_Ptr)	{ return kEvQ_Err_BadQueue; }
	if(!pEvQueueCtrl->Queue_Size)		{ return kEvQ_Err_BadQueue; }

	pEvQueueCtrl->Read_Ptr = pEvQueueCtrl->Event_Queue_Ptr;
	pEvQueueCtrl->Write_Ptr = pEvQueueCtrl->Event_Queue_Ptr;
	pEvQueueCtrl->Queue_Count = 0;

	return kEvQ_Err_NoError;
}


tEvQ_ErrorCodes
Cwsw_EvQ__PostEvent(tEvQueueCtrl *pEvQueueCtrl, tEvQ_Event ev)
{
	bool isthereroom;
	int64_t writerange;

	// check preconditions, in order of priority
	if(!initialized)							{ return kEvQ_Err_NotInitialized; }
	if(!pEvQueueCtrl)							{ return kEvQ_Err_BadCtrl; }
	if(!pEvQueueCtrl->Event_Queue_Ptr)			{ return kEvQ_Err_BadQueue; }
	if(!pEvQueueCtrl->Queue_Size)				{ return kEvQ_Err_BadQueue; }
	if(!pEvQueueCtrl->Write_Ptr)				{ return kEvQ_Err_BadCtrl; }

	writerange = pEvQueueCtrl->Write_Ptr - pEvQueueCtrl->Event_Queue_Ptr;
	if(writerange < 0)							{ return kEvQ_Err_BadCtrl; }
	if(writerange >= pEvQueueCtrl->Queue_Size)	{ return kEvQ_Err_QueueFull; }

	isthereroom = (pEvQueueCtrl->Queue_Count < pEvQueueCtrl->Queue_Size);
	if(!isthereroom)							{ return kEvQ_Err_QueueFull; }

	if(!ev)										{ return kEvQ_Err_BadEvent; }

	do {
		int crit = Cwsw_Critical_Protect(0);
		// add the item to the queue
		*( pEvQueueCtrl->Write_Ptr++ ) = ev;

		// adjust the count
		pEvQueueCtrl->Queue_Count++;

		// check for overflow
		if ( pEvQueueCtrl->Write_Ptr > ( pEvQueueCtrl->Event_Queue_Ptr + pEvQueueCtrl->Queue_Size ))
		{
			// reset it to beginning
			pEvQueueCtrl->Write_Ptr = pEvQueueCtrl->Event_Queue_Ptr;
		}
		crit = Cwsw_Critical_Release(crit);
	} while(0);

	return kEvQ_Err_NoError;
}


tEvQ_ErrorCodes
Cwsw_EvQ__GetEvent(tEvQueueCtrl *pEvQueueCtrl, tEvQ_Event *pEv)
{
	tEvQ_ErrorCodes rc = kEvQ_Ev_None;

	// check preconditions, in order of priority
	if(!initialized)							{ return kEvQ_Err_NotInitialized; }
	if(NULL == pEvQueueCtrl)					{ return kEvQ_Err_BadCtrl; }
	if(NULL == pEvQueueCtrl->Event_Queue_Ptr)	{ return kEvQ_Err_BadQueue; }
	if(0 == pEvQueueCtrl->Queue_Size)			{ return kEvQ_Err_BadQueue; }
	if(NULL == pEvQueueCtrl->Read_Ptr)			{ return kEvQ_Err_BadCtrl; }
	if(NULL == pEv)								{ return kEvQ_Err_BadParm; }

	// are there any entries
	if(pEvQueueCtrl->Queue_Count != 0)
	{
		int crit = Cwsw_Critical_Protect(0);

		// decrement the count
		pEvQueueCtrl->Queue_Count--;

		// get the event/increment the pointer
		*pEv = *(pEvQueueCtrl->Read_Ptr++);

		// check for buffer wraparound
		if(pEvQueueCtrl->Read_Ptr > (pEvQueueCtrl->Event_Queue_Ptr + pEvQueueCtrl->Queue_Size))
		{
			// reset it to beginning
			pEvQueueCtrl->Read_Ptr = pEvQueueCtrl->Event_Queue_Ptr;
		}
		crit = Cwsw_Critical_Release(crit);
	}

	// return the event
	return rc;
}


// ====	COMPONENT DOCUMENTATION ============================================== {
#if defined(IN_DOXY)													/* { */
/**	\page EvQueue_Head Reusable Component : Event Queue
 * 		@subpage Evq_Introduction \n
 * 		@subpage Evq_Design \n
 * 		@subpage Evq_Integration
 */

/*{*//**	@page Evq_Introduction						Introduction to the Event Queue component
 *	@tableofcontents
 *	The Event Queue implements a straight-up FIFO queue.
 *	-	There is no prioritization of events.
 *	-	There is no restriction on the number of distinct queues, since the
 *		Event Queue engine acts on caller-owned pointers to the queue to be
 *		operated on.
 *	-	Each queue structure needs to be initialized independently; this can
 *		either be done before the scheduler is started, or it can be done
 *		during an initialization state after the scheduler is started.
 *	-	Each queue structure is associated with one and only one queue buffer;
 *		these are created independently of each other, and are linked during
 *		initialization. The flexibility that this brings, is at the cost of a
 *		reduced amount of error checking that can be done inside the engine
 *		itself (for example, we cannot confirm that a queue buffer is not
 *		already associated with a different queue structure, and we have a
 *		reduced ability to confirm the correctness of the buffer's size and/or
 *		location). One unique usage would be to have a read-only event queue
 *		placed in read-only memory.
 *	-	Each queue can act on events unique to and tightly associated with that
 *		queue, or on a list of global events, or a mixture of the two.
 *	-	The caller can retrieve and dispatch one event per task iteration; or it
 *		can dispatch events until the queue is depleted; or it can limit by time
 *		or number of events dispatched.
 *	-	The default implementation uses an unsigned byte as the container for
 *		events, in order to conserve data space; however, if a larger number
 *		of event definitions is desired, or for other reasons, the project can
 *		customize the root data type.
 *
 *	@section Evq_related_docs					Applicable Documents
 *	TBD
 *
 *	@section Evq_terms							Terms, Acronyms, Abbreviations
 *//*}*/

/** @page Evq_Design							Event Queue Design
 *	@tableofcontents
 *		@subpage Evq_Responsibilities \n
 *		@subpage Evq_Constraints \n
 *		@subpage Evq_Interactions \n
 *		@subpage Evq_Composition \n
 *		@subpage Evq_Resources \n
 *		@subpage Evq_Interfaces \n
 *		@subpage Evq_Main_Obj_Diag \n
 *		@subpage Evq_Seq_Diag_Fail \n
 *		@subpage Evq_Dsm \n
 */

/*{*//**	@page Evq_Integration				Integrating the Reusable Component
 *	@tableofcontents
 *	To add the facilities of the CWSW Event Queue to your project, follow these steps.
 *
 *	@note Author's note: These steps are generic for all IDEs; however, the specific details
 *	(e.g., screen shots) are oriented toward IDEs based on Eclipse, such as NXP S32DS; ARM DS-5; or
 *	TI's Code Composer.
 *	While I have implemented these steps in Microchip's MPLAB v4.x, the steps are so close that I
 *	didn't feel IDE-specific instructions were required.
 *
 *	Integration Steps:
 *	-# [Share the Source](#Evq_source_share)
 *	-# [Update Includes paths](#Evq_update_includes)
 *	-# [Configuration](#Evq_configuration)
 *	-# [Update Initialization Code](#Evq_init_code)
 *	-# Optional APIs.
 *//*}*/

	/*{*//**	@page Evq_Integration
	 *	@section Evq_source_share				Share the Source
	 *	Designed to be a reusable component, the Event Queue is organized into a reusable section,
	 *	and requires additional project-specific configuration items in the project.
	 *
	 *	@subsection evq_source_share_common		Reusable Portion
	 *	The component layout in your workspace looks like this:
	 *	@code{.sh}

		cwsw_evqueue_prj
		├── cfg
		├── cwsw_evqueue
		│   └── src
		├── doc
		└── ut

	 *	@endcode
	 *
	 *	The <code>cwsw_evqueue_prj</code> directory is the home to the various project-management
	 *	files (such as the Doxygen configuration, the Eclipse project files, etc.), and is the
	 *	parent for the component.
	 *
	 *	The <code>cfg></code> directory contains project-specific configuration files. The templates
	 *	within should be copied to your project and configured for your specific requirements.
	 *
	 *	The <code>ut</code> directory is the source for the developer workspace for this reusable
	 *	component, and illustrates how to configure the component is client projects.
	 *
	 *	The <code>doc</code> directory holds relevant design information not included in this
	 *	Doxygen format. @note This component's <code>doc</code> directory assumes that
	 *	<code>cwsw_lib_prj</code> and <code>cwsw_arch_prj</code> are siblings within the same parent
	 *	directory. If this is not true in your workspace, no functionality is affected, but the
	 *	documentation shared from those sister components will be inaccessible.
	 *
	 *	The <code>cwsw_evqueue</code> directory is the sharable and reusable portion of the
	 *	component.\n
	 *	The design intent is for this folder to be shared into your project's directory structure.
	 *	-	If your code management system can share folders (e.g., PVCS / Dimensions, MKS), this
	 *		might be a good solution; else,
	 *	-	filesystem symlinks are supported by GIT, with appropriate configuration options set
	 *		properly.
	 *	-	Example (using symlinks):\n
	 *	Given the following workspace directory structure:
	 *	@code{.sh}
	 *
	 	$ tree -dL 2
	 	.
	 	├── components
	 	│   ├── cwsw_arch_prj
	 	│   ├── cwsw_lib_prj
	 	│   └── cwsw_evqueue_prj
	 	├── cwsw_example_proj
	 	│   ├── appl_swc
	 	│   ├── cfg
	 	│   ├── drivers
	 	│   ├── libs
	 	│   ├── os
	 	│   ├── rte
	 	│   └── services
	 	├── doc
	 	└── ut

	 *	@endcode
	 *	Execute the following. @note This example is given using Cygwin; the same command line
	 *	verbatim would be done in Git Bash.\n
	 *	Also, 7-Zip can create symlinks, and there are other methods in Windows to create symbolic
	 *	links.
	 *
	 *	@code{.sh}

		$ cd cwsw_example_prj/libs/
		$ ln -s ../../components/cwsw_lib_prj/cwsw_lib cwsw_lib
		$ git add cwsw_lib
		$ cd ../appl_swc/
		$ ln -s ../../components/cwsw_evqueue_prj/cwsw_evqueue cwsw_evqueue
		$ git add cwsw_evqueue
		$ tree -dL 4 ../..
		../..
		├── components
		│   ├── cwsw_arch_prj
		│   ├── cwsw_evqueue_prj
		│   │   ├── cwsw_evqueue
		│   │   ├── doc
		│   │   └── ut
		│   └── cwsw_lib_prj
		│   │   ├── cwsw_lib
		│   │   │   ├── include
		│   │   │   └── src
		│   │   ├── doc
		│   │   └── ut
		└── cwsw_example_proj
		    ├── appl_swc
			│   └── cwsw_evqueue -> ../../components/cwsw_evqueue_prj/cwsw_evqueue
		    ├── cfg
		    ├── drivers
		    ├── libs
		    │   └── cwsw_lib -> ../../components/cwsw_lib_prj/cwsw_lib
		    ├── os
		    ├── rte
		    └── services

	 *	@endcode
	 *
	 *	@subsection evq_source_share_project	Project-specific Portion
	 *	TBD
	 *	NEEDS EVQ_PROJ
	 *
	 *//*}*/

	/*{*//**	@page Evq_Integration
	 *	@section Evq_update_includes			Update Includes paths
	 *	@subsection Evq_update_includes_paths	Include Paths
	 *	Update your build system to add the relative paths to the selected
	 *	library and event queue folders.
	 *
	 *	To clarify what you're looking for, here is the annotation for each of
	 *	the files in the <code> arch </code> project.
	 *	@note The design intent, is for all references within the project, to be
	 *	relative to the project itself. Portability is greatly reduced when the
	 *	project refers to fully qualified pathnames, or those outside of the
	 *	project tree itself.
	 *
	 *	@code{.sh}

		cwsw_evqueue_prj
		├── bsp
		│   └── src
		├── cwsw_evqueue	<<== target for symlink into your project; point your includes path here
		└── ut

	 *	@endcode
	 *	@note Some elements of the tree above have been excluded for clarity.
	 *
	 *	To illustrate how this might be done in an Eclipse-based project, see
	 *	the following screen capture: \n
	 *	@image html doc/arch/images/eclipse_add_includes_path.png			"Example Includes Path"
	 *	\n \n
	 *//*}*/

/*
 *	dependencies: lib. UT depends on arch, board, but this is not imposed on the evq.
 */
#endif																	/* } */
// ==== /COMPONENT DOCUMENTATION ============================================= }
