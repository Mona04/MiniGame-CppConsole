#include "stdafx.h"
#include "Skill.h"

Skill::Skill(Manipulate_Screen* scr)
{

	skill_1 = Text_Obj(scr, "skill_1", 10, 3);
	skill_2 = Text_Obj(scr, "skill_2", 10, 3);
}

Skill::Skill()
{}

Skill::~Skill()
{
}

void Skill::Show(int in_x, int in_y)
{
	x = 0 < (in_x - 4) ? (in_x - 4) : 0;
	x = 138 > (in_x - 4) ? (in_x - 4) : 138;
	y = 3;

	skill_1.x = x;
	skill_1.y = y;
	skill_2.x = x;
	skill_2.y = y;

	if (skill_render%2==0) {
		skill_1.Show();
	}
	else {
		skill_2.Show();
	}

	skill_render = ++skill_render % 2;
}