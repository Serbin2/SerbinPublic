#include "pchApp.h"
#include "OptionScene.h"
#include "../Object/UI_SIZE_Def.h"
#include "../GameManager/GameManager.h"
#include "../Resource/ResourceManager.h"

OptionScene::OptionScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother)
	: ChildScene(id, layer, vec, box, mother)
{
	//Info = GameManager::GetInstance().GetOptionData();
	Next = new Scene * [2];
	AttachObject(new Button(static_cast<unsigned int>(ObjectID::OPTION_SELECT_SOUND), 1, Option_Sound_Vec, Option_Menu_Box, VK_LBUTTON));
	AttachObject(new Button(static_cast<unsigned int>(ObjectID::OPTION_SELECT_GAME), 1, Option_Select_Vec, Option_Menu_Box, VK_LBUTTON));
	AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_EXIT), 1, Exit_Button_Vec, Option_Exit_Box, VK_LBUTTON));

	/// Option Sound
	Next[0] = new OptionSound(1, 1, Vector2(0, 0), D2D1::RectF(0, 0, 0, 0), this);

	/// Option Control
	Next[1] = new OptionSettiong(1, 1, Vector2(0, 0), D2D1::RectF(0, 0, 0, 0), this);
}

OptionScene::~OptionScene()
{
	if (Next[0] != nullptr)
		delete Next[0];
	if (Next[0] != nullptr)
		delete Next[1];
	if (Next != nullptr)
		delete Next;

	unsigned int size = Object_Layer1.size();
	for (int i = 0; i < size; i++)
	{
		if (Object_Layer1[i] != nullptr)
			delete Object_Layer1[i];
	}
	Object_Layer1.clear();
}

void OptionScene::Awake()
{
	Next[0]->Awake();
	Next[1]->Sleep();
	IsActive = true;
}

void OptionScene::Sleep()
{
	Next[0]->Sleep();
	Next[1]->Sleep();
	IsActive = false;
}

void OptionScene::OnEvent()
{
	unsigned int size = Object_Layer1.size();
	for (unsigned int i = 0; i < size; i++)
	{
		Object_Layer1[i]->OnEvent();
	}
	Next[0]->OnEvent();
	Next[1]->OnEvent();
}

void OptionScene::OnRender()
{
	if (IsActive)
	{
		Mother->OnRender();
		Mother->RenderObject(1);
		Mother->RenderObject(2);
		Mother->RenderObject(3);

		Identify();
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PAUSE_PLAN), 0, 0, 0.5, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

		Identify();
		MakeTranslate(World_Position);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::SETTING_WINDOW), 0, 0);
		Identify();

		RenderObject(1);
		Next[0]->OnRender();
		Next[1]->OnRender();
	}
}

void OptionScene::DefaultKeyEvent()
{
}

void OptionScene::Update()
{
}

OptionSound::OptionSound(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother)
	:ChildScene(id, layer, vec, box, mother)
{
	AttachObject(new ScrollBar(static_cast<unsigned int>(ObjectID::SCROLL_BAR_BGSOUND), 1, BG_ScrollBar_Vec, BarSize,
		BG_ScrollBar_Stone_Vec, ScrollBar_Stone_Size, VK_LBUTTON));
	AttachObject(new ScrollBar(static_cast<unsigned int>(ObjectID::SCROLL_BAR_EFFECTSOUND), 1, Effect_ScrollBar_Vec, BarSize,
		Effect_ScrollBar_Stone_Vec, ScrollBar_Stone_Size, VK_LBUTTON));
	AttachObject(new ScrollBar(static_cast<unsigned int>(ObjectID::SCROLL_BAR_PLAYSOUND), 1, Play_ScrollBar_Vec, BarSize,
		Play_ScrollBar_Stone_Vec, ScrollBar_Stone_Size, VK_LBUTTON));
}

OptionSound::~OptionSound()
{
	unsigned int size = Object_Layer1.size();
	for (int i = 0; i < size; i++)
	{
		if (Object_Layer1[i] != nullptr)
			delete Object_Layer1[i];
	}
	Object_Layer1.clear();
}

void OptionSound::Awake()
{
	IsActive = true;
}

void OptionSound::Sleep()
{
	IsActive = false;
}

void OptionSound::OnEvent()
{
	unsigned int size = Object_Layer1.size();
	for (unsigned int i = 0; i < size; i++)
	{
		Object_Layer1[i]->OnEvent();
	}
}

void OptionSound::OnRender()
{
	if (IsActive)
	{
		Identify();
		MakeTranslate(Option_Sound_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::SETTING_SOUND_TEXT), 0, 0);
		RenderObject(1);
		Identify();
	}
}

void OptionSound::DefaultKeyEvent()
{
}

void OptionSound::Update()
{
}

OptionSettiong::OptionSettiong(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother)
	: ChildScene(id, layer, vec, box, mother)
{
	AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_JUDGMENT_LEFTARROW), 1, Left_Arrow_Vec, Arrow_Size, VK_LBUTTON));
	AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_JUDGMENT_RIGHTARROW), 1, Right_Arrow_Vec, Arrow_Size, VK_LBUTTON));
	//AttachObject(new TextBox(static_cast<unsigned int>(ObjectID::TEXTBOX_OPTION_JUDGMENT), 1, Judgment_TextBox_Vec, Judgment_TextBox_Layout, WstJudgment.c_str()));

	WstJudgment = L"text";
}

OptionSettiong::~OptionSettiong()
{
	unsigned int size = Object_Layer1.size();
	for (int i = 0; i < size; i++)
	{
		if (Object_Layer1[i] != nullptr)
			delete Object_Layer1[i];
	}
	Object_Layer1.clear();
}

void OptionSettiong::Awake()
{
	IsActive = true;
}

void OptionSettiong::Sleep()
{
	IsActive = false;
}

void OptionSettiong::OnEvent()
{
	if (IsActive)
	{
		unsigned int size = Object_Layer1.size();

		for (int i = 0; i < size; i++)
		{
			Object_Layer1[i]->OnEvent();
		}
	}
}

void OptionSettiong::OnRender()
{
	if (IsActive)
	{
		Identify();
		MakeTranslate(Option_Setting_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::SETTING_SETTING_TEXT), 0, 0);
		RenderObject(1);
		Identify();

		Identify();
		MakeTranslate(Vector2(1440, 750));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Brown, D2D1::RectF(0.0, 0.0, 150.f, 150.f), L"HY∞ﬂ∏Ì¡∂", 35, L"%.3f", GameManager::GetInstance().m_InputRev);
		Identify();
	}
}

void OptionSettiong::DefaultKeyEvent()
{
}

OptionControl::OptionControl(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother)
	: ChildScene(id, layer, vec, box, mother)
{
}

OptionControl::~OptionControl()
{
	unsigned int size = Object_Layer1.size();
	for (int i = 0; i < size; i++)
	{
		if (Object_Layer1[i] != nullptr)
			delete Object_Layer1[i];
	}
}

void OptionControl::Awake()
{
	IsActive = true;
}

void OptionControl::Sleep()
{
	IsActive = false;
}

void OptionControl::AttachObject(GameObject* obj)
{

}

void OptionControl::OnRender()
{
	if (IsActive)
	{
		RenderObject(1);
	}

}

void OptionControl::DefaultKeyEvent()
{

}
