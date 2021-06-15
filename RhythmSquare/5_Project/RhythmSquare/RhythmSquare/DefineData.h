#pragma once

// 노트를 미리 보여주는 시간 길이(박자)
#define PRE_BEAT	2

// 판정 기준(초)
#define JUD_EXAC	0.020 //20ms
#define JUD_PERF	0.040
#define JUD_GOOD	0.100
#define JUD_MISS	0.101

// 판정 반환값(여기는 수정하지 마세요)
#define JUD_NO_MATCH	0
#define JUD_EARL_MISS	1
#define JUD_EARL_GOOD	2
#define JUD_EARL_PERF	3
#define JUD_EXAC_PERF	4
#define JUD_LATE_PERF	5
#define JUD_LATE_GOOD	6
#define JUD_LATE_MISS	7

// 디폴트 입력 키
#define DEF_KEY_1	0x61 // 키패드 1번
#define DEF_KEY_2	0x62
#define DEF_KEY_3	0x63
#define DEF_KEY_4	0x64
#define DEF_KEY_6	0x66
#define DEF_KEY_7	0x67
#define DEF_KEY_8	0x68
#define DEF_KEY_9	0x69 // 키패드 9번

#define DEF_KEY_F	0x41 // A
#define DEF_KEY_W	0x53 // S
#define DEF_KEY_G	0x44 // D

// 기본 경로
#define WAVE_PATH			L"../Data/music/"
#define SHEET_PATH			L"../Data/sheet/"
/// .bin 파일의 경우 (노래 이름)_Easy/Normal/Hard.bin 으로 통일해주셔야 합니다.

// 곡 수 만큼 만들어야 함
// 파일명(노래 이름)
#define PLOT_TWIST				100
#define PLOT_TWIST_WAVE			L"Lokan_Plot_Twist"
#define PLOT_TWIST_EXT			L".wav"

#define PRECISION_STRIKE		101
#define PRECISION_STRIKE_WAVE	L"Lokan_Precision_Strike"
#define PRECISION_STRIKE_EXT	L".wav"

#define INTROSPECT				102
#define INTROSPECT_WAVE			L"Lokan_introspect"				
#define INTROSPECT_EXT			L".wav"


// 플레이중 음악 앞뒤의 여유시간
#define AFTER_MUSIC_TIME	0 // 음악이 끝나고 해당 시간만큼 게임이 지속됩니다.

// 노트 판정 위치 좌표
#define X_5		1634
#define X_4		1532
#define X_3		1280
#define X_2		1028
#define X_1		926

#define Y_5		1014
#define Y_4		914
#define Y_3		660
#define Y_2		410
#define Y_1		306


// UI / FX 위치 정의
#define SCORE_BOX_X			2004
#define SCORE_BOX_Y			40
#define SCORE_FONT_X		88
#define SCORE_FONT_Y		120

#define COMBO_TEXT_X		280
#define COMBO_TEXT_Y		78

#define COMBO_BOX_X			336
#define COMBO_BOX_Y			152
#define COMBO_FONT_X		88
#define COMBO_FONT_Y		120

#define JUDGE_BOX_X			1155
#define JUDGE_BOX_Y			555

#define UI_PROGRESS_BAR_X	0
#define UI_PROGRESS_BAR_Y	0

#define UI_BAR_X			725
#define UI_HP_BAR_Y			1313
#define UI_FEVER_BAR_Y		1253
#define UI_HP_BAR_STEP_X	10
#define UI_HP_BAR_STEP_Y	9
#define UI_FE_BAR_STEP_X	10
#define UI_FE_BAR_STEP_Y	10
#define UI_HP_BAR_BODY_X	1063
#define UI_FE_BAR_BODY_X	1079

// 노트당 점수
#define SCORE_PER_NOTE		20
#define DAMAGE_PER_NOTE		10

// 피버에 필요한 퍼펙트 수
#define FEVER_STACK			10

// 플레이어 기본 체력
#define PLAYER_DEF_HP		200

// 입력 타이밍 보정
#define INPUT_REV			0.010