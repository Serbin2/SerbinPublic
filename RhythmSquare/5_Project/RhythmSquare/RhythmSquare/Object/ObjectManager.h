#pragma once
#include <vector>
#include "../../RhythmLibary/GameObject/GameObject.h"
#include "../../RhythmLibary/Util/Singleton.h"
#include "Object2.h"
#include "../Monster/Monster.h"
#include "../Player/Player.h"
#include "ObjectDef.h"

/// layer 2������ �ִ� ������Ʈ�� �����ϱ� ���� �������.
/// layer 1������ �ִ� �ֵ��� SceneManager �̳��� �����Ѵ�.
/// �̰� Ȯ���ؼ� ��ü ������Ʈ�� ���������� ���߿� �����ҵ�.

class UnitManager : public Singleton<UnitManager*>
{
public:
	UnitManager();
	~UnitManager();

public:
	Object2* GetObject2(ObjectID id);
	Monster* GenerateMonster();

private:
	std::vector<Object2*> Object_Layer2;
};

