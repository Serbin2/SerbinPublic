#include "stdafx.h"
#include "Logger.h"

BOOL startLogger(BOOL isTimestampFileName)
{
	InitializeCriticalSection(&csLogger);

	TCHAR* logFileName = (TCHAR*)malloc(sizeof(TCHAR) * MAXLOGSTRING);
	if (logFileName == NULL)
	{
		logDebug("logFileName malloc() FAIL");
		return FALSE;
	}

	if (isTimestampFileName)
	{
		time_t now = time(NULL);
		struct tm t;

		gmtime_s(&t, &now);
		localtime_s(&t, &now);
		strftime(logFileName, MAXLOGSTRING, "[%F %H%M%S] ", &t);
		StringCbCat(logFileName, MAXLOGSTRING, "log.txt");
	}
	else
	{
		StringCbPrintf(logFileName, MAXLOGSTRING, "log.txt");
	}

	hLogFile = CreateFile(logFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (hLogFile == INVALID_HANDLE_VALUE)
	{
		logDebugError("startLogger()");
		return FALSE;
	}

	free(logFileName);
	return TRUE;
}

void endLogger()
{
	DeleteCriticalSection(&csLogger);
	CloseHandle(hLogFile);
}

void logDebugComment(const TCHAR* format, ...)
{
	EnterCriticalSection(&csLogger);

	va_list List;
	va_start(List, format);

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXLOGSTRING);
	if (log == NULL)
	{
		OutputDebugString("logDebugComment() malloc() FAIL\n");
	}
	else
	{
		StringCbVPrintf(log, MAXLOGSTRING, format, List);

		OutputDebugString(log);

		free(log);
	}

	va_end(List);
	LeaveCriticalSection(&csLogger);
}

void logDebugTimestamp()
{
	EnterCriticalSection(&csLogger);

	time_t now = time(NULL);
	struct tm t;

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXTIMESTAMPSTRING);
	if (log == NULL)
	{
		OutputDebugString("logDebugTimestamp() malloc() FAIL\n");
	}
	else
	{
		gmtime_s(&t, &now);
		strftime(log, MAXTIMESTAMPSTRING, "[%Y-%m-%d %X] ", &t);

		OutputDebugString(log);

		free(log);
	}

	LeaveCriticalSection(&csLogger);
}

void logDebug(const TCHAR* format, ...)
{
	EnterCriticalSection(&csLogger);

	va_list List;
	va_start(List, format);

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXLOGSTRING);
	if (log == NULL)
	{
		OutputDebugString("logDebug() malloc() FAIL");
	}
	else
	{
		StringCbVPrintf(log, MAXLOGSTRING, format, List);

		logDebugTimestamp();
		OutputDebugString(log);
		OutputDebugString("\n");

		free(log);
	}
	va_end(List);

	LeaveCriticalSection(&csLogger);
}

void logDebugErrorMsg()
{
	EnterCriticalSection(&csLogger);

	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	OutputDebugString(lpMsgBuf);
	LocalFree(lpMsgBuf);

	LeaveCriticalSection(&csLogger);
}

void logDebugError(const TCHAR* format, ...)
{
	EnterCriticalSection(&csLogger);

	va_list List;
	va_start(List, format);

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXLOGSTRING);
	if (log == NULL)
	{
		OutputDebugString("logDebugError() malloc() FAIL");
	}
	else
	{
		StringCbVPrintf(log, MAXLOGSTRING, format, List);
		StringCbCat(log, MAXLOGSTRING, " : ");

		logDebugTimestamp();
		OutputDebugString(log);
		logDebugErrorMsg();
		OutputDebugString("\n");

		free(log);
	}
	va_end(List);

	LeaveCriticalSection(&csLogger);
}

void logDebugSockErrorMsg()
{
	EnterCriticalSection(&csLogger);

	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	OutputDebugString(lpMsgBuf);
	LocalFree(lpMsgBuf);

	LeaveCriticalSection(&csLogger);
}

void logDebugSockError(const TCHAR* format, ...)
{
	EnterCriticalSection(&csLogger);

	va_list List;
	va_start(List, format);

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXLOGSTRING);
	if (log == NULL)
	{
		OutputDebugString("logDebugSockError() malloc() FAIL");
	}
	else
	{
		StringCbVPrintf(log, MAXLOGSTRING, format, List);
		StringCbCat(log, MAXLOGSTRING, " : ");

		logDebugTimestamp();
		OutputDebugString(log);
		logDebugSockErrorMsg();
		OutputDebugString("\n");

		free(log);
	}
	va_end(List);

	LeaveCriticalSection(&csLogger);
}

void logFileTimestamp()
{
	EnterCriticalSection(&csLogger);

	time_t now = time(NULL);
	struct tm t;
	int len = 0;

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXTIMESTAMPSTRING);
	if (log == NULL)
	{
		logDebug("logFileTimestamp() malloc() FAIL");
	}
	else
	{
		gmtime_s(&t, &now);
		strftime(log, MAXTIMESTAMPSTRING, "[%Y-%m-%d %X] ", &t);
		StringCbLength(log, MAXTIMESTAMPSTRING, &len);

		if (WriteFile(hLogFile, log, len, NULL, NULL) == FALSE)
		{
			logDebugError("logFileTimestamp()");
		}
		free(log);
	}

	LeaveCriticalSection(&csLogger);
}

void logFileEndLine()
{
	EnterCriticalSection(&csLogger);

	if (WriteFile(hLogFile, "\r\n", 3, NULL, NULL) == FALSE)
	{
		logDebugError("logFileEndLine()");
	}

	LeaveCriticalSection(&csLogger);
}

BOOL logFile(const TCHAR* format, ...)
{
	EnterCriticalSection(&csLogger);

	va_list List;
	va_start(List, format);
	int len = 0;

	if (hLogFile == INVALID_HANDLE_VALUE)
	{
		va_end(List);

		LeaveCriticalSection(&csLogger);
		return FALSE;
	}

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXLOGSTRING);
	if (log == NULL)
	{
		logDebug("logFile() malloc() Fail");
		va_end(List);

		LeaveCriticalSection(&csLogger);
		return FALSE;
	}
	else
	{
		StringCbVPrintf(log, MAXLOGSTRING, format, List);
		StringCbLength(log, MAXLOGSTRING, &len);

		logFileTimestamp();
		if (WriteFile(hLogFile, log, len, NULL, NULL) == FALSE)
		{
			free(log);
			va_end(List);
			logDebugError("logFile()");

			LeaveCriticalSection(&csLogger);
			return FALSE;
		}
		logFileEndLine();
	}

	free(log);
	va_end(List);

	LeaveCriticalSection(&csLogger);
	return TRUE;
}

BOOL logFileErrorMsg()
{
	EnterCriticalSection(&csLogger);

	LPVOID lpMsgBuf;
	int len = 0;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	StringCbLength(lpMsgBuf, MAXLOGSTRING, &len);

	if (WriteFile(hLogFile, lpMsgBuf, len, NULL, NULL) == FALSE)
	{
		LocalFree(lpMsgBuf);
		logDebugError("logFileErrorMsg()");

		LeaveCriticalSection(&csLogger);
		return FALSE;
	}
	LocalFree(lpMsgBuf);

	LeaveCriticalSection(&csLogger);
	return TRUE;
}

BOOL logFileError(const TCHAR* format, ...)
{
	EnterCriticalSection(&csLogger);

	va_list List;
	va_start(List, format);
	int len = 0;

	if (hLogFile == INVALID_HANDLE_VALUE)
	{
		va_end(List);

		LeaveCriticalSection(&csLogger);
		return FALSE;
	}

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXLOGSTRING);
	if (log == NULL)
	{
		logDebug("logFileError() malloc() FAIL");
		va_end(List);

		LeaveCriticalSection(&csLogger);
		return FALSE;
	}
	else
	{
		StringCbVPrintf(log, MAXLOGSTRING, format, List);
		StringCbCat(log, MAXLOGSTRING, " : ");
		StringCbLength(log, MAXLOGSTRING, &len);

		logFileTimestamp();
		if (WriteFile(hLogFile, log, len, NULL, NULL) == FALSE)
		{
			logDebugError("logFileError()");

			LeaveCriticalSection(&csLogger);
			return FALSE;
		}
		logFileErrorMsg();
		logFileEndLine();
	}
	va_end(List);

	LeaveCriticalSection(&csLogger);
	return TRUE;
}

BOOL logFileSockErrorMsg()
{
	EnterCriticalSection(&csLogger);

	LPVOID lpMsgBuf;
	int len = 0;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	StringCbLength(lpMsgBuf, MAXLOGSTRING, &len);

	if (WriteFile(hLogFile, log, len, NULL, NULL) == FALSE)
	{
		LocalFree(lpMsgBuf);
		logDebugError("logFileSockErrorMsg()");

		LeaveCriticalSection(&csLogger);
		return FALSE;
	}
	LocalFree(lpMsgBuf);

	LeaveCriticalSection(&csLogger);
	return TRUE;
}

BOOL logFileSockError(const TCHAR* format, ...)
{
	EnterCriticalSection(&csLogger);

	va_list List;
	va_start(List, format);
	int len = 0;

	if (hLogFile == INVALID_HANDLE_VALUE)
	{
		va_end(List);

		LeaveCriticalSection(&csLogger);
		return FALSE;
	}

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXLOGSTRING);
	if (log == NULL)
	{
		logDebug("logFileError() malloc() FAIL");
		va_end(List);

		LeaveCriticalSection(&csLogger);
		return FALSE;
	}
	else
	{
		StringCbVPrintf(log, MAXLOGSTRING, format, List);
		StringCbCat(log, MAXLOGSTRING, " : ");
		StringCbLength(log, MAXLOGSTRING, &len);

		logFileTimestamp();
		if (WriteFile(hLogFile, log, len, NULL, NULL) == FALSE)
		{
			logDebugError("logFileError()");

			LeaveCriticalSection(&csLogger);
			return FALSE;
		}
		logFileSockErrorMsg();
		logFileEndLine();
	}
	va_end(List);

	LeaveCriticalSection(&csLogger);
	return TRUE;
}

void debugMsgbox(const TCHAR* format, ...)
{
#ifdef _DEBUG

	va_list List;
	va_start(List, format);
	TCHAR text[MAXLOGSTRING];
	TCHAR timeStamp[64];
	time_t now = time(NULL);
	struct tm t;

	gmtime_s(&t, &now);
	strftime(timeStamp, 64, "[%Y-%m-%d %X]", &t);
	StringCbVPrintf(text, MAXLOGSTRING, format, List);
	va_end(List);

	MessageBox(NULL, text, timeStamp, MB_OK);

#endif // _DEBUG
}

void errorMsgbox(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}

void sockErrorMsgbox(char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}

void logDebugMCIError(DWORD error, const TCHAR* format, ...)
{
	EnterCriticalSection(&csLogger);

	va_list List;
	va_start(List, format);

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXLOGSTRING);
	if (log == NULL)
	{
		OutputDebugString("logDebugMCIError() malloc() FAIL");
	}
	else
	{
		StringCbVPrintf(log, MAXLOGSTRING, format, List);
		StringCbCat(log, MAXLOGSTRING, " : ");

		logDebugTimestamp();
		OutputDebugString(log);
		
		mciGetErrorString(error, log, MAXLOGSTRING);
		OutputDebugString(log);
		OutputDebugString("\n");

		free(log);
	}
	va_end(List);

	LeaveCriticalSection(&csLogger);
}

BOOL logFileMCIError(DWORD error, const TCHAR* format, ...)
{
	EnterCriticalSection(&csLogger);

	va_list List;
	va_start(List, format);
	int len = 0;

	if (hLogFile == INVALID_HANDLE_VALUE)
	{
		va_end(List);

		LeaveCriticalSection(&csLogger);
		return FALSE;
	}

	TCHAR* log = (TCHAR*)malloc(sizeof(TCHAR) * MAXLOGSTRING);
	if (log == NULL)
	{
		logDebug("logFileError() malloc() FAIL");
		va_end(List);

		LeaveCriticalSection(&csLogger);
		return FALSE;
	}
	else
	{
		StringCbVPrintf(log, MAXLOGSTRING, format, List);
		StringCbCat(log, MAXLOGSTRING, " : ");
		StringCbLength(log, MAXLOGSTRING, &len);

		logFileTimestamp();
		if (WriteFile(hLogFile, log, len, NULL, NULL) == FALSE)
		{
			logDebugError("logFileError()");

			LeaveCriticalSection(&csLogger);
			return FALSE;
		}

		mciGetErrorString(error, log, MAXLOGSTRING);
		StringCbLength(log, MAXLOGSTRING, &len);
		if (WriteFile(hLogFile, log, len, NULL, NULL) == FALSE)
		{
			logDebugError("logFileError()");

			LeaveCriticalSection(&csLogger);
			return FALSE;
		}
		
		logFileEndLine();
	}
	va_end(List);

	LeaveCriticalSection(&csLogger);
	return TRUE;
}