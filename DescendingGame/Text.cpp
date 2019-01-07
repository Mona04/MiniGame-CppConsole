#include "stdafx.h"
#include "Text.h"

Text_Obj::Text_Obj()
{
	text = new string[40, 150];
}

Text_Obj::Text_Obj(Manipulate_Screen* in_scr, string name, int in_x, int in_y)
{
	text = new string[40, 150];
	Set(in_scr, name, in_x, in_y, text);
}

void Text_Obj::Set(Manipulate_Screen* in_scr, string name, int in_x, int in_y, string* txt)
{
	ifstream iFile;
	
	scr = in_scr;
	this->name = name;
	file_path += name + ".txt";
	x = in_x;
	y = in_y;

	iFile.open(file_path);
	int i = 0;

	while (getline(iFile, txt[i]))
	{
		i++;
	};
	row_length = i;

	iFile.close();
}

void Text_Obj::Show()
{
	int temp_y = y;
	for (int i = 0; i < row_length; i++) {
		std::vector<char> writable(text[i].begin(), text[i].end());
		writable.push_back('\0');
		scr->Print(x, temp_y++, &writable[0]);
	}
}

Text_Obj::~Text_Obj()
{
	if (text) {
		delete[] text;
	}
}