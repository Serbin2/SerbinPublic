#include "stdafx.h"
#include "Network.h"

BOOL netStart()
{
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		logDebugSockError("WSAStartup()");
		return FALSE;
	}
	return TRUE;
}

void netEnd()
{
	WSACleanup();
}

BOOL netSocket(C_SOCKET* sock)
{
	sock->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock->sock == INVALID_SOCKET)
	{
		logDebugSockError("socket()");
		return FALSE;
	}
	return TRUE;
}

BOOL netListen(C_SOCKET* sock)
{
	ZeroMemory(&sock->addr, sizeof(SOCKADDR_IN));
	sock->addr.sin_family = AF_INET;
	sock->addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sock->addr.sin_port = htons(SERVERPORT);

	int retVal = bind(sock->sock, (SOCKADDR*)& sock->addr, sizeof(SOCKADDR_IN));
	if (retVal == SOCKET_ERROR)
	{
		logDebugSockError("bind()");
		return FALSE;
	}

	retVal = listen(sock->sock, SOMAXCONN);
	if (retVal == SOCKET_ERROR)
	{
		logDebugSockError("listen()");
		return FALSE;
	}
	return TRUE;
}

BOOL netConnect(C_SOCKET* sock, char* ip)
{
	ZeroMemory(&sock->addr, sizeof(sock->addr));

	sock->addr.sin_family = AF_INET;
	sock->addr.sin_addr.s_addr = inet_addr(ip);
	sock->addr.sin_port = htons(SERVERPORT);

	int retVal = connect(sock->sock, (SOCKADDR*)& sock->addr, sizeof(sock->addr));
	if (retVal == SOCKET_ERROR)
	{
		logDebugSockError("connect()");
		return FALSE;
	}
	return TRUE;
}

BOOL netAccept(C_SOCKET* sock)
{
	int addrlen = sizeof(SOCKADDR_IN);
	sock->sock = accept(listenSock.sock, (SOCKADDR*)& sock->addr, &addrlen);
	if (sock->sock == INVALID_SOCKET)
	{
		logDebugSockError("accept()");
		return FALSE;
	}
	return TRUE;
}

BOOL sendPacket(void* data, int cbData)
{
	int size = PackPacket(sock.sendBuf, sendProtocol, data, cbData);
	int retval = send(sock.sock, sock.sendBuf, size, 0);
	if (retval == SOCKET_ERROR)
	{
		logDebugSockError("send()");
		return FALSE;
	}
	return TRUE;
}

void netSend(PROTOCOL protocol)
{
	WaitForSingleObject(sendCompleteEvent, INFINITE);
	sendProtocol = protocol;
	SetEvent(sendStartEvent);
}

BOOL startServer()
{
	BOOL retval;
	retval = netSocket(&listenSock);
	if (retval == FALSE)
	{
		logDebugSockError("startServer() socket");
		return FALSE;
	}
	retval = netListen(&listenSock);
	if (retval == FALSE)
	{
		logDebugSockError("startServer() listen");
		return FALSE;
	}
	sendStartEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (sendStartEvent == NULL)
	{
		logDebugError("startServer() sendStartEvent");
		return FALSE;
	}
	sendCompleteEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (sendCompleteEvent == NULL)
	{
		logDebugError("startServer() sendCompleteEvent");
		return FALSE;
	}

	sendProtocol = NP_DATA;
	bRecvThreadisWork = TRUE;
	bSendThreadisWork = TRUE;

	hRecvThread = (HANDLE)_beginthreadex(NULL, 0, recvServerProc, NULL, 0, NULL);
	if (hRecvThread == INVALID_HANDLE_VALUE)
	{
		logDebugError("startServer() hRecvThread Create Fail");
		return FALSE;
	}

	hSendThread = (HANDLE)_beginthreadex(NULL, 0, sendProc, NULL, 0, NULL);
	if (hSendThread == INVALID_HANDLE_VALUE)
	{
		logDebugError("startServer() hSendThread Create Fail");
		return FALSE;
	}

	return TRUE;
}

BOOL startClient(const char* ip)
{
	BOOL retval;
	retval = netSocket(&sock);
	if (retval == FALSE)
	{
		logDebugSockError("startClient() socket");
		return FALSE;
	}

	retval = netConnect(&sock, ip);
	if (retval == FALSE)
	{
		logDebugSockError("startServer() connect");
		return FALSE;
	}
	sendStartEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (sendStartEvent == NULL)
	{
		logDebugError("startClient() sendStartEvent");
		return FALSE;
	}
	sendCompleteEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (sendCompleteEvent == NULL)
	{
		logDebugError("startClient() sendCompleteEvent");
		return FALSE;
	}
	sendProtocol = NP_DATA;

	bRecvThreadisWork = TRUE;
	bSendThreadisWork = TRUE;

	hRecvThread = (HANDLE)_beginthreadex(NULL, 0, recvClientProc, NULL, 0, NULL);
	if (hRecvThread == INVALID_HANDLE_VALUE)
	{
		logDebugError("startClient() hRecvThread Fail");
		return FALSE;
	}
	hSendThread = (HANDLE)_beginthreadex(NULL, 0, sendProc, NULL, 0, NULL);
	if (hSendThread == INVALID_HANDLE_VALUE)
	{
		logDebugError("startClient() hSendThread Fail");
		return FALSE;
	}

	return TRUE;
}

void endServer()
{
	bRecvThreadisWork = FALSE;
	bSendThreadisWork = FALSE;

	sendProtocol = NP_DISCONNECT;
	SetEvent(sendStartEvent);
	WaitForSingleObject(hRecvThread, INFINITE);
	WaitForSingleObject(sendCompleteEvent, INFINITE);

	CloseHandle(hRecvThread);
	CloseHandle(hSendThread);
	CloseHandle(sendStartEvent);
	CloseHandle(sendCompleteEvent);

	closesocket(listenSock.sock);
	closesocket(sock.sock);
}

void endClient()
{
	bRecvThreadisWork = FALSE;
	bSendThreadisWork = FALSE;

	sendProtocol = NP_DISCONNECT;
	SetEvent(sendStartEvent);
	WaitForSingleObject(hRecvThread, INFINITE);
	WaitForSingleObject(sendCompleteEvent, INFINITE);

	CloseHandle(hRecvThread);
	CloseHandle(hSendThread);
	CloseHandle(sendStartEvent);
	CloseHandle(sendCompleteEvent);

	closesocket(sock.sock);
}

UINT WINAPI recvServerProc(PVOID arg)
{
	logDebug("recvServerThread Start");

	if (netAccept(&sock))
	{
		logDebugSockError("Accepted! IP: %s PORT : %d",inet_ntoa(sock.addr.sin_addr),ntohs(sock.addr.sin_port));
	}
	//버퍼는 값받을 구조체
	zzOneMonster buffer;

	multiMonsterQue.count = 0;
	monListInit(&multiMonsterQue);

	while (bRecvThreadisWork)
	{
		if (!packetRecv(sock.sock, sock.recvBuf))
		{
			sockErrorMsgbox("disconnect");
			_endthreadex(-1);
		}
		PROTOCOL protocol = GetProtocol(sock.recvBuf);

		switch (protocol)
		{
		default:
			unPackPacket(sock.recvBuf, &buffer);
			//받은 값 처리
			/*if (buffer.spawntime == 1)
			{
				if (data.spawntime == 1)
				{
					m_GameStarted = TRUE;*/
					monListInsertLast(&multiMonsterQue, buffer);
					//monListInsert(&multiMonsterQue, multiMonsterQue.count - 1, buffer);
					/*	}
					}
					*/
			break;
		}
	}

	logDebug("recvServerThread End");
	return 0;
}

UINT WINAPI recvClientProc(PVOID arg)
{
	logDebug("recvClientThread Start");

	/*BOOL retval = netConnect(&sock, (char*)arg);
	if (retval == FALSE)
	{
		endClient();
		return FALSE;
	}*/

	//버퍼는 값받을 구조체
	zzOneMonster buffer;

	multiMonsterQue.count = 0;
	monListInit(&multiMonsterQue);

	while (bRecvThreadisWork)
	{
		if (!packetRecv(sock.sock, sock.recvBuf))
		{
			sockErrorMsgbox("disconnect");
			_endthreadex(-1);
		}
		PROTOCOL protocol = GetProtocol(sock.recvBuf);

		switch (protocol)
		{
		default:
			unPackPacket(sock.recvBuf, &buffer);
			/*if (buffer.spawntime == 1)
			{
				if (data.spawntime == 1)
				{
					m_GameStarted = TRUE;*/
					monListInsertLast(&multiMonsterQue, buffer);
					//monListInsert(&multiMonsterQue, multiMonsterQue.count - 1, buffer);

			/*	}
			}*/
			break;
		}
	}

	logDebug("recvClientThread End");
	return 0;
}

UINT WINAPI sendProc(PVOID arg)
{
	logDebug("sendThread Start");

	while (bSendThreadisWork)
	{
		WaitForSingleObject(sendStartEvent, INFINITE);

		switch (sendProtocol)
		{
		case NP_DATA:
			//버퍼에 값 쓰기
			sendPacket(&data, sizeof(data));
			break;
		}
		SetEvent(sendCompleteEvent);
	}

	logDebug("sendThread End");
	return 0;
}