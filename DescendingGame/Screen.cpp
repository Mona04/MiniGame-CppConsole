#include "stdafx.h"
#include "Screen.h""
#include <iostream>


Manipulate_Screen::Manipulate_Screen()
{
	// Ŀ�� �ɼ� ��ü�� �����.
	CONSOLE_CURSOR_INFO cci;
	COORD size = { 150, 40 };

	//Ŀ�� �ɼ��� �ٲ۴�.
	cci.dwSize = 1;
	cci.bVisible = 0;
	
	//â ũ�� ���� ����ü
	SMALL_RECT rect; 
	rect.Left = 0;
	rect.Right = 150 - 1;
	rect.Top = 0;
	rect.Bottom = 40 - 1;

	//ȭ�� ���� 2���� �����.
	for (int i = 0; i < 2; i++) {
		s_buffer[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleScreenBufferSize(s_buffer[i], size); //�ܼ� ������ ũ�� ����
		SetConsoleWindowInfo(s_buffer[i], TRUE, &rect); //�ܼ�
		SetConsoleCursorInfo(s_buffer[i], &cci); //Ŀ�� �ɼ��� ����
	}

	// �ε��� �ʱ�ȭ
	s_b_index = 0;
}

void Manipulate_Screen::Flipping()
{
	// �ε����� 0, 1 �� �ٲ�鼭 ȭ���� ����� �ٲ�
	SetConsoleActiveScreenBuffer(s_buffer[s_b_index]);
	s_b_index = !s_b_index;
}

void Manipulate_Screen::Clear()
{
	// �Ʒ� �Լ���, ���, ��������, � ũ���, ��𼭺��� 
	// �׸��� ��ǥ�� ����Ǵ� ������ arg �� ������
	COORD Coor = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(s_buffer[s_b_index], ' ', 150 * 40, Coor, &dw);
}
void Manipulate_Screen::Release()
{
	//���� �� ȭ�� ����
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

