
#define _WINSOCKAPI_
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "../Debug/InputControl.lib")
#pragma comment (lib, "../Debug/ESServer.lib")

#include "../InputControl/DInputControl.h"
#include "../InputControl/Timer.h"
#include "../ESServer/ESNetwork.h"
#include "../ESServer/CLogger.h"
#include "Process.h"
#include <iostream>
//#include <Windows.h>

int main()
{
	ITCPServer* pNet = new ESNetwork();
	ILog* pLogger = new ConsoleLogger();
	//Process* pProcess = new Process(pNet, pLogger);
	DInputControl* pInput = new DInputControl();
	Timer* pTimer = new Timer();

	//long long tim;

	if (pNet->InitClient(pLogger) != ERR_CODE::ISOK)
	{
		return -1;
	}

	while (1)
	{
		pTimer->calcFPS();
		pInput->diCheckInput();
		pNet->ClientRun();

		if (pInput->GetKeyState(VK_SPACE) == eKeyState::KEYDOWN)
		{
			Packet _SendPkt;
			Stream _SendStream;
			C2SUserInput _body;

			_body.userID = 1;
			_body.Input = VK_SPACE;
			_body.KeyState = eKeyState::KEYDOWN;

			_body.encode(_SendStream);

			_SendPkt.head.id = static_cast<int>(PACKET_ID::C2S_PLAYER_INPUT);
			_SendPkt.head.length = _SendStream.size() + PACKET_HEAD_SIZE;

			Stream::StreamCpyBuffer(_SendStream, _SendPkt.segment.body);

			pNet->SendPacket(0, _SendPkt);
		}

		if (pInput->GetKeyState(VK_ESCAPE) == eKeyState::KEYDOWN)
		{
			break;
		}
	}

	//delete pProcess;
	delete pLogger;
	delete pNet;
	delete pInput;

	return 0;

}