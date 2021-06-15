#include "pchApp.h"
#include "Monster.h"
#include "../Resource/ResourceManager.h"
#include "../../RhythmLibary/Graphics/D2DGraphics.h"

Monster::Monster(std::string name, unsigned int id, unsigned int layer, Vector2 vec, MonsterLevel type, MonsterProperty property)
	:Object2(name, id, layer, vec), Status(MonsterStatus::Walk), WalkMotion(nullptr), AttackMotion(nullptr), DeadMotion(nullptr)
{
	Status = MonsterStatus::Walk;
	DivAlpha = 0.01f;
	DeathTime = new Flag_Fream();
	DeathTime->Set(0.125f);
	CurSize = 0.5f;
}

Monster::Monster(int level, int type) :Object2("mon", 99, 2, Vector2(2280,1080))
{
	Level = static_cast<MonsterLevel>(level);
	ProPerty = static_cast<MonsterProperty>(type);
	
}

Monster::~Monster()
{
	delete DeathTime;
}

void Monster::Update()
{
	OnEvent();
}

void Monster::ChangeType()
{
	switch (Level)
	{
	case MonsterLevel::Small:
		Level = MonsterLevel::Medium;
		break;
	case MonsterLevel::Medium:
		Level = MonsterLevel::Large;
		break;
	case MonsterLevel::Large:
		Level = MonsterLevel::Small;
		break;
	}
}

void Monster::ChangeProperty()
{
	switch (ProPerty)
	{
	case MonsterProperty::Fire:
		ProPerty = MonsterProperty::Water;
		break;
	case MonsterProperty::Water:
		ProPerty = MonsterProperty::Leaf;
		break;
	case MonsterProperty::Leaf:
		ProPerty = MonsterProperty::Fire;
		break;
	}
}

void Monster::ChangeMotion()
{
	switch (Status)
	{
	case MonsterStatus::Walk:
		Status = MonsterStatus::Attack;
		break;
	case MonsterStatus::Attack:
		Status = MonsterStatus::Dead;
		break;
	case MonsterStatus::Dead:
		Status = MonsterStatus::Walk;
		break;
	default:
		break;
	}
}

void Monster::SetMonsterInfo()
{
	switch (ProPerty)
	{
	case MonsterProperty::Fire:
		switch (Level)
		{
		case MonsterLevel::Small:
			WalkMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_RED_EASY_WALK);
			AttackMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_RED_EASY_ATTACK);
			DeadMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_RED_EASY_DEATH);
			CurSize = 0.5f;
			break;

		case MonsterLevel::Medium:
			WalkMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_RED_NORMAL_WALK);
			AttackMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_RED_NORMAL_ATTACK);
			DeadMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_RED_NORMAL_DEATH);
			CurSize = 0.6f;
			break;

		case MonsterLevel::Large:
			WalkMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_RED_HARD_WALK);
			AttackMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_RED_HARD_ATTACK);
			DeadMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_RED_HARD_DEATH);
			CurSize = 0.5f;
			break;
		}
		break;
	case MonsterProperty::Water:
		switch (Level)
		{
		case MonsterLevel::Small:
			WalkMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_BLUE_EASY_WALK);
			AttackMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_BLUE_EASY_ATTACK);
			DeadMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_BLUE_EASY_DEATH);
			CurSize = 0.5f;
			break;

		case MonsterLevel::Medium:
			WalkMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_BLUE_NORMAL_WALK);
			AttackMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_BLUE_NORMAL_ATTACK);
			DeadMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_BLUE_NORMAL_DEATH);
			CurSize = 0.6f;
			break;

		case MonsterLevel::Large:
			WalkMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_BLUE_HARD_WALK);
			AttackMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_BLUE_HARD_ATTACK);
			DeadMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_BLUE_HARD_DEATH);
			CurSize = 0.5f;
			break;
		}
		break;
	case MonsterProperty::Leaf:
		switch (Level)
		{
		case MonsterLevel::Small:
			WalkMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_GREEN_EASY_WALK);
			AttackMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_GREEN_EASY_ATTACK);
			DeadMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_GREEN_EASY_DEATH);
			CurSize = 0.5f;
			break;

		case MonsterLevel::Medium:
			WalkMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_GREEN_NORMAL_WALK);
			AttackMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_GREEN_NORMAL_ATTACK);
			DeadMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_GREEN_NORMAL_DEATH);
			CurSize = 0.6f;
			break;

		case MonsterLevel::Large:
			WalkMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_GREEN_HARD_WALK);
			AttackMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_GREEN_HARD_ATTACK);
			DeadMotion = ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_GREEN_HARD_DEATH);
			CurSize = 0.5f;
			break;
		}
		break;
	default:
		break;
	}
}

void Monster::SetState(int stat)
{
	Status = static_cast<MonsterStatus>(stat);
}

void Monster::SetState(MonsterStatus stat)
{
	Status = stat;
}

int Monster::GetState()
{
	return static_cast<int>(Status);
}

void Monster::Animate()
{
	SpriteInfo spriteInfWalk = D2DGraphics::GetInstance().CurrentSheetInfo(WalkMotion);
	SpriteInfo spriteAttack = D2DGraphics::GetInstance().CurrentSheetInfo(AttackMotion);
	SpriteInfo spriteDead = D2DGraphics::GetInstance().CurrentSheetInfo(DeadMotion);

	//D2D1_RECT_F walkrect = D2D1::RectF(0, 0, spriteInfWalk.Layout.right - spriteInfWalk.Layout.left, spriteInfWalk.Layout.bottom - spriteInfWalk.Layout.top);
	//D2D1_RECT_F attackrect = D2D1::RectF(0, 0, spriteAttack.Layout.right - spriteAttack.Layout.left, spriteAttack.Layout.bottom - spriteAttack.Layout.top);
	//D2D1_RECT_F deadrect = D2D1::RectF(0, 0, spriteDead.Layout.right - spriteDead.Layout.left, spriteDead.Layout.bottom - spriteDead.Layout.top);

	Identify();
	
	switch (Status)
	{
	case MonsterStatus::Walk:
		if (Level == MonsterLevel::Small)
		{
			MakeScale({ CurSize,CurSize }, { WalkMotion->Height,0 });
			MakeTranslate(World_Position - Vector2(250, 140) - Vector2(0, 150 * (1.f - CurSize)));
			MakeTransformMatrix();
			D2DGraphics::GetInstance().SetTransform(TransformMatrix);
			D2DGraphics::GetInstance().AnimateImage(ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_SHADOW_SPRITE), 0, 0, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, 0);
		}
		MakeScale({ CurSize,CurSize }, { WalkMotion->Height,0 });
		MakeTranslate(World_Position - Vector2(spriteInfWalk.CenterX, spriteInfWalk.CenterY));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().AnimateImage(WalkMotion, 0, 0, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, 0);
		//D2DGraphics::GetInstance().DrawRectangle(walkrect, D2D1::ColorF::Black, false);
		break;

	case MonsterStatus::Attack:
		if (Level == MonsterLevel::Small)
		{
			MakeScale({ CurSize,CurSize }, { WalkMotion->Height,0 });
			MakeTranslate(World_Position - Vector2(250, 140) - Vector2(0, 150 * (1.f - CurSize)));
			MakeTransformMatrix();
			D2DGraphics::GetInstance().SetTransform(TransformMatrix);
			D2DGraphics::GetInstance().AnimateImage(ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_SHADOW_SPRITE), 0, 0, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, 0);
		}
		MakeTranslate(World_Position - Vector2(spriteAttack.CenterX, spriteAttack.CenterY));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().AnimateImage(AttackMotion, 0, 0, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, 0);
		//D2DGraphics::GetInstance().DrawRectangle(attackrect, D2D1::ColorF::Black, false);
		break;

	case MonsterStatus::Dead:
		if (Level == MonsterLevel::Small)
		{
			MakeScale({ CurSize,CurSize }, { WalkMotion->Height,0 });
			MakeTranslate(World_Position - Vector2(250, 140) - Vector2(0, 150 * (1.f - CurSize)));
			MakeTransformMatrix();
			D2DGraphics::GetInstance().SetTransform(TransformMatrix);
			D2DGraphics::GetInstance().AnimateImage(ResourceManager::GetInstance().GetMotionSheet(ResourceID::MONSTER_SHADOW_SPRITE), 0, 0, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, 0);
		}
		MakeTranslate(World_Position - Vector2(spriteDead.CenterX, spriteDead.CenterY));
		MakeTransformMatrix();

		DivAlpha = DeadMotion->Motions[DeadMotion->CurrentMotionCount][DeadMotion->CurrentSpriteCount].DelayFream * (DeadMotion->CurrentSpriteCount + 1);
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().AnimateImage(DeadMotion, 0, 0, 1 - DivAlpha, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, 0);
		//D2DGraphics::GetInstance().DrawRectangle(deadrect, D2D1::ColorF::Black, false);
		break;
	}
	Identify();
	if (CurSize < 1.f)
	{
		CurSize += 0.01f;
	}
	else
	{
		CurSize = 1.f;
	}
}

void Monster::OnRender()
{
	Animate();
}

void Monster::OnEvent()
{
	switch (Key::GetInstance().GetKeyState(KEYQ))
	{
	case KEYRELEASE:
		break;
	case KEYDOWN:
		break;
	case KEYPRESS:
		break;
	case KEYUP:
		ChangeProperty();
		break;
	}

	switch (Key::GetInstance().GetKeyState(KEYW))
	{
	case KEYRELEASE:
		break;
	case KEYDOWN:
		break;
	case KEYPRESS:
		break;
	case KEYUP:
		ChangeMotion();
		break;
	}

	switch (Key::GetInstance().GetKeyState(KEYE))
	{
	case KEYRELEASE:
		break;
	case KEYDOWN:
		break;
	case KEYPRESS:
		break;
	case KEYUP:
		ChangeType();
		break;
	}

	SetMonsterInfo();
}

bool Monster::isDead()
{
	if (DeadMotion->CurrentSpriteCount == DeadMotion->MaxSpriteCount -1)
	{
		return true;
	}
	if (AttackMotion->CurrentSpriteCount == AttackMotion->MaxSpriteCount -1 )
	{
		return true;
	}
	return false;
}
