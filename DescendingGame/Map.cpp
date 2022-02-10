#include "stdafx.h"
#include "Map.h"

Map::Map()
{}

Map::Map(Manipulate_Screen* scr)
{
	this->name = "";
	this->scr = scr;
	for (int i = 0; i < 45; i++)
		map_txt.push_back("happy");
}

Map::~Map()
{
	UnLoad();
}

void Map::New(string file_name)
{
	this->name = file_name;
	file_path += name + ".txt";

	ofstream oFile;
	oFile.open(file_path);
	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 150; j++) {
			oFile << " ";
		}
		oFile << "\n";
	}

	char temp = 30;
	for (int j = 0; j < 150; j++) {
		oFile << temp;
	}
	oFile << "\n";

	oFile.close();
}

void Map::Load(string file_name, int mode)
{
	// Editor Load
	if (mode == 0) {
		this->name = file_name;
		file_path += file_name + ".txt";
	}
	// OnPlay Load
	if (mode == 1) {
		this->name = file_name;
		string origin = file_path + file_name + ".txt";
		file_path += file_name + "_pasted.txt";

		std::ifstream in(origin); // open original file
		std::ofstream out(file_path); // open target file
		out << in.rdbuf(); // read original file into target
		out.close(); // explicit close, unnecessary in this case
		in.close();// explicit close, unnecessary in this case
	}

}

void Map::UnLoad()
{
	if (iFile.is_open())
		iFile.close();
	if (oFile.is_open())
		oFile.close();
}

void Map::Map_Input(int mode, int in_x, int in_y, char in_char)
{
	if (iFile.is_open()) iFile.close();
	if (!oFile.is_open()) oFile.open(file_path, ios::in | ios::out | fstream::ate);
	
	int cur = in_x  + (in_y + cur_upon_line) * 152;    
	oFile.seekp(cur, ios::beg);
	if (mode == 0) {
		char obj = in_char;
		oFile.put(obj);
	}
}

void Map :: Show()
{
	if (oFile.is_open())  oFile.close();
	if (!iFile.is_open()) iFile.open(file_path);
	iFile.seekg(cur_upon_line * 152);

	string text;
	int temp_y = 0;

	for(int i = 0 ; i<40 ; i++)
	{
		getline(iFile, text);
		map_txt[i] = text;
		std::vector<char> writable(text.begin(), text.end());
		writable.push_back('\0');
		scr->Print(0, temp_y++, &writable[0]);
	};
	getline(iFile, text);
	map_txt[40] = text;
}

void Map::Move_Frame(int var)
{
	switch (var)
	{
		case 0:   // up
		{
			if (cur_upon_line > 0) {
				cur_upon_line -= 1;
			} break;
		}
		case 1:   // down
		{
			if (cur_upon_line < 502) {
				cur_upon_line += 1;
			} break;
		}
	}
}