#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Snake.h"

void Snake::ConsoleTextFailed(const char* s)
{
	gotoxy(0, 0);
	color(4);
	std::cout << s << "\n";
}

void Snake::snakeWelcometo()
{
	int choice;
	int x, y;
	int count1 = 0, count2 = 0;

	gotoxy(37, 15);
	color(11);
	std::cout << "贪   吃   蛇   大   作   战";

	for (x = 20; x < 80; x++)
	{
		count2++;
		for (y = 17; y < 26; y++)
		{
			count1++;
			if (x == 20 || x == 79)
			{
				if (count1 % 2 == 0)
					color(9);
				else
					color(13);

				gotoxy(x, y);
				printf("|");
			}

			if (y == 17 || y == 25)
			{
				if (count2 % 2 == 0)
					color(9);
				else
					color(13);

				gotoxy(x, y);
				printf("-");
			}
		}
	}

	gotoxy(32, 19);
	color(13);
	printf("1:开始游戏");

	gotoxy(58, 19);
	printf("2:游戏说明");

	gotoxy(32, 23);
	printf("3:退出游戏");

	gotoxy(43, 26);
	printf("请选择[1 2 3]:[ ]\b\b");
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		system("cls");
		iniMap();
		iniSanke();
		createFood();
		controlKey();
		break;
	case 2:
		ConsoleTextFailed("功能未实现");
		break;
	case 3:
		exit(0);
	default:
		gotoxy(40, 28);
		color(12);
		ConsoleTextFailed("输入错误,请输入1~3的数!");
		gotoxy(43, 26);
		_getch();             //除了vs系列之外的编译器需要把这一行改成: getch();
		system("cls");
		snakeWelcometo();
		break;
	}
}

void Snake::gotoxy(int x, int y)
{
	COORD Pos = {(short)x, (short)y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut	, Pos);
}

void Snake::iniMap()
{
	color(9);
	for (int i = 0; i < 26; i++)
	{
		gotoxy(0, i);
		std::cout << "■";
		gotoxy(56, i);
		std::cout << "■";
	}

	for (int i = 0; i < 58; i += 2)
	{
		gotoxy(i, 0);
		std::cout << "■";
		gotoxy(i, 26);
		std::cout << "■";
	}

	
	color(7);
	for (int j = 1; j < 26; j += 2)
	{
		for (int i = 2; i < 56; i += 4)
		{
			gotoxy(i, j);
			printf("■");
			Sleep(2);       //增加点延时效果
		}
	}

	for (int i = 2; i < 56; i += 4)
	{
		for (int j = 2; j < 26; j += 2)
		{
			gotoxy(i, j);
			printf("■");
			Sleep(2);       //增加点延时效果
		}
	}

	for (int i = 2; i < 56; i += 2)
	{
		for (int j = 1; j < 26; j++)
		{
			gotoxy(i, j);
			printf("■");
		}
		Sleep(100);       //增加点延时效果
	}
	
	return;
}

void Snake::iniSanke()
{
	Node* tail = new Node[sizeof(Node)];
	tail->x = 24;
	tail->y = 5;
	tail->next = nullptr;
	
	for (int i = 0; i < 4; i++)
	{
		head = new Node[sizeof(Node)];
		head->next = tail;
		head->x = 24 + 2 * i;
		head->y = 5;
		tail = head;
	}

	while (tail != nullptr)
	{
		color(6);
		gotoxy(tail->x, tail->y);
		std::cout << "■";
		tail = tail->next;
	}
}

void Snake::createFood()
{
	Node* food_t = new Node[sizeof(Node)];

	food_t->x = 1;
	food_t->y = 0;
	food_t->next = nullptr;

	srand((unsigned)time(nullptr));
	while (food_t->x % 2 != 0 )
		food_t->x = rand() % 56 + 2;
	food_t->y = rand() % 25 + 1;

	p = head;
	while (p->next == nullptr)
	{
		if (p->x == food_t->x && p->y == food_t->y)
		{
			delete[] food_t;
			createFood();
		}
		p = p->next;
	}
	food = food_t;

	gotoxy(food_t->x, food_t->y);
	std::cout << "●";

	return;
}

void Snake::controlKey()
{
	dir = D;
	while (1)
	{
		if (GetAsyncKeyState(0x57) && dir != S)
			dir = W;
		else if (GetAsyncKeyState(0x53) && dir != W)
			dir = S;
		else if (GetAsyncKeyState(0x41) && dir != D)
			dir = A;
		else if (GetAsyncKeyState(0x44) && dir != A)
			dir = D;

		if (GetAsyncKeyState(0x20))
		{
			while (1)
			{
				Sleep(300);
				if (GetAsyncKeyState(0x20))
					break;
			}
		}
		Sleep(100);
		moveSanke();
	}
	return;
}

void Snake::moveSanke()
{
	Node* nexthead = new Node[sizeof(Node)];

	if (dir == W)
	{
		nexthead->x = head->x;
		nexthead->y = head->y - 1;
		nexthead->next = head;
		head = nexthead;

		p = head;
		if (nexthead->x == food->x && nexthead->y == food->y)
		{
			while (p != nullptr)
			{
				color(6);
				gotoxy(p->x, p->y);
				std::cout << "■";
				p = p->next;
			}
			createFood();
		}
		else
		{
			while (p->next->next != nullptr)
			{
				color(6);
				gotoxy(p->x, p->y);
				std::cout << "■";
				p = p->next;
			}

			gotoxy(p->x, p->y);
			color(7);
			std::cout << "■";
			delete p->next;
			p->next = nullptr;
		}
	}

	if (dir == S)
	{
		nexthead->x = head->x;
		nexthead->y = head->y + 1;
		nexthead->next = head;
		head = nexthead;

		p = head;
		if (nexthead->x == food->x && nexthead->y == food->y)
		{
			while (p != nullptr)
			{
				color(6);
				gotoxy(p->x, p->y);
				std::cout << "■";
				p = p->next;
			}
			createFood();
		}
		else
		{
			while (p->next->next != nullptr)
			{
				color(6);
				gotoxy(p->x, p->y);
				std::cout << "■";
				p = p->next;
			}

			//删除尾部填充
			gotoxy(p->x, p->y);
			color(7);
			std::cout << "■";
			delete p->next;
			p->next = nullptr;
		}
	}

	if (dir == A)
	{
		nexthead->x = head->x - 2;
		nexthead->y = head->y;
		nexthead->next = head;
		head = nexthead;

		p = head;

		if (nexthead->x == food->x && nexthead->y == food->y)
		{
			while (p != nullptr)
			{
				color(6);
				gotoxy(p->x, p->y);
				std::cout << "■";
				p = p->next;
			}
			createFood();
		}
		else
		{
			while (p->next->next != nullptr)
			{
				color(6);
				gotoxy(p->x, p->y);
				std::cout << "■";
				p = p->next;
			}

			gotoxy(p->x, p->y);
			color(7);
			std::cout << "■";
			delete p->next;
			p->next = nullptr;
		}
	}

	if (dir == D)
	{
		nexthead->x = head->x + 2;
		nexthead->y = head->y;
		nexthead->next = head;
		head = nexthead;

		p = head;

		if (nexthead->x == food->x && nexthead->y == food->y)
		{
			while (p != nullptr)
			{
				color(6);
				gotoxy(p->x, p->y);
				std::cout << "■";
				p = p->next;
			}
			createFood();
		}
		else
		{
			while (p->next->next != nullptr)
			{
				color(6);
				gotoxy(p->x, p->y);
				std::cout << "■";
				p = p->next;
			}

			gotoxy(p->x, p->y);
			color(7);
			std::cout << "■";
			delete p->next;
			p->next = nullptr;
		}
	}
	return;
}

void Snake::cantWall()
{

}

void Snake::color(int col)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, col);
}