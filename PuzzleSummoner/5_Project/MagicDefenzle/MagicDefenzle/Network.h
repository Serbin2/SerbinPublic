//#ifndef _NETWORK_H
//#define _NETWORK_H
#pragma once

/*
소켓통신을 담당하는 헤더
*/

zzOneMonster data;
zzOneStage multiMonsterQue;
BOOL m_GameStarted;

//recv스레드 핸들
HANDLE hRecvThread;
//send스레드 핸들
HANDLE hSendThread;
//send스레드의 시작이벤트
HANDLE sendStartEvent;
//send스레드의 작업완료를 알리는 이벤트
HANDLE sendCompleteEvent;
//send스레드에서 사용할 프로토콜
PROTOCOL sendProtocol;
//리슨소켓
C_SOCKET listenSock;
//통신에 사용할 소켓구조체
C_SOCKET sock;
//recv스레드가 작업을 해야하는지 나타내는 변수
BOOL bRecvThreadisWork;
//send스레드가 작업을 해야하는지 나타내는 변수
BOOL bSendThreadisWork;

//네트워크 dll 초기화
BOOL netStart();
//네트워크 dll 해제
void netEnd();
//send스레드에 일을 시키는 함수
void netSend(PROTOCOL protocol);
//서버 스타트
BOOL startServer();
//클라 스타트
BOOL startClient(const char* ip);
//서버 네트워킹 종료
void endServer();
//클라 네트워킹 종료
void endClient();

//현제 클라이언트가 server로 작동할 경우, recv스레드의 콜백함수
UINT WINAPI recvServerProc(PVOID arg);
//현제 클라이언트가 client로 작동혈 경우, recv스레드의 콜백함수
UINT WINAPI recvClientProc(PVOID arg);
//send스레드의 콜백함수
UINT WINAPI sendProc(PVOID arg);

//#endif // !_NETWORK_H