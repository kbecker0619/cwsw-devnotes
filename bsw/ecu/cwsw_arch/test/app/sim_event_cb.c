/** @file
 *	@brief	callbacks for simulated event handling.
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Created on: May 2, 2019
 *	@author KBECKE35
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stddef.h>		/* NULL */
#include <limits.h>		/* INT_MAX */

// ----	Project Headers -------------------------
#include "projcfg.h"

// ----	Module Headers --------------------------


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

/** UT support for Enter Critical Section behavior.
 *	@xreq{SR_LIB_0307}
 */
bool crit_section_seen = false;

int crit_sec_prot_lvl = 0;

/** UT support for Enter Critical Section behavior.
 *	Note that here, we're relying on a compile-time constant string that
 *	will "be there" when this variable is inspected (e.g., does not go out of
 *	scope).
 *	@xreq{SR_LIB_0307}
 */
char const *crit_sect_file = NULL;

/** UT support for Enter Critical Section behavior.
 *	@xreq{SR_LIB_0307}
 */
int crit_section_line = 0;


// ============================================================================
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/**	Project-specific configuration to engage Critical Section / Protected Region
 *	behavior.
 *
 *	For the demo app + UT environment for the CWSW Library, we'll define this
 *	as a macro that supplies information that might be useful to the UT enviro.
 *
 *	@xreq{SR_LIB_0307}
 *
 *	@ingroup cwsw_lib_crit_section_group
 */
void
cb_lib_demo_cs_enter(int protlvl, char const * const filename, int const lineno)
{
	crit_section_seen = true;
	crit_sec_prot_lvl = protlvl;
	crit_sect_file = filename;
	crit_section_line = lineno;
}


void
cb_lib_demo_cs_leave(int protlvl, char const * const filename, int const lineno)
{
	crit_section_seen = true;
	crit_sec_prot_lvl = (0 == protlvl) ? INT_MAX : -protlvl;
	crit_sect_file = filename;
	crit_section_line = lineno;
}
