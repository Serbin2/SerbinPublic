#pragma once


#include "Stream.h"


// Server To Client -> S2C
// Client To Server -> C2S

// 자기 자신에게 보내는 패킷 (네트워크 상에서 나타나는 이벤트를 프로세스에 태우려고 만듦)
// Server - S_   
// Clinet - C_   

enum class PACKET_ID : unsigned int
{
	NONE = 0,

	/// Server - 10 ~
	SERVER = 10,
	S_NEWCONNECT,
	S_CLOSESESSION,

	S2C_ID_ASSIGNMENT,
	S2C_STARTTIME,
	S2C_NOWTIME,
	S2C_ALL_OBJECT_UPDATE,
	S2C_ECHO_REQ,
	S2C_ECHO_ANS,

	/// Client - 50 ~
	Client = 50,
	C2S_WHATTIME,
	C2S_MY_OBJ_UPDATE,
	C2S_ECHO_REQ,
	C2S_ECHO_ANS,
	C2S_MOVE_GOAL,
	C2S_PLAYER_INPUT,
	MAX = 255,
};

// http://egloos.zum.com/paulownia/v/4366254

#pragma pack(push, 1)
union Packet
{
	struct PacketHeader
	{
		unsigned short id;
		unsigned short length;
	};

	struct Segment
	{
		unsigned short id;
		unsigned short length;
		char body[PACKET_SIZE - PACKET_HEAD_SIZE];
	};

	PacketHeader head;
	Segment segment;
	char buffer[PACKET_SIZE];
};

//struct PacketInfo
//{
//	PacketInfo() { session_id = MAX_CLIENT_COUNT + 10; }
//	int session_id;
//	Packet data;
//};

///----------------------------------------------------------------------------------

struct PacketBody
{
	PacketBody();
	virtual ~PacketBody();

	virtual void encode(Stream& stream);
	virtual void decode(Stream& stream);
};



struct C2SUserInput : public PacketBody
{
	int userID;
	unsigned char Input;
	unsigned char KeyState;

	C2SUserInput();
	virtual ~C2SUserInput();

	void encode(Stream& stream)override;
	void decode(Stream& stream)override;
};

struct C2SPlayerMove : public PacketBody
{
	int objid;
	float x, y, z;

	C2SPlayerMove();
	virtual ~C2SPlayerMove();

	void encode(Stream& stream)override;
	void decode(Stream& stream)override;
};
#pragma pack(pop)
