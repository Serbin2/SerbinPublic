#include "pchApp.h"
#include "Player.h"



Player::Player() : m_PlayingTime(0), m_PlayLength(0), m_TimePerBeat(0),
m_key1(DEF_KEY_1), m_key2(DEF_KEY_2), m_key3(DEF_KEY_3), m_key4(DEF_KEY_4), m_key6(DEF_KEY_6),
m_key7(DEF_KEY_7), m_key8(DEF_KEY_8), m_key9(DEF_KEY_9),
m_key1State(0), m_key2State(0), m_key3State(0), m_key4State(0), m_key6State(0), m_key7State(0),
m_key8State(0), m_key9State(0), m_EscKetState(0), m_isPlaying(false),
m_keyFire(DEF_KEY_W), m_keyWater(DEF_KEY_G), m_keyGrass(DEF_KEY_F),
m_keyFireState(0), m_keyWaterState(0), m_keyGrassState(0)
{

}

Player::~Player()
{
}

void Player::OnRender()
{

}

void Player::Animate()
{

}

void Player::PlayingSheetLoad(LPCTSTR filePath)
{
	for (int i = 0; i < m_CurPlayingSheet.m_Page.size(); i++)
	{
		for (int j = 0; j < m_CurPlayingSheet.m_Page[i]->m_Note.size(); j++)
		{
			delete m_CurPlayingSheet.m_Page[i]->m_Note[j];
		}
		m_CurPlayingSheet.m_Page[i]->m_Note.clear();
		delete m_CurPlayingSheet.m_Page[i];
	}
	m_CurPlayingSheet.m_Page.clear();

	RSLoadSheet(filePath, &m_CurPlayingSheet);
	
}

void Player::PlayingMusicLoad(LPCTSTR filePath)
{
	if (m_CurPlayingMusic != nullptr)
	{
		delete m_CurPlayingMusic;
	}
	m_CurPlayingMusic = new SoundEvent();
	AudioManager::GetInstance().AudioEngine->loadFile(filePath, *m_CurPlayingMusic);
}

void Player::GamePlayInit() // 처음 시작 또는 재시작 시 호출하세요
{
	m_CurPlayingSheet.RestoreNotePool();
	m_CurPlayingMusic->sourceVoice->FlushSourceBuffers();
	AudioManager::GetInstance().AudioEngine->SubmitSourceVoice(*m_CurPlayingMusic);

	m_PlayLength = m_CurPlayingSheet.m_SongLength + AFTER_MUSIC_TIME;
	m_TimePerBeat = 60.f / m_CurPlayingSheet.m_BPM;

	for (int i = 0; i < m_CurPlayingSheet.m_Page.size(); i++)
	{
		m_CurPlayingSheet.m_Page[i]->InitMonsterInfo();
		int k = m_CurPlayingSheet.m_Page[i]->m_Note.size();
		if (k > 0)
		{
			m_CurPlayingSheet.m_Page[i]->m_Note[k - 1]->SetLast();
		}
		
	}
	MagicCircle::GetInstance().ClearLine();
	m_IsFisrt = true;
	b_ShotEvent = false;
}

unsigned int Player::GamePlay()
{
	if (m_IsFisrt)
	{
		AudioManager::GetInstance().AudioEngine->playSoundEvent(*m_CurPlayingMusic);
		m_isPlaying = true;
		b_ShotEvent = false;

		Timer::GetInstance().Update();
		Timer::GetInstance().Update();
		m_PlayingTime = 0;
		m_IsFisrt = false;
	}

	if (!m_isPlaying)
	{
		AudioManager::GetInstance().AudioEngine->playSoundEvent(*m_CurPlayingMusic);
		m_isPlaying = true;
	}

	m_PlayingTime += Timer::GetInstance().DeltaTime; // 여기부터 논리 시작
	

	// 입력을 받는 부분
	if (!GetKey()) // ESC key를 누른경우 들어감
	{
		AudioManager::GetInstance().AudioEngine->stopSoundEvent(*m_CurPlayingMusic);
		m_isPlaying = false;
		// 여기에 루프를 탈출하고 메뉴를 호출하는 구문을 넣어주세요.

		return 1;
	}
	m_CurPlayingSheet.PageEvent();


	if (m_PlayingTime >= m_PlayLength)
	{
		// 여기에서 게임이 종료됩니다.
		AudioManager::GetInstance().AudioEngine->stopSoundEvent(*m_CurPlayingMusic);
		OneGameData data;
		data.m_Combo = m_CurPlayingSheet.m_MaxCombo;
		data.m_Good = m_CurPlayingSheet.m_Good;
		data.m_HP = m_CurPlayingSheet.m_PlayerHP;
		data.m_Miss = m_CurPlayingSheet.m_Miss;
		data.m_Perfect = m_CurPlayingSheet.m_Perfect;
		data.m_Score = m_CurPlayingSheet.m_Score;
		data.m_Kill = m_CurPlayingSheet.m_KilledMonster;
		float allnote = m_CurPlayingSheet.m_Good + m_CurPlayingSheet.m_Perfect + m_CurPlayingSheet.m_Early + m_CurPlayingSheet.m_Late + m_CurPlayingSheet.m_Miss;
		float oknote = m_CurPlayingSheet.m_Perfect * (m_CurPlayingSheet.m_Good * 0.8);
		data.m_Rate = oknote / allnote * 100;

		GameManager::GetInstance().SetOneGameData(data);		
		GameManager::GetInstance().AddOneGameDataFromFile();

		m_isPlaying = false;
		// 여기에 루프를 탈출하고 메뉴를 호출하는 구문을 넣어주세요.
		return 2;
	}

	if (m_CurPlayingSheet.b_ShotEvent)
		this->b_ShotEvent = true;
	return 0;
}

void Player::PlayRender()
{
	m_CurPlayingSheet.RenderNote(m_PlayingTime, m_TimePerBeat);
	m_CurPlayingSheet.RenderMonster();

	float progress = m_PlayingTime / m_PlayLength;
	// 노래 진행도
	SetPositionW(Vector2(0, 0));
	Identify();
	MakeScale(Vector2(progress, 1), Vector2(0, 0));
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_UI_PROGRESS_BAR), 0, 0);

	// 디버그 데이터
	/*
	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(800.f, 0.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 300.f), L"Combo : %d", m_CurPlayingSheet.m_Combo);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1000.f, 0.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 350.f), L"Miss : %d", m_CurPlayingSheet.m_Miss);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1200.f, 0.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 400.f), L"Good : %d", m_CurPlayingSheet.m_Good);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1400.f, 0.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 450.f), L"Perfect : %d", m_CurPlayingSheet.m_Perfect);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1600.f, 0.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 450.f), L"Early : %d", m_CurPlayingSheet.m_Early);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1800.f, 0.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"Late : %d", m_CurPlayingSheet.m_Late);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1400.f, 400.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"Passed : %d", m_CurPlayingSheet.m_PassedNote);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1400.f, 600.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"total : %d", m_CurPlayingSheet.m_MonNoteEa);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0.f, 400.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"PlayingTime : %.2f", m_PlayingTime);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0.f, 500.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"Missed : %d", m_CurPlayingSheet.m_Missed);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0.f, 600.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"HP : %.2f", m_CurPlayingSheet.m_PlayerHP);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0.f, 700.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"totalMon : %d", m_CurPlayingSheet.m_TotalMon);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0.f, 800.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"totalMon : %d", m_CurPlayingSheet.m_CurMon);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0.f, 900.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"FeverStack : %d", m_CurPlayingSheet.m_FeverStack);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(0.f, 1000.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"Fever : %d", m_CurPlayingSheet.m_Fever);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1400.f, 800.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"Time : %.2f", m_PlayingTime);
	
	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1400.f, 900.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"Long : %.2f", m_CurPlayingSheet.m_SongLength);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1400.f, 1000.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"true : %d", m_isPlaying);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1400.f, 1100.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"true : %d", m_IsFisrt);

	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Translation(1500.f, 1100.f));
	D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::Black, D2D1::RectF(500.0f, 0.0f, 700.f, 500.f), L"per bit : %.2f", m_TimePerBeat);


	D2DGraphics::GetInstance().GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	*/
}

bool Player::GetKey()
{
	if (GetAsyncKeyState(m_key1))
	{
		m_key1State = m_key1State | 0x01;
		if (m_key1State == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(0, m_PlayingTime);
		}
	}
	if (GetAsyncKeyState(m_key2))
	{
		m_key2State = m_key2State | 0x01;
		if (m_key2State == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(1, m_PlayingTime);
		}
	}
	if (GetAsyncKeyState(m_key3))
	{
		m_key3State = m_key3State | 0x01;
		if (m_key3State == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(2, m_PlayingTime);
		}
	}
	if (GetAsyncKeyState(m_key4))
	{
		m_key4State = m_key4State | 0x01;
		if (m_key4State == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(3, m_PlayingTime);
		}
	}
	if (GetAsyncKeyState(m_key6))
	{
		m_key6State = m_key6State | 0x01;
		if (m_key6State == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(4, m_PlayingTime);
		}
	}
	if (GetAsyncKeyState(m_key7))
	{
		m_key7State = m_key7State | 0x01;
		if (m_key7State == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(5, m_PlayingTime);
		}
	}
	if (GetAsyncKeyState(m_key8))
	{
		m_key8State = m_key8State | 0x01;
		if (m_key8State == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(6, m_PlayingTime);
		}
	}
	if (GetAsyncKeyState(m_key9))
	{
		m_key9State = m_key9State | 0x01;
		if (m_key9State == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(7, m_PlayingTime);
		}
	}
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		m_EscKetState = m_EscKetState | 0x01;
		if (m_EscKetState == KEYDOWN)
		{
			return false;
		}
	}
	
	if (GetAsyncKeyState(m_keyFire))
	{
		m_keyFireState = m_keyFireState | 0x01;
		if (m_keyFireState == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(11, m_PlayingTime);
		}
	}
	if (GetAsyncKeyState(m_keyWater))
	{
		m_keyWaterState = m_keyWaterState | 0x01;
		if (m_keyWaterState == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(12, m_PlayingTime);
		}
	}
	if (GetAsyncKeyState(m_keyGrass))
	{
		m_keyGrassState = m_keyGrassState | 0x01;
		if (m_keyGrassState == KEYDOWN)
		{
			m_CurPlayingSheet.GetInput(13, m_PlayingTime);
		}
	}

	return true;
}

void Player::Finalize()
{
	for (int i = 0; i < m_CurPlayingSheet.m_Page.size(); i++)
	{
		for (int j = 0; j < m_CurPlayingSheet.m_Page[i]->m_Note.size(); j++)
		{
			delete m_CurPlayingSheet.m_Page[i]->m_Note[j];
		}
		m_CurPlayingSheet.m_Page[i]->m_Note.clear();
		delete m_CurPlayingSheet.m_Page[i];
	}
	m_CurPlayingSheet.m_Page.clear();
	delete m_CurPlayingMusic;
}

