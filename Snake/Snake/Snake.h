#pragma once

/*
	项目名称: 贪吃蛇
	版本 : v1.1
	作者 : LlTS
*/

class Snake
{
public:
	enum { W, S, A, D};
	struct Node
	{
		int x, y;   //坐标
		Node* next;  //下一个节点
	}; 
	Node* head, *p, *food;
	int dir;   //方位

	Snake() : head(nullptr), p(nullptr), dir(1), food(nullptr) {}
	~Snake() {};

	void ConsoleTextFailed(const char * s);

	void gameOver();
	void gameExplation();
	void snakeWelcometo();
	void gotoxy(int x, int y);
	void iniMap(); 
	void iniSanke();
	void createFood();
	void controlKey();
	void moveSanke();
	void cantWall();
	void color(int col);
};