#include "pchApp.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	ImagePool.clear();
	MotionPool.clear();
}

ResourceManager::~ResourceManager()
{
	if (ImagePool.size() > 0)
	{
		std::map<unsigned int, ImageSheet*>::iterator it;
		for (it = ImagePool.begin(); it != ImagePool.end(); it++)
		{
			delete it->second;
		}
	}
	ImagePool.clear();

	if (MotionPool.size() > 0)
	{
		std::map<unsigned int, MotionSheet*>::iterator it;
		for (it = MotionPool.begin(); it != MotionPool.end(); it++)
		{
			delete it->second;
		}
	}
	MotionPool.clear();
}

void ResourceManager::Initialize()
{
	std::string PrePath = "../Data/Image/Complete file/";

	/// Image Load...
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::SCROLL_BAR), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::SCROLL_STONE), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::SCENE_START), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::SCENE_MAINMENU), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_EXIT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_MENU_EXIT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::SCENE_INGAME_DESERT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::SCENE_INGAME_FOREST), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::SCENE_INGAME_SEA), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_EASY), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_NORMAL), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_HARD), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_EASY_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_NORMAL_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_HARD_LIGHT), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_START_EASY), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_START_NORMAL), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_START_HARD), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::CHILD_NEXT_SCENE_SLIDE_INGAMEMENU), new ImageSheet()));


	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_NAME_TOWN), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_NAME_FOREST), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_NAME_DESERT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_NAME_SEA), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_NAME_SELECT_FOREST), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_NAME_SELECT_DESERT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_NAME_SELECT_SEA), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MUSIC_COVER_1), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MUSIC_COVER_2), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MUSIC_COVER_3), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::TEXTBOX_MENU_MUSIC_INFO_BG), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MENU_SELECT_STARTS), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MENU_SELECT_SPEED_UP), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MENU_SELECT_SPEED_DOWN), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::SETTING_WINDOW), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::SETTING_SOUND_TEXT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::SETTING_SETTING_TEXT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_OPTION), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_OPTION_GAME), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_OPTION_GAMESELECT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_OPTION_SOUND), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_OPTION_SOUNDSELECT), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_JUDGMENT_LEFTARROW), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::BUTTON_JUDGMENT_RIGHTARROW), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_SQUARE), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_SQUARE_MISS), new ImageSheet()));


	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_SCORE_BOX), new ImageSheet()));

	
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFECT_GOOD), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFECT_FEVER_GOOD), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFECT_MISS), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFECT_PREFECT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFECT_PREFECT_FEVER), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_0), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_1), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_2), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_3), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_4), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_5), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_6), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_7), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_8), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_9), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_0), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_1), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_2), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_3), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_4), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_5), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_6), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_7), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_8), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_9), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_ATTRIBUTE_BOX), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::CONTINUE_NUMBER_1), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::CONTINUE_NUMBER_2), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::CONTINUE_NUMBER_3), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::LODINGIMAGE), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PAUSE_PLAN), new ImageSheet()));


	/// start
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/01_Start/main Logo_PressAnyKey.png", ImagePool.find(static_cast<unsigned int>(ResourceID::SCENE_START))->second);

	/// main menu
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/02_Lobby/Lobby_Map_03.png", ImagePool.find(static_cast<unsigned int>(ResourceID::SCENE_MAINMENU))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/02_Lobby/town_0320.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_NAME_TOWN))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/02_Lobby/Lobby_UI_button_forest.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_NAME_FOREST))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/02_Lobby/Lobby_UI_button_desert.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_NAME_DESERT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/02_Lobby/Lobby_UI_button_sea.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_NAME_SEA))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/02_Lobby/Lobby_UI_button_forest_click.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_NAME_SELECT_FOREST))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/02_Lobby/Lobby_UI_button_desert_click.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_NAME_SELECT_DESERT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/02_Lobby/Lobby_UI_button_sea_click.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_NAME_SELECT_SEA))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_scroll.png", ImagePool.find(static_cast<unsigned int>(ResourceID::CHILD_NEXT_SCENE_SLIDE_INGAMEMENU))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_cover_Introspect.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MUSIC_COVER_1))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_cover_PlotTwist.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MUSIC_COVER_2))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_cover_PrecisionStrike.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MUSIC_COVER_3))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_button_level_easy_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_EASY))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_button_level_normal_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_NORMAL))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_button_level_hard_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_HARD))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_button_level_easy.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_EASY_LIGHT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_button_level_normal.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_NORMAL_LIGHT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_button_level_hard.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_SELECT_HARD_LIGHT))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_button_start_easy.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_START_EASY))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_button_start_normal.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_START_NORMAL))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_button_start_hard.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_START_HARD))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_MusicSelcet_button_speed_right.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MENU_SELECT_SPEED_UP))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_MusicSelcet_button_speed_left.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MENU_SELECT_SPEED_DOWN))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_MusicSelcet_IconExplain.png", ImagePool.find(static_cast<unsigned int>(ResourceID::TEXTBOX_MENU_MUSIC_INFO_BG))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/Lobby_UI_settings_sound_bar.png", ImagePool.find(static_cast<unsigned int>(ResourceID::SCROLL_BAR))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/settings_sound_bar_circle.png", ImagePool.find(static_cast<unsigned int>(ResourceID::SCROLL_STONE))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/setting button.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_OPTION))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/Lobby_UI_settings_sound_text.png", ImagePool.find(static_cast<unsigned int>(ResourceID::SETTING_SOUND_TEXT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/Lobby_UI_settings_GameSetting_text.png", ImagePool.find(static_cast<unsigned int>(ResourceID::SETTING_SETTING_TEXT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/Lobby_UI_settings_button_gamesetting.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_OPTION_GAME))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/settings_Button_gamesetting_click.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_OPTION_GAMESELECT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/Lobby_UI_settings_button_sound.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_OPTION_SOUND))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/settings_Button_sound_click.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_OPTION_SOUNDSELECT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/x button.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_EXIT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_MusicSelcet_button_X.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_MENU_EXIT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/Lobby_UI_Settings_window.png", ImagePool.find(static_cast<unsigned int>(ResourceID::SETTING_WINDOW))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/03_Play/background_desert_0317.png", ImagePool.find(static_cast<unsigned int>(ResourceID::SCENE_INGAME_DESERT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/03_Play/background_forest_0320.png", ImagePool.find(static_cast<unsigned int>(ResourceID::SCENE_INGAME_FOREST))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/03_Play/background_sea_0318.png", ImagePool.find(static_cast<unsigned int>(ResourceID::SCENE_INGAME_SEA))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/Lobby_settings_button_left.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_JUDGMENT_LEFTARROW))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Setting/Lobby_settings_button_right.png", ImagePool.find(static_cast<unsigned int>(ResourceID::BUTTON_JUDGMENT_RIGHTARROW))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_magicsquare_scroll.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_SQUARE))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_magicsquare_scroll_MissJudgement.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_SQUARE_MISS))->second);

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MENU_SELECT_RANK_A), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MENU_SELECT_RANK_B), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MENU_SELECT_RANK_C), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MENU_SELECT_RANK_S), new ImageSheet()));

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_Rank_A.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MENU_SELECT_RANK_A))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_Rank_B.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MENU_SELECT_RANK_B))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_Rank_C_02.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MENU_SELECT_RANK_C))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/02_Lobby/Music_Select/Lobby_UI_MusicSelcet_Rank_S_02.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MENU_SELECT_RANK_S))->second);


	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_UI_COMBO_TEXT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_UI_COMBO_FEVER), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_UI_PROGRESS_BAR), new ImageSheet()));

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_text_normal.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_UI_COMBO_TEXT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_text_fever.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_UI_COMBO_FEVER))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_music progress.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_UI_PROGRESS_BAR))->second);


	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_score.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_SCORE_BOX))->second);

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAYER_HP_BAR_BODY), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAYER_HP_BAR_HEAD), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAYER_HP_BAR_TAIL), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAYER_HP_BAR_COVER), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_FEVER_BAR_HEAD), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_FEVER_BAR_TAIL), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_FEVER_BAR_BODY), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_FEVER_BAR_COVER), new ImageSheet()));

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_hp_gauge_body.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAYER_HP_BAR_BODY))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_hp_gauge_head.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAYER_HP_BAR_HEAD))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_hp_gauge_tail.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAYER_HP_BAR_TAIL))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_ui_hp_border.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAYER_HP_BAR_COVER))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_fever_gauge_head.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_FEVER_BAR_HEAD))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_fever_gauge_body.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_FEVER_BAR_BODY))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_fever_gauge_tail.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_FEVER_BAR_TAIL))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_fever_border.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_FEVER_BAR_COVER))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_NoteJudgementText_good.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFECT_GOOD))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_NoteJudgementText_good_fever.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFECT_FEVER_GOOD))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_NoteJudgementText_miss.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFECT_MISS))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_NoteJudgementText_perfect.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFECT_PREFECT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_NoteJudgementText_perfect_fever.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFECT_PREFECT_FEVER))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_window_attribute.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_ATTRIBUTE_BOX))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_normal_0.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_0))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_normal_1.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_1))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_normal_2.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_2))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_normal_3.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_3))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_normal_4.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_4))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_normal_5.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_5))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_normal_6.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_6))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_normal_7.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_7))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_normal_8.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_8))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_normal_9.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_NORMAL_9))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_fever_0.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_0))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_fever_1.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_1))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_fever_2.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_2))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_fever_3.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_3))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_fever_4.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_4))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_fever_5.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_5))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_fever_6.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_6))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_fever_7.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_7))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_fever_8.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_8))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_combo_number_fever_9.png", ImagePool.find(static_cast<unsigned int>(ResourceID::COMBO_NUMBER_FEVER_9))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/04_Loding/loading_final.png", ImagePool.find(static_cast<unsigned int>(ResourceID::LODINGIMAGE))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Background/black alpa image.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PAUSE_PLAN))->second);

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PAUSE_SCENE), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PAUSE_SCENE_BUTTON_CONTINUE), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PAUSE_SCENE_BUTTON_RESTART), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PAUSE_SCENE_BUTTON_MUSIC_SELECT), new ImageSheet()));
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Pause/Play_UI_Pause_window.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PAUSE_SCENE))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Pause/Play_UI_Pause_button_continue.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PAUSE_SCENE_BUTTON_CONTINUE))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Pause/Play_UI_Pause_button_restart.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PAUSE_SCENE_BUTTON_RESTART))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Pause/Play_UI_Pause_button_musicselect.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PAUSE_SCENE_BUTTON_MUSIC_SELECT))->second);

	/// Dummy Image
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/dummy/02_Lobby/MusicSelcet_star.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MENU_SELECT_STARTS))->second);


	/// Image contiune Number
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::CONTINUE_NUMBER_1), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::CONTINUE_NUMBER_2), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::CONTINUE_NUMBER_3), new ImageSheet()));
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Pause/Play_UI_Pause_continue_1.png", ImagePool.find(static_cast<unsigned int>(ResourceID::CONTINUE_NUMBER_1))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Pause/Play_UI_Pause_continue_2.png", ImagePool.find(static_cast<unsigned int>(ResourceID::CONTINUE_NUMBER_2))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Pause/Play_UI_Pause_continue_3.png", ImagePool.find(static_cast<unsigned int>(ResourceID::CONTINUE_NUMBER_3))->second);

	/// Image attack effect
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::ATT_EFF_LEAF_1), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::ATT_EFF_LEAF_2), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::ATT_EFF_LEAF_3), new ImageSheet()));
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/attack/effect_leaf_1.png", ImagePool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_LEAF_1))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/attack/effect_leaf_2.png", ImagePool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_LEAF_2))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/attack/effect_leaf_3.png", ImagePool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_LEAF_3))->second);

	/// Motion attack effect
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::ATT_EFF_FIRE), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::ATT_EFF_GRASS), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::ATT_EFF_SLIME_FIRE), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::ATT_EFF_SLIME_GLASS), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::ATT_EFF_WATER), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::ATT_EFF_SLIME_WATER), new MotionSheet()));
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/attack/fire_effect.png", MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_FIRE))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/attack/grass_effect_1.png", MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_GRASS))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/attack/slime_fire.png", MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_SLIME_FIRE))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/attack/slime_grass.png", MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_SLIME_GLASS))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/attack/slime_water.png", MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_SLIME_WATER))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/attack/water_effect_2.png", MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_WATER))->second);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_FIRE))->second, 1, 12, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_GRASS))->second, 1, 12, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_SLIME_FIRE))->second, 1, 12, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_SLIME_GLASS))->second, 1, 12, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_SLIME_WATER))->second, 1, 12, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::ATT_EFF_WATER))->second, 1, 12, 1);

	/// Image Square effect
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE_BLACK), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE_ATT_LIGHT), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_BAR), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_BAR_LIGHT), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_1), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_2), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_3), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_4), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_5), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_6), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_7), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_8), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_9), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_1_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_2_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_3_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_4_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_5_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_6_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_7_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_8_LIGHT), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_9_LIGHT), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_1_BLACK), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_2_BLACK), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_3_BLACK), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_4_BLACK), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_5_BLACK), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_6_BLACK), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_7_BLACK), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_8_BLACK), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_9_BLACK), new ImageSheet()));


	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_NOTE_CLICK), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_NOTE_GUIDE_CIRCLE), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_NOTE_BACKROUND), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::DUMMY_NOTE), new ImageSheet()));

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_magic square_unlight 02.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_magic square_light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE_LIGHT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_magic square_unlight 02_black.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE_BLACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_effect_magicsquare_AttributeCircle.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE_ATT_LIGHT))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_effect_magicsquare_line_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_BAR))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_effect_magicsquare_line_light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_MAGIC_BAR_LIGHT))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_magicsquare_number_background.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_NOTE_BACKROUND))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_1_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_1))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_2_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_2))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_3_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_3))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_4_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_4))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_6_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_6))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_7_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_7))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_8_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_8))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_9_unlight.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_9))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_1_light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_1_LIGHT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_2_light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_2_LIGHT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_3_light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_3_LIGHT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_4_light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_4_LIGHT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_6_light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_6_LIGHT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_7_light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_7_LIGHT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_8_light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_8_LIGHT))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_9_light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_9_LIGHT))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_1_unlight_black.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_1_BLACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_2_unlight_black.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_2_BLACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_3_unlight_black.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_3_BLACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_4_unlight_black.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_4_BLACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_6_unlight_black.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_6_BLACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_7_unlight_black.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_7_BLACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_8_unlight_black.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_8_BLACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_Effect_magicsquare_number_9_unlight_black.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_EFFECT_NUM_9_BLACK))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_effect_numberClick.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_NOTE_CLICK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_magicsquare_guide light.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_NOTE_GUIDE_CIRCLE))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/MagicSquare/Play_magicsquare_guide light_Dummy.png", ImagePool.find(static_cast<unsigned int>(ResourceID::DUMMY_NOTE))->second);

	/// Heal Icon
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PLAY_HEAL_ICON), new ImageSheet()));
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Effect/heal.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PLAY_HEAL_ICON))->second);

	/// game clear image
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::GAME_LOSE_BACK_GROUND), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::GAME_CLEAR_BACKGROUND), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::GAME_CLEAR_SCROLL), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::GAME_CLEAR_CHARACTER), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::PERPECT_), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::GOOD_), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MISS_), new ImageSheet()));

	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::RANK_S), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::RANK_A), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::RANK_B), new ImageSheet()));
	ImagePool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::RANK_C), new ImageSheet()));
	
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/BackGround/03_Play/fail.png", ImagePool.find(static_cast<unsigned int>(ResourceID::GAME_LOSE_BACK_GROUND))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/BackGround/05_Clear/Clear.png", ImagePool.find(static_cast<unsigned int>(ResourceID::GAME_CLEAR_BACKGROUND))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/MusicEnd/Play_UI_MusicEnd_scroll.png", ImagePool.find(static_cast<unsigned int>(ResourceID::GAME_CLEAR_SCROLL))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fairy/2_completion/fairy_ani_happy_4.png", ImagePool.find(static_cast<unsigned int>(ResourceID::GAME_CLEAR_CHARACTER))->second);
	
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_NoteJudgementText_perfect.png", ImagePool.find(static_cast<unsigned int>(ResourceID::PERPECT_))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_NoteJudgementText_good.png", ImagePool.find(static_cast<unsigned int>(ResourceID::GOOD_))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/Play_UI_NoteJudgementText_miss.png", ImagePool.find(static_cast<unsigned int>(ResourceID::MISS_))->second);
	
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/MusicEnd/Play_UI_MusicSelcet_Rank_A.png", ImagePool.find(static_cast<unsigned int>(ResourceID::RANK_A))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/MusicEnd/Play_UI_MusicSelcet_Rank_B.png", ImagePool.find(static_cast<unsigned int>(ResourceID::RANK_B))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/MusicEnd/Play_UI_MusicSelcet_Rank_C.png", ImagePool.find(static_cast<unsigned int>(ResourceID::RANK_C))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/UI/03_Play/MusicEnd/Play_UI_MusicSelcet_Rank_S.png", ImagePool.find(static_cast<unsigned int>(ResourceID::RANK_S))->second);

	/// motion Load...
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::OBJECT_PLAYER_), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_EASY_WALK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_EASY_ATTACK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_EASY_DEATH), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_NORMAL_WALK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_NORMAL_ATTACK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_NORMAL_DEATH), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_HARD_WALK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_HARD_ATTACK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_HARD_DEATH), new MotionSheet()));

	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_EASY_WALK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_EASY_ATTACK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_EASY_DEATH), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_NORMAL_WALK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_NORMAL_ATTACK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_NORMAL_DEATH), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_HARD_WALK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_HARD_ATTACK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_HARD_DEATH), new MotionSheet()));

	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_RED_EASY_WALK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_RED_EASY_ATTACK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_RED_EASY_DEATH), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_RED_NORMAL_WALK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_RED_NORMAL_ATTACK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_RED_NORMAL_DEATH), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_RED_HARD_WALK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_RED_HARD_ATTACK), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_RED_HARD_DEATH), new MotionSheet()));
	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::MONSTER_SHADOW_SPRITE), new MotionSheet()));


	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fairy/2_completion/fairy_ani_standing_9.png", MotionPool.find(static_cast<unsigned int>(ResourceID::OBJECT_PLAYER_))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/grass/ani_green1_walk_sprite_2.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_EASY_WALK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/grass/ani_green1_attack_sprite1.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_EASY_ATTACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/grass/ani_green1_death_sprite_4.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_EASY_DEATH))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/grass/ani_green2_walk_sprite_2.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_NORMAL_WALK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/grass/ani_green2_attack_sprite2.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_NORMAL_ATTACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/grass/ani_green2_death_sprite_2.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_NORMAL_DEATH))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/grass/ani_green3_walk_sprite_3_real.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_HARD_WALK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/grass/ani_green3_attack_sprite_2.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_HARD_ATTACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/grass/ani_green3_death_sprite_1.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_HARD_DEATH))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/water/ani_blue1_walk_sprite.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_EASY_WALK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/water/ani_blue1_attack_sprite.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_EASY_ATTACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/water/ani_blue1_death_sprite.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_EASY_DEATH))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/water/ani_blue2_walk_sprite.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_NORMAL_WALK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/water/ani_blue2_attack_sprite.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_NORMAL_ATTACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/water/ani_blue2_death_sprite.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_NORMAL_DEATH))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/water/ani_blue3_walk_sprite.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_HARD_WALK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/water/ani_blue3_attack_sprite.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_HARD_ATTACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/water/ani_blue3_death_sprite.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_HARD_DEATH))->second);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fire/ani_red_walk_sprite_.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_EASY_WALK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fire/ani_red1_attack_sprite1.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_EASY_ATTACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fire/ani_red1_death_sprite_5.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_EASY_DEATH))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fire/ani_red2_walk_sprite_1.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_NORMAL_WALK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fire/ani_red2_attack_sprite3.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_NORMAL_ATTACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fire/ani_red2_death_sprite_1.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_NORMAL_DEATH))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fire/ani_red3_walk_sprite.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_HARD_WALK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fire/ani_red3_attack_sprite_.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_HARD_ATTACK))->second);
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fire/ani_red3_death_sprite_1.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_HARD_DEATH))->second);

	MotionPool.insert(std::make_pair(static_cast<unsigned int>(ResourceID::OBJECT_PLAYER_FAIRY_SHOT), new MotionSheet()));
	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/fairy/2_completion/fairy_ani_shot_4.png", MotionPool.find(static_cast<unsigned int>(ResourceID::OBJECT_PLAYER_FAIRY_SHOT))->second);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::OBJECT_PLAYER_FAIRY_SHOT))->second, 1, 6, 0.8);

	D2DGraphics::GetInstance().CreateImage(L"../Data/Image/Complete file/Character/monster_shadow/sline_shadow1_sprite_walk.png", MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_SHADOW_SPRITE))->second);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_SHADOW_SPRITE))->second, 1, 8, 1);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::OBJECT_PLAYER_))->second, 1, 6, 0.8);
	SettingCharacterSheet(MotionPool.find(static_cast<unsigned int>(ResourceID::OBJECT_PLAYER_))->second);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_EASY_WALK))->second, 1, 8, 1);
	SettingEasyModeSheet(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_EASY_WALK))->second);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_EASY_ATTACK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_EASY_DEATH))->second, 1, 8, 1);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_NORMAL_WALK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_NORMAL_ATTACK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_NORMAL_DEATH))->second, 1, 8, 1);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_HARD_WALK))->second, 1, 8, 1);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_HARD_ATTACK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_GREEN_HARD_DEATH))->second, 1, 8, 1);

	//////// blue
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_EASY_WALK))->second, 1, 8, 1);
	SettingEasyModeSheet(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_EASY_WALK))->second);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_EASY_ATTACK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_EASY_DEATH))->second, 1, 8, 1);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_NORMAL_WALK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_NORMAL_ATTACK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_NORMAL_DEATH))->second, 1, 8, 1);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_HARD_WALK))->second, 1, 8, 1);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_HARD_ATTACK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_BLUE_HARD_DEATH))->second, 1, 8, 1);

	///////// red 
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_EASY_WALK))->second, 1, 8, 1);
	SettingEasyModeSheet(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_EASY_WALK))->second);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_EASY_ATTACK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_EASY_DEATH))->second, 1, 8, 1);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_NORMAL_WALK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_NORMAL_ATTACK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_NORMAL_DEATH))->second, 1, 8, 1);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_HARD_WALK))->second, 1, 8, 1);

	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_HARD_ATTACK))->second, 1, 8, 1);
	D2DGraphics::GetInstance().CreateAnimation(MotionPool.find(static_cast<unsigned int>(ResourceID::MONSTER_RED_HARD_DEATH))->second, 1, 8, 1);
}

void ResourceManager::Update()
{

}

void ResourceManager::Finalize()
{

}

ImageSheet* ResourceManager::GetImageSheet(ObjectID id)
{
	if (ImagePool.find(static_cast<unsigned int>(id)) == ImagePool.end())
		return nullptr;
	else
		return ImagePool.find(static_cast<unsigned int>(id))->second;
}

ImageSheet* ResourceManager::GetImageSheet(ResourceID id)
{
	if (ImagePool.find(static_cast<unsigned int>(id)) == ImagePool.end())
		return nullptr;
	else
		return ImagePool.find(static_cast<unsigned int>(id))->second;
}

MotionSheet* ResourceManager::GetMotionSheet(ObjectID id)
{
	if (MotionPool.find(static_cast<unsigned int>(id)) == MotionPool.end())
		return nullptr;
	else
		return MotionPool.find(static_cast<unsigned int>(id))->second;
}

MotionSheet* ResourceManager::GetMotionSheet(ResourceID id)
{
	if (MotionPool.find(static_cast<unsigned int>(id)) == MotionPool.end())
		return nullptr;
	else
		return MotionPool.find(static_cast<unsigned int>(id))->second;
}
