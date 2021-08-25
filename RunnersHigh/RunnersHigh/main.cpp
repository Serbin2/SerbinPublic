
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
	Process* pProcess = new Process(pNet, pLogger);
	DInputControl* pInput = new DInputControl();

	if (pNet->InitServer(pLogger) != ERR_CODE::ISOK)
	{
		return -1;
	}

	while (1)
	{
		pInput->diCheckInput();
		pNet->ServerRun();

		/*while (1)
		{
			PacketInfo message = pNet->GetPacket();
			if (message.session_id > MAX_CLIENT_COUNT)
				break;
			pProcess->ReadEvent(message);
		}*/
		pProcess->Run();

		if (pInput->GetKeyState(VK_ESCAPE) == eKeyState::KEYDOWN)
		{
			break;
		}
	}

	delete pProcess;
	delete pLogger;
	delete pNet;
	delete pInput;

	return 0;

}