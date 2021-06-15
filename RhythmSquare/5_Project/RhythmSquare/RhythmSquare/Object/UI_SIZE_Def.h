#pragma once
#include "../../RhythmLibary/Util/Vector2.h"
#include "../../RhythmLibary/Graphics/D2DMacros.h"

// start scene
const Vector2 Main_Start_Vec(0, 0);
const D2D1_RECT_F Main_Start_Box = D2D1::RectF(0, 0, 2560, 1440);

// start main menu
const Vector2 Main_Menu_Vec(0, 0);
const D2D1_RECT_F Main_Menu_Box = D2D1::RectF(0, 0, 2560, 1440);

// start main ending
const Vector2 Main_Ending_Vec(0, 0);
const D2D1_RECT_F Main_Ending_Box = D2D1::RectF(0, 0, 2560, 1440);

// Ingame scene desert
const Vector2 Ingame_Desert_Vec(0, 0);
const D2D1_RECT_F  Ingame_Desert_Box = D2D1::RectF(0, 0, 2560, 1440);

// Ingame scene forest
const Vector2 Ingame_Forest_Vec(0, 0);
const D2D1_RECT_F Ingame_Forest_Box = D2D1::RectF(0, 0, 2560, 1440);

// Ingame scene sea
const Vector2 Ingame_Sea_Vec(0, 0);
const D2D1_RECT_F Ingame_Sea_Box = D2D1::RectF(0, 0, 2560, 1440);

// music select scene
/// ���� ����Ʈ â, �����̴��� �ƴ� ��׶����� �ܿ� ������ ��
// ----> music select background scene------------------------------------------------------------------------------------
const Vector2 Music_BackGround_Vec(0, 0);
const D2D1_RECT_F Music_BackGround_Box = D2D1::RectF(0, 0, 2560, 1440);

/// ���� Ŀ���� �ѹ��� �ð�
const float ZoomTime = 0.01f;

/// ���� ������
const Vector2 BaseScaleSize(1.0f, 1.0f);
/// �ִ� ������
const Vector2 MaxScaleSize(3.0f, 3.0f);
/// �ѹ��� Ŀ���� ������
const Vector2 ZoomDiv(0.2f, 0.2f);

const Vector2 Desert_Zoom_Point(1810.f, 110.f);
const Vector2 Forest_Zoom_Point(780.f, 450.f);
const Vector2 Sea_Zoom_Point(2340.f, 1050.f);

// ----> music select slider scene---------------------------------------------------------------------------------------


/// ���� �� ����, �����̵� �ϸ鼭 ������ ��, �����̵� �ϱ� ������ ȭ�� ������ �����ȴ�.
const Vector2 Slide_Start_Vec(2560, 0);
const D2D1_RECT_F Slide_Size_Box = D2D1::RectF(0, 0, 1260, 1440);
const float Slide_Size_X = 1260;

// �����̴��� �����̴� Ÿ�̸�
const float SlideTime = 0.0001f;
const Vector2 SlideDivVec(-1.f, 0);

/// Slide�� �پ� ������ ��ư�� ��ġ.
// ���̵� ��ư
const Vector2 Easy_Button_Vec(Slide_Size_X + 1408, 1112);
const Vector2 Normal_Button_Vec(Slide_Size_X + 1408, 1192);
const Vector2 Hard_Button_Vec(Slide_Size_X + 1408, 1272);

// ���� ���� ��ư
const Vector2 Start_Button_Vec(Slide_Size_X + 1768, 1112);

// 

// ���� �ӵ����� ��ư
const Vector2 Speed_Up_Button_Vec(Slide_Size_X + 1788, 1033);
const Vector2 Speed_Down_Button_Vec(Slide_Size_X + 2336, 1033);

// ���� �������� ���� ��ư
const Vector2 Menu_Exit_Button_Vec(Slide_Size_X + Slide_Size_X - 55, 60);
const D2D1_RECT_F Menu_Exit_Button_Box = D2D1::RectF(0, 0, 120.f, 120.f);

// ���̵��� ��ư�� ũ�� (������ ����.)
const D2D1_RECT_F Select_Button_Size = D2D1::RectF(0.0f, 0.0f, 360.0f, 80.0f);

// ���� ���� ��ư�� ũ��
const D2D1_RECT_F Start_Button_Size = D2D1::RectF(0.0f, 0.0f, 688.f, 240.0f);

// �ӵ����� ��ư�� ũ��
const D2D1_RECT_F Speed_Button_Size = D2D1::RectF(0.0f, 0.0f, 88.f, 72.0f);


/// Slide�� �پ� ������ �ؽ�Ʈ �ڽ� ������ ��ġ
const Vector2 TextBox_BPM(Slide_Size_X + 2208, 202);
const D2D1_RECT_F TextBox_BPM_Layout = D2D1::RectF(0.0f, 0.0f, 392.0f, 112.0f);

const Vector2 TextBox_Composer(Slide_Size_X + 1432, 202);
const D2D1_RECT_F TextBox_Composer_Layout = D2D1::RectF(0.0f, 0.0f, 392.0f, 112.0f);

const Vector2 TextBox_MusicName(Slide_Size_X + 1432, 101);
const D2D1_RECT_F TextBox_MusicName_Layout = D2D1::RectF(0.0f, 0.0f, 392.0f, 112.0f);

const Vector2 TextBox_BestScore(Slide_Size_X + 1408, 904);
const D2D1_RECT_F BestScore_Layout = D2D1::RectF(0.0f, 0.0f, 392.0f, 112.0f);

const Vector2 TextBox_Combo(Slide_Size_X + 1800, 904);
const D2D1_RECT_F Combo_Layout = D2D1::RectF(0.0f, 0.0f, 226.0f, 112.0f);

const Vector2 TextBox_Kill(Slide_Size_X + 2026, 904);
const D2D1_RECT_F Kill_Layout = D2D1::RectF(0.0f, 0.0f, 192.0f, 112.0f);

const Vector2 TextBox_Rate(Slide_Size_X + 2218, 904);
const D2D1_RECT_F Rate_Layout = D2D1::RectF(0.0f, 0.0f, 238.0f, 112.0f);

const Vector2 TextBox_Speed(Slide_Size_X + 1768, 1016);
const D2D1_RECT_F Speed_Layout = D2D1::RectF(0.0f, 0.0f, 688.0f, 96.0f);

// ������ �ۼ��Ǵ� �ؽ�Ʈ �ڽ� ��ġ ���� ���� �ؽ�Ʈ �ڽ� ���� �׷��� Ui �̹���
const unsigned int TextSize = 20;

/// �ؽ�Ʈ �ڽ��� ����̵Ǵ� ���� �̹������� ��ġ, �뷡 ������ ��ġ.
const Vector2 Music_Cover_Vec(Slide_Size_X + 1408.f, 344.f);
const Vector2 Name_Box_Vec(Slide_Size_X + 1408.f, 80.f);
const Vector2 Speed_Box_Vec(Slide_Size_X + 1408.f, 1016.f);
const Vector2 Star_Box_Vec(Slide_Size_X + 1408.f, 256.f);

const Vector2 RANK_Vec(Slide_Size_X + 2248.f, 696.f);


/// option box scene
const Vector2 Option_Box_Vec(540.f, 360.f);
const D2D1_RECT_F Option_Box_Size = D2D1::RectF(0, 0, 2560, 1440);

/// option scene back_ground --------------------------------------------------------------------------

const Vector2 Option_Sound_Text_Vec(724.f, 656.f);
const Vector2 Option_Setting_Text_Vec(724.f, 656.f);

const Vector2 Exit_Button_Vec(1856.f, 384.f);
const Vector2 Option_Sound_Vec(564.f, 384.f);
const Vector2 Option_Select_Vec(904.f, 384.f);

const D2D1_RECT_F Option_Menu_Box = D2D1::RectF(0, 0, 320.f, 320.f);
const D2D1_RECT_F Option_Exit_Box = D2D1::RectF(0, 0, 120.f, 120.f);

const Vector2 BG_ScrollBar_Vec(1156.f, 656.f);
const Vector2 Effect_ScrollBar_Vec(1156.f, 784.f);
const Vector2 Play_ScrollBar_Vec(1156.f, 912.f);

const D2D1_SIZE_F BarSize = D2D1::SizeF(0.f, 680.f);

const Vector2 BG_ScrollBar_Stone_Vec(1496.f - 24, 612.f + 24.f);
const Vector2 Effect_ScrollBar_Stone_Vec(1496.f - 24, 740.f + 24.f);
const Vector2 Play_ScrollBar_Stone_Vec(1496.f - 24, 868.f + 24.f);

const D2D1_RECT_F ScrollBar_Stone_Size = D2D1::RectF(0.0f, 0.0f, 52.f, 88.f);

const Vector2 Left_Arrow_Vec(1144.f, 768.f);
const Vector2 Right_Arrow_Vec(1780.f, 780.f);

const D2D1_RECT_F Arrow_Size = D2D1::RectF(0.0f, 0.0f, 80.f, 80.f);

const Vector2 Judgment_TextBox_Vec(1400.f, 750.f);
const D2D1_RECT_F Judgment_TextBox_Layout = D2D1::RectF(0.0f, 0.0f, 192.0f, 112.0f);

/// InGame Scene
const Vector2 Attribute_Vec(1800, 280.f);

/// InGame Pause Scene

const Vector2 Pause_Scene_Vec(888.f, 352.f);
const D2D1_RECT_F Pause_Scene_Size = D2D1::RectF(0.0f, 0.0f, 784.f, 736.f);

const Vector2 Continue_Button_Vec(960.f, 424.f);
const D2D1_RECT_F Continue_Button_Size = D2D1::RectF(0.0f, 0.0f, 640.f, 160.f);

const Vector2 Restart_Button_Vec(960.f, 640.f);
const D2D1_RECT_F Restart_Button_Size = D2D1::RectF(0.0f, 0.0f, 640.f, 160.f);

const Vector2 MusicSelect_Button_Vec(960.f, 856.f);
const D2D1_RECT_F MusicSelect_Button_Size = D2D1::RectF(0.0f, 0.0f, 640.f, 160.f);

/// Ŭ���� ȭ�� ������ġ
const Vector2 Clear_Scene_Vec(0, 0);
const D2D1_RECT_F  Clear_Scene_Size = D2D1::RectF(0.0f, 0.0f, 2560.f, 1440.f);

/// ���� ��ũ�� ��ġ
const Vector2 Clear_Scroll_Vec(1016, 480);

/// ĳ������ ��ġ
const Vector2 Clear_CharacterVec(200, 486);

/// �����̸� ��ġ
const Vector2 Music_Name_Vec(600 + 400  , 160 +80-60);

/// ��ũ ������ ��ġ
const Vector2 Clear_Rank_Vec(1780, 140);

/// ���ھ� �ؽ�Ʈ �̸�
const Vector2 Score_Text_Vec(1158, 624-30);

/// �޺� �ؽ�Ʈ �̸�
const Vector2 Combo_Text_Vec(1158, 724 - 30);

/// ų �ؽ�Ʈ �̸�
const Vector2 Kill_Text_Vec(1158, 824 - 30);

/// ���ھ� �ؽ�Ʈ ����
const Vector2 Score_Num_Text_Vec(1980, 624 - 30);

/// �޺� �ؽ�Ʈ ����
const Vector2 Combo_Num_Text_Vec(1980, 724 - 30);

/// ų �ؽ�Ʈ ����
const Vector2 Kill_Num_Text_Vec(1980, 824 - 30);

/// ����Ʈ �̹��� 
const Vector2 PerPect_Image_Vec(1157, 811);

/// �� �̹���
const Vector2 Good_Image_Vec(1117, 897);

/// �̽� �̹���
const Vector2 Miss_Image_Vec(1117, 984);

/// ����Ʈ ���� 
const Vector2 PerPect_Num_Text_Vec(1980, 914);

/// �� ����
const Vector2 Good_Num_Text_Vec(1980, 1000);

/// �̽� ����
const Vector2 Miss_Num_Text_Vec(1980, 1080);

/// ���� ����
const Vector2 Lose_Scene_Vec(0, 0);
const D2D1_RECT_F Lose_Scene_Size = D2D1::RectF(0.0f, 0.0f, 2560.f, 1440.f);
