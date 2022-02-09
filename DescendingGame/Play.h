#pragma once
#include <vector>
#include <conio.h>

#include "Screen.h"
#include "Sound.h"
#include "Text.h"
#include "Player.h"
#include "Map.h"
#include "Skill.h"

class Play
{
	Player player;
	std::unique_ptr<Map> map;
	Skill skill;

	Manipulate_Screen* scr;
	Sound_Set* sound;
	
	std::vector<char> cur_obj[30];
	string map_name;
	
	int player_direct;
	int is_air_dash;
	int map_decreasing_num;
	int map_engine_even;
	int is_skill;

public:
	int is_on;
	int is_game_over;
	int is_player_jump;
	int points;

	Play(Manipulate_Screen *scr, Sound_Set *sound);
	~Play();

	void Reset(int, int);
	void Load_Map();
	void Set_Test(string map_name, int x, int y, int cur_upon_line);

	void Show();
	void Option_Show();
	void Check_Input(int var);

	int Map_Engine();
	void Player_Engine();

};

