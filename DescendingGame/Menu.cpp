#include "stdafx.h"
#include "Menu.h"
#include <iostream>

Menu::Menu(Manipulate_Screen *scr)
{
	page = 0;
	cur = 0;

	start = Text_Obj(scr, "start", 15, 18);
	option = Text_Obj(scr, "option", 15, 24);
	exit = Text_Obj(scr, "exit", 15, 30);
	check = Text_Obj(scr, "check", 5, 19);
	on = Text_Obj(scr, "on", 15, 18);
	off = Text_Obj(scr, "off", 15, 24);
	edit = Text_Obj(scr, "edit", 15, 24);
	fail = Text_Obj(scr, "fail", 80, 17);
	success = Text_Obj(scr, "success", 60, 17);
}

Menu::~Menu()
{
}

void Menu::Show()
{
	if (page == 0) {
		start.Show();
		option.Show();
		exit.Show();
		check.Show();
	}
	else if (page == 1) {
		on.Show();
		off.Show();
		exit.Show();
		check.Show();
	}
	else if (page == 2) {
		start.Show();
		edit.Show();
		exit.Show();
		check.Show();
	}
	else if (page == 3) {
		fail.Show();
	}
	else if (page == 4) {
		success.Show();
	}
}

void Menu::Check_Move(int key)
{
	if (page == 0 || page == 1 || page == 2) {
		switch (key)
		{
			case 1:  //up
			{
				if (check.y > 19)
					check.y -= 6;
				break;
			}
			case 0:  //down
			{
				if (check.y < 31)
					check.y += 6;
			} break;
		}
	}
}

int Menu::Change()
{
	switch (page)
	{
		case 0:
		{
			if (check.y == 31) {  // exit => game exit
				return -1;
			}
			else if (check.y == 25) {   // option
				page = 1;
				check.y = 19;
				return 0;
			} 
			else if (check.y == 19) {   // start => choice
				page = 2;
				return 0;
			}
		}
		case 1:
		{
			if (check.y == 31) {   // exit => page 0
				page = 0;
				check.y = 19;
				return 0;
			} 
			else if (check.y == 25) {
				return 1;  // sound off
			}
			if (check.y == 19) {
				return 2;   // sound on
			}
		}
		case 2:
		{
			if (check.y == 31) {   // exit => page 0
				page = 0;
				check.y = 19;
				return 0;
			}
			else if (check.y == 25) {  // edit
				page = 2;
				return 3;
			}
			if (check.y == 19) {   // start
				page = 2;
				return 4;   
			}
		}
	}

}