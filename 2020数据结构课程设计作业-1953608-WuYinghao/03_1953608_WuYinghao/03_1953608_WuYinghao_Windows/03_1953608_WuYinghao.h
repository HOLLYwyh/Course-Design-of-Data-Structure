#pragma once
#ifndef _03_1953608_WUYINGHAO_H_
#define _03_1953608_WUYINGHAO_H_

/*
* 设计一个21*21的迷宫
* '#'代表墙壁（不能通过），'*'代表可以通过的路径
* 本迷宫最终的通路唯一，所以采用DFS而非BFS
* 将最终的结果存放在栈中
*/

#include<iostream>
#include<graphics.h>

using namespace std;
//迷宫总边长
const int maze_size = 21;
//围墙（方块）边长
const int block_size = 25;
//初始位置
const int left_side = 75;
const int right_side = 100;
const int top_side = 10;
const int bottom_side = 35;

const int init_left = 75;
const int init_top = 10;
const int dir_x[4] = { 0,0,1,-1 };
const int dir_y[4] = { 1,-1,0,0 };


template<class T>
class Stack;

template<class T>
class Maze
{
private:
	
	//建立迷宫
	T** maze;
	T** maze_map;
	Stack<int> _stack;   //用于存放最终的坐标
	//迷宫坐标
	int _left = left_side;
	int _top = top_side;
	int _right = right_side;
	int _bottom = bottom_side;
	//出口坐标
	int out_x = 20;
	int out_y = 19;


protected:
	void setMaze();
	bool isInRange(int & x,int & y);   //判断搜索坐标是否在界内
public:
	//入口坐标
	const int in_x=1;
	const int in_y = 0;

	Maze();
	~Maze();

	void printPath();          //打印最终的路径
	void runMaze(int x,int y);
	void printMaze();
};

template<class T>
bool Maze<T>::isInRange(int& x, int& y)
{
	if ((x >= 0) && (x < maze_size) && (y >= 0) && (y < maze_size)&&(maze[x][y]=='*')) //可以被访问
		return true;
	else
		return false;
}

template<class T>
void Maze<T>::runMaze(int x,int y)
{
	if (out_x == x && out_y == y) //找到出口
	{
		_stack.push(x, y);
		_stack.setFlag(true);
		return;
	}
	else
	{
		maze_map[x][y] = '1';   //这个点已经被找到过
		for (int i = 0; i < 4; i++)
		{
			if (_stack.getFlag())
				break;
			int next_x = x + dir_x[i];
			int next_y = y + dir_y[i];
			if (isInRange(next_x, next_y) && (maze_map[next_x][next_y]=='0'))//下一个点没有出界并且没有被访问过
			{
				runMaze(next_x, next_y);
				if (_stack.getFlag())              //已经找到出口
				{
					_stack.push(x, y);
					//cout << x << "  " << y << endl;
				}
			}
		}
	}
}

template<class T>
void Maze<T>::printPath()
{
	setcolor(BLACK);
	outtextxy(750, 10, _T("此迷宫为21*21的迷宫"));
	outtextxy(700, 30, _T("迷宫从上至下，从左至右坐标增大，左上为(0,0)"));
	outtextxy(700, 50, _T("路径坐标分成四列（从上到下排列）"));
	outtextxy(700,70,_T("每列坐标最左列上方为入口，最右列下方为出口"));

	int x = 0, y = 0, loc_x=0, loc_y =0, length = _stack.getLength();
	const int interval_x = 10;
	const int interval_y = 20;
	char words[20]="(00,00)";
	int locx = 700, locy = 90, tempx = 700;

	for (int i = 0; i < length; i++)
	{
		_stack.pop(x,y);
		loc_x = y * block_size + (block_size / 2) + init_left;   //画路径
		loc_y = x * block_size + (block_size / 2) + init_top;
		setfillcolor(RED);
		solidcircle(loc_x, loc_y, 5);
		words[1] = x / 10 + '0';
		words[2] = x % 10 + '0';
		words[4] = y / 10 + '0';
		words[5] = y % 10 + '0';
		//写出路径
		for (int i = 0; i<strlen(words); i++)
		{
			outtextxy(locx, locy, words[i]);
			locx += interval_x;
		}
		locy += interval_y;
		if (locy >= 680)
		{
			locy = 90;
			tempx+=80;
		}
		locx = tempx;
	}
}


template<class T>
Maze<T>::Maze()
{
	try 
	{
		maze = new T * [maze_size];             //建立迷宫
		for (int i = 0; i < maze_size; i++)
		{
			maze[i] = new T[maze_size];
		}

		maze_map = new T * [maze_size];         //建立地图
		for (int i = 0; i < maze_size; i++)
		{
			maze_map[i] = new T[maze_size];
		}

	}
	catch(const std::bad_alloc& ba)
	{
		cerr << "出错" << endl;
		cerr << "bad_alloc caught: " << ba.what() << endl;
		system("pause");
		exit(1);
	}
	//迷宫的初始化
	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			maze[i][j] = '*';
		}
	}
	//迷宫地图的初始化
	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			maze_map[i][j] = '0';
		}
	}
	//创建迷宫
	setMaze();
}

template<class T>
Maze<T>::~Maze()
{
	for (int i = 0; i < maze_size; i++)
	{
		delete[]maze[i];
	}
	delete[]maze;
	for (int i = 0; i < maze_size; i++)
	{
		delete[]maze_map[i];
	}
	delete[]maze_map;
}

template<class T>
void Maze<T>::setMaze()
{
	for (int i = 0; i < maze_size; i++)
	{
		maze[0][i] = '#';
	}
	for (int i = 0; i < maze_size; i++)
	{
		maze[maze_size - 1][i] = '#';
	}
	for (int i = 0; i < maze_size; i++)
	{
		maze[i][0] = '#';
	}
	for (int i = 0; i < maze_size; i++)
	{
		maze[i][maze_size - 1] = '#';
	}
	maze[1][0] = '*';    //入口
	maze[maze_size - 1][maze_size - 2] = '*';//出口

	maze[1][6] = maze[1][14] = maze[1][18] =
		maze[2][2] = maze[2][4] = maze[2][6] = maze[2][7] = maze[2][8] = maze[2][9] =
		maze[2][10] = maze[2][11] = maze[2][12] = maze[2][14] = maze[2][16] = maze[2][18] =
		maze[3][2] = maze[3][4] = maze[3][10] = maze[3][16] =
		maze[5][4] = maze[5][12] = maze[5][18] =
		maze[7][6] = maze[7][10] = maze[7][14] = maze[7][16] =
		maze[9][2] = maze[9][6] = maze[9][8] = maze[9][12] = maze[9][16] = maze[9][18] =
		maze[11][4] = maze[11][6] = maze[11][8] = maze[11][12] = maze[11][16] =
		maze[13][4] = maze[13][6] = maze[13][8] = maze[13][10] = maze[13][14] = maze[13][18] =
		maze[15][4] = maze[15][16] = maze[15][18] =
		maze[17][2] = maze[17][8] = maze[17][13] =
		maze[19][6] = maze[19][10] = '#';
	for (int i = 0; i < maze_size; i++)
	{
		maze[4][i] = '#';
		maze[6][i] = '#';
		maze[8][i] = '#';
		maze[10][i] = '#';
		maze[12][i] = '#';
		maze[14][i] = '#';
		maze[16][i] = '#';
		maze[18][i] = '#';
	}
	maze[4][3] = maze[4][11] = maze[4][19] =
		maze[6][1] = maze[6][7] = maze[6][13] = maze[6][15] = maze[6][17] = maze[6][19] =
		maze[8][1] = maze[8][5] = maze[8][7] = maze[8][11] = maze[8][15] = maze[8][17] =
		maze[10][3] = maze[10][7] = maze[10][9] = maze[10][13] = maze[10][17] = maze[10][19] =
		maze[12][1] = maze[12][5] = maze[12][7] = maze[12][11] = maze[12][15] = maze[12][19] =
		maze[14][3] = maze[14][5] = maze[14][7] = maze[14][9] = maze[14][17] = maze[14][19] =
		maze[16][1] = maze[16][7] = maze[16][17] =
		maze[18][1] = maze[18][3] = maze[18][7] = maze[18][9] = maze[18][14] = '*';

	setfillcolor(RED);
	solidcircle(left_side - block_size, bottom_side + block_size / 2, 10);		// 画填充圆(无边框)

}

template<class T>
void Maze<T>::printMaze()
{
	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			if (maze[i][j] == '#')
			{
				setfillcolor(LIGHTCYAN);
				fillrectangle(_left, _top, _right, _bottom);	// 画矩形
			}
			_left += block_size;
			_right += block_size;
		}
		_left = left_side;
		_right = right_side;
		_top += block_size;
		_bottom += block_size;
	}
}

template<class T>
class StackNode                  //栈的结点
{
private:
	T _x;
	T _y;
	StackNode<T>* _next;
public:
	StackNode();
	StackNode(T x, T y);
	~StackNode();
	friend class Stack<T>;
};

template<class T>
StackNode<T>::StackNode()
{
	_x = _y = 0;
	_next = NULL;
}

template<class T>
StackNode<T>::StackNode(T x, T y)
{
	_x = x, _y = y;
	_next = NULL;
}

template<class T>
StackNode<T>::~StackNode()
{

}

template<class T>
class Stack
{
private:
	StackNode<T>* _top;                 //栈顶指针
	bool _flag;                          //目标位置是否入栈
public:
	Stack();
	~Stack();
	void push(T x,T y);            //入栈操作
	void pop(T &x,T &y);                        //出栈操作
	void setFlag(bool flag);               
	bool getFlag()const;
	int getLength()const;              //返回栈的长度
};

template<class T>
Stack<T>::Stack()
{
	try
	{
		_flag = false;
		_top = new StackNode<T>;
		_top->_x = _top->_y = 0;
		_top->_next = NULL;
	}
	catch (bad_alloc& ba)
	{
		cerr << ba.what();
		exit(1);
	}
}

template<class T>
Stack<T>::~Stack()
{
	StackNode<T>* current = _top;
	StackNode<T>* temp;
	while (current != NULL)
	{
		temp = current;
		current = current->_next;
		delete temp;
	}

}

template<class T>
void Stack<T>::push(T x,T y)
{
	try
	{
		StackNode<T>* newNode = new StackNode<T>;
		newNode->_x = x;
		newNode->_y = y;
		newNode->_next = _top->_next;
		_top->_next = newNode;
	}
	catch (bad_alloc& ba)
	{
		cerr << ba.what();
		exit(1);
	}
}

template<class T>
void Stack<T>::pop(T& x,T &y)
{
	if (NULL == _top->_next)  //说明栈空
	{
		cerr << "栈为空，不能删除元素";
		return;
	}
	else
	{
		StackNode<T>* temp = _top->_next;
		_top->_next = temp->_next;
		  x = temp->_x;
		  y = temp->_y;
		delete temp;
	}
}

template<class T>
void Stack<T>::setFlag(bool flag)
{
	_flag = flag;
}

template<class T>
bool Stack<T>::getFlag()const
{
	return this->_flag;
}

template<class T>
int Stack<T>::getLength()const
{
	StackNode<T>* temp = _top->_next;
	int count = 0;
	while (temp != NULL)
	{
		count++;
		temp = temp->_next;
	}
	return count;
}

#endif // !_03_1953608_WUYINGHAO_H_) 