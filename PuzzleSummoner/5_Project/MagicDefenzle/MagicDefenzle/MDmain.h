#pragma once

#define TileSize 48
#define GameboardX 632
#define GameboardY 120
#define NumOfTile_X 7
#define NumOfTile_Y 7
#define KINDOFCOLOR 5
#define PORTAL_AXIS 850
#define ENEMYPORTAL 300
#define MYPORTAL 1300
#define ANIMATE_SPEED 4

void zzInitializeGame();
void zzGetStage(int level);
void zzEndGame();

void zzStartStage();
void zzStartMultiStage(int i);
int zzMDmain(COORD mouse);

void zzDrawUIHealth();
void zzDrawUIMove();
void zzDropGemCheck();
void zzBlowCheck();
void zzSummoningCreature();

int zzCheckUpGem(int y, int x);
int zzCheckDownGem(int y, int x);
int zzCheckLeftGem(int y, int x);
int zzCheckRightGem(int y, int x);

void zzDestroyGem(int y, int x);

int zzCheckGem(int y, int x);

//여기부터 출력에 대한 함수
void zzGemSwap(); // 타일을 바꾸면서 출력
void zzDrawMovingGems(); // 타일을 떨구면서 출력
void zzDrawCharacters();
void zzDrawNoMoveGem();

// 소환수 생성용 더미 설정 함수
BOOL zzCreateSummonee(int type, int power, int team, int speed);

OneNode* zzFindFirst(zzList* list);
void zzCreateTower(int team, int health);


int zzAttackType(int myType, int enemType, int power);


void zzUserInput();
void zzUserSelect();
typedef struct _tagGems
{
	int GemType; // 보석 속성
	int speciality; // 특수 블럭

	BOOL isEmpty;
	BOOL DropMe;
	BOOL SwapMe;

} zzGems;