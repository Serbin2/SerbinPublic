#pragma once

/// �׳� Ÿ�̹� ����� �����

class Flag
{
public:
	Flag();
	Flag(float time);
	~Flag();

	void Set(float time);
	bool OneTimeCheck();
	bool Check();

private:
	float BaseTime;
	float Sum;
};

class Flag_Fream
{
public:
	Flag_Fream();
	Flag_Fream(float time);
	~Flag_Fream();

	void Set(float time);
	bool OneTimeCheck();
	bool Check();

private:
	float BaseTime;
	float Sum;
};