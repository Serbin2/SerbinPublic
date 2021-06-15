// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"
#pragma comment(lib, "..\\Debug\\RhythmLibary.lib")

/// Graphics
#include "../RhythmLibary/Graphics/D2DGraphics.h"
#include "../RhythmLibary/Graphics/D2DMacros.h"

/// Audio
#include "../RhythmLibary/Audio/AudioComponent.h"
#include "AudioManager.h"

/// System, Device
#include "../RhythmLibary/Key/KeyDef.h"
#include "../RhythmLibary/Key/Key.h"

/// Utility
#include "../RhythmLibary/Util/Utility.h"
#include "../RhythmLibary/Util/Vector2.h"
#include "../RhythmLibary/Util/Singleton.h"
#include "../RhythmLibary/Util/Timer.h"
#include "../RhythmLibary/Util/TimeUtil.h"
#include "../RhythmLibary/Transform/Transform.h"
#include "../RhythmLibary/GameObject/GameObject.h"
#include <vector>

/// GameDef
#include "DefineData.h"
#include "../RhythmSquare/GameProcess/DefaultGameData.h"
#include "../RhythmSquare/Object/UI_SIZE_Def.h"
#include "../RhythmSquare/Object/ObjectDef.h"
#include "Resource/ResourceManager.h"
#include "FXManager.h"
#include "Object/MagicCircle.h"

#include "Monster/Monster.h"
#include "RSQNote.h"
#include "RSPage.h"
#include "RSSheet.h"
#include "FileIO.h"
#include "Player/Player.h"

/// Manager
#include "../RhythmSquare/Scene/SceneManager.h"
#include "../RhythmSquare/GameManager/GameManager.h"

/// InGame Layout





static int ina;

#endif //PCH_H
