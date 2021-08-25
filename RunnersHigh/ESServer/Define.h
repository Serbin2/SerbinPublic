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

// 왜 버퍼사이즈를 송수신 버퍼보다 크게만들까? 2배 더 커질텐데.
const unsigned int MAX_SOCKOPT_SEND_BUFSIZE = 10240;
const unsigned int MAX_SOCKOPT_RECV_BUFSIZE = 10240;

// 최대 3개의 패킷을 받을 수 있도록 버퍼의 사이즈를 만든다. -- 송수신 버퍼의 적절한 사이즈는 얼마일까?
const int MAX_SEND_BUF_SIZE = 8192;
const int MAX_RECV_BUF_SIZE = 8192;

const unsigned int MAX_IP_SIZE = 32;

const int PACKET_HEAD_SIZE = 4;
const int PACKET_SIZE = 1024;

const unsigned int MAX_STREAM_SIZE = 8192;

// 서버 바인딩 하는데 필요한 데이터.
#pragma pack(push, 1)
struct ServerConfig
{
	char IP[MAX_IP_SIZE];
	short PORT;
};
#pragma pack(pop)


/// 여기부터 process define

const unsigned int MAX_USER_COUNT = MAX_CLIENT_COUNT;
