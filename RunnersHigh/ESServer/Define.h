#pragma once

#include <WinSock2.h>
#include<stdlib.h>
#include<stdio.h> 
#include <WS2tcpip.h>

//const char* DEFAULT_SERVER_IP = "127.0.0.1";
const short DEFAULT_SERVER_PORT = 2610;

/// TODO : ini setting
const unsigned int MAX_CLIENT_COUNT = 100;
const unsigned int EXTRA_CLIENT_COUNT = 30;

// �� ���ۻ���� �ۼ��� ���ۺ��� ũ�Ը����? 2�� �� Ŀ���ٵ�.
const unsigned int MAX_SOCKOPT_SEND_BUFSIZE = 10240;
const unsigned int MAX_SOCKOPT_RECV_BUFSIZE = 10240;

// �ִ� 3���� ��Ŷ�� ���� �� �ֵ��� ������ ����� �����. -- �ۼ��� ������ ������ ������� ���ϱ�?
const int MAX_SEND_BUF_SIZE = 8192;
const int MAX_RECV_BUF_SIZE = 8192;

const unsigned int MAX_IP_SIZE = 32;

const int PACKET_HEAD_SIZE = 4;
const int PACKET_SIZE = 1024;

const unsigned int MAX_STREAM_SIZE = 8192;

// ���� ���ε� �ϴµ� �ʿ��� ������.
#pragma pack(push, 1)
struct ServerConfig
{
	char IP[MAX_IP_SIZE];
	short PORT;
};
#pragma pack(pop)


/// ������� process define

const unsigned int MAX_USER_COUNT = MAX_CLIENT_COUNT;
