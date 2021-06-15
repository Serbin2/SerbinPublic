#pragma once
#include <vector>
#include "Scene.h"
#include "MainScene.h"
#include "ChildScene.h"
#include "MusicSelectScene.h"
#include "OptionScene.h"
#include "PauseScene.h"
#include "InGameScene.h"
#include "../../RhythmLibary/Util/Singleton.h"

const unsigned int main_scene_size = 3;
const unsigned int ingame_scene_size = 3;
const unsigned int child_scene_size = 5;
const unsigned int max_scene_size = 11;
const unsigned int scene_start_number = 100;

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

public:
	void Initialize();
	void Load();
	Scene* GetScene(ObjectID id);
	void Finalize();
	void SetCurrentScene(ObjectID id);
	Scene* GetCurrenctScene();
	void MoveInGameScene();

private:
	std::vector<Scene*> ScenePool;
	Scene* CurrentScene;
};

