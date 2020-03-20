/** @file
 *	@brief	One-sentence short description of file.
 *
 *	\copyright
 *	Copyright (c) 2020 Kevin L. Becker. All rights reserved.
 *
 *	Created on: Jan 5, 2018
 *	@author kbecker
 */

// ============================================================================
// ----	Include Files ---------------------------------------------------------
// ============================================================================

// ----	System Headers --------------------------
#include <limits.h>		/* CHAR_BIT */

// ----	Project Headers -------------------------
#include "projcfg.h"

// ----	Module Headers --------------------------
#include "ports_api.h"


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

/* mvp for this build: one "channel" of 8 bits, we'll call it channel a */
// implementation note: we're intentionally not complying w/ C90 (by use of `bool`, in addition to other things)
bool channel_stat[kNumPortsChannels][kNumPortBits] = {0};


// ============================================================================
// ----	Private Functions -----------------------------------------------------
// ============================================================================

static void
ShowDoStatus(void)
{
	int rowidx, colidx;

	#if defined(DEMO_APP)
	// show header line
	(void)puts("\nDigital Output status:");
	(void)puts("\n       Bit: [F][E][D][C][B][A][9][8][7][6][5][4][3][2][1][0]");

	// show port status
	for(rowidx = 0; rowidx < kNumPortsChannels; rowidx++)
	{
		(void)printf("\nChannel: %c: ", rowidx + 'A');
		colidx = kNumPortBits;
		while(colidx--)
		{
			(void)printf("[%c]", channel_stat[rowidx][colidx] ? '+' : '-');
		}
	}
	(void)puts("\n");
	#endif
}


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
PLIB_PORTS_PinWrite(PORTS_MODULE_ID index, tPORTS_CHANNEL channel, PORTS_BIT_POS bitPos, bool value)
{
	(void)(index);
	(void)(channel);
	(void)(bitPos);
	(void)(value);

	if( (channel < kNumPortsChannels) && (bitPos < kNumPortBits) )
	{
		channel_stat[channel][bitPos] = !!value;	// convert any non-binary value to bool
	}

	#if defined(DEMO_APP)
	ShowDoStatus();
	#endif

	#if (XPRJ_Debug_CVI)
	{
		lwWriteVirtualPin(bitPos, value);

	}
	#endif
}

bool
PLIB_PORTS_PinGet(PORTS_MODULE_ID index, tPORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
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
