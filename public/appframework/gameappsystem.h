#ifndef GAMEAPPSYSTEM_H
#define GAMEAPPSYSTEM_H

#ifdef _WIN32
#pragma once
#endif

#include "tier3/tier3.h"

template< class IInterface, int ConVarFlag = 0 >
class CGameAppSystem : public CTier3AppSystem< IInterface, ConVarFlag >
{
	typedef CTier3AppSystem< IInterface, ConVarFlag > BaseClass;
};

#endif
