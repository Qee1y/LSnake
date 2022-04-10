#pragma once

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

	Snake() : head(nullptr), p(nullptr), dir(1) {}
	~Snake() {};

	void ConsoleTextFailed(const char * s);

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