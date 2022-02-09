#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Screen.h"

using namespace std;

class Map
{
private:
	string file_path = "../dot/map/";
	Manipulate_Screen* scr;
	ifstream iFile;
	ofstream oFile;


public:
	string name;
	std::vector<string> map_txt;
	int cur_upon_line = 0;

	Map();
	Map(Manipulate_Screen* scr);
	~Map();

	void New(string file_name);
	void Load(string file_name, int mode);
	void UnLoad();
	void Map_Input(int var, int in_x, int in_y, char in_char);
	void Show();
	void Move_Frame(int var);
};


