#include <Windows.h>
#include <stdio.h>
#include "Snake.h"

void HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}

void gameIni()
{
	Snake snake;
	snake.snakeWelcometo();
}

int main()
{
	system("mode con cols=100 lines=30");
	HideCursor();
	gameIni();
	return 0;
}