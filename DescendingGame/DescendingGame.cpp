// Decending.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <locale.h> 
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "Screen.h"
#include "Text.h"
#include "Menu.h"
#include "Sound.h"
#include "Edit.h"
#include "Play.h"

using namespace std;

Manipulate_Screen screen;
Sound_Set sound;
Menu menu(&screen);
Edit edit(&screen);
Play play(&screen, &sound);

void init();
void Rendering(int menu_key);
void Release();

void main()
{
	init();
	char in_key;
	int menu_key = 0;
	int is_run = 1;

	while (is_run) {
		
		screen.Clear();
		cin.clear();

		if (_kbhit()) {

			in_key = _getch();
			if(in_key==224)
				 in_key = _getch();
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

// =========================== menu ==========================
			if (menu_key < 3) {
				switch (in_key)
				{
					case(13):  //enter
					{
						menu_key = menu.Change();

						if (menu_key) {
							if (menu_key == 2) {
								sound.On(0);
							}
							else if (menu_key == 1) {
								sound.Off(0);
							}
							else if (menu_key == -1) {
								is_run = 0;
							}
						}
						break;
					}
					case(72): // up
					{
						menu.Check_Move(1);
						break;
					}
					case(80):  //down
					{
						menu.Check_Move(0);
						break;
					}
				}
			}

			// =========================== edit ==========================
			else if (menu_key == 3) {
				if (edit.is_on == 0) {
					edit.New_or_Load();
				}
				else {
					switch (in_key)
					{
						case(77): // right
						{
							edit.Check_Input(0);
							break;
						}
						case(75):  //left
						{
							edit.Check_Input(1);
							break;
						}
						case(72):  //up
						{
							edit.Check_Input(2);
							break;
						}
						case(80):  //down
						{
							edit.Check_Input(3);
							break;
						}
						case(32):  //space
						{
							edit.Check_Input(4);
							break;
						}
						case(13):  //enter
						{
							edit.Check_Input(5);
							break;
						}
						case('t'):  // put
						{
							edit.Check_Input(6);
							break;
						}
						case('r'):  // roll
						{
							edit.Check_Input(7);
							break;
						}
						case(27):  //esc
						{
							menu_key = 2;
							edit.Reset();
							break;
						}
						case('g'):  //go
						{
							menu_key = 7;
							break;
						}
					}
				}
			}

			// =========================== play ==========================
			else if (menu_key == 4 || menu_key == 7) {
				if (play.is_on == 0) {
					if (menu_key == 4) {
						play.Reset(3, 3);
						play.Load_Map();
					}
					else if (menu_key == 7) {
						edit.Set_Test();
						play.Set_Test(edit.map_name, edit.player_x, edit.player_y, edit.cur_upon_line);
					}
				}
				else {

					switch (in_key)
					{
						case(77): // right
						{
							play.Check_Input(0);
							break;
						}
						case(75):  //left
						{
							play.Check_Input(1);
							break;
						}
						case(72):  //up
						{
							play.Check_Input(2);
							break;
						}
						case(80):  //down
						{
							play.Check_Input(3);
							break;
						}
						case(32):  //space
						{
							play.Check_Input(4);
							break;
						}
						case(13):  //enter
						{
							play.Check_Input(5);
							break;
						}
						case(27):  //esc
						{
							if (menu_key == 7) {
								menu_key = 3;
								play.is_on = 0;
							}
							else {
								menu_key = 2;
								menu.page = 2;
							}
							break;
						}
					}

					play.Map_Engine();
					play.Player_Engine();

					if (play.is_game_over == 1) {   // game over
						if (menu_key == 7) {
							menu_key = 3;
						}
						else {
							menu_key = 5;
						}
						play.is_on = 0;
						sound.On(7);
					}
					else if (play.is_game_over == 2) {   // game clear
						if (menu_key == 7) {
							menu_key = 3;
						}
						else {
							menu_key = 6;
						}
						play.is_on = 0;
						sound.On(8);
					}

					if (in_key == 27) {    // for reset
						play.Reset(3, 3);
					}
				}
			}
// =========================== success or fail ==========================
			else if (menu_key == 5 || menu_key == 6) {
				switch (in_key)
				{
					case(27):  //esc
					{
						menu_key = 2;
						menu.page = 2;
						play.Reset(3, 3);
						break;
					}
				}
			}
		}
		/*if (menu_key == 4) {
			play.Check_Hittig();
		}*/
		Rendering(menu_key);
		sound.Update();
	}
	Release();
}

void init()
{
	_wsetlocale(LC_ALL, L"korean");      //지역화 설정을 전역적으로 적용할 
	sound.On(0);
}

void Rendering(int menu_key)
{
	if (menu_key < 3) {
		menu.Show();
	}
	else if (menu_key == 3) {
		if (edit.is_on == 1)
			edit.Show();
	}
	else if (menu_key == 4 || menu_key == 7) {
		if (play.is_on == 1)
			play.Show();
	}
	else if (menu_key == 5 || menu_key == 6) {
		menu.page = menu_key - 2;
		menu.Show();
	}

	screen.Flipping();
}

void Release()
{
}

/* 경로 얻기 
char strBuffer[_MAX_PATH] = { 0, };
char *pstrBuffer = NULL;
pstrBuffer = _getcwd(strBuffer, _MAX_PATH);
std::cout << pstrBuffer << std::endl;
*/