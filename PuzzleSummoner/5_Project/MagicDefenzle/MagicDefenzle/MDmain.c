#include "stdafx.h"
#include "MDmain.h"

zzBitmap Background, Gems, myCursor, myCursor_s;
zzBitmap Hbar_Empty, Hbar_G, Hbar_R, Cbar_Empty, Cbar_f;
zzBitmap bit_StageMove;
zzBitmap bit_TileBoard;

zzBitmap summonFire, summonWater, summonWood, summonLight, summonDark;
zzBitmap enemFire, enemWater, enemWood, enemLight, enemDark;
zzBitmap bit_Ready, bit_Start, bit_stat;
zzSummonee summonDummy;
zzBitmap bit_ePortalL, bit_ePortalR, bit_mPortalL, bit_mPortalR;
zzSummonee TowerDummy;

zzList myList, enemyList;
zzList StageList;

SoundInfo snd_Battle, snd_PickTile, snd_TileMove;
SoundInfo snd_TileBreak01, snd_TileBreak02, snd_TileBreak03, snd_TileBreak04, snd_TileBreak05, snd_TileBreak06;
SoundInfo snd_Start;
SoundInfo snd_MakeSpec01, snd_MakeSpec02, snd_UseSpec01, snd_UseSpec02;

OneNode* CurNode;
OneNode* myFirst;
OneNode* enemyFirst;
OneNode* myTower;
OneNode* enemyTower;
OneNode* MDCurStage;
OneNode* NextMonster;

BOOL isCatch;

// �ִϸ��̼ǿ� ����
BOOL DroptheGem; // ��� �������� �ִϸ��̼�
int DroppingGemTick;
BOOL BlowCheck;
BOOL OnSwap;
BOOL BackSwap;
BOOL GameStarted;

BOOL SummonTime;

// ���� ������ Ÿ�̹� ��Ʈ�ѷ�
BOOL canControl;


COORD player1Cursor;
COORD oriGem, dstGem;
COORD oriMouse;

// �ʰ� ����
zzGems** GemMap;
zzGems* dummyGem;
zzGems swaper;



// ���� üũ�� ����
int myPower; // �̹� üũ�� ���� Ÿ�� ��
BOOL isMulti;
BOOL isServer;

// ��ȯ���� ����� ���� ���� üũ
int GemFire, GemWater, GemWood, GemLight, GemDark;

// ���� �÷��̾��� ����
int gameReady;
int tileSpeed;
int ComboPower;
int CurCombo;
int EnemySpawnTick;
int StageMove;
int NowStageNumber;
int NowMonsterNumber;
int TotalMonster;
int restoreMove;
int myFullHealth, enFullHealth;

void zzInitializeGame()
{
	/// ���ҽ� �ҷ�����
	LoadBitmap_FromFile2(&Background, "./Resources/Background.bmp");
	LoadBitmap_FromFile2(&Gems, "./Resources/Gemss.bmp");
	LoadBitmap_FromFile2(&myCursor, "./Resources/UI/Cursor.bmp");
	LoadBitmap_FromFile2(&myCursor_s, "./Resources/UI/Cursor_s.bmp");
	LoadBitmap_FromFile2(&bit_StageMove, "./Resources/UI/Number.bmp");
	LoadBitmap_FromFile2(&bit_TileBoard, "./Resources/TileBoard.bmp");

	LoadBitmap_FromFile2(&bit_Ready, "./Resources/UI/ready.bmp");
	LoadBitmap_FromFile2(&bit_Start, "./Resources/UI/start.bmp");

	LoadBitmap_FromFile2(&summonFire, "./Resources/Fire.bmp");
	LoadBitmap_FromFile2(&summonWater, "./Resources/Water.bmp");
	LoadBitmap_FromFile2(&summonWood, "./Resources/Wood.bmp");
	LoadBitmap_FromFile2(&summonLight, "./Resources/Light.bmp");
	LoadBitmap_FromFile2(&summonDark, "./Resources/Dark.bmp");

	LoadBitmap_FromFile2(&enemFire, "./Resources/enemFire01.bmp");
	LoadBitmap_FromFile2(&enemWater, "./Resources/enemWater01.bmp");
	LoadBitmap_FromFile2(&enemWood, "./Resources/enemWood01.bmp");
	LoadBitmap_FromFile2(&enemLight, "./Resources/enemLight01.bmp");
	LoadBitmap_FromFile2(&enemDark, "./Resources/enemDark01.bmp");

	LoadBitmap_FromFile2(&bit_ePortalL, "./Resources/enemPortalL.bmp");
	LoadBitmap_FromFile2(&bit_ePortalR, "./Resources/enemPortalR.bmp");
	LoadBitmap_FromFile2(&bit_mPortalL, "./Resources/PortalL.bmp");
	LoadBitmap_FromFile2(&bit_mPortalR, "./Resources/PortalR.bmp");

	LoadBitmap_FromFile2(&Hbar_Empty, "./Resources/UI/Hbar_Empty.bmp");
	LoadBitmap_FromFile2(&Hbar_G, "./Resources/UI/Hbar_G.bmp");
	LoadBitmap_FromFile2(&Hbar_R, "./Resources/UI/Hbar_R.bmp"); // ���� �¿� 4�ȼ� ���� 6�ȼ�
	LoadBitmap_FromFile2(&Cbar_Empty, "./Resources/UI/Combo_e.bmp");
	LoadBitmap_FromFile2(&Cbar_f, "./Resources/UI/Combo_f.bmp");
	LoadBitmap_FromFile2(&bit_stat, "./Resources/UI/stat.bmp");


	// �����
	soundOpen(&snd_Battle, "./sounds/mp3/BattleBGM.mp3");

	// ȿ����
	soundOpen(&snd_TileBreak01, "./sounds/mp3/Round x1.mp3");
	soundOpen(&snd_TileBreak02, "./sounds/mp3/Round x2.mp3");
	soundOpen(&snd_TileBreak03, "./sounds/mp3/Round x3.mp3");
	soundOpen(&snd_TileBreak04, "./sounds/mp3/Round x4.mp3");
	soundOpen(&snd_TileBreak05, "./sounds/mp3/Round x5.mp3");
	soundOpen(&snd_TileBreak06, "./sounds/mp3/Round x6.mp3");

	soundOpen(&snd_PickTile, "./sounds/mp3/Standard Button.mp3");
	soundOpen(&snd_TileMove, "./sounds/mp3/Symbol Drop Down.mp3");

	soundOpen(&snd_MakeSpec01, "./sounds/mp3/Fast Spin.mp3");
	soundOpen(&snd_MakeSpec02, "./sounds/mp3/Spin Button.mp3");
	soundOpen(&snd_UseSpec01, "./sounds/mp3/Symbol Effect_2-3.mp3");
	soundOpen(&snd_UseSpec02, "./sounds/mp3/Symbol Effect_4.mp3");

	soundOpen(&snd_Start, "./sounds/mp3/Machine break.mp3");


	/// �� ũ�� �Ҵ�
	GemMap = (zzGems * *)malloc(sizeof(zzGems*) * NumOfTile_Y);
	for (int i = 0; i < NumOfTile_Y; i++)
	{
		GemMap[i] = (zzGems*)malloc(sizeof(zzGems) * NumOfTile_X);
	}

	dummyGem = (zzGems*)malloc(sizeof(zzGems) * NumOfTile_X);
	NowStageNumber = 0;

	/// ����Ʈ �ʱ�ȭ
	ListInit(&myList);
	ListInit(&enemyList);
	ListInit(&StageList);


	zzLoadMap("./Stage/Stage.bin", &StageList);
	isMulti = FALSE;

	srand((int)time(NULL));
}

void zzGetStage(int level)
{
	NowStageNumber = level - 1;
}

void zzEndGame()
{
	for (int i = 0; i < NumOfTile_Y; i++)
	{
		free(GemMap[i]);
	}
	free(GemMap);
	free(dummyGem);
	/// ����Ʈ ����
	while (ListRemoveFirst(&myList))
	{
	}
	free(myList.head);
	while (ListRemoveFirst(&enemyList))
	{
	}
	free(enemyList.head);

	while (!ListIsEmpty(&StageList))
	{
		MDCurStage = stgListFindAtNode(&StageList, 0);
		while (!monListIsEmpty(&MDCurStage->d_stg))
		{
			monListRemoveFirst(&MDCurStage->d_stg);
		}
		free(MDCurStage->d_stg.head);
		stgListRemoveFirst(&StageList);
	}
	//for (int i = 0; i < StageList.count; i)
	//{
	//	MDCurStage = stgListFindAtNode(&StageList, StageList.count - 1);
	//	while (monListRemoveFirst(&MDCurStage->d_stg))
	//	{
	//	}
	//	free(MDCurStage->d_stg.head);
	//	stgListRemoveLast(&StageList);
	//}
	free(StageList.head);

}

void zzStartStage()
{
	soundSeek(&snd_Battle, 0);
	soundPlayLooping(&snd_Battle);
	soundPause(&snd_Battle);

	soundSeek(&snd_Start, 0);
	soundPlay(&snd_Start);
	soundPause(&snd_Start);

	MDCurStage = stgListFindAtNode(&StageList, NowStageNumber);
	TotalMonster = MDCurStage->d_stg.numofMonster;
	NowMonsterNumber = 0;
	NextMonster = monListFindAtNode(&MDCurStage->d_stg, NowMonsterNumber);

	/// ���� ������ �ʱ�ȭ
	gameReady = 0;
	DroppingGemTick = 0;
	ComboPower = 0;
	CurCombo = 0;
	EnemySpawnTick = 0;
	myPower = 0;
	canControl = FALSE;
	SummonTime = FALSE;
	BackSwap = FALSE;
	OnSwap = FALSE;
	BlowCheck = FALSE;
	DroptheGem = FALSE;
	isCatch = FALSE;
	GameStarted = FALSE;

	/// Ŀ�� ��ġ �ʱ�ȭ
	player1Cursor.X = 0;
	player1Cursor.Y = 0;
	oriGem.X = 0;
	oriGem.Y = 0;
	dstGem.X = 0;
	dstGem.Y = 0;

	/// �ƹ�ư �ʱ�ȭ
	GemFire = 0;
	GemWater = 0;
	GemWood = 0;
	GemLight = 0;
	GemDark = 0;
	restoreMove = 0;
	StageMove = MDCurStage->d_stg.stageTime;

	/// �� �ʱ�ȭ
	for (int x = 0; x < NumOfTile_Y; x++)
	{
		for (int y = 0; y < NumOfTile_X; y++)
		{
			GemMap[x][y].speciality = 0;
			GemMap[x][y].GemType = 0;
			GemMap[x][y].isEmpty = TRUE;
			GemMap[x][y].DropMe = FALSE;
			GemMap[x][y].SwapMe = FALSE;
		}
	}

	/// ����Ʈ ����
	while (ListRemoveFirst(&myList))
	{
	}
	while (ListRemoveFirst(&enemyList))
	{
	}

	tileSpeed = 48;

	/// �� �� Ÿ�� ����
	zzCreateTower(0, MDCurStage->d_stg.stageHP);
	ListInsertLast(&enemyList, TowerDummy);
	enemyTower = ListFindAtNode(&enemyList, enemyList.count - 1);
	enFullHealth = enemyTower->data.myHealth;
	zzCreateTower(1, 500);
	ListInsertLast(&myList, TowerDummy);
	myTower = ListFindAtNode(&myList, myList.count - 1);
	myFullHealth = myTower->data.myHealth;

	zzGetGameOpenTime();
}

void zzStartMultiStage(int i)
{
	isServer = FALSE;
	if (i == 1)
	{
		isServer = TRUE;
	}
	/*MDCurStage = stgListFindAtNode(&StageList, NowStageNumber);
	TotalMonster = MDCurStage->d_stg.numofMonster;
	NowMonsterNumber = 0;
	NextMonster = monListFindAtNode(&MDCurStage->d_stg, NowMonsterNumber);
*/
	/// ���� ������ �ʱ�ȭ
	gameReady = 0;
	DroppingGemTick = 0;
	ComboPower = 0;
	CurCombo = 0;
	EnemySpawnTick = 0;
	myPower = 0;
	canControl = FALSE;
	SummonTime = FALSE;
	BackSwap = FALSE;
	OnSwap = FALSE;
	BlowCheck = FALSE;
	DroptheGem = FALSE;
	isCatch = FALSE;
	GameStarted = FALSE;
	isMulti = TRUE;



	/// 
	m_GameStarted = TRUE;





	data.TYPE = 5;
	data.level = 0;
	data.spawntime = 0;

	/// Ŀ�� ��ġ �ʱ�ȭ
	player1Cursor.X = 0;
	player1Cursor.Y = 0;
	oriGem.X = 0;
	oriGem.Y = 0;
	dstGem.X = 0;
	dstGem.Y = 0;

	/// �ƹ�ư �ʱ�ȭ
	GemFire = 0;
	GemWater = 0;
	GemWood = 0;
	GemLight = 0;
	GemDark = 0;
	restoreMove = 0;
	StageMove = 5;

	/// �� �ʱ�ȭ
	for (int x = 0; x < NumOfTile_Y; x++)
	{
		for (int y = 0; y < NumOfTile_X; y++)
		{
			GemMap[x][y].speciality = 0;
			GemMap[x][y].GemType = 0;
			GemMap[x][y].isEmpty = TRUE;
			GemMap[x][y].DropMe = FALSE;
			GemMap[x][y].SwapMe = FALSE;
		}
	}

	/// ����Ʈ ����
	while (ListRemoveFirst(&myList))
	{
	}
	while (ListRemoveFirst(&enemyList))
	{
	}

	tileSpeed = 48;

	/// �� �� Ÿ�� ����
	zzCreateTower(0, 500);
	ListInsertLast(&enemyList, TowerDummy);
	enemyTower = ListFindAtNode(&enemyList, enemyList.count - 1);
	enFullHealth = enemyTower->data.myHealth;
	zzCreateTower(1, 500);
	ListInsertLast(&myList, TowerDummy);
	myTower = ListFindAtNode(&myList, myList.count - 1);
	myFullHealth = myTower->data.myHealth;

	zzGetGameOpenTime();
}

int zzMDmain(COORD mouse)
{
	if (snd_Start.isPause)
	{
		soundResume(&snd_Start);
	}
	if (GameStarted)
	{
		if (!isMulti)
		{
			if (snd_Battle.isPause)
			{

				soundResume(&snd_Battle);

			}
		}
	}


	// ��� ���
	DrawBitmap_Simple(0, 0, &Background);

	// ������ üũ
	zzCheckNowTime();

	/*_TT(100, 100, "TotalMonster : %d", TotalMonster);
	_TT(100, 130, "NowMonsterNumber : %d", NowMonsterNumber);
	_TT(1000, 200, "PlayerMove : %d", StageMove);



	_TT(100, 450, "RealTimeTick : %d", zzGetTick());
	_TT(100, 500, "RealTimeElapsed : %d", zzGetTotalTime());
	_TT(100, 550, "RealTimeFPS : %f", zzGetmyFPS());
	_TT(100, 600, "points : %d", CurCombo);
	_TT(100, 630, "Combo : %d", ComboPower);
	_TT(100, 680, "EnenmyHealth : %d", enemyTower->data.myHealth);
	_TT(100, 710, "Myhealth : %d", myTower->data.myHealth);
*/

	/// � �ൿ�� ���ϰ������� ��Ϲ�ġ�� üũ�ؾ��ϴ� ����.
	if (OnSwap == FALSE && BlowCheck == FALSE)
	{
		if (DroptheGem == FALSE && canControl == FALSE) // ��� ��ġ�� �ٲ�κ��� �ִ°�� ��� üũ
		{
			zzDropGemCheck();
		}
	}

	/// ���� üũ
	if (BlowCheck == TRUE)
	{
		zzBlowCheck();
	}

	if (GameStarted)
	{
		// ��ȯ�� ����
		if (SummonTime == TRUE)
		{
			zzSummoningCreature();
			SummonTime = FALSE;
		}
		// ��� ��ȯ�� ����
		if (!isMulti)
		{
			if (enemyTower->data.myHealth > 0)
			{
				if (NowMonsterNumber + 1 < TotalMonster)
				{
					if (EnemySpawnTick > NextMonster->d_mon.spawntime)
					{
						if (zzCreateSummonee(NextMonster->d_mon.TYPE, NextMonster->d_mon.level, 0, MDCurStage->d_stg.stageSpeed))
						{
							ListInsert(&enemyList, enemyList.count - 1, summonDummy);
						}
						NowMonsterNumber++;
						NextMonster = monListFindAtNode(&MDCurStage->d_stg, NowMonsterNumber);
						EnemySpawnTick = 0;
					}
					else
					{
						EnemySpawnTick++;
					}
				}
			}
		}
		else // net ��Ƽ �÷��̽� ��� ������ �޾Ƽ� ��ȯ�� ��ȯ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
			while (multiMonsterQue.count > 0)
			{
				NextMonster = monListFindAtNode(&multiMonsterQue, 0);
				if (zzCreateSummonee(NextMonster->d_mon.TYPE, NextMonster->d_mon.level, 0, 1))
				{
					ListInsert(&enemyList, enemyList.count - 1, summonDummy);
				}
				monListRemoveFirst(&multiMonsterQue);
			}
		}
		restoreMove++; // Ƚ������ ����
		if (restoreMove > 300)
		{
			StageMove += 1;
			restoreMove = 0;
		}
		if (StageMove > 5)
		{
			StageMove = 5;
		}
	}
	else
	{
		GemFire = 0;
		GemWater = 0;
		GemWood = 0;
		GemLight = 0;
		GemDark = 0;
	}

	/// ������ ����
	if (canControl == TRUE)
	{
		/// ������ ���°� �Ǹ� Ư����� ����
		if (ComboPower > 9)
		{
			if (rand() % 3 == 2)
			{
				soundSeek(&snd_MakeSpec02, 0);
				soundPlay(&snd_MakeSpec02);
				GemMap[rand() % NumOfTile_Y][rand() % NumOfTile_X].speciality = 2;
			}
			else
			{
				soundSeek(&snd_MakeSpec01, 0);
				soundPlay(&snd_MakeSpec01);
				GemMap[rand() % NumOfTile_Y][rand() % NumOfTile_X].speciality = 1;
			}
			ComboPower = 0;
		}

		if (!isMulti || (isMulti == TRUE && m_GameStarted == TRUE))
		{
			switch (MLBTNInput())
			{
			case 1: // ���콺 ����
				if (StageMove > 0)
				{
					if (mouse.X > GameboardX)
					{
						if (mouse.X < GameboardX + (TileSize * NumOfTile_X))
						{
							if (mouse.Y > GameboardY)
							{
								if (mouse.Y < GameboardY + (TileSize * NumOfTile_Y))
								{
									player1Cursor.X = (mouse.X - GameboardX) / TileSize;
									player1Cursor.Y = (mouse.Y - GameboardY) / TileSize;
									isCatch = TRUE;
									oriGem = player1Cursor;
									soundSeek(&snd_PickTile, 0);
									soundPlay(&snd_PickTile);
									oriMouse = mouse;
								}
							}
						}
					}
				}
				break;
			case 2: // ���콺 ��������(�巡��)
				if (StageMove > 0)
				{
					if (mouse.X > oriMouse.X)
					{
						if (mouse.X - oriMouse.X > TileSize)
						{
							player1Cursor.X++;
							if (player1Cursor.X > NumOfTile_X - 1)
							{
								player1Cursor.X = NumOfTile_X - 1;
							}
							else
							{
								dstGem = player1Cursor;
								GemMap[oriGem.Y][oriGem.X].SwapMe = TRUE;
								GemMap[dstGem.Y][dstGem.X].SwapMe = TRUE;
								OnSwap = TRUE;
								canControl = FALSE;

							}
						}
					}
					if (mouse.X < oriMouse.X)
					{
						if (oriMouse.X - mouse.X > TileSize)
						{
							player1Cursor.X--;
							if (player1Cursor.X < 0)
							{
								player1Cursor.X = 0;
							}
							else
							{
								dstGem = player1Cursor;
								GemMap[oriGem.Y][oriGem.X].SwapMe = TRUE;
								GemMap[dstGem.Y][dstGem.X].SwapMe = TRUE;
								OnSwap = TRUE;
								canControl = FALSE;
							}
						}
					}
					if (mouse.Y > oriMouse.Y)
					{
						if (mouse.Y - oriMouse.Y > TileSize)
						{
							player1Cursor.Y++;
							if (player1Cursor.Y > NumOfTile_Y - 1)
							{
								player1Cursor.Y = NumOfTile_Y - 1;
							}
							else
							{

								dstGem = player1Cursor;
								GemMap[oriGem.Y][oriGem.X].SwapMe = TRUE;
								GemMap[dstGem.Y][dstGem.X].SwapMe = TRUE;
								OnSwap = TRUE;
								canControl = FALSE;

							}
						}
					}
					if (mouse.Y < oriMouse.Y)
					{
						if (oriMouse.Y - mouse.Y > TileSize)
						{
							player1Cursor.Y--;
							if (player1Cursor.Y < 0)
							{
								player1Cursor.Y = 0;
							}
							else
							{

								dstGem = player1Cursor;
								GemMap[oriGem.Y][oriGem.X].SwapMe = TRUE;
								GemMap[dstGem.Y][dstGem.X].SwapMe = TRUE;
								OnSwap = TRUE;
								canControl = FALSE;

							}
						}
					}
				}
				break;
			case 3: // ���콺 ��
				if (StageMove > 0)
				{
					isCatch = FALSE;
				}
				break;
			case 4:
				// ������� ����Ű �Է�
				zzUserInput();
				// ������� ����Ű �Է�
				zzUserSelect();
				break;
			}
		}
	}

	zzDrawAlphaBlendSprite_Simple(enemyTower->data.Position.X
		, enemyTower->data.Position.Y - enemyTower->data.myHeight, &bit_ePortalR);
	zzDrawAlphaBlendSprite_Simple(myTower->data.Position.X
		, myTower->data.Position.Y - myTower->data.myHeight, &bit_mPortalL);




	/// ������ Ÿ�� �׸���
	if (DroptheGem == TRUE) // Ÿ���� ������ �� �ִϸ��̼�
	{
		zzDrawMovingGems();
	}
	if (OnSwap == TRUE) // Ÿ���� �������� �� �ִϸ��̼�
	{
		zzGemSwap();
	}

	// UI
	zzDrawUIHealth();
	zzDrawAlphaBlendSprite_Simple(GameboardX - 89, GameboardY - 69, &bit_TileBoard);
	zzDrawUIMove();

	// �������� ���� ��ü Ÿ�� �׸���
	zzDrawNoMoveGem();

	// �÷��̾� Ŀ�� �׸���
	if (isCatch)
	{
		DrawSprite_Simple(GameboardX + (TileSize * player1Cursor.X), GameboardY + (TileSize * player1Cursor.Y), &myCursor_s);
	}
	else
	{
		DrawSprite_Simple(GameboardX + (TileSize * player1Cursor.X), GameboardY + (TileSize * player1Cursor.Y), &myCursor);
	}

	// ĳ���͵� �׸���
	zzDrawCharacters();


	if (!GameStarted)
	{
		gameReady++;
		if (gameReady < 100)
		{
			DrawBitmap_Simple(0, 0, &bit_Ready);
		}
		else
		{
			zzDrawAlphaBlendSprite_Simple(0, 0, &bit_Start);
		}

		if (gameReady > 200)
		{
			GameStarted = TRUE;
			tileSpeed = 4;
			data.spawntime = 1;
			if (isMulti)
			{
				//netSend(NP_DATA);
				m_GameStarted == TRUE;
			}
		}
	}



	DrawAllToScreen();

	if (EscKeyInput()) // �Ͻ�����
	{
		if (!isMulti) // ��Ƽ�÷��̴� �Ͻ����� �Ұ���
		{
			soundPause(&snd_Battle);
			return 2;
		}
	}
	if (enemyTower->data.myHealth < 0) // �¸�
	{
		NowStageNumber++;
		if (NowStageNumber >= StageList.count)
		{
			NowStageNumber = 0;
		}
		if (isMulti)
		{
			if (isServer)
			{
				endServer();
			}
			else
			{
				endClient();
			}
			
		}
		soundPause(&snd_Battle);
		
			return 20;
		
	}
	if (myTower->data.myHealth < 0) // �й�
	{
		if (isMulti)
		{
			if (isServer)
			{
				endServer();
			}
			else
			{
				endClient();
			}
			
		}
		soundPause(&snd_Battle);
		return 21;
	}
	return 1;
}
// ������� ���� ���� ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void zzDrawUIHealth()
{
	float PofH;
	zzDrawAlphaBlendSprite_Simple(50, 50, &Hbar_Empty);
	zzDrawAlphaBlendSprite_Simple(1150, 50, &Hbar_Empty);
	zzDrawAlphaBlendSprite_Simple(1030, 80, &Cbar_Empty);
	PofH = (float)myTower->data.myHealth / (float)myFullHealth * 100.f;
	zxDrawAlphaBlendSprite(1154, 56, &Hbar_G, 0, 0, (int)((float)Hbar_G.Width / 100.f * PofH), 40, 255);
	PofH = (float)enemyTower->data.myHealth / (float)enFullHealth * 100.f;
	zxDrawAlphaBlendSprite(54, 56, &Hbar_R, 0, 0, (int)((float)Hbar_R.Width / 100.f * PofH), 40, 255);
	PofH = (float)ComboPower / 10.f * 100.f;
	zxDrawAlphaBlendSprite(1030, 80 + Cbar_f.Height - (int)((float)Cbar_f.Height / 100.f * PofH), &Cbar_f, 0, Cbar_f.Height - (int)((float)Cbar_f.Height / 100.f * PofH), 48, (int)((float)Cbar_f.Height / 100.f * PofH), 255);

}

void zzDrawUIMove()
{
	DrawTile(752, 10, &bit_StageMove, 6, StageMove, 0, 1);
	zzDrawAlphaBlendSprite_Simple(1350, 130, &bit_stat);
}

void zzDropGemCheck()
{
	/// �� ������ �ִ��� Ȯ���ϴ� �κ�
	for (int y = 1; y < NumOfTile_Y; y++)
	{
		for (int x = 0; x < NumOfTile_X; x++)
		{
			if (GemMap[y][x].isEmpty == TRUE) // ��ĭ
			{
				// �� ��ĭ�� ���� ����߸�
				for (int z = y - 1; z >= 0; z--)
				{
					GemMap[z][x].DropMe = TRUE;
				}
				DroptheGem = TRUE; // ���� �����ӿ� ���Ŷ�
			}
		}
	}

	// �� ���� ����� �ִ��� Ȯ��
	for (int x = 0; x < NumOfTile_X; x++)
	{
		if (GemMap[0][x].isEmpty == TRUE || GemMap[0][x].DropMe == TRUE) // �� ��ĭ�� �������ٸ� ���̵� �����ؾ� ��
		{
			dummyGem[x].speciality = 0;
			dummyGem[x].GemType = rand() % KINDOFCOLOR;
			dummyGem[x].isEmpty = FALSE;
			dummyGem[x].DropMe = TRUE;
			dummyGem[x].SwapMe = FALSE;
			DroptheGem = TRUE;
		}
	}
	if (DroptheGem == FALSE)
	{
		BlowCheck = TRUE; // ������ Ÿ���� ������ ����!
	}
}
void zzBlowCheck()
{
	int chkr = 0;
	for (int y = 0; y < NumOfTile_Y; y++)
	{
		for (int x = 0; x < NumOfTile_X; x++)
		{
			zzCheckGem(y, x);
			switch (GemMap[y][x].GemType)
			{
			case TYPE_FIRE:
				GemFire += myPower;
				break;
			case TYPE_WATER:
				GemWater += myPower;
				break;
			case TYPE_WOOD:
				GemWood += myPower;
				break;
			case TYPE_LIGHT:
				GemLight += myPower;
				break;
			case TYPE_DARK:
				GemDark += myPower;
				break;
			}
			chkr += myPower;
			myPower = 0;
		}
	}

	if (chkr == 0)
	{
		if (GameStarted)
		{
			canControl = TRUE; // ���� Ÿ���� ������ ���� ����
			SummonTime = TRUE;
			/// �޺�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (CurCombo > 1)
			{
				ComboPower += (int)((CurCombo / 2) + 1);
			}
			CurCombo = 0;
		}
	}
	else
	{
		if (GameStarted)
		{
			CurCombo++;
			switch (CurCombo)
			{
			case 1:
				soundSeek(&snd_TileBreak01, 0);
				soundPlay(&snd_TileBreak01);
				break;
			case 2:
				soundSeek(&snd_TileBreak02, 0);
				soundPlay(&snd_TileBreak02);
				break;
			case 3:
				soundSeek(&snd_TileBreak03, 0);
				soundPlay(&snd_TileBreak03);
				break;
			case 4:
				soundSeek(&snd_TileBreak04, 0);
				soundPlay(&snd_TileBreak04);
				break;
			case 5:
				soundSeek(&snd_TileBreak05, 0);
				soundPlay(&snd_TileBreak05);
				break;
			default:
				soundSeek(&snd_TileBreak06, 0);
				soundPlay(&snd_TileBreak06);
				break;
			}
		}
	}
	BlowCheck = FALSE;
}
void zzSummoningCreature()
{

	if (zzCreateSummonee(TYPE_WOOD, GemWood, 1, 1))
	{
		data.TYPE = TYPE_WOOD;
		data.level = GemWood;
		if (isMulti)
		{
			netSend(NP_DATA);
		}
		ListInsert(&myList, myList.count - 1, summonDummy);
		GemWood = 0;
	}
	if (zzCreateSummonee(TYPE_FIRE, GemFire, 1, 1))
	{
		{ // net ���� ���濡�� ���� ���� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			data.TYPE = TYPE_FIRE;
			data.level = GemFire;
		}
		if (isMulti)
		{
			netSend(NP_DATA);
		}
		ListInsert(&myList, myList.count - 1, summonDummy);
		GemFire = 0;
	}
	if (zzCreateSummonee(TYPE_WATER, GemWater, 1, 1))
	{
		{ // net ���� ���濡�� ���� ���� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			data.TYPE = TYPE_WATER;
			data.level = GemWater;
		}
		if (isMulti)
		{
			netSend(NP_DATA);
		}
		ListInsert(&myList, myList.count - 1, summonDummy);
		GemWater = 0;
	}
	if (zzCreateSummonee(TYPE_DARK, GemDark, 1, 1))
	{
		{ // net ���� ���濡�� ���� ���� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			data.TYPE = TYPE_DARK;
			data.level = GemDark;
		}
		if (isMulti)
		{
			netSend(NP_DATA);
		}
		ListInsert(&myList, myList.count - 1, summonDummy);
		GemDark = 0;
	}
	if (zzCreateSummonee(TYPE_LIGHT, GemLight, 1, 1))
	{
		{ // net ���� ���濡�� ���� ���� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			data.TYPE = TYPE_LIGHT;
			data.level = GemLight;
		}
		if (isMulti)
		{
			netSend(NP_DATA);
		}
		ListInsert(&myList, myList.count - 1, summonDummy);
		GemLight = 0;
	}


}

int zzCheckUpGem(int y, int x)
{
	if (0 < y)
	{
		if (GemMap[y][x].GemType == GemMap[y - 1][x].GemType)
		{
			return zzCheckUpGem(y - 1, x) + 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
int zzCheckDownGem(int y, int x)
{
	if (y < NumOfTile_Y - 1)
	{
		if (GemMap[y][x].GemType == GemMap[y + 1][x].GemType)
		{
			return zzCheckDownGem(y + 1, x) + 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
int zzCheckLeftGem(int y, int x)
{
	if (0 < x)
	{
		if (GemMap[y][x].GemType == GemMap[y][x - 1].GemType)
		{
			return zzCheckLeftGem(y, x - 1) + 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
int zzCheckRightGem(int y, int x)
{
	if (x < NumOfTile_X - 1)
	{
		if (GemMap[y][x].GemType == GemMap[y][x + 1].GemType)
		{
			return zzCheckRightGem(y, x + 1) + 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void zzDestroyGem(int y, int x)
{
	if (GemMap[y][x].isEmpty == FALSE && OnSwap == FALSE)
	{
		GemMap[y][x].isEmpty = TRUE;
		if (GemMap[y][x].speciality == 1)
		{
			soundSeek(&snd_UseSpec01, 0);
			soundPlay(&snd_UseSpec01);
			if (y > 0)
			{
				zzDestroyGem(y - 1, x);
			}
			if (y < NumOfTile_Y - 1)
			{
				zzDestroyGem(y + 1, x);
			}
			if (x > 0)
			{
				zzDestroyGem(y, x - 1);
			}
			if (x < NumOfTile_X - 1)
			{
				zzDestroyGem(y, x + 1);
			}
		}
		if (GemMap[y][x].speciality == 2)
		{
			soundSeek(&snd_UseSpec02, 0);
			soundPlay(&snd_UseSpec02);
			for (int a = 0; a < NumOfTile_Y; a++)
			{
				for (int b = 0; b < NumOfTile_X; b++)
				{
					if (GemMap[a][b].GemType == GemMap[y][x].GemType)
					{
						zzDestroyGem(a, b);
					}
				}
			}
		}

		myPower++;
	}
}

int zzCheckGem(int y, int x)
{
	BOOL DestroyMe = FALSE;
	if (GemMap[y][x].isEmpty == TRUE)
	{
		return FALSE;
	}
	int up = zzCheckUpGem(y, x);
	int down = zzCheckDownGem(y, x);
	int left = zzCheckLeftGem(y, x);
	int right = zzCheckRightGem(y, x);

	// ���� �ı�
	if (up + down > 1)
	{
		DestroyMe = TRUE;
		// ��� �ı�
		for (int i = 1; i <= up; i++)
		{
			zzDestroyGem(y - i, x);
		}
		// �ϴ� �ı�
		for (int i = 1; i <= down; i++)
		{
			zzDestroyGem(y + 1, x);
		}
	}

	// �¿� �ı�
	if (left + right > 1)
	{
		DestroyMe = TRUE;
		// �´� �ı�
		for (int i = 1; i <= left; i++)
		{
			zzDestroyGem(y, x - 1);
		}
		// ��� �ı�
		for (int i = 1; i <= right; i++)
		{
			zzDestroyGem(y, x + 1);
		}
	}

	if (DestroyMe == TRUE)
	{
		zzDestroyGem(y, x);
		return up + down + left + right;
	}

	return FALSE;
}

void zzGemSwap()
{
	if (DroppingGemTick == 0)
	{
		soundSeek(&snd_TileMove, 0);
		soundPlay(&snd_TileMove);
	}
	int chkr = 0;
	int SwapX = oriGem.X - dstGem.X;
	int SwapY = oriGem.Y - dstGem.Y;
	// �������� Ÿ�� �׸�
	DrawTile(GameboardX + (TileSize * oriGem.X) + ((-1) * SwapX * DroppingGemTick),
		GameboardY + (TileSize * oriGem.Y) + ((-1) * SwapY * DroppingGemTick),
		&Gems, KINDOFCOLOR, GemMap[oriGem.Y][oriGem.X].GemType, GemMap[oriGem.Y][oriGem.X].speciality, 3);
	// ��ǥ Ÿ�� �׸�
	DrawTile(GameboardX + (TileSize * dstGem.X) + (SwapX * DroppingGemTick),
		GameboardY + (TileSize * dstGem.Y) + (SwapY * DroppingGemTick),
		&Gems, KINDOFCOLOR, GemMap[dstGem.Y][dstGem.X].GemType, GemMap[dstGem.Y][dstGem.X].speciality, 3);

	if (BackSwap == FALSE)
	{
		DroppingGemTick += tileSpeed;
	}
	else
	{
		DroppingGemTick -= tileSpeed;
	}

	if (DroppingGemTick >= TileSize) // �����ϸ� �ڸ� �ٲٰ� üũ!
	{
		swaper = GemMap[oriGem.Y][oriGem.X];
		GemMap[oriGem.Y][oriGem.X] = GemMap[dstGem.Y][dstGem.X];
		GemMap[dstGem.Y][dstGem.X] = swaper;
		GemMap[oriGem.Y][oriGem.X].SwapMe = FALSE;
		GemMap[dstGem.Y][dstGem.X].SwapMe = FALSE;

		if (BackSwap == FALSE)
		{
			for (int y = 0; y < NumOfTile_Y; y++)
			{
				for (int x = 0; x < NumOfTile_X; x++)
				{
					chkr += zzCheckGem(y, x);
				}
			}

			if (chkr != 0) // ���ҿ� ����
			{
				StageMove--;
				BlowCheck = TRUE;
				OnSwap = FALSE;
				isCatch = FALSE;
				DroppingGemTick = 0;
			}
			else
			{
				BackSwap = TRUE; // ���ư��ð�
				swaper = GemMap[oriGem.Y][oriGem.X];
				GemMap[oriGem.Y][oriGem.X] = GemMap[dstGem.Y][dstGem.X];
				GemMap[dstGem.Y][dstGem.X] = swaper;
				GemMap[oriGem.Y][oriGem.X].SwapMe = TRUE;
				GemMap[dstGem.Y][dstGem.X].SwapMe = TRUE;
			}
			chkr = 0;
		}

	}

	if (DroppingGemTick <= 0) // �ǵ��ư��� ��
	{
		DroppingGemTick = 0;
		BackSwap = FALSE;
		OnSwap = FALSE;
		isCatch = FALSE;
		GemMap[oriGem.Y][oriGem.X].SwapMe = FALSE;
		GemMap[dstGem.Y][dstGem.X].SwapMe = FALSE;
	}
}
void zzDrawMovingGems()
{
	for (int y = 0; y < NumOfTile_Y; y++)
	{
		for (int x = 0; x < NumOfTile_X; x++)
		{
			if (GemMap[y][x].isEmpty == FALSE && GemMap[y][x].DropMe == TRUE)
			{
				DrawTile(GameboardX + (TileSize * x), GameboardY + (TileSize * y) + DroppingGemTick, &Gems, KINDOFCOLOR, GemMap[y][x].GemType, GemMap[y][x].speciality, 3);
			}
		}
	}
	for (int x = 0; x < NumOfTile_X; x++) // ���̵� ����������
	{
		if (dummyGem[x].isEmpty == FALSE && dummyGem[x].DropMe == TRUE)
		{
			DrawTile(GameboardX + (TileSize * x), GameboardY - (TileSize)+DroppingGemTick, &Gems, KINDOFCOLOR, dummyGem[x].GemType, dummyGem[x].speciality, 3);
		}
	}
	DroppingGemTick += tileSpeed;
	if (DroppingGemTick >= TileSize) // ƽ�� ������ �迭�� ����� ����� ���پ� ������ ( y+ )
	{
		// �Ʒ��������� �˻��ؾ���
		for (int y = NumOfTile_Y - 1; y >= 1; y--)
		{
			for (int x = NumOfTile_X - 1; x >= 0; x--)
			{
				if (GemMap[y][x].isEmpty == TRUE)
				{
					GemMap[y - 1][x].DropMe = FALSE;
					GemMap[y][x] = GemMap[y - 1][x];
					GemMap[y - 1][x].isEmpty = TRUE;
				}
			}
		}
		for (int x = 0; x < NumOfTile_X; x++) // �� ���� �˻�
		{
			if (GemMap[0][x].isEmpty == TRUE)
			{
				dummyGem[x].DropMe = FALSE;
				GemMap[0][x] = dummyGem[x];
				dummyGem[x].isEmpty = TRUE;
			}
		}
		DroppingGemTick = 0;
		DroptheGem = FALSE;
	}
}
void zzDrawCharacters()
{
	enemyFirst = zzFindFirst(&enemyList);
	myFirst = zzFindFirst(&myList);
	// �Ʊ� ĳ���� ���
	for (int i = 0; i < myList.count; i++)
	{
		CurNode = ListFindAtNode(&myList, i);
		Animate_PickPos(CurNode->data.Position.X,
			CurNode->data.Position.Y - CurNode->data.myHeight,
			&CurNode->data,
			CurNode->data.myState,
			255);
		CurNode->data.attackDelay++; // Ÿ�̹� �����

		if (CurNode->data.myState == STATE_ATTACK)
		{
			if ((enemyFirst != NULL && CurNode->data.Position.X >= enemyFirst->data.Position.X + enemyFirst->data.myWidth - COLLIDE) || enemyFirst == NULL)
			{
				CurNode->data.moveon = TRUE;
				CurNode->data.myState = STATE_IDLE;
			}
			else
			{
				if (CurNode->data.attackDelay == CHARSPEED * 6)
				{
					enemyFirst->data.myHealth -= zzAttackType(CurNode->data.myType, enemyFirst->data.myType, CurNode->data.myPower);
				}
			}
		}

		if (CurNode->data.moveon == TRUE)
		{
			CurNode->data.Position.X -= CurNode->data.mySpeed;
		}

		if (CurNode->data.myHealth < 1)
		{
			if (CurNode->data.myState != STATE_DEATH)
			{
				CurNode->data.moveon = FALSE;
				CurNode->data.myState = STATE_DEATH;
				CurNode->data.attackDelay = 0; // �����̸� ��� ����������(35�� �Ǹ� ������ ����Ʈ)
			}
		}

		if (CurNode->data.myState == STATE_IDLE)
		{
			if (enemyFirst != NULL)
			{
				if (CurNode->data.Position.X < enemyFirst->data.Position.X + enemyFirst->data.myWidth - COLLIDE)
				{
					CurNode->data.moveon = FALSE;
					CurNode->data.myState = STATE_ATTACK;
					CurNode->data.attackDelay = 0;
					CurNode->data.motions[STATE_ATTACK].nowFrame = 0;
				}
			}
		}

		if (CurNode->data.Position.X <= ENEMYPORTAL - COLLIDE - 50)
		{
			CurNode->data.myHealth = 0;
		}

		if (CurNode->data.myState == STATE_DEATH)
		{
			if (CurNode->data.attackDelay > (CHARSPEED * 7) - 1)
			{
				ListRemove(&myList, i);
				i--;
			}
		}

		if (CurNode->data.attackDelay > CHARSPEED * 7)
		{
			CurNode->data.attackDelay = 0;
		}
	}
	// �� ĳ���� ���
	for (int i = 0; i < enemyList.count; i++)
	{
		CurNode = ListFindAtNode(&enemyList, i);
		Animate_PickPos(CurNode->data.Position.X,
			CurNode->data.Position.Y - CurNode->data.myHeight,
			&CurNode->data,
			CurNode->data.myState,
			255);
		CurNode->data.attackDelay++; // Ÿ�̹� �����

		if (CurNode->data.myState == STATE_ATTACK)
		{
			if ((myFirst != NULL && CurNode->data.Position.X + CurNode->data.myWidth - COLLIDE <= myFirst->data.Position.X) || myFirst == NULL)
			{
				CurNode->data.moveon = TRUE;
				CurNode->data.myState = STATE_IDLE;
			}
			else
			{
				if (CurNode->data.attackDelay == CHARSPEED * 6)
				{
					myFirst->data.myHealth -= zzAttackType(CurNode->data.myType, myFirst->data.myType, CurNode->data.myPower);
				}
			}
		}

		if (CurNode->data.moveon == TRUE)
		{
			CurNode->data.Position.X += CurNode->data.mySpeed;
		}

		if (CurNode->data.myHealth < 1)
		{
			if (CurNode->data.myState != STATE_DEATH)
			{
				CurNode->data.moveon = FALSE;
				CurNode->data.myState = STATE_DEATH;
				CurNode->data.attackDelay = 0; // �����̸� ��� ����������(35�� �Ǹ� ������ ����Ʈ)
			}
		}

		if (CurNode->data.myState == STATE_IDLE)
		{
			if (myFirst != NULL)
			{
				if (CurNode->data.Position.X + CurNode->data.myWidth - COLLIDE > myFirst->data.Position.X)
				{
					CurNode->data.moveon = FALSE;
					CurNode->data.myState = STATE_ATTACK;
					CurNode->data.attackDelay = 0;
					CurNode->data.motions[STATE_ATTACK].nowFrame = 0;
				}
			}
		}



		if (CurNode->data.Position.X > MYPORTAL + COLLIDE + 50)
		{
			CurNode->data.myHealth = 0;
		}

		if (CurNode->data.myState == STATE_DEATH)
		{
			if (CurNode->data.attackDelay > (CHARSPEED * 7) - 1)
			{
				ListRemove(&enemyList, i);
				i--;
			}
		}

		if (CurNode->data.attackDelay > CHARSPEED * 7)
		{
			CurNode->data.attackDelay = 0;
		}
	}
}
void zzDrawNoMoveGem()
{
	for (int y = 0; y < NumOfTile_Y; y++)
	{
		for (int x = 0; x < NumOfTile_X; x++)
		{
			if (GemMap[y][x].SwapMe == FALSE)
			{
				if (GemMap[y][x].isEmpty == FALSE)
				{
					if (GemMap[y][x].DropMe == FALSE)
					{
						DrawTile(GameboardX + (TileSize * x),
							GameboardY + (TileSize * y),
							&Gems,
							KINDOFCOLOR,
							GemMap[y][x].GemType,
							GemMap[y][x].speciality, 3);
					}
				}
			}
		}
	}
}

BOOL zzCreateSummonee(int type, int power, int team, int speed)
{
	if (power > 2)
	{
		switch (type)
		{
		case TYPE_FIRE:
			if (team == 1)
			{
				CreateCharacterRes(&summonDummy, &summonFire, 3, 7, CHARSPEED);
			}
			else
			{
				CreateCharacterRes(&summonDummy, &enemFire, 3, 7, CHARSPEED);
			}
			break;
		case TYPE_WATER:
			if (team == 1)
			{
				CreateCharacterRes(&summonDummy, &summonWater, 3, 7, CHARSPEED);
			}
			else
			{
				CreateCharacterRes(&summonDummy, &enemWater, 3, 7, CHARSPEED);
			}
			break;
		case TYPE_WOOD:
			if (team == 1)
			{
				CreateCharacterRes(&summonDummy, &summonWood, 3, 7, CHARSPEED);
			}
			else
			{
				CreateCharacterRes(&summonDummy, &enemWood, 3, 7, CHARSPEED);
			}
			break;
		case TYPE_LIGHT:
			if (team == 1)
			{
				CreateCharacterRes(&summonDummy, &summonLight, 3, 7, CHARSPEED);
			}
			else
			{
				CreateCharacterRes(&summonDummy, &enemLight, 3, 7, CHARSPEED);
			}
			break;
		case TYPE_DARK:
			if (team == 1)
			{
				CreateCharacterRes(&summonDummy, &summonDark, 3, 7, CHARSPEED);
			}
			else
			{
				CreateCharacterRes(&summonDummy, &enemDark, 3, 7, CHARSPEED);
			}
			break;
		}
		summonDummy.mySpeed = speed;
		summonDummy.myType = type;
		summonDummy.myTeam = team;
		summonDummy.myState = STATE_IDLE;
		summonDummy.Position.Y = PORTAL_AXIS;

		if (power < 5)
		{
			summonDummy.myHealth = 40;
			summonDummy.myPower = 10;
			summonDummy.mySize = 0.4f;
		}
		else
		{
			if (power < 8)
			{
				summonDummy.myHealth = 60;
				summonDummy.myPower = 15;
				summonDummy.mySize = 0.7f;
			}
			else
			{
				summonDummy.myHealth = 100;
				summonDummy.myPower = 20;
				summonDummy.mySize = 1.f;
			}
		}
		summonDummy.myHeight = (int)(((float)summonDummy.sheet->Height / 3.f) * summonDummy.mySize);
		summonDummy.myWidth = (int)(((float)summonDummy.sheet->Width / 7.f) * summonDummy.mySize);
		switch (team)
		{
		case 0:
			summonDummy.Position.X = ENEMYPORTAL - summonDummy.myWidth;
			break;
		case 1:
			summonDummy.Position.X = MYPORTAL;
			break;
		}
		summonDummy.attackDelay = 0;
		summonDummy.moveon = TRUE;
		return TRUE;
	}
	return FALSE;
}

OneNode* zzFindFirst(zzList* list)
{
	OneNode* tmp;
	for (int i = 0; i < list->count; i++)
	{
		tmp = ListFindAtNode(list, i);
		if (tmp->data.myHealth > 0)
		{
			return tmp;
		}
	}
	return NULL;
}

void zzCreateTower(int team, int health)
{
	if (team == 0)
	{
		CreateCharacterRes(&TowerDummy, &bit_ePortalL, 3, 7, 10);
	}
	else
	{
		CreateCharacterRes(&TowerDummy, &bit_mPortalR, 3, 7, 10);
	}

	TowerDummy.mySpeed = 0;
	TowerDummy.myType = TYPE_TOWER;
	TowerDummy.myTeam = team;
	TowerDummy.myState = STATE_IDLE;
	TowerDummy.Position.Y = PORTAL_AXIS;


	TowerDummy.myHealth = health;
	TowerDummy.myPower = 0;
	TowerDummy.mySize = 1.f;

	TowerDummy.myHeight = (int)(((float)TowerDummy.sheet->Height / 3.f) * TowerDummy.mySize);
	TowerDummy.myWidth = (int)(((float)TowerDummy.sheet->Width / 7.f) * TowerDummy.mySize);
	TowerDummy.attackDelay = 0;
	switch (team)
	{
	case 0:
		TowerDummy.Position.X = ENEMYPORTAL - TowerDummy.myWidth;
		break;
	case 1:
		TowerDummy.Position.X = MYPORTAL;
		break;
	}

	TowerDummy.attackDelay = 0;
	TowerDummy.moveon = FALSE;

}

int zzAttackType(int myType, int enemType, int power)
{
	if (enemType == TYPE_TOWER)
	{
		return power;
	}
	switch (myType)
	{
	case TYPE_FIRE:
		switch (enemType)
		{
		case TYPE_FIRE:
			return power;
		case TYPE_WATER:
			return (int)(power * 0.5);
		case TYPE_WOOD:
			return (int)(power * 1.5);
		case TYPE_LIGHT:
			return (int)(power * 1.2);
		case TYPE_DARK:
			return (int)(power * 0.8);
		}
	case TYPE_WATER:
		switch (enemType)
		{
		case TYPE_FIRE:
			return (int)(power * 1.5);
		case TYPE_WATER:
			return power;
		case TYPE_WOOD:
			return (int)(power * 0.5);
		case TYPE_LIGHT:
			return (int)(power * 1.2);
		case TYPE_DARK:
			return (int)(power * 0.8);
		}
	case TYPE_WOOD:
		switch (enemType)
		{
		case TYPE_FIRE:
			return (int)(power * 0.5);
		case TYPE_WATER:
			return (int)(power * 1.5);
		case TYPE_WOOD:
			return power;
		case TYPE_LIGHT:
			return (int)(power * 1.2);
		case TYPE_DARK:
			return (int)(power * 0.8);
		}
	case TYPE_LIGHT:
		switch (enemType)
		{
		case TYPE_LIGHT:
			return power;
		case TYPE_DARK:
			return power * 2;
		default:
			return (int)(power * 0.8);
		}
	case TYPE_DARK:
		switch (enemType)
		{
		case TYPE_LIGHT:
			return (int)(power * 0.5);
		case TYPE_DARK:
			return power;
		default:
			return (int)(power * 1.2);
		}
	}
	return power;
}

void zzUserInput()
{
	if (RightKeyInput())
	{
		player1Cursor.X++;
		if (player1Cursor.X > NumOfTile_X - 1)
		{
			player1Cursor.X = NumOfTile_X - 1;
		}
		else
		{
			if (isCatch == TRUE)
			{
				dstGem = player1Cursor;
				GemMap[oriGem.Y][oriGem.X].SwapMe = TRUE;
				GemMap[dstGem.Y][dstGem.X].SwapMe = TRUE;
				OnSwap = TRUE;
				canControl = FALSE;
			}
		}
	}
	if (LeftKeyInput())
	{
		player1Cursor.X--;
		if (player1Cursor.X < 0)
		{
			player1Cursor.X = 0;
		}
		else
		{
			if (isCatch == TRUE)
			{
				dstGem = player1Cursor;
				GemMap[oriGem.Y][oriGem.X].SwapMe = TRUE;
				GemMap[dstGem.Y][dstGem.X].SwapMe = TRUE;
				OnSwap = TRUE;
				canControl = FALSE;
			}
		}
	}
	if (UpKeyInput())
	{
		player1Cursor.Y--;
		if (player1Cursor.Y < 0)
		{
			player1Cursor.Y = 0;
		}
		else
		{
			if (isCatch == TRUE)
			{
				dstGem = player1Cursor;
				GemMap[oriGem.Y][oriGem.X].SwapMe = TRUE;
				GemMap[dstGem.Y][dstGem.X].SwapMe = TRUE;
				OnSwap = TRUE;
				canControl = FALSE;
			}
		}
	}
	if (DownKeyInput())
	{
		player1Cursor.Y++;
		if (player1Cursor.Y > NumOfTile_Y - 1)
		{
			player1Cursor.Y = NumOfTile_Y - 1;
		}
		else
		{
			if (isCatch == TRUE)
			{
				dstGem = player1Cursor;
				GemMap[oriGem.Y][oriGem.X].SwapMe = TRUE;
				GemMap[dstGem.Y][dstGem.X].SwapMe = TRUE;
				OnSwap = TRUE;
				canControl = FALSE;
			}
		}
	}
}

void zzUserSelect()
{
	if (SpaceKeyInput()) // �����̽� �� �Է�
	{
		if (StageMove > 0)
		{
			if (isCatch)
			{
				isCatch = FALSE;
			}
			else
			{
				if (GemMap[player1Cursor.Y][player1Cursor.X].speciality != 0)
				{
					zzDestroyGem(player1Cursor.Y, player1Cursor.X);
					canControl = FALSE;
					switch (GemMap[player1Cursor.Y][player1Cursor.X].GemType)
					{
					case TYPE_FIRE:
						GemFire += myPower;
						break;
					case TYPE_WATER:
						GemWater += myPower;
						break;
					case TYPE_WOOD:
						GemWood += myPower;
						break;
					case TYPE_LIGHT:
						GemLight += myPower;
						break;
					case TYPE_DARK:
						GemDark += myPower;
						break;
					}
					SummonTime = TRUE;
					myPower = 0;
					StageMove--;
				}
				else
				{
					isCatch = TRUE;
					oriGem = player1Cursor;
					soundSeek(&snd_PickTile, 0);
					soundPlay(&snd_PickTile);
				}
			}
		}
	}
}