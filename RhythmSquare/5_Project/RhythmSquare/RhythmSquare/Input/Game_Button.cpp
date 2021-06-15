#include "pch.h"
#include "Game_Button.h"
#include "../GameProcess/GameProcess.h"

Play_Button::Play_Button(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, unsigned int vk)
	:KeyButton(id, layer, vec, box, vk)
{
}

void Play_Button::OnRender()
{
	switch (State)
	{
	case ButtonState::RELEASE:
		break;
	case ButtonState::PRESS:
		break;
	}
}

void Play_Button::OnBtnDown()
{
	if (GameProcess::GetInstance().GamePlayer->GetScene() != SceneType::START)
		return;
	GameProcess::GetInstance().GamePlayer->SetScene(SceneType::MAINMENU);
	GameProcess::GetInstance().CurrentScene = SceneManager::GetInstance().GetScene(static_cast<unsigned int>(SceneType::MAINMENU));
}

Start_Button::Start_Button(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box)
	: BoxButton(id, layer, vec, box)
{
}

Start_Button::~Start_Button()
{
}

void Start_Button::OnRender()
{
	switch (State)
	{
	case ButtonState::PRESS:
		D2DGraphics::GetInstance().DrawRectangle(Box, D2D1::ColorF::White, true);
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, Box, L"Press");
		break;
	default:
		D2DGraphics::GetInstance().DrawRectangle(Box, D2D1::ColorF::Aqua, true);
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, Box, L"Start");
		break;
	}
}

void Start_Button::OnBtnUp()
{
	GameProcess::GetInstance().CurrentScene->Sleep();
	GameProcess::GetInstance().GamePlayer->SetScene(SceneType::INGAME);
	GameProcess::GetInstance().CurrentScene = SceneManager::GetInstance().GetScene(static_cast<unsigned int>(SceneType::INGAME));
}

Sea_Button::Sea_Button(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box)
	: BoxButton(id, layer, vec, box)
{
}

Sea_Button::~Sea_Button()
{
}

void Sea_Button::OnRender()
{
	switch (State)
	{
	case ButtonState::PRESS:
		D2DGraphics::GetInstance().DrawRectangle(Box, D2D1::ColorF::White, true);
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, Box, L"Press");
		break;
	default:
		D2DGraphics::GetInstance().DrawRectangle(Box, D2D1::ColorF::Blue, true);
		break;
	}
}

void Sea_Button::OnBtnUp()
{
	GameProcess::GetInstance().CurrentScene->Sleep();
	GameProcess::GetInstance().GamePlayer->SetScene(SceneType::MENU_CHILD_SEA);
	GameProcess::GetInstance().CurrentScene = SceneManager::GetInstance().GetScene(static_cast<unsigned int>(SceneType::MENU_CHILD_SEA));
	GameProcess::GetInstance().CurrentScene->Awake();
}

Forest_Button::Forest_Button(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box)
	: BoxButton(id, layer, vec, box)
{
}

Forest_Button::~Forest_Button()
{
}

void Forest_Button::OnRender()
{
	switch (State)
	{
	case ButtonState::PRESS:
		D2DGraphics::GetInstance().DrawRectangle(Box, D2D1::ColorF::White, true);
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, Box, L"Press");
		break;
	default:
		D2DGraphics::GetInstance().DrawRectangle(Box, D2D1::ColorF::Green, true);
		break;
	}
}

void Forest_Button::OnBtnUp()
{
	GameProcess::GetInstance().CurrentScene->Sleep();
	GameProcess::GetInstance().GamePlayer->SetScene(SceneType::MENU_CHILD_FOREST);
	GameProcess::GetInstance().CurrentScene = SceneManager::GetInstance().GetScene(static_cast<unsigned int>(SceneType::MENU_CHILD_FOREST));
	GameProcess::GetInstance().CurrentScene->Awake();
}

Option_Button::Option_Button(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box)
	: BoxButton(id, layer, vec, box)
{
}

Option_Button::~Option_Button()
{
}

void Option_Button::OnRender()
{
}

Desert_Button::Desert_Button(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box)
	: BoxButton(id, layer, vec, box)
{
}

Desert_Button::~Desert_Button()
{
}

void Desert_Button::OnRender()
{
	switch (State)
	{
	case ButtonState::PRESS:
		D2DGraphics::GetInstance().DrawRectangle(Box, D2D1::ColorF::White, true);
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, Box, L"Press");
		break;
	default:
		D2DGraphics::GetInstance().DrawRectangle(Box, D2D1::ColorF::Red, true);
		break;
	}
}

void Desert_Button::OnBtnUp()
{
	GameProcess::GetInstance().CurrentScene->Sleep();
	GameProcess::GetInstance().GamePlayer->SetScene(SceneType::MENU_CHILD_DESERT);
	GameProcess::GetInstance().CurrentScene = SceneManager::GetInstance().GetScene(static_cast<unsigned int>(SceneType::MENU_CHILD_DESERT));
	GameProcess::GetInstance().CurrentScene->Awake();
}

MyTown_Button::MyTown_Button(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box)
	: BoxButton(id, layer, vec, box)
{
}

MyTown_Button::~MyTown_Button()
{
}

void MyTown_Button::OnRender()
{
	switch (State)
	{
	case ButtonState::PRESS:
		D2DGraphics::GetInstance().DrawRectangle(Box, D2D1::ColorF::White, true);
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, Box, L"Press");
		break;
	default:
		D2DGraphics::GetInstance().DrawRectangle(Box, D2D1::ColorF::Yellow, true);
		break;
	}
}

void MyTown_Button::OnBtnUp()
{
	GameProcess::GetInstance().CurrentScene->Sleep();
	GameProcess::GetInstance().GamePlayer->SetScene(SceneType::MENU_CHILD_MYTOWN);
	GameProcess::GetInstance().CurrentScene = SceneManager::GetInstance().GetScene(static_cast<unsigned int>(SceneType::MENU_CHILD_MYTOWN));
	GameProcess::GetInstance().CurrentScene->Awake();
}


