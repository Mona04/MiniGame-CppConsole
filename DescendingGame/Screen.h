#pragma once
#include <windows.h>

class Manipulate_Screen
{

private:
	BOOL s_b_index;
	HANDLE s_buffer[2];

public:

	void Flipping();
	void Clear();
	void Release();
	void Print(int x, int y, char* string);
	void set_Color(unsigned short color);

	Manipulate_Screen();
	~Manipulate_Screen();
};
