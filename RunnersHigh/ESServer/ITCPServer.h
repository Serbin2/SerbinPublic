#pragma once

#include <deque>

#include "ES_ERR.h"
#include "ILogger.h"

#include "Packet.h"

class ITCPServer
{
protected:
	virtual ERR_CODE LoadConfig() = 0;
	virtual ERR_CODE StartUp() = 0;
	virtual ERR_CODE Socket() = 0;
	virtual ERR_CODE Bind() = 0;
	virtual ERR_CODE Listen() = 0;
	virtual ERR_CODE Connect() = 0;
	virtual ERR_CODE SocketOpt() = 0;
	virtual ERR_CODE SocketOpt(SOCKET clientsock) = 0;
	virtual ERR_CODE Accept() = 0;

	virtual ERR_CODE Receive() = 0;
	virtual ERR_CODE Send() = 0;
	//virtual ERR_CODE CloseClient(unsigned int index, std::deque<PacketInfo>& queue) = 0;
	virtual ERR_CODE CloseServer() = 0;

public:
	ITCPServer() {};
	virtual ~ITCPServer() {};

	virtual ERR_CODE InitServer(ILog* pLogger) = 0;
	virtual ERR_CODE InitClient(ILog* pLogger) = 0;

	virtual ERR_CODE ServerRun() = 0;
	virtual ERR_CODE ClientRun() = 0;

	virtual ERR_CODE CleanUp() = 0;
	//virtual PacketInfo GetPacket() = 0;
	virtual ERR_CODE SendPacket(int id, Packet msg) = 0;
};