#include "pchApp.h"
#include "FXManager.h"



void FXManager::RenderCombo(int combo, bool fever)
{
	if (combo > 0)
	{
		char buf[16];
		_itoa_s(combo, buf, sizeof(buf), 10);
		int len = 0;
		for (int i = 0; i < 16; i++)
		{
			if (buf[i] == '\0')
			{
				len = i;
			}
		}
		float startx = COMBO_BOX_X - (len / 2) * COMBO_FONT_X;
		if (fever)
		{
			for (int i = 0; i < len; i++)
			{
				// x 좌표는 stratx + (i * COMBO_FONT_X)
				// y 좌표는 COMBO_BOX_Y
				switch (buf[i])
				{
				default:
				case '0':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_FEVER_0, false);
					break;
				case '1':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_FEVER_1, false);
					break;
				case '2':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_FEVER_2, false);
					break;
				case '3':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_FEVER_3, false);
					break;
				case '4':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_FEVER_4, false);
					break;
				case '5':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_FEVER_5, false);
					break;
				case '6':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_FEVER_6, false);
					break;
				case '7':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_FEVER_7, false);
					break;
				case '8':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_FEVER_8, false);
					break;
				case '9':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_FEVER_9, false);
					break;
				}
			}
			// 추가로 COMBO 글자 이미지도 출력해야 함.
			AddFX(1, { COMBO_TEXT_X, COMBO_TEXT_Y }, ResourceID::PLAY_UI_COMBO_FEVER, false);
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				// x 좌표는 stratx + (i * COMBO_FONT_X)
				// y 좌표는 COMBO_BOX_Y
				switch (buf[i])
				{
				default:
				case '0':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_NORMAL_0, false);
					break;
				case '1':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_NORMAL_1, false);
					break;
				case '2':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_NORMAL_2, false);
					break;
				case '3':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_NORMAL_3, false);
					break;
				case '4':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_NORMAL_4, false);
					break;
				case '5':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_NORMAL_5, false);
					break;
				case '6':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_NORMAL_6, false);
					break;
				case '7':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_NORMAL_7, false);
					break;
				case '8':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_NORMAL_8, false);
					break;
				case '9':
					AddFX(1, { startx + (i * COMBO_FONT_X), COMBO_BOX_Y }, ResourceID::COMBO_NUMBER_NORMAL_9, false);
					break;
				}
			}
			// 추가로 COMBO 글자 이미지도 출력해야 함.
			AddFX(1, { COMBO_TEXT_X, COMBO_TEXT_Y }, ResourceID::PLAY_UI_COMBO_TEXT, false);
		}

	}
}

void FXManager::RenderJudgeFX(int rslt, bool fever)
{
	if (fever)
	{
		switch (rslt)
		{
		default:
		case 0:
			AddFX(30, { JUDGE_BOX_X,JUDGE_BOX_Y }, ResourceID::PLAY_EFECT_MISS, false, { 0,-2 });
			break;
		case 1:
			AddFX(30, { JUDGE_BOX_X,JUDGE_BOX_Y }, ResourceID::PLAY_EFECT_FEVER_GOOD, false, { 0,-2 });
			break;
		case 2:
			AddFX(30, { JUDGE_BOX_X,JUDGE_BOX_Y }, ResourceID::PLAY_EFECT_PREFECT_FEVER, false, { 0,-2 });
			break;
		}
	}
	else
	{
		switch (rslt)
		{
		default:
		case 0:
			AddFX(30, { JUDGE_BOX_X,JUDGE_BOX_Y }, ResourceID::PLAY_EFECT_MISS, false, { 0,-2 });
			break;
		case 1:
			AddFX(30, { JUDGE_BOX_X,JUDGE_BOX_Y }, ResourceID::PLAY_EFECT_GOOD, false, { 0,-2 });
			break;
		case 2:
			AddFX(30, { JUDGE_BOX_X,JUDGE_BOX_Y }, ResourceID::PLAY_EFECT_PREFECT, false, { 0,-2 });
			break;
		}
	}
	
}

void FXManager::RenderAll()
{
	for (int i = 0; i < m_Fx.size(); i++)
	{
		if (m_Fx[i]->Render())
		{
			continue;
		}
		delete m_Fx[i];
		m_Fx.erase(m_Fx.begin() + i);
		i--;
	}
}

void FXManager::AddFX(int count, Vector2 vec, ResourceID id, bool isAni)
{
	CFX* tmp = new CFX(count, vec, id, isAni, { 0,0 });
	m_Fx.push_back(tmp);
}

void FXManager::AddFX(int count, Vector2 vec, ResourceID id, bool isAni, Vector2 mov)
{
	CFX* tmp = new CFX(count, vec, id, isAni, mov);
	m_Fx.push_back(tmp);
}

void FXManager::RenderHeal()
{
	for (int i = 0; i < 8; i++)
	{
		AddFX(20, Vector2(400.f + (std::rand() % 200) - 100.f, 600 + (std::rand() % 200) - 100.f), ResourceID::PLAY_HEAL_ICON, false, Vector2(std::rand() % 4 - 2, std::rand() % 4 - 2));
	}
}
