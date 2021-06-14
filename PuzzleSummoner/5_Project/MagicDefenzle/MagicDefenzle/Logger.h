//#ifndef _LOGGER_H
//#define _LOGGER_H

#pragma once


/*
�α׸� ����ϴ� ���
*/

//�α׷� ���� ���ڿ��� �ִ�ũ��
#define MAXLOGSTRING 128
//�α׿� ���� Ÿ�ӽ��������ڿ��� �ִ����
#define MAXTIMESTAMPSTRING 30

//�α׸� �⏋�Ҷ� ����� ���� �ڵ�
HANDLE hLogFile;
//�α׸� ����Ҷ� ����� ũ��Ƽ�� ����
CRITICAL_SECTION csLogger;

//�Լ��̸��� createLogger���� �ұ� �ϴٰ� startLogger���� ����
//�α��� �����Ҷ� ȣ���ؾ��ϴ� �Լ�
BOOL startLogger(BOOL isTimestampFileName);
//�α��� ������ ȣ���ؾ��ϴ� �Լ�
void endLogger();
//����� â�� ����� ���� �α׸� ����ϴ� �Լ�
void logDebugComment(const TCHAR* format, ...);
//����� â�� Ÿ�ӽ������� ����ϴ� �Լ�
void logDebugTimestamp();
//����� â�� �α׸� ����ϴ� �Լ�
void logDebug(const TCHAR* format, ...);
//����� â�� ������ ���� �޽����� ����ϴ� �Լ�
void logDebugErrorMsg();
//����� â�� ������ ���� �޽����� ����ϴ� �Լ�
void logDebugError(const TCHAR* format, ...);
//����� â�� ���� ��� ���� �޽����� ����ϴ� �Լ�
void logDebugSockErrorMsg();
//����� â�� ���� ��� ���� �޽����� ����ϴ� �Լ�
void logDebugSockError(const TCHAR* format, ...);
//�α����Ͽ� Ÿ�ӽ������� ����ϴ� �Լ�
void logFileTimestamp();
//�α����Ͽ��� �����ϴ� �Լ�
void logFileEndLine();
//�α����Ͽ� �α׸� ����ϴ� �Լ�
BOOL logFile(const TCHAR* format, ...);
//�α����Ͽ� ������ ���� �޽����� ����ϴ� �Լ�
BOOL logFileErrorMsg();
//�α����Ͽ� ������ ���� �޽����� ����ϴ� �Լ�
BOOL logFileError(const TCHAR* format, ...);
//�α����Ͽ� ���� ��� ���� �޽����� ����ϴ� �Լ�
BOOL logFileSockErrorMsg();
//�α����Ͽ� ���� ��� ���� �޽����� ����ϴ� �Լ�
BOOL logFileSockError(const TCHAR* format, ...);
//����׿� �α׸� �޽����ڽ��� �����ִ� �Լ�
void debugMsgbox(const TCHAR* format, ...);
//������ ���� �޽����� �޽����ڽ��� �����ִ� �Լ�
void errorMsgbox(char* msg);
//������ ���� ��� ���� �޽����� �޽����ڽ��� �����ִ� �Լ�
void sockErrorMsgbox(char* msg);
//�����â�� MCI ���� �޽����� ����ϴ� �Լ�
void logDebugMCIError(DWORD error, const TCHAR* format, ...);
//�α����Ͽ� MCI �����޽����� ����ϴ� �Լ�
BOOL logFileMCIError(DWORD error, const TCHAR* format, ...);

//#endif // !_LOGGER_H