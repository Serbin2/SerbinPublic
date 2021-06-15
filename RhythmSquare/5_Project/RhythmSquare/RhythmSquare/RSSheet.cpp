#include "pchApp.h"

#include "RSSheet.h"

RSSheet::RSSheet() : m_SongName(0), m_Composer(0), m_SongLength(0), m_Level(0), m_Place(0), m_BPM(0)
{



#ifndef RSTOOL

	m_Combo = 0;
	m_Miss = 0;
	m_Good = 0;
	m_Perfect = 0;
	m_Early = 0;
	m_Late = 0;

	m_PlayerHP = PLAYER_DEF_HP;
	m_Fever = 1;
	b_Fever = false;
	m_FeverStack = 0;
	m_FeverTime = 0;
	m_Score = 0;
	m_CurMon = 0;
	m_PassedNote = 0;
	m_KilledMonster = 0;
	m_HealReady = true;

	m_MaxCombo = 0;
	m_Missed = 0;

#endif // !RSTOOL

}

RSSheet::~RSSheet()
{

}

#ifndef RSTOOL


void RSSheet::RestoreNotePool()
{
	for (int i = 0; i < m_Page.size(); i++)
	{
		for (int j = 0; j < m_Page[i]->m_Note.size(); j++)
		{
			m_Note[m_Page[i]->m_Note[j]->GetKey() - 1].push_back(m_Page[i]->m_Note[j]);
		}
	}

	m_Combo = 0;
	m_Miss = 0;
	m_Good = 0;
	m_Perfect = 0;
	m_Early = 0;
	m_Late = 0;

	m_PlayerHP = PLAYER_DEF_HP;
	m_Score = 0;
	m_Fever = 1;
	b_Fever = false;
	m_FeverStack = 0;
	m_FeverTime = 0;
	m_CurMon = 0;
	m_KilledMonster = 0;
	m_HealReady = true;
	m_TotalMon = m_Page.size();
	m_MonNoteEa = m_Page[m_CurMon]->m_Note.size();
	m_Page[m_CurMon]->isDraw = true;
	m_PassedNote = 0;
	m_Missed = 0;
	m_MaxCombo = 0;
	b_ShotEvent = false;
}


void RSSheet::GetInput(int input, float inputTime)
{
	if (m_Combo > m_MaxCombo)
	{
		m_MaxCombo = m_Combo;
	}
	if (input > 10)
	{
		for (int i = 0; i < 8; i++)
		{
			if (m_Note[i].size() == 0)
			{
				continue;
			}
			if (m_Note[i][0]->IsLast())
			{
				switch (m_Note[i][0]->Judge(inputTime, b_Fever))
				{
				default:
				case JUD_NO_MATCH:
					return;
				case JUD_EARL_MISS:
					m_Miss++;
					m_Early++;
					m_Combo = 0;
					m_Missed++;
					break;
				case JUD_EARL_GOOD:
					m_Good++;
					m_Early++;
					m_Combo++;
					m_Score = m_Score + (SCORE_PER_NOTE * m_Fever * 1);
					break;
				case JUD_EARL_PERF:
					m_FeverStack++;
					m_Perfect++;
					m_Early++;
					m_Combo++;
					m_Score = m_Score + (SCORE_PER_NOTE * m_Fever * 2);
					break;
				case JUD_EXAC_PERF:
					m_FeverStack++;
					m_Perfect++;
					m_Combo++;
					m_Score = m_Score + (SCORE_PER_NOTE * m_Fever * 2);
					break;
				case JUD_LATE_PERF:
					m_FeverStack++;
					m_Perfect++;
					m_Late++;
					m_Combo++;
					m_Score = m_Score + (SCORE_PER_NOTE * m_Fever * 2);
					break;
				case JUD_LATE_GOOD:
					m_Good++;
					m_Late++;
					m_Combo++;
					m_Score = m_Score + (SCORE_PER_NOTE * m_Fever * 1);
					break;
				case JUD_LATE_MISS:
					m_Miss++;
					m_Late++;
					m_Combo = 0;
					m_Missed++;
					break;
				}

				if (m_Missed == 0)
				{
					MonsterAttackJudge(input - 10);
					switch (input)
					{
					default:
					case 11:
						AudioManager::GetInstance().PlaySound(SoundID::PLAYER_ATTACK_FIRE);
						FXManager::GetInstance().AddFX(40, { 1940,776 }, ResourceID::ATT_EFF_FIRE, true);
						break;
					case 12:
						FXManager::GetInstance().AddFX(40, { 1940,776 }, ResourceID::ATT_EFF_WATER, true);
						AudioManager::GetInstance().PlaySound(SoundID::PLAYER_ATTACK_WATER);
						break;
					case 13:
						FXManager::GetInstance().AddFX(40, { 1940,776 }, ResourceID::ATT_EFF_GRASS, true);
						AudioManager::GetInstance().PlaySound(SoundID::PLAYER_ATTACK_GRASS);
						break;
					}
				}
				m_Note[i].erase(m_Note[i].begin());
				m_PassedNote++;
			}
		}
		return;
	}

	if (m_Note[input].size() > 0)
	{
		switch (m_Note[input][0]->Judge(inputTime, b_Fever))
		{
		default:
		case JUD_NO_MATCH:
			return;
		case JUD_EARL_MISS:
			m_Miss++;
			m_Early++;
			m_Combo = 0;
			m_Missed++;
			break;
		case JUD_EARL_GOOD:
			m_Good++;
			m_Early++;
			m_Combo++;
			m_Score = m_Score + (SCORE_PER_NOTE * m_Fever * 1);
			break;
		case JUD_EARL_PERF:
			m_FeverStack++;
			m_Perfect++;
			m_Early++;
			m_Combo++;
			m_Score = m_Score + (SCORE_PER_NOTE * m_Fever * 2);
			break;
		case JUD_EXAC_PERF:
			m_FeverStack++;
			m_Perfect++;
			m_Combo++;
			m_Score = m_Score + (SCORE_PER_NOTE * m_Fever * 2);
			break;
		case JUD_LATE_PERF:
			m_FeverStack++;
			m_Perfect++;
			m_Late++;
			m_Combo++;
			m_Score = m_Score + (SCORE_PER_NOTE * m_Fever * 2);
			break;
		case JUD_LATE_GOOD:
			m_Good++;
			m_Late++;
			m_Combo++;
			m_Score = m_Score + (SCORE_PER_NOTE * m_Fever * 1);
			break;
		case JUD_LATE_MISS:
			m_Miss++;
			m_Late++;
			m_Combo = 0;
			m_Missed++;
			break;
		}
		int i = m_Note[input][0]->GetKey();
		Vector2 vc;
		switch (i)
		{
		default:
		case 1:
			vc = Vector2(X_2, Y_4);
			break;
		case 2:
			vc = Vector2(X_3, Y_5);
			break;
		case 3:
			vc = Vector2(X_4, Y_4);
			break;
		case 4:
			vc = Vector2(X_1, Y_3);
			break;
		case 5:
			vc = Vector2(X_5, Y_3);
			break;
		case 6:
			vc = Vector2(X_2, Y_2);
			break;
		case 7:
			vc = Vector2(X_3, Y_1);
			break;
		case 8:
			vc = Vector2(X_4, Y_2);
			break;
		}
		vc.x -= 125.f;
		vc.y -= 125.f;
		FXManager::GetInstance().AddFX(20, vc, ResourceID::PLAY_NOTE_CLICK, false);
		m_Note[input].erase(m_Note[input].begin());
		m_PassedNote++;
	}
}

void RSSheet::RenderNote(float PlayingTime, float TimePerBeat)
{
	bool isMiss = false;
	if (m_Missed > 0)
	{
		isMiss = true;
	}

	MagicCircle::GetInstance().OnRender(isMiss,b_Fever);

	for (int i = 0; i < 8; i++)
	{
		if (m_Note[i].size() > 0)
		{
			for (unsigned int j = 0; j < m_Note[i].size(); j++)
			{
				int rslt = m_Note[i][j]->RenderPosition(PlayingTime, TimePerBeat);
				if (m_Note[i][j]->IsLast())
				{
					if (rslt == 1) // 이미 지나간 노트 -> 미스 처리를 해야한다(입력을 받지 않았기 때문)
					{
						m_Note[i].erase(m_Note[i].begin());
						m_Miss++;
						m_PassedNote++;
						m_Combo = 0;
						m_Missed++;
						j--;
					}
					if (rslt == 2) // 아직 그릴 필요가 없는 노트
					{
						// 이 뒤로는 그릴 필요가 없으니 루프 탈출
						break;
					}
				}
				else
				{
					if (rslt == 1) // 이미 지나간 노트 -> 미스 처리를 해야한다(입력을 받지 않았기 때문)
					{
						m_Note[i].erase(m_Note[i].begin());
						m_Miss++;
						m_PassedNote++;
						m_Combo = 0;
						m_Missed++;
						j--;
					}
					if (rslt == 2) // 아직 그릴 필요가 없는 노트
					{
						// 이 뒤로는 그릴 필요가 없으니 루프 탈출
						break;
					}
				}
			}
		}
	}
	if (m_FeverStack >= FEVER_STACK)
	{
		if (m_Fever == 1)
		{
			m_FeverTime = PlayingTime;
			m_Fever = 2;
			b_Fever = true;
		}
	}
	if (m_Fever > 1)
	{
		if (PlayingTime - m_FeverTime >= 10.f)
		{
			m_Fever = 1;
			m_FeverStack = 0;
			b_Fever = false;
		}
	}

	// 스코어 박스
	SetPositionW(Vector2(SCORE_BOX_X, SCORE_BOX_Y));
	Identify();
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_SCORE_BOX), 0, 0);
	D2DGraphics::GetInstance().WriteText(D2D1::ColorF(0xfffcfbee), { 0, 0,520, 144 }, L"HY견명조", 35, L"%d", m_Score);
	Identify();


	// 체력바
	float hp = m_PlayerHP / PLAYER_DEF_HP;
	SetPositionW(Vector2(UI_BAR_X, UI_HP_BAR_Y));
	Identify();
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAYER_HP_BAR_COVER), 0, 0);
	Identify();
	SetPositionW(Vector2(UI_BAR_X + UI_HP_BAR_STEP_X, UI_HP_BAR_Y + UI_HP_BAR_STEP_Y));
	Identify();
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAYER_HP_BAR_HEAD), 0, 0);
	Identify();
	SetPositionW(Vector2(UI_BAR_X + UI_HP_BAR_STEP_X + 19.f, UI_HP_BAR_Y + UI_HP_BAR_STEP_Y));
	Identify();
	MakeScale(Vector2(hp, 1), Vector2(0, 0));
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAYER_HP_BAR_BODY), 0, 0);
	Identify();
	SetPositionW(Vector2(UI_BAR_X + UI_HP_BAR_STEP_X + 18.5f + (UI_HP_BAR_BODY_X * hp), UI_HP_BAR_Y + UI_HP_BAR_STEP_Y));
	Identify();
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAYER_HP_BAR_TAIL), 0, 0);
	Identify();


	// 피버바
	float fvr;
	if (m_Fever == 1)
	{
		fvr = m_FeverStack / (float)FEVER_STACK;
	}
	else
	{
		fvr = (10.f - (PlayingTime - m_FeverTime)) / 10.f;
		if (fvr < 0)
		{
			fvr = 0;
		}
	}

	SetPositionW(Vector2(UI_BAR_X, UI_FEVER_BAR_Y));
	Identify();
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_FEVER_BAR_COVER), 0, 0);
	Identify();
	SetPositionW(Vector2(UI_BAR_X + UI_FE_BAR_STEP_X, UI_FEVER_BAR_Y + UI_FE_BAR_STEP_Y));
	Identify();
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_FEVER_BAR_HEAD), 0, 0);
	Identify();
	SetPositionW(Vector2(UI_BAR_X + UI_FE_BAR_STEP_X + 11.f, UI_FEVER_BAR_Y + UI_FE_BAR_STEP_Y));
	Identify();
	MakeScale(Vector2(fvr, 1), Vector2(0, 0));
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_FEVER_BAR_BODY), 0, 0);
	Identify();
	SetPositionW(Vector2(UI_BAR_X + UI_FE_BAR_STEP_X + 10.5f + (UI_FE_BAR_BODY_X * fvr), UI_FEVER_BAR_Y + UI_FE_BAR_STEP_Y));
	Identify();
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_FEVER_BAR_TAIL), 0, 0);
	Identify();

}


void RSSheet::MonsterAttackJudge(int key)
{
	if (m_Missed == 0)
	{
		int rslt = m_Page[m_CurMon]->m_Type - key;
		switch (rslt)
		{
		default:
		case 0:
			//return normal;
			m_Score += 50 * m_Fever;
			break;
		case -2:
		case 1:
			//return fail;

			break;
		case 2:
		case -1:
			//return success;
			m_Score += 100 * m_Fever;
			break;
		}
		m_KilledMonster++;
		if ((m_KilledMonster % 5 )== 0)
		{
			if (m_HealReady)
			{
				m_HealReady = false;
				FXManager::GetInstance().RenderHeal();
				m_PlayerHP += 30.f;
				if (m_PlayerHP > (float)PLAYER_DEF_HP)
				{
					m_PlayerHP = (float)PLAYER_DEF_HP;
				}
			}
		}
		if ((m_KilledMonster % 5) == 1)
		{
			if (!m_HealReady)
			{
				m_HealReady = true;
			}
		}
		m_Page[m_CurMon]->m_Monster->SetState(2);
		m_Page[m_CurMon]->GoRemove();
	}
}

void RSSheet::RenderMonster()
{
	for (int i = m_Page.size() - 1; i > -1; i--)
	{
		m_Page[i]->Render();
	}


	// 기타 효과들 출력

	FXManager::GetInstance().RenderCombo(m_Combo, b_Fever);

}

void RSSheet::PageEvent()
{
	if (b_ShotEvent)
	{
		// 이벤트만 발생시켜주고 다시 false
		b_ShotEvent = false;
	}

	if (m_PassedNote >= m_MonNoteEa) // 몬스터에 대한 노트가 모두 지나감
	{	
		m_PlayerHP = m_PlayerHP - (DAMAGE_PER_NOTE * m_Missed);
		if (m_Page[m_CurMon]->m_Monster->GetState() == 0) // 피격됨!
		{
			b_ShotEvent = true;
			m_Page[m_CurMon]->m_Monster->SetState(1);
			m_Page[m_CurMon]->GoRemove();
			switch (m_Page[m_CurMon]->m_Type)
			{
			default:
			case 0:
				FXManager::GetInstance().AddFX(40, { 120,342 }, ResourceID::ATT_EFF_SLIME_FIRE, true);
				AudioManager::GetInstance().PlaySound(SoundID::MONSTER_ATTACK_FIRE);
				break;
			case 1:
				FXManager::GetInstance().AddFX(40, { 120,342 }, ResourceID::ATT_EFF_SLIME_WATER, true);
				AudioManager::GetInstance().PlaySound(SoundID::MONSTER_ATTACK_WATER);
				break;
			case 2:
				FXManager::GetInstance().AddFX(40, { 120,342 }, ResourceID::ATT_EFF_SLIME_GLASS, true);
				AudioManager::GetInstance().PlaySound(SoundID::MONSTER_ATTACK_GRASS);
				break;
			}
		}
		MagicCircle::GetInstance().ClearLine();
		m_Missed = 0;
		m_CurMon++;
		if (m_CurMon >= m_TotalMon)
		{
			// 몬스터가 모두 지나감
			// 게임 종료
			m_CurMon = m_TotalMon - 1;
		}
		else
		{
			m_PassedNote = 0;
			m_MonNoteEa = m_Page[m_CurMon]->m_Note.size();
			m_Page[m_CurMon]->isDraw = true;
		}
	}
}

#endif // !RSTOOL
