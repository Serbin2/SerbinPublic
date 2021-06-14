//#ifndef _NETWORK_H
//#define _NETWORK_H
#pragma once

/*
��������� ����ϴ� ���
*/

zzOneMonster data;
zzOneStage multiMonsterQue;
BOOL m_GameStarted;

//recv������ �ڵ�
HANDLE hRecvThread;
//send������ �ڵ�
HANDLE hSendThread;
//send�������� �����̺�Ʈ
HANDLE sendStartEvent;
//send�������� �۾��ϷḦ �˸��� �̺�Ʈ
HANDLE sendCompleteEvent;
//send�����忡�� ����� ��������
PROTOCOL sendProtocol;
//��������
C_SOCKET listenSock;
//��ſ� ����� ���ϱ���ü
C_SOCKET sock;
//recv�����尡 �۾��� �ؾ��ϴ��� ��Ÿ���� ����
BOOL bRecvThreadisWork;
//send�����尡 �۾��� �ؾ��ϴ��� ��Ÿ���� ����
BOOL bSendThreadisWork;

//��Ʈ��ũ dll �ʱ�ȭ
BOOL netStart();
//��Ʈ��ũ dll ����
void netEnd();
//send�����忡 ���� ��Ű�� �Լ�
void netSend(PROTOCOL protocol);
//���� ��ŸƮ
BOOL startServer();
//Ŭ�� ��ŸƮ
BOOL startClient(const char* ip);
//���� ��Ʈ��ŷ ����
void endServer();
//Ŭ�� ��Ʈ��ŷ ����
void endClient();

//���� Ŭ���̾�Ʈ�� server�� �۵��� ���, recv�������� �ݹ��Լ�
UINT WINAPI recvServerProc(PVOID arg);
//���� Ŭ���̾�Ʈ�� client�� �۵��� ���, recv�������� �ݹ��Լ�
UINT WINAPI recvClientProc(PVOID arg);
//send�������� �ݹ��Լ�
UINT WINAPI sendProc(PVOID arg);

//#endif // !_NETWORK_H