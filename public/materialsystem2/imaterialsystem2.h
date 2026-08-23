#ifndef IMATERIALSYSTEM2_H
#define IMATERIALSYSTEM2_H

#ifdef _WIN32
	#pragma once
#endif

#include "imaterial2.h"

#include <resourcefile/resourcehandle.h>
#include <resourcefile/resourcetype.h>

#include <tier0/platform.h>

class KeyValues3;

//-----------------------------------------------------------------------------
// Source 2 material system, exposed as MATERIAL_SYSTEM2_INTERFACE_VERSION
// ( see g_pMaterialSystem2 ).
//
// Reconstructed vtable. Every slot is kept in its verified index; slots whose
// purpose is unknown are placeholders named after their index. Do not reorder,
// remove or collapse them. No base class is declared because the inheritance
// chain has not been verified - the placeholders cover whatever occupies the
// leading slots.
//-----------------------------------------------------------------------------
abstract_class IMaterialSystem2
{
public:
	virtual void Unk_Slot0( void *p ) = 0;
	virtual void Unk_Slot1( void *p ) = 0;
	virtual void Unk_Slot2( void *p ) = 0;
	virtual void Unk_Slot3( void *p ) = 0;
	virtual void Unk_Slot4( void *p ) = 0;
	virtual void Unk_Slot5( void *p ) = 0;
	virtual void Unk_Slot6( void *p ) = 0;
	virtual void Unk_Slot7( void *p ) = 0;
	virtual void Unk_Slot8( void *p ) = 0;
	virtual void Unk_Slot9( void *p ) = 0;
	virtual void Unk_Slot10( void *p ) = 0;
	virtual void Unk_Slot11( void *p ) = 0;
	virtual void Unk_Slot12( void *p ) = 0;
	virtual void Unk_Slot13( void *p ) = 0;
	virtual void Unk_Slot14( void *p ) = 0;
	virtual void Unk_Slot15( void *p ) = 0;
	virtual void Unk_Slot16( void *p ) = 0;
	virtual void Unk_Slot17( void *p ) = 0;
	virtual void Unk_Slot18( void *p ) = 0;
	virtual void Unk_Slot19( void *p ) = 0;
	virtual void Unk_Slot20( void *p ) = 0;
	virtual void Unk_Slot21( void *p ) = 0;
	virtual void Unk_Slot22( void *p ) = 0;
	virtual void Unk_Slot23( void *p ) = 0;
	virtual void Unk_Slot24( void *p ) = 0;
	virtual void Unk_Slot25( void *p ) = 0;
	virtual void Unk_Slot26( void *p ) = 0;
	virtual void Unk_Slot27( void *p ) = 0;

	// Creates a material derived from an already loaded one, applying overrides on top of it.
	virtual ResourceHandle_t *CreateMaterialFromMaterial( HMaterialStrong *pOutMaterial, const char *pMaterialName, ResourceHandle_t hSrcMaterial, KeyValues3 *pOverrides, int nFlags, bool bUnk ) = 0;	// 28

	// Creates a material from scratch out of a KeyValues3 description.
	virtual ResourceHandle_t *CreateMaterial( HMaterialStrong *pOutMaterial, const char *pMaterialName, KeyValues3 *pData, int nFlags, bool bUnk ) = 0;											// 29
};

#endif // IMATERIALSYSTEM2_H
