#include "stdafx.h"
#include "Title.h"

zzBitmap titleBG, bit_Makers, bit_HowtoCon;
zzBitmap PopUp;
zzBitmap Cursor;
zzBitmap bit_LevSelect, bit_LevCur;
zzBitmap bit_win, bit_lose;
zzBitmap bit_selmul;

int level;

HWND hEdit_GetIP;

SoundInfo snd_Lobby;
SoundInfo snd_Defeat;
SoundInfo snd_Victor;
BOOL snddef, sndvic;

BOOL ismulple;
BOOL mulOn;
int myPick = 0;
char m_ipget[16];

HWND g_hWnd;
HINSTANCE g_hInst;

void zzInitializeMenu(HWND hWnd, HINSTANCE hInst)
{
	soundOpen(&snd_Lobby, "./sounds/mp3/LobbyBGM.mp3");
	soundOpen(&snd_Defeat, "./sounds/Defeat.wav");
	soundOpen(&snd_Victor, "./sounds/Victory.wav");


	LoadBitmap_FromFile2(&titleBG, "./Resources/UI/mainTitle.bmp");
	LoadBitmap_FromFile2(&bit_Makers, "./Resources/UI/Makers.bmp");
	LoadBitmap_FromFile2(&bit_HowtoCon, "./Resources/UI/HowToCont.bmp");
	LoadBitmap_FromFile2(&PopUp, "./Resources/stop.bmp");
	LoadBitmap_FromFile2(&bit_selmul, "./Resources/hostguest.bmp");
	LoadBitmap_FromFile2(&Cursor, "./Resources/UI/button_result_click.bmp");

	LoadBitmap_FromFile2(&bit_LevSelect, "./Resources/UI/level.bmp");
	LoadBitmap_FromFile2(&bit_LevCur, "./Resources/UI/level_click.bmp");
	LoadBitmap_FromFile2(&bit_win, "./Resources/UI/win.bmp");
	LoadBitmap_FromFile2(&bit_lose, "./Resources/UI/lose.bmp");


	soundPlayLooping(&snd_Lobby);
	soundPause(&snd_Lobby);
	soundPlay(&snd_Defeat);
	soundPause(&snd_Defeat);

	soundPlay(&snd_Victor);
	soundPause(&snd_Victor);

	
	ismulple = FALSE;
	snddef = FALSE;
	sndvic = FALSE;


	level = 1;

	mulOn = TRUE;
	hEdit_GetIP = CreateWindow("edit",
		NULL,
		WS_CHILD | WS_BORDER |
		ES_AUTOHSCROLL,
		700, 250, 100, 25, g_hWnd, (HMENU)9000,
		g_hInst, NULL);

	g_hWnd = hWnd;
	g_hInst = hInst;
	mulOn = FALSE;
}

int zzMainTitle(COORD mouse)
{
	DrawBitmap_Simple(0, 0, &titleBG);
	if (snd_Lobby.isPause)
	{
		soundSeek(&snd_Lobby, 0);
		soundPlayLooping(&snd_Lobby);
	}

	switch (myPick)
	{
	case 0:
		zzDrawAlphaBlendSprite_Simple(1230, 234, &Cursor);
		break;
	case 1:
		zzDrawAlphaBlendSprite_Simple(1230, 334, &Cursor);
		break;
	case 2:
		zzDrawAlphaBlendSprite_Simple(1230, 435, &Cursor);
		break;
	case 3:
		zzDrawAlphaBlendSprite_Simple(1230, 534, &Cursor);
		break;
	case 4:
		zzDrawAlphaBlendSprite_Simple(1230, 694, &Cursor);
		break;
	}

	if (UpKeyInput())
	{
		myPick--;
		if (myPick < 0)
		{
			myPick = 4;
		}
	}

	if (DownKeyInput())
	{
		myPick++;
		if (myPick > 4)
		{
			myPick = 0;
		}
	}

	if (MLBTNInput() == 3)
	{
		if (mouse.X > 1230)
		{
			if (mouse.X < 1671)
			{
				if (mouse.Y > 234 && mouse.Y < 311)
				{
					soundPause(&snd_Lobby);
					return 17;
				}
				if (mouse.Y > 334 && mouse.Y < 411)
				{
					soundPause(&snd_Lobby);
					return 3;
				}
				if (mouse.Y > 435 && mouse.Y < 512)
				{
					return 15;
				}
				if (mouse.Y > 534 && mouse.Y < 611)
				{
					return 16;
				}
				if (mouse.Y > 694 && mouse.Y < 771)
				{
					return 5;
				}
			}
		}
	}

	if (SpaceKeyInput() || EnterKeyInput())
	{
		switch (myPick)
		{
		case 0: // 싱글플레이
			soundPause(&snd_Lobby);
			myPick = 0;
			return 17;
		case 1: // 멀티 플레이 메뉴
			soundPause(&snd_Lobby);
			myPick = 0;
			return 3;
		case 2: // 조작 방법
			return 15;
		case 3: // 만든 이들
			return 16;
		case 4: // 게임 종료
			myPick = 0;
			return 5;
		}
	}
	
	DrawAllToScreen();
	return 0;
}

int zzInGamePopUpMenu(COORD mouse)
{
	zzDrawAlphaBlendSprite_Simple(470, 150, &PopUp);
	switch (myPick)
	{
	case 0:
		zzDrawAlphaBlendSprite_Simple(662, 360, &Cursor);
		break;
	case 1:
		zzDrawAlphaBlendSprite_Simple(662, 480, &Cursor);
		break;
	}

	if (MLBTNInput() == 3)
	{
		if (mouse.X > 662 && mouse.X < 903)
		{
			if (mouse.Y > 360 && mouse.Y < 437)
			{
				return 17;
			}

			if (mouse.Y > 480 && mouse.Y < 557)
			{
				return 0;
			}
		}
	}


	if (UpKeyInput())
	{
		myPick--;
		if (myPick < 0)
		{
			myPick = 1;
		}
	}

	if (DownKeyInput())
	{
		myPick++;
		if (myPick > 1)
		{
			myPick = 0;
		}
	}

	DrawAllToScreen();
	if (SpaceKeyInput() || EnterKeyInput())
	{
		switch (myPick)
		{
		case 0:
			myPick = 0;
			return 17;
		case 1:
			myPick = 0;
			return 0;
		}
	}
	if (EscKeyInput())
	{
		return 1;
	}
	return 2;
}

int zzMultyPlayMenu(COORD mouse)
{
	zzDrawAlphaBlendSprite_Simple(470, 150, &bit_selmul);
	switch (myPick)
	{
	case 0:
		zzDrawAlphaBlendSprite_Simple(662, 360, &Cursor);
		break;
	case 1:
		zzDrawAlphaBlendSprite_Simple(662, 480, &Cursor);
		break;
	}

	if (UpKeyInput())
	{
		myPick--;
		if (myPick < 0)
		{
			myPick = 1;
		}
	}

	if (DownKeyInput())
	{
		myPick++;
		if (myPick > 1)
		{
			myPick = 0;
		}
	}

	if (MLBTNInput() == 3)
	{
		if (mouse.X > 662 && mouse.X < 903)
		{
			if (mouse.Y > 360 && mouse.Y < 437)
			{
				return 6;
			}

			if (mouse.Y > 480 && mouse.Y < 557)
			{
				return 7;
			}
		}
	}

	DrawAllToScreen();
	if (EscKeyInput())
	{
		return 0;
	}
	if (SpaceKeyInput() || EnterKeyInput())
	{
		switch (myPick)
		{
		case 0:
			return 6; // 호스트
		case 1:
			return 7; // 클라
		}
	}
	return 3;
}

int zzGetHost()
{
	if (startServer())
	{
		ismulple = TRUE;
		zzStartMultiStage(1);
		return 8;
	}
	return 6;
}

int zzGetIPAdress(COORD mouse)
{
	if (!mulOn) // 한번만 동작하도록
	{
		mulOn = TRUE;
		ShowWindow(hEdit_GetIP, SW_SHOW);
	}


	if (GetKeyState(VK_RBUTTON)&0x8000)
	{
		GetWindowText(hEdit_GetIP, m_ipget, 16);
		
		if (startClient(m_ipget)) // 성공하면
		{
			ismulple = TRUE;
			mulOn = FALSE;
			ShowWindow(hEdit_GetIP, SW_HIDE);
			zzStartMultiStage(2);
			return 9;
		}
	}


	return 7;
}

int zzVictor() // 20
{
	if (!sndvic)
	{
		sndvic = TRUE;
		soundSeek(&snd_Victor, 0);
		soundPlay(&snd_Victor);
	}
	zzDrawAlphaBlendSprite_Simple(0, 0, &bit_win);
	DrawAllToScreen();

	if (!ismulple)
	{
		if (MLBTNInput() == 3)
		{
			zzStartStage();
			sndvic = FALSE;
			return 1;
		}
		if (EscKeyInput() || SpaceKeyInput())
		{
			zzStartStage();
			sndvic = FALSE;
			return 1;
		}
		if (EnterKeyInput())
		{
			zzStartStage();
			sndvic = FALSE;
			return 1;
		}
	}
	else
	{
		if (MLBTNInput() == 3)
		{
			ismulple = FALSE;
			sndvic = FALSE;
			return 0;
		}
		if (EscKeyInput() || SpaceKeyInput())
		{
			ismulple = FALSE;
			sndvic = FALSE;
			return 0;
		}
		if (EnterKeyInput())
		{
			ismulple = FALSE;
			sndvic = FALSE;
			return 0;
		}
	}
	return 20;

}

int zzLoser() // 21
{
	if (!snddef)
	{
		snddef = TRUE;
		soundSeek(&snd_Defeat, 0);
		soundPlay(&snd_Defeat);
	}

	zzDrawAlphaBlendSprite_Simple(0, 0, &bit_lose);
	DrawAllToScreen();

	if (!ismulple)
	{
		if (MLBTNInput() == 3)
		{
			snddef = FALSE;
			return 17;
		}
		if (EscKeyInput() || SpaceKeyInput())
		{
			snddef = FALSE;
			return 17;
		}
		if (EnterKeyInput())
		{
			snddef = FALSE;
			return 17;
		}
	}
	else
	{
		if (MLBTNInput() == 3)
		{
			ismulple = FALSE;
			snddef = FALSE;
			return 0;
		}
		if (EscKeyInput() || SpaceKeyInput())
		{
			ismulple = FALSE;
			snddef = FALSE;
			return 0;
		}
		if (EnterKeyInput())
		{
			ismulple = FALSE;
			snddef = FALSE;
			return 0;
		}
	}
	return 21;
}

int zzHowToControl() // 15
{
	DrawBitmap_Simple(0, 0, &bit_HowtoCon);
	DrawAllToScreen();

	if (MLBTNInput() == 3)
	{
		return 0;
	}
	if (EscKeyInput() || SpaceKeyInput())
	{
		return 0;
	}
	if (EnterKeyInput())
	{
		return 0;
	}
	return 15;
}

int zzMakers() // 16
{
	DrawBitmap_Simple(0, 0, &bit_Makers);
	DrawAllToScreen();

	if (MLBTNInput() == 3)
	{
		return 0;
	}
	if (EscKeyInput() || SpaceKeyInput())
	{
		return 0;
	}
	if (EnterKeyInput())
	{
		return 0;
	}
	return 16;
}

int zzStageSelect(COORD mouse) // 17
{
	zzDrawAlphaBlendSprite_Simple(0, 0, &bit_LevSelect);

	switch (level)
	{
	case 1:
		zzDrawAlphaBlendSprite_Simple(410, 300, &bit_LevCur);
		break;
	case 2:
		zzDrawAlphaBlendSprite_Simple(626, 300, &bit_LevCur);
		break;
	case 3:
		zzDrawAlphaBlendSprite_Simple(838, 300, &bit_LevCur);
		break;
	case 4:
		zzDrawAlphaBlendSprite_Simple(1052, 300, &bit_LevCur);
		break;
	case 5:
		zzDrawAlphaBlendSprite_Simple(410, 490, &bit_LevCur);
		break;
	case 6:
		zzDrawAlphaBlendSprite_Simple(626, 490, &bit_LevCur);
		break;
	case 7:
		zzDrawAlphaBlendSprite_Simple(838, 490, &bit_LevCur);
		break;
	case 8:
		zzDrawAlphaBlendSprite_Simple(1052, 490, &bit_LevCur);
		break;
	}

	if (mouse.Y > 300 && mouse.Y < 480)
	{
		if (mouse.X > 410 && mouse.X < 590)
		{
			level = 1;
		}
		if (mouse.X > 626 && mouse.X < 806)
		{
			level = 2;
		}
		if (mouse.X > 838 && mouse.X < 1018)
		{
			level = 3;
		}
		if (mouse.X > 1052 && mouse.X < 1232)
		{
			level = 4;
		}
	}
	if (mouse.Y > 490 && mouse.Y < 670)
	{
		if (mouse.X > 410 && mouse.X < 590)
		{
			level = 5;
		}
		if (mouse.X > 626 && mouse.X < 806)
		{
			level = 6;
		}
		if (mouse.X > 838 && mouse.X < 1018)
		{
			level = 7;
		}
		if (mouse.X > 1052 && mouse.X < 1232)
		{
			level = 8;
		}
	}

	if (LeftKeyInput())
	{
		level--;
	}
	if (RightKeyInput())
	{
		level++;
	}
	if (DownKeyInput())
	{
		level += 4;
	}
	if (UpKeyInput())
	{
		level -= 4;
	}

	if (level < 1)
	{
		level = 1;
	}
	if (level > 8)
	{
		level = 8;
	}

	if (MLBTNInput() == 3)
	{
		zzGetStage(level);
		zzStartStage();
		level = 1;
		return 1;
	}
	if (SpaceKeyInput() || EnterKeyInput())
	{
		zzGetStage(level);
		zzStartStage();
		level = 1;
		return 1;
	}

	if (EscKeyInput())
	{
		return 0;
	}

	DrawAllToScreen();
	return 17;
}