#include "pchApp.h"
#include "GameProcess.h"
#include "../../RhythmLibary/Graphics/D2DGraphics.h"
#include "../Input/Cursor.h"


GameProcess::GameProcess()
{
}

GameProcess::~GameProcess()
{

}

void GameProcess::Initialize(HWND hwnd, HDC hdc, RECT rt)
{
	hWnd = hwnd;
	hDC = hdc;
	this->rt = rt;
}

void GameProcess::Awake()
{
	D2DGraphics::GetInstance().Initialize(hWnd, hDC);
	D2DGraphics::GetInstance().SetRenderSize(rt);
	D2DGraphics::GetInstance().CreateDeviceTarget();
	ResourceManager::GetInstance().Initialize();
	SceneManager::GetInstance().Initialize();
	GameManager::GetInstance().Initialize();
	AudioManager::GetInstance().Initialize();

	SceneManager::GetInstance().SetCurrentScene(ObjectID::SCENE_START);
	SceneManager::GetInstance().GetCurrenctScene()->Awake();
	GameFream::GetInstance().SetFPS(60.f);
}

void GameProcess::Start()
{

}

void GameProcess::OnEnable()
{
	if (IsEnable)
	{

	}
}

void GameProcess::OnCollision()
{

}

void GameProcess::OnInputEvent()
{
	//CurrentScene->OnEvent();
	SceneManager::GetInstance().GetCurrenctScene()->OnEvent();
}

void GameProcess::Update()
{
	if (SceneManager::GetInstance().GetCurrenctScene()->CheckActive())
	{
		//CurrentScene->Update();
		SceneManager::GetInstance().GetCurrenctScene()->Update();


	}
	else
	{
		//CurrentScene->Awake();
		SceneManager::GetInstance().GetCurrenctScene()->Awake();
	}
}

void GameProcess::LateUpdate()
{

}
void GameProcess::OnRender()
{
	if (GameFream::GetInstance().FreamChecker())
	{
		D2DGraphics::GetInstance().BeginDraw();
		SceneManager::GetInstance().GetCurrenctScene()->OnRender();
		SceneManager::GetInstance().GetCurrenctScene()->RenderObject(1);
		SceneManager::GetInstance().GetCurrenctScene()->RenderObject(2);
		SceneManager::GetInstance().GetCurrenctScene()->RenderObject(3);
		SceneManager::GetInstance().GetCurrenctScene()->RenderObject(4);
		D2DGraphics::GetInstance().EndDraw();
	}
}

void GameProcess::OnApplicationPause()
{

}

void GameProcess::OnDisable()
{
	if (!IsEnable)
	{

	}
}

void GameProcess::OnDestroy()
{
}
