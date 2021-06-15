#include "pchApp.h"
#include "../App.h"
#include "Cursor.h"

Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

void Cursor::OnRender()
{
	Identify();
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);

	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(0, 0, 1500, 50), L"CurPos(world) : %.2f / %.2f", World_Position.x, World_Position.y);
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(0, 100, 1500, 150), L"Ratio : %.2f / %.2f", _ratioX, _ratioY);
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(0, 150, 1500, 200), L"CurPos(original) : %.2d / %.2d", _cursorPos.x, _cursorPos.y);
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(0, 200, 1500, 250), L"ClientRect : %.2d / %.2d / %.2d / %.2d", _clientRect.left, _clientRect.top, _clientRect.right, _clientRect.bottom);
	D2DGraphics::GetInstance().DrawRectangle(0, 100, 0, 100, D2D1::ColorF::Green, true);
}

void Cursor::Update()
{
	// ��ũ������ Ŀ�� ��ġ
	GetCursorPos(&_cursorPos);

	// Ŭ���̾�Ʈ ��ġ�� �����, ������ Ŀ���� ��ġ�� �����ش�.
	ScreenToClient(D2DGraphics::GetInstance().GetHWnd(), &_cursorPos);

	// ���� Ŭ���̾�Ʈ ����
	GetClientRect(D2DGraphics::GetInstance().GetHWnd(), &_clientRect);

	// ���� Ŭ���̾�Ʈ �������, ��ü ���� �������� (��)����
	_ratioX = 2560.f / _clientRect.right;
	_ratioY = 1440.f / _clientRect.bottom;

	// ������� Ŀ�� ��ġ�� �����ش�.
	// ������ ���Ѵ�.
	World_Position.x = _cursorPos.x * _ratioX;
	World_Position.y = _cursorPos.y * _ratioY;
}

Vector2 Cursor::GetCursorEngineDpiPos()
{
	float x;
	float y;
	RECT rt;
	Vector2 result = World_Position;

	GetWindowRect(D2DGraphics::GetInstance().GetHWnd(), &rt);
	x = rt.right / rt.right;
	y = rt.bottom / rt.bottom;

	result *= x;
	result *= y;

	return result;
}

void Cursor::OnResize(int width, int height)
{
	GetClientRect(D2DGraphics::GetInstance().GetHWnd(), &_clientRect);

	// ���� Ŭ���̾�Ʈ �������, ��ü ���� �������� (��)����
	_ratioX = 2560.f / _clientRect.right;
	_ratioY = 1440.f / _clientRect.bottom;

	// ������� Ŀ�� ��ġ�� �����ش�.
	// ������ ���Ѵ�.
	World_Position.x = _cursorPos.x * _ratioX;
	World_Position.y = _cursorPos.y * _ratioY;
}
