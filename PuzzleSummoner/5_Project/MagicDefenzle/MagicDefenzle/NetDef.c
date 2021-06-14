#include "stdafx.h"
#include "NetDef.h"

int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0) {
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;
		left -= received;
		ptr += received;
	}

	return (len - left);
}

BOOL packetRecv(SOCKET _sock, char* _buf)
{
	int size;
	int retval = recvn(_sock, (char*)& size, sizeof(int), 0);
	if (retval == SOCKET_ERROR)
	{
		logDebug("size recv() Error");
		return FALSE;
	}
	else if (retval == 0)
	{
		return FALSE;
	}

	retval = recvn(_sock, _buf, size, 0);
	if (retval == SOCKET_ERROR)
	{
		logDebug("recv() Error");
		return FALSE;
	}
	else if (retval == 0)
	{
		return FALSE;
	}
	return TRUE;
}

PROTOCOL GetProtocol(char* _buf)
{
	PROTOCOL protocol;
	memcpy(&protocol, _buf, sizeof(PROTOCOL));

	return protocol;
}

int PackPacket(char* packet, PROTOCOL _protocol, void* data, int cbData)
{
	int size = 0;

	char* ptr = packet;
	ptr = ptr + sizeof(size);

	memcpy(ptr, &_protocol, sizeof(_protocol));
	ptr = ptr + sizeof(_protocol);
	size = size + sizeof(_protocol);

	memcpy(ptr, &cbData, sizeof(cbData));
	ptr = ptr + sizeof(cbData);
	size = size + sizeof(cbData);

	memcpy(ptr, data, cbData);
	ptr = ptr + cbData;
	size = size + cbData;

	ptr = packet;
	memcpy(ptr, &size, sizeof(size));

	size = size + sizeof(size);

	return size;
}

int unPackPacket(char* packet, void* data)
{
	int cbData = 0;
	char* ptr = packet;

	ptr = ptr + sizeof(PROTOCOL);

	memcpy(&cbData, ptr, sizeof(cbData));
	ptr = ptr + sizeof(cbData);

	memcpy(data, ptr, cbData);
	ptr = ptr + cbData;

	return cbData;
}