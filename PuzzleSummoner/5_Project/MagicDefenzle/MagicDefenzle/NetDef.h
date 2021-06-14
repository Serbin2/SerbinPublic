//#ifndef _NET_DEF_H
//#define _NET_DEF_H
//
#pragma once


/*
������ſ��� ����� Ÿ�Ե��� ������ �������
*/

//�����������
#define LOOPBACKIP "127.0.0.1"
//��ſ� ����� ��Ʈ
#define SERVERPORT 8080
//��ſ� ����� ������ ũ��
#define BUFSIZE 512

//�����Ŷ�� ��������
typedef enum _PROTOCOL
{
	NP_DATA,
	NP_DISCONNECT,
}PROTOCOL;

//���� ����ü
typedef struct _C_SOCKET
{
	SOCKET sock;
	SOCKADDR_IN addr;
	char sendBuf[BUFSIZE];
	char recvBuf[BUFSIZE];
}C_SOCKET;

//��Ŷ ����ü�� ���� ũ��� ����Ʈ���ĵǵ��� �մϴ�.
#pragma pack(4)
//��Ŷ ����ü�� ����
typedef struct _defaultPacket
{
	int value;
}defaultPacket;

//����� ���� recv�Լ�
//len�� ũ�⸸ŭ recv�� ����մϴ�.
int recvn(SOCKET s, char* buf, int len, int flags);
//��Ŷ�� recv�ϴ� �Լ�
BOOL packetRecv(SOCKET _sock, char* _buf);
//��Ŷ���� ���������� �������� �Լ�
PROTOCOL GetProtocol(char* _buf);
//��Ŷ�� ����� �Լ�
int PackPacket(char* packet, PROTOCOL _protocol, void* data, int cbData);
//��Ŷ�� �и��ϴ� �Լ�
int unPackPacket(char* packet, void* data);

//#endif // !_NET_DEF