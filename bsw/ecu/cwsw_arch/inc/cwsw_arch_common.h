/** @file
 *	@brief	API common to all instances of the cwsw_arch reusable component.
 *
 *	Description:
 *	Do not include this file directly; it is intended to be included by the architecture-specific
 *	API file in one of the supported architectures, located immediately below this file's location.
 *
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Jan 3, 2018
 *	@author kbecker
 */

#ifndef CWSW_ARCH_COMMON_H_
#define CWSW_ARCH_COMMON_H_

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

#include "projcfg.h"

// ----	System Headers --------------------------
#include <stdint.h>		/* uint16_t */
#include <stdbool.h>	/* bool */

// ----	Project Headers -------------------------

// ----	Module Headers --------------------------


#ifdef	__cplusplus
extern "C" {
#endif


// ============================================================================
// ----	Constants -------------------------------------------------------------
// ============================================================================
#define CWSW_ARCH_COMMON_H__REVSTRING "$Revision: 0.2.0 $"


// ============================================================================
// ----	Type Definitions ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Variables ------------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public API ------------------------------------------------------------
// ============================================================================

// ==== Discrete Functions ================================================== {

/** Initialization for the MCU Architecture Support component.
 *	This function's responsibility is to set up the local vars, and manage the
 *	necessary HW, to prepare for the task function's 1st call (once the
 *	scheduler has been started).
 *
 *	This function shall be called before the main scheduler is started.
 *
 *	As general guidance, the CWSW Library component should have been initialized
 *	before this function is called (since this module depends on the library),
 *	though this is not a strict requirement.
 *
 *	**Note**: This function (and this module) are not intended to replace the
 *	architecture support required for the integration project; rather, this
 *	function and this module are intended to interface between that MCU support
 *	and the CWSW Library suite.
 *
 *	@returns	0 if the component is successfully initialized.
 *	@returns	error code if the component is not initialized.
 *	@note		By design, this component does not depend on specific
 *				enumerated names for the return code; in the CWSW ecosystem,
 *				the simulated event mechanism is used to handle error codes.
 *
 * 	@startuml
 *		System	->		cwsw_arch: Init()
 *		System	\\--	cwsw_arch: Error code
 *	@enduml
 *
 *	@xreq{SR_ARCH_0000}	(Primary, Component-specific)
 *
 *	@note By design, this function unilaterally reinitializes the component and
 *	returns all internal operating stateful behavior to original operating
 *	state. This means it takes exception to @req{SR_tbd_0003} and @req{SR_tbd_0004}
 *
 *	@ingroup	cwsw_arch_init_group
 *//* IMPLEMENTATION NOTE
 * contrary to normal practice, this function doxymented here (at the API,
 * rather than in the implementation) so that it doesn't need to be done
 * repeatedly, for each supported architecture.
 */
extern uint16_t Cwsw_Arch__Init(void);

// ==== /Discrete Functions ================================================= }

// ==== Targets for Get/Set APIs ============================================ {

/** "Chapter Designator" for Get/Set API.
 *	Intentionally unused symbol, designed to get you to the correct starting
 *	point, when you want to find macros for the Get/Set API; simply highlight
 *	the Module argument in your IDE (e.g, Eclipse, NetBeans, etc.), and select
 *	Go To Definition.
 */
enum { Cwsw_Arch = 1 };	/* Generic architecture for all MCU architectures */

/** Target symbol for Get(Cwsw_Arch, xxx) interface */
#define Cwsw_Arch__Get(a)		Cwsw_Arch__Get_ ## a()

/** Target for Get(Cwsw_Arch, Initialized) interface */
extern bool 					Cwsw_Arch__Get_Initialized(void);

// ==== /Targets for Get/Set APIs =========================================== }


#ifdef	__cplusplus
}
#endif

// ====	COMPONENT DOCUMENTATION ============================================= {
#if defined(IN_DOXY)				/* { */
/* klb: i apologize in advance for burdening your build, by forcing your compiler to consume all of
 * this information every build, every file that includes it. My only justification is that this is
 * the only place common to all architectures, and, I want to limit reliance on supplemental
 * documents because those get lost. At least if the documentation is in the code, there is no
 * chance it'll get lost.
 */

	/**	@page Arch_Responsibilities			Component Responsibilities
	 *	@tableofcontents
	 * 	The Architecture component manages all aspects of the MCU. In some cases, one Component may
	 * 	be configured to handle multiple variants of the MCU; however, in most cases, there will be
	 * 	one Arch component per MCU variant.
	 */

	/**	@page Arch_Constraints				Constraints Imposed Upon Component
	 *	@tableofcontents
	 *	-	TBD. Should be at the "bottom" of the dependency tree, except for libraries such as the
	 *		CWSW Library.
	 */

/**	\page Arch_srs							Architecture Software Requirements
 *	@tableofcontents
 *	TBD. Might be delineated in an external document.
 */

#endif								/* } */
// ==== /COMPONENT DOCUMENTATION ============================================ }


#endif /* CWSW_ARCH_COMMON_H_ */
