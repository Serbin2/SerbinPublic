#include "pch.h"
#include "UnitManager.h"

UnitManager::UnitManager()
{
	Object_Layer2.reserve(10);
	Object_Layer2.clear();
}

UnitManager::~UnitManager()
{
	Object_Layer2.clear();
}

Object2* UnitManager::GetObject2(ObjectID id)
{

	return nullptr;
}
