#pragma once
#include <string>
#include "../Interpace/IRenderable.h"
#include "../Interpace/IEventable.h"
#include "../Object/Object1.h"
#include "../../RhythmLibary/Graphics/D2DImage.h"
#include "../../RhythmLibary/Key/Key.h"

/// 속성에 따른 Input UI의 모음. ex) BoxButton, KeyButton, ScrollBar, ScrollCircle 등등..

#define VK_ANY_KEY (unsigned int)33333

enum class ButtonState : unsigned char
{
	NONE = -1, RELEASE = 0x00, DOWN = 0x01, PRESS = 0x11, UP = 0x10
};

class Button : public Object1
{
public:
	Button();
	Button(unsigned int id, Vector2 vec, unsigned int vk);
	Button(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, unsigned int vk);
	virtual ~Button();

public:
	virtual void OnEvent();
	virtual void OnRender();

	virtual void SetKeyCode(unsigned int vk);
	virtual ButtonState GetKeyState();

	ButtonState KeyButtonState();
	ButtonState BoxButtonState();

	virtual void OnBtnRelease();
	virtual void OnBtnDown();
	virtual void OnBtnUp();
	virtual void OnBtnPress();
	virtual void Update() override;
	virtual bool CheckBox();

protected:
	unsigned int KeyCode;
	ButtonState State;
};


class TextBox : public Object1
{
public:
	TextBox(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, const wchar_t* link);
	virtual ~TextBox();

public:
	virtual void OnEvent();
	virtual void OnRender();

protected:
	const wchar_t* buf;
	D2D1_RECT_F WriteBox;
	bool IsWrite;
};

class ScrollBar : public Button
{
public:
	ScrollBar();
	ScrollBar(unsigned int id, Vector2 vec, unsigned int vk);
	ScrollBar(unsigned int id, unsigned int layer, Vector2 barvec, D2D1_SIZE_F barsize,
		Vector2 stonevec, D2D1_RECT_F stone, unsigned int vk);	

public:
	virtual void OnBtnRelease();
	virtual void OnRender();
	virtual void OnBtnDown();
	virtual void OnBtnUp();
	virtual void OnBtnPress();

protected:
	D2D1_SIZE_F Bar;
	Vector2 BarVec;
	float BarMin;
	float BarMax;
	float data;
};

