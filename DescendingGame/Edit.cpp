#include "stdafx.h"
#include "Edit.h"

Edit::Edit(Manipulate_Screen *scr)
{
	map = Map(scr);
	player = Player(scr, 3, 3);

	cur_obj->push_back(6);  //  -
	cur_obj->push_back(14);  // ¢Ý
	cur_obj->push_back(127); // ¡à
	cur_obj->push_back(30);   // ¡ã
	cur_obj->push_back(31);   // ¡å
	cur_obj->push_back(38);  //  &
	cur_obj->push_back(32);  //  " "
	for (int i = 0; i < 10; i++) {
		cur_obj->push_back(48+i);  //  "0+i"
	}
	cur_obj->push_back(42);  //  aster *
	cur_obj->push_back(39);  //   `

	this->scr = scr;

	this->Reset();
}

void Edit::Reset()
{
	map = Map(scr);
	player.Reset(3, 3);

	player_direct = 0;
	cur_obj_num = 0;
	is_on = 0;
}

Edit::~Edit()
{
}

void Edit::New_or_Load()
{
	if (is_on == 0) {
		string text = "you have two choice.\n \n    new FileName\n    load FileName\n\nexample)\n\n    load ex \n\ndon't append \"txt\"\n    ";
		std::vector<char> writable(text.begin(), text.end());
		writable.push_back('\0');
		scr->Print(0, 0, &writable[0]);

		string input = "";
		char* cur = new char[2];
		cur[0] = 0;
		cur[1] = '\0';

		int temp_x = 0;
		scr->Flipping();

		while (cur[0] !=(13))
		{
			if (_kbhit()) {
				scr->Flipping();
				cur[0] = _getch();
				_getch();
				if (cur[0] == 8) {
					if (input.length()) {
						cur[0] = ' ';
						scr->Print(--temp_x, 11, &cur[0]);
						input = input.substr(0, input.length() - 1);
						scr->Flipping();
					}
				}
				else {
					scr->Print(temp_x++, 11, &cur[0]);
					input += cur[0];
					scr->Flipping();
				}
			}
		}
		delete[] cur;

		if (input.substr(0, 3).compare("new")==0) {
			map.New(input.substr(4, input.length() - 5));
			this->map_name = input.substr(4, input.length() - 5);
			is_on = 1;
		}
		else if (input.substr(0, 4).compare("load")==0) {
			map.Load(input.substr(5, input.length() - 6));
			this->map_name = input.substr(5, input.length() - 6);
			is_on = 1;
		}
	}
}

void Edit::Show()
{
	if (is_on == 1) {
		map.Show();
		player.Show();
		Option_Show();
	}
}

void Edit::Option_Show()
{
	string text = "map name is " + map.name + " and cur char is ";
	std::vector<char> writable(text.begin(), text.end());
	writable.push_back(cur_obj->at(cur_obj_num));
	writable.push_back('\0');
	scr->Print(0, 0, &writable[0]);
}

void Edit::Check_Input(int var)
{
	switch (var)
	{
		case 0:   // right
		{
			player.Move(var);
			player_direct = var;
			break;
		}
		case 1:   // left
		{
			player.Move(var);
			player_direct = var;
			break;
		}
		case 2:   // up
		{
			if (player.y == 2) {
				map.Move_Frame(0);
				player.Move(3);
			}
			else {
				player.Move(var);
			}
			player_direct = var;
			break;
		}
		case 3:   // down
		{
			if (player.y == 36) {
				player.Move(2);
				map.Move_Frame(1);
			}
			else {
				player.Move(var);
			}
			player_direct = var;
			break;
		}
		case 4:   // space_bar
		{
			for (int i = 0; i < 5; i++)
				this->Check_Input(player_direct);
			break;
		}
		case 5:   // enter
		{
			cur_obj_num = (cur_obj_num + 1) % 19;
			break;
		}
		case 6:   // put
		{
			map.Map_Input(0, player.x, player.y, cur_obj->at(cur_obj_num));
			break;
		}
		case 7:   // roll
		{
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					map.Map_Input(0, player.x+i, player.y+j, cur_obj->at(cur_obj_num));
				}
			}
			break;
		}
	}
}


void Edit::Set_Test()
{
	this->player_x = player.x;
	this->player_y = player.y;
	this->cur_upon_line = map.cur_upon_line;
}

