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

	SOCKETINFO* ptr = new SOCKETINFO;   // 추가할 소켓의 정보를 담을 구조체
	if (ptr == NULL) {
		return ERR_CODE::SOCKET_SET_FAIL;
	}

	WSAEVENT hEvent = WSACreateEvent(); // WSAEventSelect 모델은 이벤트 객체를 통해 네트워크 이벤트를 관리한다.
										// 따라서 소켓을 생성 할 때마다 해당 소켓에 맞는 이벤트 객체를 생성해 짝을 지어주어야 한다.
										// 후에 WSAEventSelect()는 이 이벤트 객체를 관찰하여 네트워크 이벤트의 발생을 감지한다.
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
		sock,                        // 네트워크 이벤트를 처리하고자 하는 소켓
		EventArray[m_totalSocket - 1],      // 소켓과 짝을 짓는 이벤트 객체의 핸들
		NetEvent                // 관심 있는 네트워크 이벤트의 비트 마스크
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
	index = WSAWaitForMultipleEvents(   // 이벤트 객체 핸들을 전부 배열에 넣어 전달해야 한다
		m_totalSocket,              // 배열 원소의 개수
		EventArray,                 // 배열의 시작 주소
		FALSE,                      // TRUE라면 모든 이벤트 객체가 신호상태가 될 때까지 대기한다. FALSE라면 이벤트 객체중 하나가 신호 상태가 되는 즉시 리턴한다
		10,               // 밀리초 단위의 함수 대기시간이다
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
		SocketInfoArray[index]->sock,   // 대상 소켓
		EventArray[index],              // 대상 소켓과 짝지어진 이벤트 객체 핸들을 넘겨주면 이벤트 객체가 비신호 상태가 된다. 이는 선택 사항으로 NULL을 사용할 수 있다
		&NetworkEvents              // 발생한 네트워크 이벤트와 오류 정보가 저장된다
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
