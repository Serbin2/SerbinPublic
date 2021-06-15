#pragma once

const static Vector2 OneVec(1018, 904);
const static Vector2 TwoVec(1270, 1004);
const static Vector2 ThreeVec(1522, 904);
const static Vector2 FourVec(916, 650);
const static Vector2 SixVec(1624, 650);
const static Vector2 SevenVec(1018, 400);
const static Vector2 EightVec(1270, 296);
const static Vector2 NineVec(1522, 400);

class MagicCircle : public GameObject, public Singleton<MagicCircle>
{
public:
	MagicCircle();
	~MagicCircle();

public:
	void OnEvent();
	void OnRender();
	void OnRender(bool miss, bool fever);

	void BaseFourVecRender();
	void SettingTRS(Vector2 Src, Vector2 Dst);
	void DrawMagicLine(int src, int dst, bool light);

	void DrawCircle();
	void DrawCircle(bool miss,bool fever);
	void DrawNumber();
	void DrawMissNumber();
	void DrawNumberLight(int key);

	void ClearLine();
	void SetLine(int src, int dst);

private:
	bool Line[8][8];

};

