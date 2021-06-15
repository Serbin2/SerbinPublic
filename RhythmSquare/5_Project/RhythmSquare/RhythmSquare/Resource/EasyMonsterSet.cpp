#include "pchApp.h"
#include "ResourceManager.h"

void ResourceManager:: SettingEasyModeSheet(MotionSheet* sheet)
{
	/// idle
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 0, Vector2(1.f, 1.f), 1.f);
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 1, Vector2(1.f, 1.f), 1.f);

	/// jump up
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 2, Vector2(1.f, 1.2f), 1.f);
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 3, Vector2(1.f, 2.0f), 1.f);
	
	/// jump down
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 4, Vector2(1.f, 1.8f), 1.f);
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0,	5, Vector2(1.f, 1.2f), 1.f);
	
	/// idle
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 6, Vector2(1.f, 1.f), 1.f);
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 7, Vector2(1.f, 1.f), 1.f);
}

void ResourceManager::SettingCharacterSheet(MotionSheet* sheet)
{
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 0, Vector2(1.f, 1.0f), 1.f);
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 1, Vector2(1.f, 1.11f), 1.f);

	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 2, Vector2(1.f, 1.13f), 1.f);
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 3, Vector2(1.f, 1.10f), 1.f);

	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 4, Vector2(1.f, 1.08f), 1.f);
	D2DGraphics::GetInstance().SettingMotionRatio(sheet, 0, 5, Vector2(1.f, 0.97f), 1.f);

}