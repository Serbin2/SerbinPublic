#pragma once
#include "../GameProcess/DefaultGameData.h"
#include "../../RhythmLibary/Util/Frame.h"
#include "../Object/Object2.h"

class Monster : public Object2
{
public:
	Monster(std::string name, unsigned int id, unsigned int layer, Vector2 vec, MonsterLevel type, MonsterProperty property);
	Monster(int level, int type);
	~Monster();

public:
	void Update();

	void ChangeType();
	void ChangeProperty();
	void ChangeMotion();
	void SetMonsterInfo();
	void SetState(int stat);
	void SetState(MonsterStatus stat);
	int GetState();
	virtual void Animate()  override;;
	virtual void OnRender()  override;;
	virtual void OnEvent() override;

	bool isDead();

private:
	MonsterLevel Level;
	MonsterProperty ProPerty;
	MonsterStatus Status;

	MotionSheet* WalkMotion;
	MotionSheet* AttackMotion;
	MotionSheet* DeadMotion;

	MotionSheet* AttackEffect;
	Vector2 AttackEffectVec;
	Flag_Fream* DeathTime;
	float DivAlpha;
	float CurSize;
	unsigned int HP;

};