/** @file
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Nov 11, 2018
 *	@author kbecker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdlib.h>     	/* EXIT_SUCCESS */

// ----	Project Headers -------------------------
#include "projcfg.h"
#include "cwsw_lib.h"
#include "cwsw_eventsim.h"

// ----	Module Headers --------------------------
#include "cwsw_arch.h"


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
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

void
EventHandler__evTerminateRequested(tEventPayload EventData)
{
	UNUSED(EventData);
	(void)puts("Goodbye Cruel World!");
}


/** Entry for demonstration app for core part of CWSW Arch component.
 *	This is extremely limited in functionality by design, and is not intended
 *	to demonstrate the features and capabilities of the library. That task is
 *	left to the Architecture Integration project.
 */
int
main(void)
{
	tEventPayload ev = {0};
	(void)Init(Cwsw_Lib);		// Cwsw_Lib__Init()
	(void)Init(Cwsw_Arch);		// Cwsw_Arch__Init()

	PostEvent(evTerminateRequested, ev);
	return EXIT_SUCCESS;
}
