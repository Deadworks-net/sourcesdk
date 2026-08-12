#ifndef CSTRIKE15_CLIENT_USERCMD_H
#define CSTRIKE15_CLIENT_USERCMD_H

#pragma once

#include "../../shared/cstrike15/usercmd.h"

//-----------------------------------------------------------------------------
// Client side user command, as laid out by the client module.
//
// The client stores per-command prediction bookkeeping where the server keeps
// its list links.
//-----------------------------------------------------------------------------
class C_CSGOUserCmd : public CUserCmdBaseHost< CSGOUserCmdPB >
{
public:
	CInButtonState m_ButtonStates;

private:
	// Not part of the player message.
	char unknown[8];

public:
	double m_flExecutionTime;
	float m_flCurrentTime;
	bool m_bHasBeenPredicted;
	int m_nCmdType;
	int m_nCmdFlags;
};

// Cross-checked against the client command ring buffer, which holds 150 entries.
COMPILE_TIME_ASSERT( sizeof( C_CSGOUserCmd ) == 152 );

#endif // CSTRIKE15_CLIENT_USERCMD_H
