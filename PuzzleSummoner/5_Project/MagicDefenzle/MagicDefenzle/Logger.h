//#ifndef _LOGGER_H
//#define _LOGGER_H

#pragma once


/*
로그를 기록하는 헤더
*/

//로그로 쓰는 문자열의 최대크기
#define MAXLOGSTRING 128
//로그에 쓰는 타임스템프문자열의 최대길이
#define MAXTIMESTAMPSTRING 30

//로그를 기룍할때 사용할 파일 핸들
HANDLE hLogFile;
//로그를 기록할때 사용할 크리티컬 섹션
CRITICAL_SECTION csLogger;

//함수이름을 createLogger으로 할까 하다가 startLogger으로 했음
//로깅을 시작할때 호출해야하는 함수
BOOL startLogger(BOOL isTimestampFileName);
//로깅을 끝낼때 호출해야하는 함수
void endLogger();
//디버그 창에 사용자 정의 로그만 기록하는 함수
void logDebugComment(const TCHAR* format, ...);
//디버그 창에 타임스탬프만 기록하는 함수
void logDebugTimestamp();
//디버그 창에 로그를 기록하는 함수
void logDebug(const TCHAR* format, ...);
//디버그 창에 윈도우 에러 메시지만 기록하는 함수
void logDebugErrorMsg();
//디버그 창에 윈도우 에러 메시지를 기록하는 함수
void logDebugError(const TCHAR* format, ...);
//디버그 창에 소켓 통신 에러 메시지만 기록하는 함수
void logDebugSockErrorMsg();
//디버그 창에 소켓 통신 에러 메시지를 기록하는 함수
void logDebugSockError(const TCHAR* format, ...);
//로그파일에 타임스탬프를 기록하는 함수
void logFileTimestamp();
//로그파일에서 개행하는 함수
void logFileEndLine();
//로그파일에 로그를 기록하는 함수
BOOL logFile(const TCHAR* format, ...);
//로그파일에 윈도우 에러 메시지만 기록하는 함수
BOOL logFileErrorMsg();
//로그파일에 윈도우 에러 메시지를 기록하는 함수
BOOL logFileError(const TCHAR* format, ...);
//로그파일에 소켓 통신 에러 메시지만 기록하는 함수
BOOL logFileSockErrorMsg();
//로그파일에 소켓 통신 에러 메시지를 기록하는 함수
BOOL logFileSockError(const TCHAR* format, ...);
//디버그용 로그를 메시지박스로 보여주는 함수
void debugMsgbox(const TCHAR* format, ...);
//윈도우 에러 메시지를 메시지박스로 보여주는 함수
void errorMsgbox(char* msg);
//윈도우 소켓 통신 에러 메시지를 메시지박스로 보여주는 함수
void sockErrorMsgbox(char* msg);
//디버그창에 MCI 에러 메시지를 기록하는 함수
void logDebugMCIError(DWORD error, const TCHAR* format, ...);
//로그파일에 MCI 에러메시지를 기록하는 함수
BOOL logFileMCIError(DWORD error, const TCHAR* format, ...);

//#endif // !_LOGGER_H