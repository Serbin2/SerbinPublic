#include "pchTool.h"

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
}


void RSSheet::GetInput(int input, float inputTime)
{
	switch (m_Note[input][0]->Judge(inputTime))
	{
	default:
	case JUD_NO_MATCH:
		return;
	case JUD_EARL_MISS:
		m_Miss++;
		m_Early++;
		m_Combo = 0;
		break;
	case JUD_EARL_GOOD:
		m_Good++;
		m_Early++;
		m_Combo++;
		break;
	case JUD_EARL_PERF:
		m_Perfect++;
		m_Early++;
		m_Combo++;
		break;
	case JUD_EXAC_PERF:
		m_Perfect++;
		m_Combo++;
		break;
	case JUD_LATE_PERF:
		m_Perfect++;
		m_Late++;
		m_Combo++;
		break;
	case JUD_LATE_GOOD:
		m_Good++;
		m_Late++;
		m_Combo++;
		break;
	case JUD_LATE_MISS:
		m_Miss++;
		m_Late++;
		m_Combo = 0;
		break;
	}
	m_Note[input].erase(m_Note[input].begin());
}

void RSSheet::RenderNote(float PlayingTime, float TimePerBeat)
{
	for (int i = 0; i < 8; i++)
	{
		for (unsigned int j = 0; j < m_Note[i].size(); j++)
		{
			int rslt = m_Note[i][j]->RenderPosition(PlayingTime, TimePerBeat);
			if (rslt == 1) // 이미 지나간 노트 -> 미스 처리를 해야한다(입력을 받지 않았기 때문)
			{
				m_Note[i].erase(m_Note[i].begin());
				m_Miss++;
				m_Combo = 0;
				j--;
			}
			if (rslt == 2) // 아직 그릴 필요가 없는 노트
			{
				// 이 뒤로는 그릴 필요가 없으니 루프 탈출
				break;
			}

			/*D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(800.f, 0.f));
			D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 300.f), L"Combo : %d", m_Combo);

			D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1000.f, 0.f));
			D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 350.f), L"Miss : %d", m_Miss);

			D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1200.f, 0.f));
			D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 400.f), L"Good : %d", m_Good);

			D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1400.f, 0.f));
			D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 450.f), L"Perfect : %d", m_Perfect);

			D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1600.f, 0.f));
			D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 450.f), L"Early : %d", m_Early);

			D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1800.f, 0.f));
			D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"Late : %d", m_Late);
			D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());*/
		}
	}


}



#endif // !RSTOOL
