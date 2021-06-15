#pragma once
#include <map>
#include <utility>	
#include "../Object/ObjectDef.h"
#include "../../RhythmLibary/Graphics/D2DGraphics.h"
#include "../../RhythmLibary/Util/Singleton.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

public:
	void Initialize();
	void Update();
	void Finalize();
	ImageSheet* GetImageSheet(ObjectID id);
	ImageSheet* GetImageSheet(ResourceID id);

	void SettingEasyModeSheet(MotionSheet* sheet);
	void SettingCharacterSheet(MotionSheet* sheet);

	MotionSheet* GetMotionSheet(ObjectID id);
	MotionSheet* GetMotionSheet(ResourceID id);

private:
	std::map<unsigned int, ImageSheet*> ImagePool;
	std::map<unsigned int, MotionSheet*> MotionPool;

};

