#pragma once
#include "CFX.h"


class FXManager : public Singleton<FXManager>
{
public:



	void RenderCombo(int combo, bool fever);
	void RenderJudgeFX(int rslt, bool fever); // 0 : miss  1 : good  2: perfect
	void RenderAll();
	void AddFX(int count, Vector2 vec, ResourceID id, bool isAni);
	void AddFX(int count, Vector2 vec, ResourceID id, bool isAni, Vector2 mov);

	void RenderHeal();

private:

	std::vector<CFX*> m_Fx;

};

