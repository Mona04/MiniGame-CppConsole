#include "stdafx.h"
#include "Screen.h""
#include <iostream>


Manipulate_Screen::Manipulate_Screen()
{
	// 커서 옵션 객체를 만든다.
	CONSOLE_CURSOR_INFO cci;
	COORD size = { 150, 40 };

	//커서 옵션을 바꾼다.
	cci.dwSize = 1;
	cci.bVisible = 0;
	
	//창 크기 관련 구조체
	SMALL_RECT rect; 
	rect.Left = 0;
	rect.Right = 150 - 1;
	rect.Top = 0;
	rect.Bottom = 40 - 1;

	//화면 버퍼 2개를 만든다.
	for (int i = 0; i < 2; i++) {
		s_buffer[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleScreenBufferSize(s_buffer[i], size); //콘솔 버퍼의 크기 설정
		SetConsoleWindowInfo(s_buffer[i], TRUE, &rect); //콘솔
		SetConsoleCursorInfo(s_buffer[i], &cci); //커서 옵션을 적용
	}

	// 인덱스 초기화
	s_b_index = 0;
}

void Manipulate_Screen::Flipping()
{
	// 인덱스가 0, 1 로 바뀌면서 화면이 깔쌈히 바뀜
	Sleep(0);
	SetConsoleActiveScreenBuffer(s_buffer[s_b_index]);
	s_b_index = !s_b_index;
}

void Manipulate_Screen::Clear()
{
	// 아래 함수는, 어디서, 무엇으로, 어떤 크기로, 어디서부터 
	// 그리고 좌표가 저장되는 곳으로 arg 가 설정됨
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(s_buffer[s_b_index], ' ', 150 * 40, Coor, &dw);
}
void Manipulate_Screen::Release()
{
	//끝날 때 화면 지움
	CloseHandle(s_buffer[0]);
	CloseHandle(s_buffer[1]);
}

void Manipulate_Screen::Print(int x, int y, char* string)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(s_buffer[s_b_index], CursorPosition);
	WriteFile(s_buffer[s_b_index], string, strlen(string), &dw, NULL);
}

void Manipulate_Screen::set_Color(unsigned short color)
{
	SetConsoleTextAttribute(s_buffer[s_b_index], color);
}

Manipulate_Screen::~Manipulate_Screen() 
{}

