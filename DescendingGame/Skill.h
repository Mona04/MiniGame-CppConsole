#pragma once
#include "Text.h"

class Skill
{
	Text_Obj skill_1;
	Text_Obj skill_2;
	int skill_render = 0;
public:
	int x;
	int y;

	Skill(Manipulate_Screen* scr);
	Skill();
	~Skill();

	void Show(int in_x, int in_y);
};

