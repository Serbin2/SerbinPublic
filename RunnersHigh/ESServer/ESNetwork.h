#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "ITCPServer.h"

#define BUFSIZE    1024

class ESNetwork : public ITCPServer
{
	ServerConfig				 m_Config;
	//fd_set						 m_readFD;
	//fd_set						 m_writeFD;
	SOCKET						 m_ListenSock;
	//std::deque<PacketInfo>		 m_RecvQueue;

	//SessionManager* m_pSessionManager;
	ILog* m_pLogger;

	struct SOCKETINFO
	{
		SOCKET sock;
		char buf[BUFSIZE + 1];
		int recvbytes;
		int sendbytes;
		bool sendready;
	};

	int m_totalSocket;
	SOCKETINFO* SocketInfoArray[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];
	WSANETWORKEVENTS NetworkEvents;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;

	Packet RecvPckt;

	int index;

	HANDLE						 m_SelectThreadHandle;
	unsigned					 m_SelectThreadId;

	ERR_CODE LoadConfig() override;
	ERR_CODE StartUp() override;
	ERR_CODE Socket() override;
	ERR_CODE Bind() override;
	ERR_CODE Listen() override;
	ERR_CODE Connect() override;
	ERR_CODE SocketOpt() override;
	ERR_CODE SocketOpt(SOCKET clientsock) override;

	// 家南 包府 窃荐
	ERR_CODE AddSocketInfo(SOCKET sock, long NetEvent);
	ERR_CODE RemoveSocketInfo(int nIndex);

	ERR_CODE Select();
	ERR_CODE EventSelect();

	ERR_CODE Accept() override;

	ERR_CODE Receive() override;
	ERR_CODE Send() override;
	ERR_CODE SendAll();
	ERR_CODE Close();
	ERR_CODE SendPacket(int id, Packet msg) override;
	ERR_CODE RecvPacket();

	//ERR_CODE CloseClient(unsigned int index, std::deque<PacketInfo>& queue) override;
	ERR_CODE CloseServer() override;

public:
	ESNetwork();
	virtual ~ESNetwork();
	ERR_CODE InitServer(ILog* pLogger) override;
	ERR_CODE InitClient(ILog* pLogger) override;
	ERR_CODE ServerRun() override;
	ERR_CODE ClientRun() override;
	ERR_CODE CleanUp() override;
	//PacketInfo GetPacket() override;


};

