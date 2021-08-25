#include "ESNetwork.h"

ERR_CODE ESNetwork::LoadConfig()
{
	memcpy_s(&m_Config.IP, MAX_IP_SIZE, "127.0.0.1", _countof("127.0.0.1"));

	m_Config.PORT = DEFAULT_SERVER_PORT;
	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::StartUp()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != NOERROR)
		return ERR_CODE::WSASTART_FAIL;
	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::Socket()
{
	m_ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_ListenSock == INVALID_SOCKET) return ERR_CODE::SOCKET_SET_FAIL;

	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::Bind()
{
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(DEFAULT_SERVER_PORT);
	int retval = bind(m_ListenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR)
		return ERR_CODE::SOCKET_BIND_FAIL;

	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::Listen()
{
	int retval = listen(m_ListenSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
		return ERR_CODE::SOCKET_LISTEN_FAIL;
	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::Connect()
{
	// connect()
	SOCKADDR_IN serveraddr;
	const char* ip = "127.0.0.1";

	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &serveraddr.sin_addr.S_un.S_addr);
	serveraddr.sin_port = htons(DEFAULT_SERVER_PORT);
	int result = connect(m_ListenSock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (result == SOCKET_ERROR)
	{
		return ERR_CODE::CLIENT_2_SERVER_CONNECT_FAIL;
	}
	//m_pSessionManager->SetSession(m_ListenSock, serveraddr);
	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::SocketOpt()
{
	auto on = 1;
	if (setsockopt(m_ListenSock, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(int)) == SOCKET_ERROR)
		return ERR_CODE::SOCKET_OPT_SET_FAIL;

	unsigned long btn = 1;
	if (ioctlsocket(m_ListenSock, FIONBIO, &btn) == SOCKET_ERROR)
		return ERR_CODE::SOCKET_OPT_SET_FAIL;

	int option = TRUE;
	setsockopt(m_ListenSock, IPPROTO_TCP, TCP_NODELAY, (const char*)&option, sizeof(option));


	linger ling;
	ling.l_onoff = 0;
	ling.l_linger = 0;
	setsockopt(m_ListenSock, SOL_SOCKET, SO_LINGER, (char*)&ling, sizeof(ling));
	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::SocketOpt(SOCKET clientsock)
{
	int option = TRUE;
	setsockopt(m_ListenSock, IPPROTO_TCP, TCP_NODELAY, (const char*)&option, sizeof(option));

	linger ling;
	ling.l_onoff = 0;
	ling.l_linger = 0;
	setsockopt(m_ListenSock, SOL_SOCKET, SO_LINGER, (char*)&ling, sizeof(ling));

	int size1 = MAX_SOCKOPT_RECV_BUFSIZE;
	int size2 = MAX_SOCKOPT_SEND_BUFSIZE;
	setsockopt(m_ListenSock, SOL_SOCKET, SO_RCVBUF, (char*)&size1, sizeof(size1));
	setsockopt(m_ListenSock, SOL_SOCKET, SO_SNDBUF, (char*)&size2, sizeof(size2));

	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::AddSocketInfo(SOCKET sock, long NetEvent)
{
	int retval;

	SOCKETINFO* ptr = new SOCKETINFO;   // �߰��� ������ ������ ���� ����ü
	if (ptr == NULL) {
		return ERR_CODE::SOCKET_SET_FAIL;
	}

	WSAEVENT hEvent = WSACreateEvent(); // WSAEventSelect ���� �̺�Ʈ ��ü�� ���� ��Ʈ��ũ �̺�Ʈ�� �����Ѵ�.
										// ���� ������ ���� �� ������ �ش� ���Ͽ� �´� �̺�Ʈ ��ü�� ������ ¦�� �����־�� �Ѵ�.
										// �Ŀ� WSAEventSelect()�� �� �̺�Ʈ ��ü�� �����Ͽ� ��Ʈ��ũ �̺�Ʈ�� �߻��� �����Ѵ�.
	if (hEvent == WSA_INVALID_EVENT) {
		return ERR_CODE::SOCKET_SET_FAIL;
	}

	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	ptr->sendready = false;
	ZeroMemory(ptr->buf, BUFSIZE + 1);

	SocketInfoArray[m_totalSocket] = ptr;
	EventArray[m_totalSocket] = hEvent;
	++m_totalSocket;

	retval = WSAEventSelect(
		sock,                        // ��Ʈ��ũ �̺�Ʈ�� ó���ϰ��� �ϴ� ����
		EventArray[m_totalSocket - 1],      // ���ϰ� ¦�� ���� �̺�Ʈ ��ü�� �ڵ�
		NetEvent                // ���� �ִ� ��Ʈ��ũ �̺�Ʈ�� ��Ʈ ����ũ
	);

	if (retval == SOCKET_ERROR) return ERR_CODE::EVENTSELECT_FAIL;


	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::RemoveSocketInfo(int nIndex)
{
	SOCKETINFO* ptr = SocketInfoArray[nIndex];

	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);

	shutdown(ptr->sock, 2);
	closesocket(ptr->sock);
	delete ptr;
	WSACloseEvent(EventArray[nIndex]);

	if (nIndex != (m_totalSocket - 1)) {
		SocketInfoArray[nIndex] = SocketInfoArray[m_totalSocket - 1];
		EventArray[nIndex] = EventArray[m_totalSocket - 1];
	}
	--m_totalSocket;

	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::Select()
{
	return ERR_CODE::ISOK;

}

ERR_CODE ESNetwork::EventSelect()
{
	index = WSAWaitForMultipleEvents(   // �̺�Ʈ ��ü �ڵ��� ���� �迭�� �־� �����ؾ� �Ѵ�
		m_totalSocket,              // �迭 ������ ����
		EventArray,                 // �迭�� ���� �ּ�
		FALSE,                      // TRUE��� ��� �̺�Ʈ ��ü�� ��ȣ���°� �� ������ ����Ѵ�. FALSE��� �̺�Ʈ ��ü�� �ϳ��� ��ȣ ���°� �Ǵ� ��� �����Ѵ�
		10,               // �и��� ������ �Լ� ���ð��̴�
		FALSE
	);

	if (index == WSA_WAIT_TIMEOUT)
	{
		//m_pLogger->Write(LOG_TYPE::L_INFO, " no event");
		return ERR_CODE::ES_NO_EVENT;
	}

	if (index == WSA_WAIT_FAILED)
	{
		return ERR_CODE::EVENTSELECT_FAIL;
	}

	index -= WSA_WAIT_EVENT_0;

	int retval = WSAEnumNetworkEvents(
		SocketInfoArray[index]->sock,   // ��� ����
		EventArray[index],              // ��� ���ϰ� ¦������ �̺�Ʈ ��ü �ڵ��� �Ѱ��ָ� �̺�Ʈ ��ü�� ���ȣ ���°� �ȴ�. �̴� ���� �������� NULL�� ����� �� �ִ�
		&NetworkEvents              // �߻��� ��Ʈ��ũ �̺�Ʈ�� ���� ������ ����ȴ�
	);

	if (retval == SOCKET_ERROR) return ERR_CODE::EVENTSELECT_FAIL;

	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::Accept()
{
	if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
	{
		//err_display(NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
		return ERR_CODE::ACCEPT_API_ERROR;
	}
	SOCKET sock;
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	sock = accept(SocketInfoArray[index]->sock, (SOCKADDR*)&clientaddr, &addrlen);

	if (sock == INVALID_SOCKET)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
			return ERR_CODE::ACCEPT_WSAWOULDBLOCK;

		m_pLogger->Write(LOG_TYPE::L_WARN, "%s Client Connect Fail", __FUNCTION__);
		return ERR_CODE::ACCEPT_API_ERROR;
	}

	if (m_totalSocket >= WSA_MAXIMUM_WAIT_EVENTS)
	{
		m_pLogger->Write(LOG_TYPE::L_DEBUG, "%s Client Max Connect", __FUNCTION__);
		return ERR_CODE::MAX_CLIENT_CONNECT_COUNT;
	}

	AddSocketInfo(sock, FD_READ | FD_WRITE | FD_CLOSE);
	m_pLogger->Write(LOG_TYPE::L_INFO, "%s ACCEPT", __FUNCTION__);



	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::Receive()
{

	if (NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
	{
		//err_display(NetworkEvents.iErrorCode[FD_READ_BIT]);
		return ERR_CODE::RECV_API_ERROR;
	}

	int retval;

	SOCKETINFO* ptr = SocketInfoArray[index];

	retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);
	if (retval == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			m_pLogger->Write(LOG_TYPE::L_ERROR, "recv()");
			RemoveSocketInfo(index);
		}
		return ERR_CODE::ISOK;
	}

	ptr->recvbytes = retval;

	ptr->buf[retval] = '\0';
	int addrlen = sizeof(clientaddr);
	getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);
	m_pLogger->Write(LOG_TYPE::L_INFO, "%d [TCP/%s:%d] %s", index, inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), ptr->buf);

	memcpy_s(RecvPckt.buffer, PACKET_SIZE, ptr->buf, ptr->recvbytes);
	ptr->recvbytes = 0;
	//m_pSessionManager->RecvSession(m_RecvQueue);
	RecvPacket();

	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::Send()
{

	if (NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)
	{
		//err_display(NetworkEvents.iErrorCode[FD_READ_BIT]);
		return ERR_CODE::EVENTSELECT_FAIL;
	}
	SocketInfoArray[index]->sendready = true;

	//m_pSessionManager->SendSession(m_RecvQueue);

	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::SendAll()
{
	for (int i = 0; i < m_totalSocket; i++)
	{
		if (SocketInfoArray[i]->sendready)
		{
			int retval;

			SOCKETINFO* ptr = SocketInfoArray[i];
			if (ptr->sendbytes == ptr->recvbytes)
			{
				return ERR_CODE::ISOK;
			}

			retval = send(ptr->sock, ptr->buf + ptr->sendbytes,
				ptr->recvbytes - ptr->sendbytes, 0);

			if (retval == SOCKET_ERROR)
			{
				retval = WSAGetLastError();
				if (retval != WSAEWOULDBLOCK)
				{
					m_pLogger->Write(LOG_TYPE::L_ERROR, "send()");
					RemoveSocketInfo(i);
				}

				SocketInfoArray[i]->sendready = false;
				return ERR_CODE::ISOK;
			}

			ptr->sendbytes += retval;
			if (ptr->recvbytes == ptr->sendbytes)
			{
				ptr->recvbytes = ptr->sendbytes = 0;
			}
		}
	}
}

ERR_CODE ESNetwork::Close()
{

	if (NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
	{
		return ERR_CODE::EVENTSELECT_FAIL;
	}
	RemoveSocketInfo(index);
	m_pLogger->Write(LOG_TYPE::L_INFO, "close()");


	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::SendPacket(int id, Packet msg)
{
	//SocketInfoArray[id]->buf = msg.buffer;

	memcpy_s(SocketInfoArray[id]->buf, PACKET_SIZE, msg.buffer, sizeof(Packet));
	SocketInfoArray[id]->buf[BUFSIZE] = '\0';
	SocketInfoArray[id]->recvbytes = BUFSIZE + 1;
	SocketInfoArray[id]->sendbytes = 0;

	return ERR_CODE::ISOK;
}

ERR_CODE ESNetwork::RecvPacket()
{
	//Packet RecvPkt;
	Stream readstr;
	C2SUserInput inp;

	Stream::BufferCpyStream(readstr, RecvPckt.segment.body, (RecvPckt.head.length - PACKET_HEAD_SIZE));
	inp.decode(readstr);

	if (inp.Input == VK_SPACE)
	{
		m_pLogger->Write(LOG_TYPE::L_INFO, "INPUT KEY : SPACE");
	}

	return ERR_CODE::ISOK;
}

//ERR_CODE ESNetwork::CloseClient(unsigned int index, std::deque<PacketInfo>& queue)
//{
//	return ERR_CODE::ISOK;
//
//}

ERR_CODE ESNetwork::CloseServer()
{
	return ERR_CODE::ISOK;

}

ESNetwork::ESNetwork()
	:ITCPServer(), m_pLogger(nullptr)
{
	ZeroMemory(&m_Config, sizeof(ServerConfig));
	ZeroMemory(&m_ListenSock, sizeof(SOCKET));
	//FD_ZERO(&m_readFD);
	//FD_ZERO(&m_writeFD);

	//m_RecvQueue.clear();
}

ESNetwork::~ESNetwork()
{
	//delete m_pSessionManager;
	WSACleanup();
}

ERR_CODE ESNetwork::InitServer(ILog* pLogger)
{
	ERR_CODE error = ERR_CODE::ISOK;
	m_pLogger = pLogger;
	if (m_pLogger == nullptr)
		error = ERR_CODE::CONSOLE_LOGGER_LOAD_FAIL;

	//m_pSessionManager = new SessionManager();
	//m_pSessionManager->InitServer(m_pLogger, m_readFD);
	if (error != ERR_CODE::ISOK) return error;
	error = LoadConfig();
	m_pLogger->Write(LOG_TYPE::L_TRACE, "%s Config Load Sucess.....", __FUNCTION__);

	if (error != ERR_CODE::ISOK) return error;
	error = StartUp();
	m_pLogger->Write(LOG_TYPE::L_TRACE, "%s WinSock StartUp.....", __FUNCTION__);

	if (error != ERR_CODE::ISOK) return error;
	error = Socket();
	m_pLogger->Write(LOG_TYPE::L_TRACE, "%s Socket.....", __FUNCTION__);

	if (error != ERR_CODE::ISOK) return error;
	error = Bind();
	m_pLogger->Write(LOG_TYPE::L_TRACE, "%s Bind.....", __FUNCTION__);

	if (error != ERR_CODE::ISOK) return error;
	error = SocketOpt();
	m_pLogger->Write(LOG_TYPE::L_TRACE, "%s SetSocketOpt.....", __FUNCTION__);

	if (error != ERR_CODE::ISOK) return error;
	error = Listen();
	m_pLogger->Write(LOG_TYPE::L_TRACE, "%s Listen.....", __FUNCTION__);

	AddSocketInfo(m_ListenSock, FD_ACCEPT | FD_CLOSE);

	//FD_ZERO(&m_readFD);
	//FD_SET(m_ListenSock, &m_readFD);
	return error;
}

ERR_CODE ESNetwork::InitClient(ILog* pLogger)
{
	ERR_CODE error = ERR_CODE::ISOK;

	m_pLogger = pLogger;
	if (m_pLogger == nullptr)
		error = ERR_CODE::CONSOLE_LOGGER_LOAD_FAIL;

	//m_pSessionManager = new SessionManager();
	//m_pSessionManager->InitServer(m_pLogger, m_readFD);

	if (error != ERR_CODE::ISOK) return error;
	error = StartUp();
	m_pLogger->Write(LOG_TYPE::L_TRACE, "%s WinSock StartUp.....", __FUNCTION__);

	if (error != ERR_CODE::ISOK) return error;
	error = Socket();
	m_pLogger->Write(LOG_TYPE::L_TRACE, "%s Socket.....", __FUNCTION__);

	if (error != ERR_CODE::ISOK) return error;
	error = Connect();
	m_pLogger->Write(LOG_TYPE::L_TRACE, "%s Connect.....", __FUNCTION__);

	if (error != ERR_CODE::ISOK) return error;
	error = SocketOpt();
	m_pLogger->Write(LOG_TYPE::L_TRACE, "%s SetSocketOpt.....", __FUNCTION__);


	AddSocketInfo(m_ListenSock, FD_READ | FD_WRITE | FD_CLOSE);
	//FD_ZERO(&m_readFD);
	//FD_SET(m_ListenSock, &m_readFD);
	return error;
}

ERR_CODE ESNetwork::ServerRun()
{
	ERR_CODE er;
	er = EventSelect();
	if (er == ERR_CODE::ISOK)
	{
		switch (NetworkEvents.lNetworkEvents)
		{
		case FD_ACCEPT:
			er = Accept();
			break;
		case FD_READ:
			er = Receive();
			break;
		case FD_CLOSE:
			er = Close();
			break;
		case FD_WRITE:
			er = Send();
			break;
		}

		if (er != ERR_CODE::ISOK)
		{
			return er;
		}
	}
	else if (er != ERR_CODE::ES_NO_EVENT)
	{
		return er;
	}

	er = SendAll();

	return er;
}

ERR_CODE ESNetwork::ClientRun()
{
	ERR_CODE er;
	er = EventSelect();
	if (er == ERR_CODE::ISOK)
	{
		switch (NetworkEvents.lNetworkEvents)
		{
		case FD_READ:
			Receive();
			break;
		case FD_CLOSE:
			Close();
			break;
		case FD_WRITE:
			Send();
			break;
		}

		if (er != ERR_CODE::ISOK)
		{
			return er;
		}
	}
	else if (er != ERR_CODE::ES_NO_EVENT)
	{
		return er;
	}

	er = SendAll();


	return er;
}

ERR_CODE ESNetwork::CleanUp()
{
	return ERR_CODE::ISOK;
}

//PacketInfo ESNetwork::GetPacket()
//{
//	if (!m_RecvQueue.empty())
//	{
//		auto info = m_RecvQueue.front();
//		m_RecvQueue.pop_front();
//		return info;
//	}
//	return PacketInfo();
//}
