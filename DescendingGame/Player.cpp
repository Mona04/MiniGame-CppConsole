#include "stdafx.h"
#include "Player.h"


Player::Player(Manipulate_Screen* scr, int in_x, int in_y)
{
	x = in_x;
	y = in_y;
	player_1 = Text_Obj(scr, "player_1", in_x, in_y);
	player_2 = Text_Obj(scr, "player_2", in_x, in_y);
}

Player::Player()
{}

void Player::Reset(int in_x, int in_y)
{
	x = in_x;
	y = in_y;
	player_1.x = in_x;
	player_1.y = in_y;
	player_2.x = in_x;
	player_2.y = in_y;
}

Player::~Player()
{
}

void Player::Show()
{
	if (player_render) {
		player_1.Show();
	}
	else {
		player_2.Show();
	}
}

void Player::Move(int var)
{
	switch (var)
	{
		case 0:   // right
		{
			if (x < 148) 
			{
				x++;
				player_1.x++;
				player_2.x++;
				player_render = !player_render;
			} break;
		}
		case 1:   // left
		{
			if (x > 2)
			{
				x--;
				player_1.x--;
				player_2.x--;
				player_render = !player_render;
			} break;
		}
		case 2:   // up
		{
			if (y > 2)
			{
				y--;
				player_1.y--;
				player_2.y--;
				player_render = !player_render;
			} break;
		}
		case 3:   // down
		{
			if (y < 36)
			{
				y++;
				player_1.y++;
				player_2.y++;
				player_render = !player_render;
			} break;
		}
	}
}