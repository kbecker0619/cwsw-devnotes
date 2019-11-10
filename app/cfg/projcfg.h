/** @file
 *	@brief	Project Configuration for CWSW Library Unit test environment.
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Sep 4, 2016
 *	@author kbecker
 */

#ifndef PROJCFG_H_
#define PROJCFG_H_

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <stdbool.h>	/* true, false - for preprocessor usage */

// ----	Project Headers -------------------------
#include "ctassert.h"

// ----	Module Headers --------------------------


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================
#define PROJCFG_H__REVSTRING "$Revision: 09042016 $"

// ==== PROJECT-INVARIANT CONSTANTS ========================================= {
/* ==== A WORD ABOUT BUILD TARGETS ============================================
 *	Within Eclipse, the configuration is available as an IDE variable named
 *		"${ConfigName}"
 *	This can be put into a command-line define, for use in the code itself;
 *	within this project's settings, this is done by defining
 *		"XPRJ_${ConfigName}"
 *
 *	Use by preprocessor code such as
 *		"#if defined(XPRJ_Debug)"
 *
 *	Note the name of this define is specifically chosen for cross-platform
 *	Compatibility, for example with MPLAB X.
 *
 *	Within the NetBeans IDE used by MPLAB X, the equivalent mechanism is to
 *	detect off the command-line define "XPRJ_NB_${CONF}",
 *		"#if defined(XPRJ_Debug)"
 *
 *	Note the name of the default configuration created by MPLAB X' New Project
 *	wizard is "default" - if you want a configuration named "Debug", you need to
 *	create it.
 *
 *	Within my development environment, I let Eclipse' New Project Wizard create
 *	its standard Debug and Release configurations, then create new ones for on-
 *	target debugging, as required. I assume my Windows/Linux Debug configuration
 *	is also intended for unit tests, so I rather indiscriminately print things
 *	to the console.
 * ========================================================================= */

/* ==== A FOLLOW-UP WORD ABOUT BUILD TARGETS ==================================
 * ANSI/ISO C says that the preprocessor evaluates an undefined symbol as having
 * the value '0' - however, many of the environments i'm targeting, and also many
 * of the static analysis tools, emit warnings about usage of undefined symbols
 * in normal C code - and even though i do it when necessary, i have a rather
 * strong aversion to using #if defined(x) mechanisms in normal code.
 * therefore, i'll here define all of the non-active build targets.
 * ========================================================================= */

/* ==== One final word ========================================================
 * This section is intended to be pristine and unchanged for all projects.
 * Configuration-specific defines (aka options specific to one of these Build
 * Targets) should be done in a followup section below.
 * ========================================================================= */
/* Configuration Check */
/* XPRJ (Cross-Compile Project) _ Platform _ Tool _ Config */
#if defined(XPRJ_Debug)
	/* This configuration is created by Eclipse; we do not want it used, unless ... */
	#if (XPRJ_Debug == 99)
		#pragma message "Building Within Atmel Studio"

	#else
		#error This configuration reserved for Atmel Studio
	#endif

#elif defined(XPRJ_Release)
	/* This configuration is created by Eclipse; we do not want it used */
	#error For now, do not build with the "Release" build target active

#elif defined(XPRJ_Debug_Linux_GCC) || defined(XPRJ_Debug_Linux_GCC_Desktop)
	/* This is the configuration intended for development & debugging in a Linux VM */
	/* The 1st is intended to debug on a PowerPC Target from a Linux development environment */
	/* The 2nd (Desktop) is intended for building within S32DS on Linux for a Linux debugging session */
	#define	XPRJ_CVI_Debug				0
	#define	XPRJ_Win_MSVC_Debug			0
	#define	XPRJ_Win_MinGW_Debug	 	0

#elif defined(XPRJ_Win_MinGW_Debug)
	/* This is the configuration intended for development on Windows, using MinGW */
	#define XPRJ_Win_Cygwin_Debug_UT	0
	#define XPRJ_Win_MSVC_Debug			0
	#define XPRJ_NB_Debug				0
	#define	XPRJ_CVI_Debug				0
	#define XPRJ_Debug_Linux_GCC		0

#elif defined(XPRJ_Win_Cygwin_Debug_UT)
	/* This is the configuration intended for unit test development on Windows, using GCOV */
	#define XPRJ_Win_MinGW_Debug		0
	#define XPRJ_Win_MSVC_Debug			0
	#define XPRJ_NB_Debug				0
	#define	XPRJ_CVI_Debug				0
	#define XPRJ_Debug_Linux_GCC		0

#elif defined(XPRJ_NB_Debug)
	#define XPRJ_Win_MinGW_Debug		0
	#define XPRJ_Win_Cygwin_Debug_UT	0
	#define XPRJ_Debug_Linux_GCC		0
	#define XPRJ_Win_MSVC_Debug			0
	#define	XPRJ_CVI_Debug				0

#elif defined(XPRJ_Debug_Cx_AtmelSamv71)
	/* This configuration is intended for the Atmel SAMV71 Xplained Ultra board */

#elif defined(XPRJ_Win_MSVC_Debug)
	/* Visual Studio 8, which is decidedly shy of C11 */
	/* NOTE: VS8 does not ship w/ headers <stdint.h> or <stdbool.h>, so i found alternate versions
	 * and copied them into my install directory. i happened to find some web sites w/ versions
	 * that claimed to work w/ VS8 or VS10, but you could also probably pull them from any other
	 * compiler you may have installed.
	 */
	#define XPRJ_Win_MinGW_Debug		0
	#define XPRJ_Win_Cygwin_Debug_UT	0
	#define XPRJ_Debug_Linux_GCC		0
	#define XPRJ_NB_Debug				0
	#define	XPRJ_CVI_Debug				0

#elif defined(XPRJ_CVI_Debug)
#error
	#define	XPRJ_Win_MinGW_Debug 		0
	#define XPRJ_Win_Cygwin_Debug_UT	0
	#define XPRJ_Debug_Linux_GCC		0
	#define XPRJ_NB_Debug				0
	#define	XPRJ_Win_MSVC_Debug			0

#else
#error Must define command-line symbol XPRJ_${ConfigName}

#endif

// ====	/PROJECT-INVARIANT CONSTANTS ======================================== }

// ==== PROJECT SPECIFIC CONSTANTS ========================================== {
// todo: pull in stuff from gen 0 of this same project
#if (XPRJ_Debug_Linux_GCC)
	/* enable or disable individual architectural features */
#endif

#if (XPRJ_CVI_Debug)
	// use cwsw simulated events to achieve separation between UI panels
	#define USE_NOTIFICATION_EVENTS		(1)
#endif


/*	Allow for the possibility that USE_NOTIFICATION_EVENTS might be a command-line
 *	define. Pick reasonable defaults if not defined.
 */
#if !defined(USE_NOTIFICATION_EVENTS)
#define USE_NOTIFICATION_EVENTS			(true)

#else
#endif

/*	For this component, equate simulated events with notification events. */
#if defined(USE_NOTIFICATION_EVENTS)
#define USE_SIMULATED_EVENTS	(true)
#endif


/**	Special "magic" marker for CUNIT unit testing environment.
 * 	If the command-line define of the CUNIT project defines BUILD_FOR_UNIT_TEST
 * 	with a value of 99, certain behaviors within the component are different,
 * 	depending on the needs of the unit test environment.
 */
#define CUNIT	99

/**	Special "magic" marker for the CONSOLE- based demo application.
 * 	If the command-line define of the demo project defines BUILD_FOR_UNIT_TEST
 * 	with a value of 1, certain behaviors within the component are different,
 * 	depending on the needs of the demo app environment.
 *
 * 	This value specifically chosen because most instances of value #true also
 * 	have the value "1", so that the default build, in the absence of a command-
 * 	line define, will enable console behavior.
 */
#define CONSOLE	 1

/*	Allow for the possibility that BUILD_FOR_UNIT_TEST might be a command-line
 *	define. Pick reasonable defaults if not defined.
 */
#if !defined(BUILD_FOR_UNIT_TEST)
	#if (XPRJ_Debug_Linux_GCC)		||	\
		(XPRJ_Win_MinGW_Debug)		||	\
		(XPRJ_Win_Cygwin_Debug_UT)	||	\
		(XPRJ_NB_Debug)				||  \
		(XPRJ_Win_MSVC_Debug)		||  \
		(XPRJ_CVI_Debug)
		#define BUILD_FOR_UNIT_TEST		(true)

	#else
		#define BUILD_FOR_UNIT_TEST		(false)

	#endif
#endif

// ==== /PROJECT SPECIFIC CONSTANTS ========================================= }


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

/* Define WEAK attribute */
/**	Macro to designate a function as weakly bound.
 *	This allows a project to define a default function that can be overridden by
 *	a specific implementation. Note not all compilers support this, so on projects
 *	that rely on this, you'll need to figure out a work-around.
 */
#if !defined(WEAK)
#if defined (__GNUC__)					/* GCC CS3 2009q3-68 */
#define WEAK __attribute__ ((weak))

#elif defined (__CC_ARM  )				/* Keil �Vision 4 */
#define WEAK __attribute__ ((weak))

#elif defined (__ICCARM__)				/* IAR Ewarm 5.41+ */
#define WEAK __weak

#elif defined(_MSC_VER) || defined(_CVI_)	/* visual studio 8 and LabWindows/CVI v7.1 */
#define	WEAK	/* WEAK not available */

#else
#error Unrecognized or unsupported compiler

#endif
#endif


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
#define CWSW_LIB_CRIT_SECT_ENTER(protlvl)	cb_lib_demo_cs_enter(protlvl, __FILE__, __LINE__)
extern void cb_lib_demo_cs_enter(int protlvl, char const * const filename, int const lineno);

/**	Project-specific configuration, invoked when Critical Section is already
 *	active.
 *
 *	Normally, we recommend the definition of:
 *		do {} while(0)
 *
 *	For this project's UT environment, we'll define this as a macro that
 *	supplies info that might be useful to the UT enviro.
 *
 *	@xreq{SR_LIB_0308}
 *
 *	@ingroup cwsw_lib_crit_section_group
 */
#define	CWSW_LIB_CRIT_SECT_LEAVE(protlvl)	cb_lib_demo_cs_leave(protlvl, __FILE__, __LINE__)
extern void cb_lib_demo_cs_leave(int protlvl, char const * const filename, int const lineno);


// define specifically for Eclipse CDT parser
#ifdef __CDT_PARSER__
  #define __BASE_FILE__ __FILE__
#endif


#ifdef	__cplusplus
}
#endif

#endif /* PROJCFG_H_ */
