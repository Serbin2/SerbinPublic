#pragma once
#include <vector>
#include "DefaultGameData.h"
#include "../Scene/SceneManager.h"
#include "../Resource/ResourceManager.h"
#include "../GameManager/GameManager.h"
#include "../../RhythmLibary/Util/Singleton.h"
#include "../../RhythmLibary/Util/Frame.h"
#include "../Interpace/IFastEvent.h"
#include "../Player/Player.h"



///
/// 게임의 절차적 진행
///
/// 게임의 가장 큰 단위, 하부에 매니저 클래스 포함
///
///  [3/19/2020 GonGonGon]
class GameProcess
{
public:
	GameProcess();
	~GameProcess();	

public:	
	/// 유니티 플로우 차트 참고
	void Initialize(HWND hwnd, HDC hdc, RECT rt);
	//Start
	void Awake();
	void OnEnable();
	void Start();

	void OnCollision();

	void OnInputEvent();

	// GameLogic
	void Update();
	void LateUpdate();

	void OnRender();

	void OnApplicationPause();

	void OnDisable();
	void OnDestroy();


private:
	bool IsEnable;
	bool IsPause;
	HWND hWnd;
	HDC hDC;
	RECT rt;
};

