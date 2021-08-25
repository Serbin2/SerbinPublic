#include "Packet.h"


PacketBody::PacketBody()
{
}

PacketBody::~PacketBody()
{
}

void PacketBody::encode(Stream& stream)
{
}

void PacketBody::decode(Stream& stream)
{
}

C2SPlayerMove::C2SPlayerMove()
{

}

C2SPlayerMove::~C2SPlayerMove()
{

}

void C2SPlayerMove::encode(Stream& stream)
{
	stream << objid;
	stream << x;
	stream << y;
	stream << z;
}

void C2SPlayerMove::decode(Stream& stream)
{
	stream >> objid;
	stream >> x;
	stream >> y;
	stream >> z;
}

C2SUserInput::C2SUserInput()
{

}

C2SUserInput::~C2SUserInput()
{

}

void C2SUserInput::encode(Stream& stream)
{
	stream << userID;
	stream << Input;
	stream << KeyState;
}

void C2SUserInput::decode(Stream& stream)
{
	stream >> userID;
	stream >> Input;
	stream >> KeyState;
}
