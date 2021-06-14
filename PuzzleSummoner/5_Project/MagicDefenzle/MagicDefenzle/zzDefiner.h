#pragma once

// ���ǵ�
#define COLORKEY RGB(255, 0, 255)
#define CHARSPEED 10 // �ִϸ��̼� �ӵ�
#define COLLIDE 50 // ��ȯ�� ������ ��ĥ ũ��

// ȭ���� ũ��
#define SCREENWIDTH 1600
#define SCREENHEIGHT 900

// �Ӽ�
#define TYPE_FIRE 0
#define TYPE_WATER 1
#define TYPE_WOOD 2
#define TYPE_LIGHT 3
#define TYPE_DARK 4
#define TYPE_TOWER 5

// �ִϸ��̼� ����
#define STATE_IDLE 0
#define STATE_ATTACK 1
#define STATE_DEATH 2

typedef struct _tagOneNode OneNode;

// ��¥ ��Ʈ�� �ϳ��� ����ü
typedef struct _tagMDBitmap
{
	// �⺻
	HDC hMemDC;			// ��Ʈ���� ����Ǵ� memory device comtext handle
	HBITMAP hBitmap;	// ��Ʈ�� ���ҽ��� �ٷ�� �ڵ�

	// ��Ʈ�� ����
	int Width;			// ��
	int Height;			// ����

	// ��������Ʈ ����
	int KeyColor;		// Ű �÷� (TransparentBlt�� ���)

} zzBitmap;


/// �ִϸ��̼ǿ� ���Ե� �ϳ��� ��������Ʈ ����ü
typedef struct _tagOneSprite
{
	int oriX;			// ��Ʈ �������� ��ġ
	int oriY;

	int width;			// ��Ʈ �������� ��
	int height;			// ��Ʈ �������� ����

	/// ������ ���� ����
			// �� ��������Ʈ�� ������ ������

} OneSprite;


/// ��������Ʈ�� ���Ե� �ϳ��� �ִϸ��̼� ����ü
typedef struct _tagOneMotion
{
	// ū �ϳ��� ��Ʈ�� ��Ʈ
	zzBitmap* sheet;

	// �ִ� �ȿ����� ��������Ʈ ����
	int spriteNum;

	// �� �ִϸ��̼��� ���� ������ ���൵
	int nowFrame;

	// �� �ִϸ��̼��� �ӵ�
	int delayFrame;

	// �����Ҵ� �� ��������Ʈ�� (�� �ִϿ� ����ִ� ��������Ʈ)
	OneSprite* sprites;

} OneMotion;


/// ��ü ĳ���� ����ü
typedef struct _tagOneCharacterRes
{
	/// ��� ���� ��������Ʈ ��Ʈ (ĳ���� �� �ϳ�)
	zzBitmap* sheet;	// ū �ϳ��� ��Ʈ�� ��Ʈ

	// �ִϸ��̼� ����
	int NumofAni;

	// �ִϸ��̼ǵ�..
	OneMotion* motions;

	/// ĳ���ͺ� ���� (�ӵ�, ü��..)

	int myType; // �Ӽ�

	int myHealth;
	int myPower;

	// ũ�� ������ ��Ʈ���� ũ��
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

