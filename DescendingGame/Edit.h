#pragma once
#include "Screen.h"
#include "Text.h"
#include "Player.h"
#include "Map.h"
#include <vector>
#include <conio.h>

class Edit
{
private:
	Player player;
	std::unique_ptr<Map> map = nullptr;
	Manipulate_Screen* scr;
	
	std::vector<char> cur_obj[30];
	int cur_obj_num;
	int player_direct;

public:
	int is_on;
	int player_x;
	int player_y;
	int cur_upon_line;
	string map_name;

	Edit(Manipulate_Screen *scr);
	~Edit();

	void Reset();
	void New_or_Load();
	void Show();
	void Option_Show();
	void Check_Input(int var);
	void Set_Test();
};

