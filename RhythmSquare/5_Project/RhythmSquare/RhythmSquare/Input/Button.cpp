#include "pchApp.h"
#include "Button.h"
#include "Cursor.h"
#include "../Object/ObjectDef.h"
#include "../../RhythmLibary/Graphics/D2DGraphics.h"
#include "../../RhythmLibary/Util/Utility.h"
#include "../Object/UI_SIZE_Def.h"

#include "../GameManager/GameManager.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/SceneManager.h"

Button::Button()
	:KeyCode(0), State(ButtonState::RELEASE)
{
}

Button::Button(unsigned int id, Vector2 vec, unsigned int vk)
	: Object1(id, vec), KeyCode(vk), State(ButtonState::RELEASE)
{
}

Button::Button(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, unsigned int vk)
	: Object1(id, layer, vec, box), KeyCode(vk), State(ButtonState::RELEASE)
{
}

Button::~Button()
{
}

void Button::Update()
{
}

void Button::SetKeyCode(unsigned int vk)
{
	KeyCode = vk;
}

ButtonState Button::GetKeyState()
{
	State = ButtonState::RELEASE;
	switch (static_cast<ObjectID>(ID))
	{
		/// Key Button
	case ObjectID::BUTTON_PALY:
	case ObjectID::BUTTON_INGAME_1:
	case ObjectID::BUTTON_INGAME_2:
	case ObjectID::BUTTON_INGAME_3:
	case ObjectID::BUTTON_INGAME_4:
	case ObjectID::BUTTON_INGAME_5:
	case ObjectID::BUTTON_INGAME_6:
	case ObjectID::BUTTON_INGAME_7:
	case ObjectID::BUTTON_INGAME_8:
		return KeyButtonState();
		/// Box Button
	case ObjectID::BUTTON_SELECT_EASY:
	case ObjectID::BUTTON_SELECT_NORMAL:
	case ObjectID::BUTTON_SELECT_HARD:
	case ObjectID::BUTTON_MENU_DESERT:
	case ObjectID::BUTTON_GAME_START:
	case ObjectID::BUTTON_MENU_SEA:
	case ObjectID::BUTTON_MENU_FOREST:
	case ObjectID::BUTTON_MENU_MYTOWN:
	case ObjectID::BUTTON_OPTION:
	case ObjectID::BUTTON_EXIT:
	case ObjectID::BUTTON_MENU_SELECT_SPEED_UP:
	case ObjectID::BUTTON_MENU_SELECT_SPEED_DOWN:
	case ObjectID::OPTION_SELECT_GAME:
	case ObjectID::OPTION_SELECT_SOUND:
	case ObjectID::SCROLL_BAR_PLAYSOUND:
	case ObjectID::SCROLL_BAR_EFFECTSOUND:
	case ObjectID::SCROLL_BAR_BGSOUND:
	case ObjectID::PAUSE_SCENE_BUTTON_CONTINUE:
	case ObjectID::PAUSE_SCENE_BUTTON_RESTART:
	case ObjectID::PAUSE_SCENE_BUTTON_MUSIC_SELECT:
	case ObjectID::BUTTON_MENU_EXIT:
	case ObjectID::BUTTON_JUDGMENT_RIGHTARROW:
	case ObjectID::BUTTON_JUDGMENT_LEFTARROW:
		return BoxButtonState();
	}
	return State;
}

ButtonState Button::KeyButtonState()
{
	if (KeyCode == VK_ANY_KEY)
	{
		if (Key::GetInstance().AnyKey())
		{
			OnBtnDown();
		}
	}

	switch (Key::GetInstance().GetKeyState(KeyCode))
	{
	case eKeyState::KEYRELEASE:
		State = ButtonState::RELEASE;
		break;
	case eKeyState::KEYDOWN:
		State = ButtonState::DOWN;
		OnBtnDown();
		break;
	case eKeyState::KEYPRESS:
		State = ButtonState::PRESS;
		OnBtnPress();
		break;
	case eKeyState::KEYUP:
		State = ButtonState::UP;
		OnBtnUp();
		break;
	}
	return State;
}

ButtonState Button::BoxButtonState()
{
	if (CheckBox())
	{
		switch (Key::GetInstance().GetKeyState(KeyCode))
		{
		case eKeyState::KEYRELEASE:
			State = ButtonState::RELEASE;
			OnBtnRelease();
			break;
		case eKeyState::KEYDOWN:
			State = ButtonState::DOWN;
			OnBtnDown();
			break;
		case eKeyState::KEYPRESS:
			State = ButtonState::PRESS;
			OnBtnPress();
			break;
		case eKeyState::KEYUP:
			State = ButtonState::UP;
			OnBtnUp();
			break;
		default:
			State = ButtonState::RELEASE;
		}
	}
	else
		State = ButtonState::NONE;
	return State;
}

void Button::OnEvent()
{
	GetKeyState();
}

void Button::OnRender()
{
	Identify();
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	switch (static_cast<ObjectID>(ID))
	{
	case ObjectID::BUTTON_PALY:
		break;
	case ObjectID::BUTTON_INGAME_1:
		break;
	case ObjectID::BUTTON_INGAME_2:
		break;
	case ObjectID::BUTTON_INGAME_3:
		break;
	case ObjectID::BUTTON_INGAME_4:
		break;
	case ObjectID::BUTTON_INGAME_5:
		break;
	case ObjectID::BUTTON_INGAME_6:
		break;
	case ObjectID::BUTTON_INGAME_7:
		break;
	case ObjectID::BUTTON_INGAME_8:
		break;
	case ObjectID::BUTTON_OPTION:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_OPTION), 0, 0);
		break;
	case ObjectID::BUTTON_SELECT_EASY:
		switch (State)
		{
		case ButtonState::NONE:
		case ButtonState::RELEASE:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_SELECT_EASY), 0, 0);
			break;
		case ButtonState::PRESS:
		case ButtonState::UP:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_SELECT_EASY_LIGHT), 0, 0);
			break;
		}
		break;
	case ObjectID::BUTTON_SELECT_NORMAL:
		switch (State)
		{
		case ButtonState::NONE:
		case ButtonState::RELEASE:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_SELECT_NORMAL), 0, 0);
			break;
		case ButtonState::PRESS:
		case ButtonState::UP:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_SELECT_NORMAL_LIGHT), 0, 0);
			break;
		}
		break;
	case ObjectID::BUTTON_SELECT_HARD:
		switch (State)
		{
		case ButtonState::NONE:
		case ButtonState::RELEASE:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_SELECT_HARD), 0, 0);
			break;
		case ButtonState::PRESS:
		case ButtonState::UP:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_SELECT_HARD_LIGHT), 0, 0);
			break;
		}
		break;
	case ObjectID::BUTTON_GAME_START:
		switch (GameManager::GetInstance().GetDifficulty())
		{
		case GameDifficulty::EASY:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_START_EASY), 0, 0);
			break;
		case GameDifficulty::NORMAL:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_START_NORMAL), 0, 0);
			break;
		case GameDifficulty::HARD:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_START_HARD), 0, 0);
			break;
		default:
			break;
		}
		break;
	case ObjectID::OPTION_SELECT_GAME:
		if (SceneManager::GetInstance().GetCurrenctScene()->GetNext()[1]->CheckActive())
		{
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_OPTION_GAMESELECT), 0, 0);
		}
		else
		{
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_OPTION_GAME), 0, 0);
		}
		break;
	case ObjectID::OPTION_SELECT_SOUND:
		if (SceneManager::GetInstance().GetCurrenctScene()->GetNext()[0]->CheckActive())
		{
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_OPTION_SOUNDSELECT), 0, 0);
		}
		else
		{
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_OPTION_SOUND), 0, 0);
		}

		break;
	case ObjectID::BUTTON_MENU_DESERT:
		switch (State)
		{
		case ButtonState::NONE:
		case ButtonState::RELEASE:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_NAME_DESERT), 0, 0);
			break;
		case ButtonState::PRESS:
		case ButtonState::UP:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_NAME_SELECT_DESERT), 0, 0);
			break;
		}
		break;
	case ObjectID::BUTTON_MENU_SEA:
		switch (State)
		{
		case ButtonState::NONE:
		case ButtonState::RELEASE:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_NAME_SEA), 0, 0);
			break;
		case ButtonState::PRESS:
		case ButtonState::UP:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_NAME_SELECT_SEA), 0, 0);
			break;
		}
		break;
	case ObjectID::BUTTON_MENU_FOREST:
		switch (State)
		{
		case ButtonState::NONE:
		case ButtonState::RELEASE:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_NAME_FOREST), 0, 0);
			break;
		case ButtonState::PRESS:
		case ButtonState::UP:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_NAME_SELECT_FOREST), 0, 0);
			break;
		}
		break;
	case ObjectID::BUTTON_MENU_SELECT_SPEED_DOWN:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::MENU_SELECT_SPEED_DOWN), 0, 0);
		break;
	case ObjectID::BUTTON_MENU_EXIT:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_MENU_EXIT), 0, 0);
		break;
	case ObjectID::BUTTON_MENU_SELECT_SPEED_UP:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::MENU_SELECT_SPEED_UP), 0, 0);
		break;
	case ObjectID::BUTTON_MENU_MYTOWN:
		break;
	case ObjectID::BUTTON_EXIT:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_EXIT), 0, 0);
		break;
	case ObjectID::BUTTON_JUDGMENT_LEFTARROW:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_JUDGMENT_LEFTARROW), 0, 0);
		break;
	case ObjectID::BUTTON_JUDGMENT_RIGHTARROW:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_JUDGMENT_RIGHTARROW), 0, 0);
		break;
	case ObjectID::PAUSE_SCENE_BUTTON_CONTINUE:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PAUSE_SCENE_BUTTON_CONTINUE), 0, 0);
		break;
	case ObjectID::PAUSE_SCENE_BUTTON_RESTART:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PAUSE_SCENE_BUTTON_RESTART), 0, 0);
		break;
	case ObjectID::PAUSE_SCENE_BUTTON_MUSIC_SELECT:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PAUSE_SCENE_BUTTON_MUSIC_SELECT), 0, 0);
		break;
	}
	Identify();
}

void Button::OnBtnRelease()
{
}

void Button::OnBtnDown()
{
	AudioManager::GetInstance().PlaySound(SoundID::SFX_BUTTON);
	switch (static_cast<ObjectID>(ID))
	{
	case ObjectID::BUTTON_PALY:
		SceneManager::GetInstance().GetCurrenctScene()->Sleep();
		SceneManager::GetInstance().SetCurrentScene(ObjectID::SCENE_MAINMENU);
		SceneManager::GetInstance().GetCurrenctScene()->Awake();
		break;
	case ObjectID::BUTTON_SELECT_EASY:
		break;
	case ObjectID::BUTTON_SELECT_NORMAL:
		break;
	case ObjectID::BUTTON_SELECT_HARD:
		break;
	case ObjectID::BUTTON_MENU_DESERT:
		break;
	case ObjectID::BUTTON_MENU_SEA:
		break;
	case ObjectID::BUTTON_MENU_FOREST:
		break;
	case ObjectID::BUTTON_MENU_MYTOWN:
		break;
	case ObjectID::BUTTON_OPTION:
		break;
	case ObjectID::BUTTON_EXIT:
		break;
	}
}

void Button::OnBtnUp()
{
	Scene* curscene = SceneManager::GetInstance().GetCurrenctScene();
	Scene* mother = curscene->GetMother();

	switch (static_cast<ObjectID>(ID))
	{
	case ObjectID::BUTTON_PALY:
		break;
	case ObjectID::BUTTON_SELECT_EASY:
		GameManager::GetInstance().SetDifficulty(GameDifficulty::EASY);
		break;
	case ObjectID::BUTTON_SELECT_NORMAL:
		GameManager::GetInstance().SetDifficulty(GameDifficulty::NORMAL);
		break;
	case ObjectID::BUTTON_SELECT_HARD:
		GameManager::GetInstance().SetDifficulty(GameDifficulty::HARD);
		break;
	case ObjectID::BUTTON_GAME_START: // 곡 선택 부분 개선 필요 !!!!!!!!!!!!!!!!!!!!!
		SceneManager::GetInstance().GetCurrenctScene()->GetNext()[0]->Sleep();
		break;

	case ObjectID::BUTTON_MENU_DESERT:
		SceneManager::GetInstance().GetCurrenctScene()->Sleep();
		SceneManager::GetInstance().SetCurrentScene(ObjectID::CHILD_SCENE_DESERT_MAINMENU);
		GameManager::GetInstance().SetProperty(InGameProperty::DESERT);
		GameManager::GetInstance().LoadBestData();
		AudioManager::GetInstance().AllSoundStop();
		AudioManager::GetInstance().PlaySound(SoundID::INTROSPECT_PRE_WAVE);
		SceneManager::GetInstance().GetCurrenctScene()->Awake();
		break;
	case ObjectID::BUTTON_MENU_SEA:
		SceneManager::GetInstance().GetCurrenctScene()->Sleep();
		SceneManager::GetInstance().SetCurrentScene(ObjectID::CHILD_SCENE_SEA_MAINMENU);
		GameManager::GetInstance().SetProperty(InGameProperty::SEA);
		GameManager::GetInstance().LoadBestData();
		AudioManager::GetInstance().AllSoundStop();
		AudioManager::GetInstance().PlaySound(SoundID::PRECISION_STRIKE_PRE_WAVE);
		SceneManager::GetInstance().GetCurrenctScene()->Awake();
		break;
	case ObjectID::BUTTON_MENU_FOREST:
		SceneManager::GetInstance().GetCurrenctScene()->Sleep();
		SceneManager::GetInstance().SetCurrentScene(ObjectID::CHILD_SCENE_FOREST_MAINMENU);
		GameManager::GetInstance().SetProperty(InGameProperty::FOREST);
		GameManager::GetInstance().LoadBestData();
		AudioManager::GetInstance().AllSoundStop();
		AudioManager::GetInstance().PlaySound(SoundID::PLOT_TWIST_PRE_WAVE);
		SceneManager::GetInstance().GetCurrenctScene()->Awake();
		break;
	case ObjectID::BUTTON_MENU_MYTOWN:
		SceneManager::GetInstance().GetCurrenctScene()->Sleep();
		SceneManager::GetInstance().SetCurrentScene(ObjectID::CHILD_SCENE_MYTOWN_MAINMENU);
		SceneManager::GetInstance().GetCurrenctScene()->Awake();
		break;
	case ObjectID::BUTTON_MENU_SELECT_SPEED_UP:
		if (GameManager::GetInstance().GetMusicSelectData()->Speed >= 4)
			GameManager::GetInstance().GetMusicSelectData()->Speed = 4;
		else
			GameManager::GetInstance().GetMusicSelectData()->Speed *= 2;
		break;
	case ObjectID::BUTTON_MENU_SELECT_SPEED_DOWN:
		if (GameManager::GetInstance().GetMusicSelectData()->Speed < 2)
			GameManager::GetInstance().GetMusicSelectData()->Speed = 1;
		else
			GameManager::GetInstance().GetMusicSelectData()->Speed /= 2;
		break;
	case ObjectID::BUTTON_OPTION:
		SceneManager::GetInstance().GetCurrenctScene()->Sleep();
		SceneManager::GetInstance().SetCurrentScene(ObjectID::CHILD_SCENE_OPTION_MAINMENU);
		SceneManager::GetInstance().GetCurrenctScene()->Awake();
		break;
	case ObjectID::OPTION_SELECT_SOUND:
		SceneManager::GetInstance().GetCurrenctScene()->GetNext()[1]->Sleep();
		SceneManager::GetInstance().GetCurrenctScene()->GetNext()[0]->Awake();
		break;
	case ObjectID::OPTION_SELECT_GAME:
		SceneManager::GetInstance().GetCurrenctScene()->GetNext()[0]->Sleep();
		SceneManager::GetInstance().GetCurrenctScene()->GetNext()[1]->Awake();
		break;
	case ObjectID::BUTTON_EXIT:

		if (mother == nullptr)
		{
			PostQuitMessage(0);
		}
		else
		{
			curscene->Sleep();
			mother->Awake();
			SceneManager::GetInstance().SetCurrentScene(static_cast<ObjectID>(mother->GetID()));
		}
		break;
	case ObjectID::BUTTON_MENU_EXIT:
		switch (State)
		{
		case ButtonState::UP:
			AudioManager::GetInstance().AllSoundStop();
			SceneManager::GetInstance().GetCurrenctScene()->GetNext()[0]->Sleep();
			GameManager::GetInstance().SetProperty(InGameProperty::NONE);
			break;
		}
		break;
	case ObjectID::BUTTON_JUDGMENT_LEFTARROW:
		GameManager::GetInstance().m_InputRev -= 0.005f;
		break;
	case ObjectID::BUTTON_JUDGMENT_RIGHTARROW:
		GameManager::GetInstance().m_InputRev += 0.005f;
		break;
	case ObjectID::PAUSE_SCENE_BUTTON_CONTINUE:
		SceneManager::GetInstance().GetCurrenctScene()->Continue();
		break;
	case ObjectID::PAUSE_SCENE_BUTTON_RESTART:
		SceneManager::GetInstance().GetCurrenctScene()->Restart();
		break;
	case ObjectID::PAUSE_SCENE_BUTTON_MUSIC_SELECT:
		//SceneManager::GetInstance().GetCurrenctScene()->Restart();
		SceneManager::GetInstance().GetCurrenctScene()->Sleep();
		SceneManager::GetInstance().SetCurrentScene(ObjectID::SCENE_MAINMENU);
		break;
	}
}

void Button::OnBtnPress()
{
	switch (static_cast<ObjectID>(ID))
	{
	case ObjectID::BUTTON_PALY:
		break;
	case ObjectID::BUTTON_MENU_DESERT:
		break;
	case ObjectID::BUTTON_MENU_SEA:
		break;
	case ObjectID::BUTTON_MENU_FOREST:
		break;
	case ObjectID::BUTTON_MENU_MYTOWN:
		break;
	case ObjectID::BUTTON_OPTION:
		break;
	case ObjectID::BUTTON_EXIT:
		break;
	}
}

bool Button::CheckBox()
{
	return Collision::CheckRectPoint(Box, Cursor::GetInstance().GetPosition());
}

TextBox::TextBox(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, const wchar_t* link)
	:Object1(id, layer, vec, box), buf(link), WriteBox(box)
{
	switch (static_cast<ObjectID>(id))
	{
	case ObjectID::TEXTBOX_MENU_BESTSCORE:
	case ObjectID::TEXTBOX_MENU_COMBO:
	case ObjectID::TEXTBOX_MENU_KILL:
	case ObjectID::TEXTBOX_MENU_RATE:
		WriteBox.top += 30;
		break;
	case ObjectID::TEXTBOX_MENU_MUSIC_NAME:
		break;
	case ObjectID::TEXTBOX_MENU_MUSIC_COMPOSER:
		break;
	case ObjectID::TEXTBOX_MENU_SPEED:
		break;
	case ObjectID::TEXTBOX_MENU_MUSIC_BPM:
		break;
	}
}

TextBox::~TextBox()
{
}

void TextBox::OnEvent()
{
}

void TextBox::OnRender()
{
	Identify();
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);

	switch (static_cast<ObjectID>(ID))
	{
	case ObjectID::TEXTBOX_MENU_BESTSCORE:
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, WriteBox, L"HY견명조", 35, L"%s", buf);
		break;
	case ObjectID::TEXTBOX_MENU_COMBO:
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, WriteBox, L"HY견명조", 35, L"%s", buf);

		break;
	case ObjectID::TEXTBOX_MENU_KILL:
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, WriteBox, L"HY견명조", 35, L"%s", buf);

		break;
	case ObjectID::TEXTBOX_MENU_RATE:
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, WriteBox, L"HY견명조", 35, L"%s", buf);

		break;
	case ObjectID::TEXTBOX_MENU_SPEED:
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, WriteBox, L"HY견명조", 35, L"%s", buf);

		break;
	case ObjectID::TEXTBOX_MENU_MUSIC_NAME:
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF(0xfffcfbee), WriteBox, L"HY견명조", 50, L"%s", buf);

		break;
	case ObjectID::TEXTBOX_MENU_MUSIC_COMPOSER:
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF(0xfffcfbee), WriteBox, L"HY견명조", 30, L"%s", buf);

		break;
	case ObjectID::TEXTBOX_MENU_MUSIC_BPM:
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF(0xfffcfbee), WriteBox, L"HY견명조", 30, L"%s", buf);

		break;
	case ObjectID::TEXTBOX_OPTION_JUDGMENT:
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, WriteBox, L"HY견명조", 20, L"%s", buf);

	}
	Identify();
}


ScrollBar::ScrollBar()
	:Button()
{
}

ScrollBar::ScrollBar(unsigned int id, Vector2 vec, unsigned int vk)
	: Button(id, vec, vk)
{
}

ScrollBar::ScrollBar(unsigned int id, unsigned int layer, Vector2 barvec, D2D1_SIZE_F barsize, Vector2 stonevec, D2D1_RECT_F stone, unsigned int vk)
	: Button(id, layer, stonevec, stone, vk), Bar(barsize), data(0.0f), BarVec(barvec)
{
	BarMin = Bar.width + BarVec.x;
	BarMax = Bar.height + BarVec.x;
}


void ScrollBar::OnRender()
{
	Identify();
	MakeTranslate(BarVec);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	switch (static_cast<ObjectID>(ID))
	{
	case ObjectID::SCROLL_BAR_BGSOUND:
	case ObjectID::SCROLL_BAR_PLAYSOUND:
	case ObjectID::SCROLL_BAR_EFFECTSOUND:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::SCROLL_BAR), 0, 0);
		Identify();
		MakeTranslate(World_Position);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::SCROLL_STONE), 0, 0);
		Identify();
		break;
	}
	Identify();
}

void ScrollBar::OnBtnDown()
{
}

void ScrollBar::OnBtnUp()
{
}

void ScrollBar::OnBtnPress()
{
	switch (static_cast<ObjectID>(ID))
	{
	case ObjectID::SCROLL_BAR_BGSOUND:
	case ObjectID::SCROLL_BAR_PLAYSOUND:
	case ObjectID::SCROLL_BAR_EFFECTSOUND:

		Vector2 DivVec = Vector2(Cursor::GetInstance().GetCursorEngineDpiPos().x, 0) - Vector2(CenterPos.x, 0);
		if (CenterPos.x > BarMin && CenterPos.x < BarMax)
		{
			World_Position += DivVec;
			CenterPos += DivVec;
			AddBox(DivVec);
		}
		if (CenterPos.x >= BarMax)
		{
			World_Position += Vector2(-10, 0);
			CenterPos += Vector2(-10, 0);
			AddBox(Vector2(-10, 0));
		}
		if (CenterPos.x <= BarMin)
		{
			World_Position += Vector2(10, 0);
			CenterPos += Vector2(10, 0);
			AddBox(Vector2(10, 0));
		}
	}
}

void ScrollBar::OnBtnRelease()
{
	switch (static_cast<ObjectID>(ID))
	{
	case ObjectID::SCROLL_BAR_BGSOUND:
	case ObjectID::SCROLL_BAR_PLAYSOUND:
	case ObjectID::SCROLL_BAR_EFFECTSOUND:

		float maxLineSize = BarMax - BarMin;
		float curLineSize = BarMax - Box.left + 24;

		data = 1.0f - (curLineSize / maxLineSize);
		if (data < 0)
			data * -1;
		switch (static_cast<ObjectID>(ID))
		{
		case ObjectID::SCROLL_BAR_BGSOUND:
			AudioManager::GetInstance().SetVolume(1, data);
			break;
		case ObjectID::SCROLL_BAR_PLAYSOUND:
			AudioManager::GetInstance().SetVolume(2, data);
			break;
		case ObjectID::SCROLL_BAR_EFFECTSOUND:
			AudioManager::GetInstance().SetVolume(3, data);
			break;
		}
		break;
	}
}
