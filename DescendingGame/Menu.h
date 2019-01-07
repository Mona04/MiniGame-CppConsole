#pragma once
#include "Text.h"

class Menu
{
private:
	int cur;

	Text_Obj start;
	Text_Obj option;
	Text_Obj exit;
	Text_Obj check;
	Text_Obj on;
	Text_Obj off;
	Text_Obj edit;
	Text_Obj fail;
	Text_Obj success;

public:
	int page;

	Menu(Manipulate_Screen* scr);
	~Menu();

	void Show();
	void Check_Move(int var);
	int Change();
};
