#include "pchApp.h"
#include "ClearScene.h"
#include "../Resource/ResourceManager.h"

ClearScene::ClearScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother)
	:ChildScene(id, layer, vec, box, mother)
{

}

ClearScene::~ClearScene()
{

}

void ClearScene::OnEvent()
{
	DefaultKeyEvent();
}

void ClearScene::OnRender()
{
	if (IsActive)
	{
		/// image 입력.
		Identify();
		MakeTranslate(World_Position);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::GAME_CLEAR_BACKGROUND), 0, 0);
		Identify();
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PAUSE_PLAN), 0, 0, 0.5, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
		Identify();
		MakeTranslate(Clear_CharacterVec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::GAME_CLEAR_CHARACTER), 0, 0);
		Identify();
		MakeTranslate(Clear_Scroll_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::GAME_CLEAR_SCROLL), 0, 0);
		Identify();
		MakeTranslate(PerPect_Image_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PERPECT_), 0, 0);
		Identify();
		MakeTranslate(Good_Image_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::GOOD_), 0, 0);
		Identify();
		MakeTranslate(Miss_Image_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::MISS_), 0, 0);
		Identify();

		/// text 입력.
		// 제목 입력
		Identify();
		MakeTranslate(Music_Name_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);

		int type = GameManager::GetInstance().GetSelectedSong();
		switch (type)
		{
		case PLOT_TWIST:
			D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 85, L"%s", L"Plot Twist");
			break;
		case PRECISION_STRIKE:
			D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 85, L"%s", L"Precision Strike");
			break;
		case INTROSPECT:
			D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 85, L"%s", L"Introspect");
			break;
		}
		Identify();
		MakeTranslate(Clear_Rank_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);

		OneGameData info = GameManager::GetInstance().GetOneGameData();
		if (info.m_Rate > 95)
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::RANK_S), 0, 0);
		if (info.m_Rate > 80 && info.m_Rate <= 95)
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::RANK_A), 0, 0);
		if (info.m_Rate > 70 && info.m_Rate <= 80)
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::RANK_B), 0, 0);
		if (info.m_Rate < 70)
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::RANK_C), 0, 0);

		Identify();
		MakeTranslate(Score_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 50, L"%s", L"Score");
		Identify();
		MakeTranslate(Combo_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 50, L"%s", L"Combo");
		Identify();
		MakeTranslate(Kill_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 50, L"%s", L"Kill");

		Identify();
		MakeTranslate(Score_Num_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 50, L"%d", info.m_Score);
		Identify();
		MakeTranslate(Combo_Num_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 50, L"%d", info.m_Combo);
		Identify();
		MakeTranslate(Kill_Num_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 50, L"%d", info.m_Kill);

		Identify();
		MakeTranslate(PerPect_Num_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 50, L"%d", info.m_Perfect);
		Identify();
		MakeTranslate(Good_Num_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 50, L"%d", info.m_Good);
		Identify();
		MakeTranslate(Miss_Num_Text_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().WriteTextDebug(D2D1::ColorF::White, D2D1::RectF(0.0f, 0.0f, 1000.f, 100.f), L"HY견명조", 50, L"%d", info.m_Miss);
	}
}

void ClearScene::Sleep()
{
	IsActive = false;
	IsPause = false;
}

void ClearScene::DefaultKeyEvent()
{
	switch (Key::GetInstance().GetKeyState(VK_ESCAPE))
	{
	case KEYRELEASE:
		break;
	case KEYDOWN:
		break;
	case KEYPRESS:
		break;
	case KEYUP:
		IsActive = false;
		Mother->OffPause();
		SceneManager::GetInstance().SetCurrentScene(ObjectID::SCENE_MAINMENU);
		break;
	default:
		break;
	}
}
