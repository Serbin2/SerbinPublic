#pragma once

// 정의들
#define COLORKEY RGB(255, 0, 255)
#define CHARSPEED 10 // 애니메이션 속도
#define COLLIDE 50 // 소환수 전투시 겹칠 크기

// 화면의 크기
#define SCREENWIDTH 1600
#define SCREENHEIGHT 900

// 속성
#define TYPE_FIRE 0
#define TYPE_WATER 1
#define TYPE_WOOD 2
#define TYPE_LIGHT 3
#define TYPE_DARK 4
#define TYPE_TOWER 5

// 애니메이션 상태
#define STATE_IDLE 0
#define STATE_ATTACK 1
#define STATE_DEATH 2

typedef struct _tagOneNode OneNode;

// 통짜 비트맵 하나의 구조체
typedef struct _tagMDBitmap
{
	// 기본
	HDC hMemDC;			// 비트맵이 내장되는 memory device comtext handle
	HBITMAP hBitmap;	// 비트맵 리소스를 다루는 핸들

	// 비트맵 관련
	int Width;			// 폭
	int Height;			// 높이

	// 스프라이트 관련
	int KeyColor;		// 키 컬러 (TransparentBlt의 경우)

} zzBitmap;


/// 애니메이션에 포함된 하나의 스프라이트 구조체
typedef struct _tagOneSprite
{
	int oriX;			// 시트 내에서의 위치
	int oriY;

	int width;			// 시트 내에서의 폭
	int height;			// 시트 내에서의 높이

	/// 프레임 제어 관련
			// 이 스프라이트가 가지는 딜레이

} OneSprite;


/// 스프라이트에 포함된 하나의 애니메이션 구조체
typedef struct _tagOneMotion
{
	// 큰 하나의 비트맵 시트
	zzBitmap* sheet;

	// 애니 안에서의 스프라이트 갯수
	int spriteNum;

	// 이 애니메이션의 현재 프레임 진행도
	int nowFrame;

	// 이 애니메이션의 속도
	int delayFrame;

	// 동적할당 될 스프라이트들 (한 애니에 들어있는 스프라이트)
	OneSprite* sprites;

} OneMotion;


/// 전체 캐릭터 구조체
typedef struct _tagOneCharacterRes
{
	/// 통맵 원본 스프라이트 시트 (캐릭터 당 하나)
	zzBitmap* sheet;	// 큰 하나의 비트맵 시트

	// 애니메이션 개수
	int NumofAni;

	// 애니메이션들..
	OneMotion* motions;

	/// 캐릭터별 정보 (속도, 체력..)

	int myType; // 속성

	int myHealth;
	int myPower;

	// 크기 조절된 비트맵의 크기
	float mySize;
	int myHeight;
	int myWidth;

	int mySpeed;

	COORD Position;
	BOOL moveon;

	int myTeam;


	int myState;

	int attackDelay;

} zzSummonee;

typedef struct _tagOneMonster
{
	int TYPE;
	int level;
	int spawntime;

} zzOneMonster;

typedef struct _tagList
{
	OneNode* head;
	int count;

} zzList;

typedef struct _tagOneStageInfo
{
	int stageNumber;
	int stageHP;
	int stageTime;
	int stageSpeed;

	int numofMonster;

	OneNode* head;
	int count;


} zzOneStage;

typedef struct _tagOneNode
{
	struct _tagOneNode* next;

	zzOneMonster d_mon;
	zzOneStage d_stg;

	zzSummonee data;
} OneNode;

