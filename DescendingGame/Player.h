#pragma once
#include "Text.h"
#include "Screen.h"

class Player
{
	Text_Obj player_1;
	Text_Obj player_2;
	BOOL player_render = 0;
	BOOL is_floor = 0;
public:
	int x;
	int y;
	
	Player(Manipulate_Screen* scr, int in_x, int in_y);
	Player();
	~Player();

	void Reset(int in_x, int in_y);
	void Show();
	void Move(int var);
};

