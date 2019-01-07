#include "stdafx.h"
#include "Play.h"


Play::Play(Manipulate_Screen *scr, Sound_Set *sound)
{
	player = Player(scr, 3, 3);
	skill = Skill(scr);

	cur_obj->push_back(6);  //  -
	cur_obj->push_back(14);  // ¢Ý
	cur_obj->push_back(127); // ¡à
	cur_obj->push_back(30);   // ¡ã
	cur_obj->push_back(31);   // ¡å
	cur_obj->push_back(38);  //  &
	cur_obj->push_back(32);  //  " "
	for (int i = 0; i < 10; i++) {
		cur_obj->push_back(48 + i);  //  "0+i"
	}
	cur_obj->push_back(42);  //  aster *
	cur_obj->push_back(39);  //  `


	this->scr = scr;
	this->sound = sound;
	this->Reset(3, 3);
}

void Play::Reset(int in_x, int in_y)
{
	map = Map(scr);
	player.Reset(in_x, in_y);
	map_name = "";

	player_direct = 0;

	is_on = 0;
	is_air_dash = 0;
	map_decreasing_num = 0;
	map_engine_even = 0;
	is_skill = 0;
	is_game_over = 0;
	is_player_jump = 0;
	points = 0;
}

void Play::Load_Map()
{
	if (is_on == 0) {
		string text = "Please Enter Map Name like below.\n \n    FileName\n\n  don't append \"txt\"\n    ";
		std::vector<char> writable(text.begin(), text.end());
		writable.push_back('\0');
		scr->Print(0, 0, &writable[0]);

		string input = "";
		char* cur = new char[2];
		cur[0] = 0;
		cur[1] = '\0';

		int temp_x = 0;
		scr->Flipping();

		while (cur[0] != (13))
		{
			if (_kbhit()) {
				scr->Flipping();
				cur[0] = _getch();
				_getch();
				if (cur[0] == 8) {   // back space
					if (input.length()) {
						cur[0] = ' ';
						scr->Print(--temp_x, 8, &cur[0]);
						input = input.substr(0, input.length() - 1);
						scr->Flipping();
					}
				}
				else {
					scr->Print(temp_x++, 8, &cur[0]);
					input += cur[0];
					scr->Flipping();
				}
			}
		}
		map.Load(input.substr(0,input.length() - 1), 1);
		is_on = 1;
		delete cur;
	}
}

void Play::Set_Test(string map_name, int in_x, int in_y, int cur_upon_line)
{
	string tmp = "";
	for (int i = 0; i < map_name.length(); i++)
		tmp += map_name[i];
	this->Reset(in_x, in_y);
	map.Load(map_name, 1);
	map.cur_upon_line = cur_upon_line;
	is_on = 1;
}

Play::~Play()
{
}

void Play::Show()
{
	if (is_on == 1) {
		map.Show();
		player.Show();
		Option_Show();
		if (is_skill == 1) {
			for (int i = 0; i < 10; i++) {
				skill.Show(player.x, player.y);
				scr->Flipping();
				Sleep(33);
			}
			is_skill = 0;
		}
	}
}

void Play::Option_Show()
{
	string text = "map name is " + map.name + " and power | ";

	std::vector<char> writable(text.begin(), text.end());
	for(int i = 0 ; i<points ; i++)
		writable.push_back('@');
	writable.push_back('\0');
	scr->Print(0, 0, &writable[0]);

	writable.clear();
	for (int i = 0; i < 150; i++) {
		writable.push_back(31);
	}
	writable.push_back('\0');
	scr->Print(0, 1, &writable[0]);
}

void Play::Check_Input(int var)
{
	switch (var)
	{
		case 0:   // right
		{
			for (int i = 0; i < 3; i++) {
				char tmp = map.map_txt[player.y + i + 1][player.x + 2];
				if (tmp == 6 || tmp == 127) {
					break;
				}
				if (i == 2) {
					player.Move(var);
				}
			}
			player_direct = var;
			break;
		}
		case 1:   // left
		{
			for (int i = 0; i < 3; i++) {
				char tmp = map.map_txt[player.y + i + 1][player.x - 1];
				if (tmp == 6 || tmp == 127) {
					break;
				}
				if (i == 2) {
					player.Move(var);
				}
			}
			player_direct = var;
			break;
		}
		case 2:   // jump
		{
			if (is_player_jump == 0) {
				if (player.y == 2) {
					is_game_over = 1; // game over by floor
					sound->On(5);
				}
				player.Move(var);
				is_player_jump = 2;
				sound->On(1);
			}
			break;
		}
		case 3:   // down
		{
			break;
		}
		case 4:   // dash
		{
			if (is_player_jump != 0 && is_air_dash == 0) {
				for (int i = 0; i < 10; i++) {
					map.Map_Input(0, player.x + player_direct, player.y + 1, '=');
					Check_Input(player_direct);
					sound->On(2);
				}
				is_air_dash = 1;
			}
			break;
		}		
		case 5: // skill
		{
			if (points >= 5) {
				points -= 5;
				is_skill = 1;
				sound->On(3);
			}
		}

	}
}

int Play::Map_Engine()
{
	map_engine_even = (map_engine_even + 1) % 2;

	if (map_engine_even == 0)
		return 0;

	std::vector<int> for_dupulicate(40 * 150, 0);
	for (int j = 0; j < 40; j++) {
		for (int i = 0; i < 150; i++) {

			char key = map.map_txt[j][i];

			if (is_skill == 1) {
				if (key == 30 || key == 31 || key == 3 || key == 42) {
					if(player.x-5<i && i<player.x+8)
						map.Map_Input(0, i, j, ' ');
				}
				for (int t = 0; t < 10; t++) {
					if (key == 48 + t) {
						if (player.x - 5<i && i<player.x + 8)
							map.Map_Input(0, i, j, ' ');
					}
				}
			}

			if (for_dupulicate[150 * j + i] == 0) {

				switch (key) 
				{
					case('='):
					{
						map.Map_Input(0, i, j, ' ');
						break;
					}

					case(49):   // 1  saw tooth right
					{
						if (i < 145) {
							if (map.map_txt[j][i+4] == ' ') {
								map.Map_Input(0, i, j, ' ');
								map.Map_Input(0, i + 4, j, '2');
								for_dupulicate[150 * j + (i+4)] = 1;
							}
						}
						break;
					}
					case(50):   // 2   up
					{
						if (j > 3) {
							if (map.map_txt[j-2][i] == ' ') {
								map.Map_Input(0, i, j, ' ');
								map.Map_Input(0, i, j-2, '3');
								for_dupulicate[150 * (j-2) + i] = 1;
							}
						}
						break;
					}
					case(51):   // 3  saw tooth  left
					{
						if (i > 5) {
							if (map.map_txt[j][i - 4] == ' ') {
								map.Map_Input(0, i, j, ' ');
								map.Map_Input(0, i - 4, j, '4');
								for_dupulicate[150 * j + i-4] = 1;
							}
						}
						break;
					}
					case(52):   // 4   saw tooth down
					{
						if (j < 37) {
							if (map.map_txt[j+2][i] == ' ') {
								map.Map_Input(0, i, j, ' ');
								map.Map_Input(0, i, j+2, '1');
								for_dupulicate[150 * (j+2) + i] = 1;
							}
						}
						break;
					}

					case(53):   // 5   down
					{
						if (j < 37) {
							if (map.map_txt[j + 2][i] == ' ') {
								map.Map_Input(0, i, j, ' ');
								map.Map_Input(0, i, j + 2, '6');
								for_dupulicate[150 * (j + 2) + i] = 1;
							}
						}
						break;
					}
					case(54):   // 6   up
					{
						if (j > 3) {
							if (map.map_txt[j - 2][i] == ' ') {
								map.Map_Input(0, i, j, ' ');
								map.Map_Input(0, i, j - 2, '5');
								for_dupulicate[150 * (j - 2) + i] = 1;
							}
						}
						break;
					}

					case(55):   // 7 right
					{
						if (i < 145) {
							if (map.map_txt[j][i + 4] == ' ') {
								map.Map_Input(0, i, j, ' ');
								map.Map_Input(0, i + 4, j, '8');
								for_dupulicate[150 * j + (i + 4)] = 1;
							}
						}
						break;
					}
					case(56):   // 8 left
					{
						if (i > 5) {
							if (map.map_txt[j][i - 4] == ' ') {
								map.Map_Input(0, i, j, ' ');
								map.Map_Input(0, i - 4, j, '7');
								for_dupulicate[150 * j + i - 4] = 1;
							}
						}
						break;
					}

					case(57):   // 9  straight left
					{
						if (i > 5 && map.map_txt[j][i - 1] != 127 
							&& map.map_txt[j][i - 2] != 127 
							&& map.map_txt[j][i - 3] != 127
							&& map.map_txt[j][i - 4] == ' ') {
							if (map.map_txt[j][i - 4] == ' ') {
								map.Map_Input(0, i, j, ' ');
								map.Map_Input(0, i - 4, j, '9');
								for_dupulicate[150 * j + i - 4] = 1;
							}
						}
						else {
							map.Map_Input(0, i, j, '0');
						}
						break;
					}
					case(48):   // 0 right
					{
						if (i < 145 && map.map_txt[j][i + 1] != 127
							&& map.map_txt[j][i + 2] != 127
							&& map.map_txt[j][i + 3] != 127
							&& map.map_txt[j][i + 4] == ' ') {
							if (map.map_txt[j][i + 4] == ' ') {
								map.Map_Input(0, i, j, ' ');
								map.Map_Input(0, i + 4, j, '0');
								for_dupulicate[150 * j + (i + 4)] = 1;
							}
						}
						else {
							map.Map_Input(0, i, j, '9');
						}
						break;
					}

					case(42):   // ` ª­ªéª­ªé
					{
						map.Map_Input(0, i, j, 39);
						break;
					}
					case(39):   // " ª­ªéª­ªé
					{
						map.Map_Input(0, i, j, 34);
						break;
					}
					case(34):   // ^ ª­ªéª­ªé
					{
						map.Map_Input(0, i, j, 94);
						break;
					}
					case(94):   // * ª­ªéª­ªé
					{
						map.Map_Input(0, i, j, 44);
						break;
					}
					case(44):   // , ª­ªéª­ªé
					{
						map.Map_Input(0, i, j, 46);
						break;
					}
					case(46):   // . ª­ªéª­ªé
					{
						map.Map_Input(0, i, j, 42);
						break;
					}
				}
			}
		}
	}



}

void Play::Player_Engine()
{

	char* map_where_player = new char[10];


	// make array of a map of subset where player is in 
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			map_where_player[2*i+j] = map.map_txt[player.y+i][player.x+j];
		}
	}	
	for (int i = 0; i < 10; i++) {   // check touched Thorn => game over
		if (map_where_player[i] == 30 || map_where_player[i] == 31 
			|| map_where_player[i] == 3 || map_where_player[i]==42) {
			sound->On(5);
			is_game_over = 1;
		}
		for (int j = 0; j < 10; j++) {
			if (map_where_player[i] == 48+j) {
				sound->On(5);
				is_game_over = 1;
			}
		}
	}
	for (int i = 2; i < 8; i++) {   // check getting points
		if (map_where_player[i] == 14) {
			map.Map_Input(0, player.x + i % 2, player.y + i / 2 , ' ');
			if(points<10)   // max is 10
				points += 1;
			sound->On(4);
		}
	}
	for (int i = 2; i < 8; i++) {   // check game clear
		if (map_where_player[i] == 38) {
			is_game_over = 2;
		}
	}
	for (int i = 0; i < 2; i++) {   // check whether player is in air
		if (map_where_player[8+i] == 6 || map_where_player[8+i] == 127) {
			is_player_jump = 0;
			is_air_dash = 0;
			break;
		}
		if (i == 1 && is_player_jump == 0)
			is_player_jump = 1;
	}

	if (++map_decreasing_num > 10) {     // map decreasing
		map_decreasing_num = 0;
		if (player.y == 3) {  // game over by floor
			is_game_over = 1;
			sound->On(5);
		}
		player.Move(2);
		map.Move_Frame(1);
		sound->On(6);
	}

	if (is_player_jump==1) {    //  falling
		if (player.y == 30) {
			player.Move(2);
			map.Move_Frame(1);
		}
		else {
			player.Move(3);
		}		
	}

	else if (is_player_jump >= 2 && is_player_jump !=8 ) {    // jump jump
		if (player.y == 2) {    // game over by floor
			is_game_over = 1;
		}
		if (is_player_jump != 2) {
			if(map_where_player[0]!=127 && map_where_player[1]!=127)
				player.Move(2);
		}
		else if (is_player_jump == 7) {
			;
		}
		is_player_jump = ++is_player_jump % 8;
	}

	delete[] map_where_player;
}