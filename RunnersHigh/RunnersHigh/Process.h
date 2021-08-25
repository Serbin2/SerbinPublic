#pragma once

#pragma comment(lib, "../Debug/ESServer.lib")
#pragma comment(lib, "../Debug/InputControl.lib")

#include "../ESServer/ES_ERR.h"
#include "../ESServer/Define.h"
#include "../ESServer/ILogger.h"
#include "../ESServer/Clock.h"
#include "../ESServer/ITCPServer.h"
#include "../InputControl/Timer.h"


const int NONE_CONNECT = -1;

class Process
{
private:
	ITCPServer* m_pNet;
	ILog* m_pLogger;

	Timer* m_pTimer;

	std::vector<int> m_ConnectionPool;
	unsigned int m_ConnectionCount;




	void Update(float dTime);

public:
	Process(ITCPServer* pNet, ILog* pLog);
	~Process();

	void Run();





};

