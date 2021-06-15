#pragma once
#include <iostream>
#include <vector>	

#include "Button.h"
#include "Cursor.h"

#include "../Scene/Scene.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

public:
	void Update();
	void SetInputItem();

private:	
	Cursor* pCursor;
	std::vector<Button*> BtnPool;
};

