#pragma once
#include <vector>
#include "../../RhythmLibary/GameObject/GameObject.h"
#include "../../RhythmLibary/Util/Singleton.h"
#include "Object2.h"
#include "../Monster/Monster.h"
#include "../Player/Player.h"
#include "ObjectDef.h"

/// layer 2영역에 있는 오브젝트를 관리하기 위해 만들었다.
/// layer 1영역에 있는 애들은 SceneManager 이놈이 관리한다.
/// 이걸 확장해서 전체 오브젝트를 관리할지는 나중에 생각할듯.

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

