/** @file
 *	@brief	Initialize the MCU.
 *
 *	This module is not intended to stand alone; it depends on some parts of the CWSW Lib component.
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Jan 3, 2018
 *	@author kbecker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

#include "projcfg.h"
#if !(  (XPRJ_Win_MinGW_Debug)	||	\
        (XPRJ_Debug_Linux_GCC)	||	\
        (XPRJ_NB_Debug)			||	\
		(XPRJ_Win_MSVC_Debug)	||	\
        (XPRJ_CVI_Debug) )
#error Unknown CPU Architecture
#endif

// ----	System Headers --------------------------
#include <stddef.h>		/* NULL */
#include <stdbool.h>

// ----	Project Headers -------------------------
#include "../../../../svc/cwsw_lib/inc/cwsw_lib.h"

// ----	Module Headers --------------------------
#include "../../inc/i386/cwsw_arch.h"


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
static char const * const cwsw_arch_RevString = "$Revision: 0.2.0 $";

PRIVATE bool cwsw_arch_initialized = false;


// ============================================================================
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

#if (USE_SYS_CLK)
#include "system/clk/sys_clk.h"

#else
#define SYS_CLK_Initialize(a)			do { (void)(a); } while(0)

#endif

#if (USE_SYS_DEVCON)
#else
#define SYS_DEVCON_Initialize(a, b)		do { (void)(a); (void)(b); } while(0)
#define SYS_DEVCON_PerformanceConfig(a)	do { (void)(a); } while(0)
#endif

#if (USE_SYS_PORTS)
#include "system/ports/sys_ports.h"
#else
#define SYS_PORTS_Initialize()			do {} while(0)
#endif


// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/* See function documentation at prototype.
 */
uint16_t
Cwsw_Arch__Init(void)
{
	// for desktop use, there's really not much to do here.
	if(BUILD_FOR_UNIT_TEST == CONSOLE)
	{
		SUPPRESS_EXTRAISO_IDENT;	/* suppress warning for function name */

		dbg_printf(
				"\tModule ID %i\t%s\t%s\n"
				"\tEntering %s()\n\n",
				Cwsw_Arch, __FILE__, cwsw_arch_RevString,
				__FUNCTION__);

		RESTORE_WARNING_CONTEXT;
	}

	/* Core Processor Initialization
	 * forgive this flagrant violation of personal ingenuity, but the names and call order is
	 * borrowed, /FOR NOW/, from MHC. I fully intend to abstract this so it's my own implementation,
	 * not a blatant borrowing of someone else's favored methods.
	 */
	SYS_CLK_Initialize( NULL );
	SYS_DEVCON_Initialize(0, NULL);
	SYS_DEVCON_PerformanceConfig(0);
	SYS_PORTS_Initialize();

	cwsw_arch_initialized = true;
	return 0;
}


bool
Cwsw_Arch__Get_Initialized(void)
{
	return cwsw_arch_initialized;
}
