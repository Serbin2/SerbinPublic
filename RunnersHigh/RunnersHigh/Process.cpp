#include "Process.h"

void Process::Update(float dTime)
{

}

Process::Process(ITCPServer* pNet, ILog* pLog) : m_pNet(pNet), m_pLogger(pLog), m_ConnectionCount(0)
{
	m_pTimer = new Timer();

	m_ConnectionPool.clear();
	m_ConnectionPool.reserve(MAX_CLIENT_COUNT);

	for (int i = 0; i < MAX_CLIENT_COUNT; i++)
	{
		m_ConnectionPool.push_back(NONE_CONNECT);
	}
}

Process::~Process()
{
	m_ConnectionPool.clear();

}

void Process::Run()
{
	m_pTimer->calcFPS();

	Update(m_pTimer->TimerDeltaTime());
}
