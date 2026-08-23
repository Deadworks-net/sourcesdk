#ifndef CSTRIKE15_SERVER_USERCMD_H
#define CSTRIKE15_SERVER_USERCMD_H

#pragma once

#include "../../shared/cstrike15/usercmd.h"

//-----------------------------------------------------------------------------
// Server side user command, as laid out by the server module.
//
// The server keeps its pending commands in an intrusive list, so the tail of
// the class differs from the client one.
//-----------------------------------------------------------------------------
class CCSGOUserCmd : public CUserCmdBaseHost< CSGOUserCmdPB >
{
public:
	CInButtonState m_ButtonStates;

private:
	// Not part of the player message.
	uint32 unknown[4];

public:
	CCSGOUserCmd *m_pPrev;
	CCSGOUserCmd *m_pNext;
};

#endif // CSTRIKE15_SERVER_USERCMD_H
