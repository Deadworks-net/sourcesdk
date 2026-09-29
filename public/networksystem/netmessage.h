#ifndef NETMESSAGE_H
#define NETMESSAGE_H

#ifdef _WIN32
#pragma once
#endif

#include "platform.h"
#include "iserver.h"
#include "networksystem/inetworkmessages.h"
#include "networksystem/inetworkserializer.h"

#include <typeinfo>

#define DEFAULT_NETMESSAGE_COLOR Color(255, 255, 255, 255)

inline constexpr const char *k_pszNetGroupNames[ SG_TOTAL ] =
{
	"Generic",          // SG_GENERIC = 0
	"Local Player",     // SG_LOCALPLAYER = 1
	"Other Players",    // SG_OTHERPLAYER = 2
	"Entities",         // SG_ENTITIES = 3
	"Sounds",           // SG_SOUNDS = 4
	"Events",           // SG_EVENTS = 5
	"Voice",            // SG_VOICE = 6
	"String Table",     // SG_STRINGTABLE = 7
	"Move",             // SG_MOVE = 8
	"String Command",   // SG_STRINGCMD = 9
	"Signon",           // SG_SIGNON = 10
	"System",           // SG_SYSTEM = 11
	"Unknown",          // gap (12)
	"User Messages",    // SG_USERMSG = 13
	"Client Messages",  // SG_CLIENTMSG = 14
	"Spawn Groups",     // SG_SPAWNGROUPS = 15
	"Game Engine",      // SG_ENGINE = 16
	"Hltv Replay",      // SG_HLTVREPLAY = 17
	"Decals"            // SG_DECALS = 18
};

class CNetMessage
{
public:
	CNetMessage( NetChannelBufType_t bufType = BUF_DEFAULT ) : m_dbRecivedTime( -1.0 ), m_nSignatrue( 0 ), m_bufType( bufType ), m_nPacketSize( -1 ), m_nSendCount( -1 ), m_flMargin( -1.0f ), m_nUnk( -1 ) {}
	CNetMessage( const CNetMessage &copyFrom ) = default;
	CNetMessage( CNetMessage &&moveFrom ) = default;
	CNetMessage &operator=( const CNetMessage &copyFrom ) = default;
	CNetMessage &operator=( CNetMessage &&moveFrom ) = default;
	virtual ~CNetMessage() = default;

	// Returns the underlying proto object
	virtual const google::protobuf::MessageLite *AsMessageLite() const = 0;
	virtual const google::protobuf::Message     *AsMessage() const = 0;

	virtual INetworkSerializerPB *GetSerializerPB() const = 0;
	virtual CNetMessage *Clone() const = 0;
	// Deadlock: since 6711, but without upstream's virtual GetName() after it.
	virtual NetworkMessageId GetMessageId() const = 0;

	// Helper function to cast up the abstract message to a concrete T message type.
	// Doesn't do any validity checks itself!
	template< typename T > T *As() { return static_cast< T * >( this ); }
	template< typename T > const T *As() const { return static_cast< const T * >( this ); }

	double GetRecivedTime() const { return m_dbRecivedTime; }
	uint32 GetSignature() const { return m_nSignatrue; }
	NetChannelBufType_t GetBufType() const { return m_bufType; }
	int GetPacketSize() const { return m_nPacketSize; }
	int GetSendCount() const { return m_nSendCount; }
	float GetMargin() const { return m_flMargin; }

	bool Send( CPlayerSlot slot ) const;
	int Send( const CPlayerBitVec &playerBits ) const;
	int Send( const CUtlVector< CPlayerSlot > &vecSlots ) const;
	int SendToAllClients() const;

private:
	double m_dbRecivedTime;
	uint32 m_nSignatrue;
	NetChannelBufType_t m_bufType;
	int m_nPacketSize;
	int m_nSendCount;
	float m_flMargin;
	int64 m_nUnk;
};

// AMNOTE: This is a stub class over real CNetMessagePB!
// This is mainly to access the game constructed objects, and not for direct initialization of them
// since this misses the CNetMessage implementation which requires supplying other proto related info like
// proto binding object, proto msg id/group, etc.
// So to allocate the message yourself use INetworkMessageInternal::AllocateMessage() instead of direct initialization,
// and free it with delete, which goes through the game's deleting destructor!
// Example usage:
// auto *msg = INetworkMessageInternal::AllocateMessage()->As<CYourMessage_t>();
// msg->field1( 2 );
// msg->field2( 3 );
// IGameEventSystem::PostEventAbstract( ..., msg, ... );
template< NetworkMessageId ID, typename PROTO_TYPE, SignonGroup_t SIGNON = SG_GENERIC, NetChannelBufType_t BUF_TYPE = BUF_RELIABLE, bool IS_FOR_SERVER = false >
class CNetMessagePB : public CNetMessage, public PROTO_TYPE
{
public:
	using MyType_t = CNetMessagePB< ID, PROTO_TYPE, SIGNON, BUF_TYPE, IS_FOR_SERVER >;
	using PBType_t = PROTO_TYPE;

	static constexpr NetworkMessageId kMsgId = ID;
	static constexpr SignonGroup_t kSignonGroup = SIGNON;
	static constexpr NetChannelBufType_t kBufType = BUF_TYPE;
	static constexpr bool kIsForServer = IS_FOR_SERVER;

	// Deadlock: since 6711 FindOrCreateNetMessage takes this instead of an IProtobufBinding.
	static CNetMessage *AllocateMessage()
	{
		auto *pNewMsg = Alloc< MyType_t >();

		if ( !pNewMsg )
			return nullptr;

		return static_cast< CNetMessage * >( Construct( pNewMsg ) );
	}

public:
	CNetMessagePB() : CNetMessage( kBufType ), PBType_t() {}
	CNetMessagePB( const MyType_t &copyFrom ) = default;
	CNetMessagePB( MyType_t &&moveFrom ) = default;
	MyType_t &operator=( const MyType_t &copyFrom ) = default;
	MyType_t &operator=( MyType_t &&moveFrom ) = default;
	virtual ~CNetMessagePB() {}

	virtual const google::protobuf::MessageLite *AsMessageLite() const { return static_cast< const PBType_t * >( this ); };
	virtual const google::protobuf::Message     *AsMessage() const { return static_cast< const PBType_t * >( this ); };

	virtual INetworkSerializerPB *GetSerializerPB() const
	{
		static INetworkSerializerPB *s_pSerializerPB = nullptr;

		if ( !s_pSerializerPB && g_pNetworkMessages )
		{
			s_pSerializerPB = g_pNetworkMessages->FindOrCreateNetMessage( kMsgId, &AllocateMessage, kSignonGroup, kBufType, kIsForServer );
		}

		return s_pSerializerPB;
	}

	virtual CNetMessage *Clone() const
	{
		auto *pClone = Alloc< MyType_t >();

		*pClone = *this;

		return static_cast< CNetMessage * >( pClone );
	}

	virtual NetworkMessageId GetMessageId() const { return kMsgId; }

public:
	const char *GetName() const { return PBType_t::GetTypeName().c_str(); }

	NetMessageInfo_t *GetProtoInfo() const
	{
		INetworkSerializerPB *pSerializerPB = GetSerializerPB();

		if ( !pSerializerPB )
			return nullptr;

		return pSerializerPB->GetNetMessageInfo();
	}
};

template< NetworkMessageId ID, typename PROTO_TYPE, NetChannelBufType_t BUF_TYPE = BUF_RELIABLE >
class CUserMessagePB : public CNetMessagePB< ID, PROTO_TYPE, SG_USERMSG, BUF_TYPE > {};

#endif // NETMESSAGE_H

