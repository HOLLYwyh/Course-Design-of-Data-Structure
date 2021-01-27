#pragma once
#ifndef _03_1953608_WUYINGHAO_H_
#define _03_1953608_WUYINGHAO_H_

/*
* ���һ��21*21���Թ�
* '#'����ǽ�ڣ�����ͨ������'*'�������ͨ����·��
* ���Թ����յ�ͨ·Ψһ�����Բ���DFS����BFS
* �����յĽ�������ջ��
*/

#include<iostream>
#include<graphics.h>

using namespace std;
//�Թ��ܱ߳�
const int maze_size = 21;
//Χǽ�����飩�߳�
const int block_size = 25;
//��ʼλ��
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
	
	//�����Թ�
	T** maze;
	T** maze_map;
	Stack<int> _stack;   //���ڴ�����յ�����
	//�Թ�����
	int _left = left_side;
	int _top = top_side;
	int _right = right_side;
	int _bottom = bottom_side;
	//��������
	int out_x = 20;
	int out_y = 19;


protected:
	void setMaze();
	bool isInRange(int & x,int & y);   //�ж����������Ƿ��ڽ���
public:
	//�������
	const int in_x=1;
	const int in_y = 0;

	Maze();
	~Maze();

	void printPath();          //��ӡ���յ�·��
	void runMaze(int x,int y);
	void printMaze();
};

template<class T>
bool Maze<T>::isInRange(int& x, int& y)
{
	if ((x >= 0) && (x < maze_size) && (y >= 0) && (y < maze_size)&&(maze[x][y]=='*')) //���Ա�����
		return true;
	else
		return false;
}

template<class T>
void Maze<T>::runMaze(int x,int y)
{
	if (out_x == x && out_y == y) //�ҵ�����
	{
		_stack.push(x, y);
		_stack.setFlag(true);
		return;
	}
	else
	{
		maze_map[x][y] = '1';   //������Ѿ����ҵ���
		for (int i = 0; i < 4; i++)
		{
			if (_stack.getFlag())
				break;
			int next_x = x + dir_x[i];
			int next_y = y + dir_y[i];
			if (isInRange(next_x, next_y) && (maze_map[next_x][next_y]=='0'))//��һ����û�г��粢��û�б����ʹ�
			{
				runMaze(next_x, next_y);
				if (_stack.getFlag())              //�Ѿ��ҵ�����
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
	outtextxy(750, 10, _T("���Թ�Ϊ21*21���Թ�"));
	outtextxy(700, 30, _T("�Թ��������£���������������������Ϊ(0,0)"));
	outtextxy(700, 50, _T("·������ֳ����У����ϵ������У�"));
	outtextxy(700,70,_T("ÿ�������������Ϸ�Ϊ��ڣ��������·�Ϊ����"));

	int x = 0, y = 0, loc_x=0, loc_y =0, length = _stack.getLength();
	const int interval_x = 10;
	const int interval_y = 20;
	char words[20]="(00,00)";
	int locx = 700, locy = 90, tempx = 700;

	for (int i = 0; i < length; i++)
	{
		_stack.pop(x,y);
		loc_x = y * block_size + (block_size / 2) + init_left;   //��·��
		loc_y = x * block_size + (block_size / 2) + init_top;
		setfillcolor(RED);
		solidcircle(loc_x, loc_y, 5);
		words[1] = x / 10 + '0';
		words[2] = x % 10 + '0';
		words[4] = y / 10 + '0';
		words[5] = y % 10 + '0';
		//д��·��
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
		maze = new T * [maze_size];             //�����Թ�
		for (int i = 0; i < maze_size; i++)
		{
			maze[i] = new T[maze_size];
		}

		maze_map = new T * [maze_size];         //������ͼ
		for (int i = 0; i < maze_size; i++)
		{
			maze_map[i] = new T[maze_size];
		}

	}
	catch(const std::bad_alloc& ba)
	{
		cerr << "����" << endl;
		cerr << "bad_alloc caught: " << ba.what() << endl;
		system("pause");
		exit(1);
	}
	//�Թ��ĳ�ʼ��
	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			maze[i][j] = '*';
		}
	}
	//�Թ���ͼ�ĳ�ʼ��
	for (int i = 0; i < maze_size; i++)
	{
		for (int j = 0; j < maze_size; j++)
		{
			maze_map[i][j] = '0';
		}
	}
	//�����Թ�
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
	maze[1][0] = '*';    //���
	maze[maze_size - 1][maze_size - 2] = '*';//����

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
	solidcircle(left_side - block_size, bottom_side + block_size / 2, 10);		// �����Բ(�ޱ߿�)

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
				fillrectangle(_left, _top, _right, _bottom);	// ������
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
class StackNode                  //ջ�Ľ��
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
	StackNode<T>* _top;                 //ջ��ָ��
	bool _flag;                          //Ŀ��λ���Ƿ���ջ
public:
	Stack();
	~Stack();
	void push(T x,T y);            //��ջ����
	void pop(T &x,T &y);                        //��ջ����
	void setFlag(bool flag);               
	bool getFlag()const;
	int getLength()const;              //����ջ�ĳ���
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
	if (NULL == _top->_next)  //˵��ջ��
	{
		cerr << "ջΪ�գ�����ɾ��Ԫ��";
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