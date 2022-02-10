#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Screen.h"

using namespace std;

class Text_Obj
{
protected:
	string file_path = "../dot/other/";
	string* text;
	string name;
	Manipulate_Screen* scr;
	int row_length;
public:
	int x;
	int y;
	Text_Obj();
	Text_Obj(Manipulate_Screen* in_scr, string name, int x, int y);
	~Text_Obj();
	void Set(Manipulate_Screen* in_scr, string name, int in_x, int in_y, string* txt);
	void Show();
	Text_Obj& operator=(const Text_Obj& that)
	{
		Set(that.scr, that.name, that.x, that.y, text);
		return *this;
	}
};