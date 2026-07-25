//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: The nav mesh's window onto collision detection.
//
//=============================================================================//

#ifndef NAVPHYSICSINTERFACE_H
#define NAVPHYSICSINTERFACE_H
#ifdef _WIN32
#pragma once
#endif

#include "gametrace.h"

class CBaseEntity;
class CNavArea;

abstract_class INavPhysicsInterface
{
public:
	virtual ~INavPhysicsInterface() {}

	virtual bool Nav_TraceLine( const Vector &vStart, const Vector &vEnd, const CBaseEntity *pIgnore, uint64 nInteractsWith, uint8 nCollisionGroup, uint8 nObjectSetMask, trace_t *pTraceOut ) = 0;
	virtual bool Nav_TraceLine( const Vector &vStart, const Vector &vEnd, CTraceFilter *pFilter, trace_t *pTraceOut ) = 0;
	virtual bool Nav_TraceShape( const Ray_t &ray, const Vector &vStart, const Vector &vEnd, const CBaseEntity *pIgnore, uint64 nInteractsWith, uint8 nCollisionGroup, uint8 nObjectSetMask, trace_t *pTraceOut ) = 0;
	virtual bool Nav_TraceShape( const Ray_t &ray, const Vector &vStart, const Vector &vEnd, CTraceFilter *pFilter, trace_t *pTraceOut ) = 0;

	virtual uint64 Nav_PointContents( const Vector &vTestPos, uint64 nContentsMask ) = 0;

	virtual bool Nav_CheckAreaOverlappingEntity( const CNavArea &rArea, const CBaseEntity &rEntity, bool bExtrudeHullHeight ) = 0;
	virtual void Nav_GetEntityWorldSpaceAABB( const CBaseEntity &rEntity, Vector *pMinsOut, Vector *pMaxsOut ) = 0;

	virtual void Nav_DeleteObject( CTraceFilter *pObject ) = 0;
};

#endif // NAVPHYSICSINTERFACE_H
