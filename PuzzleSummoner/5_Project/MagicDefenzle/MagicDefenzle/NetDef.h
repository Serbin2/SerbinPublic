//#ifndef _NET_DEF_H
//#define _NET_DEF_H
//
#pragma once


/*
소켓통신에서 사용할 타입들을 정의한 헤더파일
*/

//루프백아이피
#define LOOPBACKIP "127.0.0.1"
//통신에 사용할 포트
#define SERVERPORT 8080
//통신에 사용할 버퍼의 크기
#define BUFSIZE 512

//통신패킷의 프로토콜
typedef enum _PROTOCOL
{
	NP_DATA,
	NP_DISCONNECT,
}PROTOCOL;

//소켓 구조체
typedef struct _C_SOCKET
{
	SOCKET sock;
	SOCKADDR_IN addr;
	char sendBuf[BUFSIZE];
	char recvBuf[BUFSIZE];
}C_SOCKET;

//패킷 구조체가 같은 크기로 바이트정렬되도록 합니다.
#pragma pack(4)
//패킷 구조체의 예제
typedef struct _defaultPacket
{
	int value;
}defaultPacket;

//사용자 정의 recv함수
//len의 크기만큼 recv를 계속합니다.
int recvn(SOCKET s, char* buf, int len, int flags);
//패킷을 recv하는 함수
BOOL packetRecv(SOCKET _sock, char* _buf);
//패킷에서 프로토콜을 가져오는 함수
PROTOCOL GetProtocol(char* _buf);
//패킷을 만드는 함수
int PackPacket(char* packet, PROTOCOL _protocol, void* data, int cbData);
//패킷을 분리하는 함수
int unPackPacket(char* packet, void* data);

//#endif // !_NET_DEF