/** @file
 *	@brief	One-sentence short description of file.
 *
 *	Copyright (c) 2019 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Jan 5, 2018
 *	@author kbecker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

#include "../../../../inc/i386/peripheral/ports/ports_api.h"

#include "projcfg.h"

// ----	System Headers --------------------------

// ----	Project Headers -------------------------

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

// ============================================================================
// ----	Private Prototypes ----------------------------------------------------
// ============================================================================

// ============================================================================
// ----	Public Functions ------------------------------------------------------
// ============================================================================

/* klb: this is architecture-specific, but Microchip adds one more level of indirection, to
 * customize to the specific MCU actually used.
 *
 * This is agnostic about the board on which the MCU resides.
 *
 * For "none", this is a nop. For LabWindows/CVI, this would light an LED (when I add that support).
 *
 * @note can't use the default "PLIB_INLINE_API" decorator, because of two opposing things:
 * 	(a) "extern" in conflict with "static"
 * 	(b) sans "static", you get multiple-definition linking errors. don't know (yet) how this is
 * 		avoided in MPLAB projects.
 *
 * to compensate, modified the Microchip definition of PLIB_INLINE, to eliminate the "extern"
 * storage identifier.
 */
#if (XPRJ_CVI_Debug)
#include "cwsw_dio_uir.h"
#endif
void
PLIB_PORTS_PinWrite(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos, bool value)
{
	(void)(index);
	(void)(channel);
	(void)(bitPos);
	(void)(value);

#if defined(DEMO_APP)
	dbg_printf(
		"\tDO Write, Idx: %i, Channel: %i, Bit: %i, Value: %s\n",
		index, channel, bitPos, value ? "On" : "Off");
#endif

	#if (XPRJ_Debug_CVI)
	{
		lwWriteVirtualPin(bitPos, value);

	}
	#endif
}

bool
PLIB_PORTS_PinGet(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
	(void)(index);
	(void)(bitPos);

#if defined(DEMO_APP)
	dbg_printf(
		"\tDO Read, Idx: %i, Channel: %i, Bit: %i\n",
		index, channel, bitPos);
#endif

	#if (XPRJ_Debug_CVI)
	return lwReadVirtualPin(channel, bitPos);

	#else
	switch(channel)
	{
	case PORT_CHANNEL_B:
		switch(bitPos)
		{
		case PORTS_BIT_POS_0:
			break;
		default:
			break;
		}
		break;
	default:
		return false;
	}

	#endif
	return false;
}
