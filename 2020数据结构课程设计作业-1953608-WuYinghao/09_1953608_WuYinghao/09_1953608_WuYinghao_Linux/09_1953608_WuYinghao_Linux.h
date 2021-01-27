#pragma once
#ifndef _09_1953608_WUYINGHAO_H_
#define _09_1953608_WUYINGHAO_H_

#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>
#include <cstdio>
using namespace std;
void end()
{
	cout << "press a number to end the system" << endl;
	cin.get();
	cin.get();
}

template<class T, class E>
class Graph;
template<class T, class E>
class Queue;
template<class T, class E>
class Timetable;

//顶点类
template<class T, class E>
class Vertex
{
private:
	T _number;            //课程编号
	T _name;              //课程名称
	E _classHour;         //课时数
	E _semester;          //开课学期

	Vertex<T, E>* _vnext;    //指向下一个顶点
	Vertex<T, E>* _enext;    //指向下一个临接顶点
	int _inDegree;            //入度数
public:
	Vertex(T number = "", T name = "", E classHour = 0, E semester = 0);
	Vertex(Vertex<T, E>* vertex);              //复制构造函数
	~Vertex();

	friend class Graph<T, E>;
	friend class Queue<T, E>;
	friend class Timetable<T, E>;
};

template<class T, class E>
Vertex<T, E>::Vertex(T number, T name, E classHour, E semester)
	:_number(number), _name(name), _classHour(classHour), _semester(semester),
	_vnext(NULL), _enext(NULL), _inDegree(0)
{

}

template<class T, class E>
Vertex<T, E>::Vertex(Vertex<T, E>* vertex)
	:_number(vertex->_number), _name(vertex->_name), _classHour(vertex->_classHour),
	_semester(vertex->_semester), _vnext(NULL), _enext(NULL), _inDegree(vertex->_inDegree)
{

}

template<class T, class E>
Vertex<T, E>::~Vertex()
{

}

//图
template<class T, class E>
class Graph
{
private:
	Vertex<T, E>* _first;
protected:
	T deleteNode(Vertex<T, E>*& pre);            //删除pre的下一个_enext结点
	void adjustInDegree(T number);               //调整number的入度(--)
public:
	Graph();
	~Graph();
	void topologicalSort(Queue<T, E>& queue);      //拓扑排序,将最终的结果存在queue中
	bool insertVertex(T number, T name, E classHour, E semester);        //插入顶点
	bool insertEdge(T number1, T number2);              //通过课号来插入边
};

template<class T, class E>
Graph<T, E>::Graph()
{
	try
	{
		_first = new Vertex<T, E>;
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法创建图" << endl << ba.what() << endl;
		end();
		exit(1);
	}
}

template<class T, class E>
Graph<T, E>::~Graph()
{
	Vertex<T, E>* vCurrent = _first->_vnext;
	Vertex<T, E>* eCurrent;
	Vertex<T, E>* temp;
	while (vCurrent)
	{
		eCurrent = vCurrent->_enext;
		while (eCurrent)
		{
			temp = eCurrent;
			eCurrent = eCurrent->_enext;
			delete temp;
		}
		temp = vCurrent;
		vCurrent = vCurrent->_vnext;
		delete temp;
	}
	delete _first;
}

template<class T, class E>
bool Graph<T, E>::insertVertex(T number, T name, E classHour, E semester)
{
	Vertex<T, E>* current = _first;
	while (current->_vnext)
	{
		if (current->_vnext->_number == number)
		{
			return false;        //此结点已经存在,无法插入节点
		}
		else
		{
			current = current->_vnext;
		}
	}
	try
	{
		Vertex<T, E>* newNode = new Vertex<T, E>(number, name, classHour, semester);
		current->_vnext = newNode;
		return true;
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法创建图" << endl << ba.what() << endl;
		end();
		exit(1);
	}
}

template<class T, class E>
bool Graph<T, E>::insertEdge(T number1, T number2)
{
	Vertex<T, E>* firstNode = NULL, * secondNode = NULL, * current = _first->_vnext;
	int tag = 0;//记录找到的结点的个数
	while (current)//寻找两个结点number1和number2
	{
		if (2 == tag)
		{
			break;
		}
		else if (current->_number == number1)
		{
			firstNode = current;
			current = current->_vnext;
			tag++;
		}
		else if (current->_number == number2)
		{
			secondNode = current;
			current = current->_vnext;
			tag++;
		}
		else
		{
			current = current->_vnext;
		}
	}
	if ((!firstNode) || (!secondNode))  //没有找到
	{
		return false;
	}
	else
	{
		current = firstNode;
		while (current->_enext)
		{
			if (current->_enext->_number == number2)  //<number1,number2>已经存在
			{
				return false;
			}
			else
			{
				current = current->_enext;
			}
		}
		//没有找到<number1,number2>这一条边
		try
		{
			Vertex<T, E>* newNode = new Vertex<T, E>(number2);
			current->_enext = newNode;
			secondNode->_inDegree++;
			return true;
		}
		catch (bad_alloc& ba)
		{
			cerr << "无法创建图" << endl << ba.what() << endl;
		}
	}

}

template <class T, class E>
T Graph<T, E>::deleteNode(Vertex<T, E>*& pre)  //删除pre的下一个_enext结点
{
	if (!pre->_enext)  //下一个结点为空
	{
		return " ";
	}
	else
	{
		Vertex<T, E>* temp = pre->_enext;
		pre->_enext = temp->_enext;
		T number = temp->_number;
		delete temp;
		return number;
	}
}

template<class T, class E>
void Graph<T, E>::adjustInDegree(T number)
{
	Vertex<T, E>* current = _first->_vnext;
	while (current)
	{
		if (current->_number == number)
		{
			current->_inDegree--;
			return;
		}
		else
		{
			current = current->_vnext;
		}
	}
}

template<class T, class E>
void Graph<T, E>::topologicalSort(Queue<T, E>& queue)       //拓扑排序
{
	try
	{
		queue.makeEmpty();//清空队列
		Vertex<T, E>* vCurrent = _first;
		Vertex<T, E>* eCurrent = vCurrent;
		Vertex<T, E>* tempVertex = new Vertex<T, E>;                  //用于暂存入度为0的结点
		E semester = 0;
		while (_first->_vnext)
		{
			if (!vCurrent->_vnext->_inDegree)           //下一个结点入度为0
			{
				Vertex<T, E>* temp = vCurrent->_vnext;        //temp入度为0的结点
				Vertex<T, E>* vtemp = tempVertex;
				while (vtemp->_vnext)
				{
					vtemp = vtemp->_vnext;
				}
				vtemp->_vnext = temp;
				vCurrent->_vnext = temp->_vnext;
				temp->_vnext = NULL;
			}
			else
			{
				vCurrent = vCurrent->_vnext;
			}
			if (!vCurrent->_vnext)//走到队尾
			{
				vCurrent = _first;  //回到队首
				semester++;
				while (tempVertex->_vnext)
				{
					eCurrent = tempVertex->_vnext;
					while (eCurrent->_enext)
					{
						adjustInDegree(deleteNode(eCurrent));
					}
					tempVertex->_vnext = eCurrent->_vnext;
					eCurrent->_semester = semester;
					queue.push(eCurrent);
					delete  eCurrent;
				}
			}
		}
		delete tempVertex;
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法进行拓扑排序" << endl << ba.what() << endl;
	}
}

//队列
template<class T, class E>
class Queue
{
private:
	Vertex<T, E>* _first;
	Vertex<T, E>* _last;
	//队列使用顶点Vertex<T,E>的_vnext指向下一个队列结点
public:
	Queue();
	~Queue();
	void makeEmpty();
	void push(Vertex<T, E>* vertex);
	bool pop(Vertex<T, E>*& vertex);

	//用于测试，输出所有的队列结点
	void printNode();
};

template<class T, class E>
Queue<T, E>::Queue()
{
	try
	{
		_first = new Vertex<T, E>;
		_last = new Vertex<T, E>;
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法创建拓扑序列" << endl << ba.what() << endl;
		end();
		exit(1);
	}
}

template<class T, class E>
Queue<T, E>::~Queue()
{
	makeEmpty();
	delete _first;
	delete _last;
}

template<class T, class E>
void Queue<T, E>::makeEmpty()
{
	Vertex<T, E>* current = _first->_vnext;
	Vertex<T, E>* temp;
	while (current)
	{
		temp = current;
		current = current->_vnext;
		delete temp;
	}
	_first->_vnext = _last->_vnext = NULL;
}

template<class T, class E>
void Queue<T, E>::push(Vertex<T, E>* vertex)
{
	try
	{
		Vertex<T, E>* newNode = new Vertex<T, E>(vertex);  //新建拓扑序列结点
		if (!_first->_vnext)//队列为空
		{
			_first->_vnext = _last->_vnext = newNode;
		}
		else  //队列不为空
		{
			_last->_vnext->_vnext = newNode;
			_last->_vnext = newNode;
		}
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法创建拓扑序列" << endl << ba.what() << endl;
		end();
		exit(1);
	}
}

template<class T, class E>
bool Queue<T, E>::pop(Vertex<T, E>*& vertex)
{
	if (!_first->_vnext)  //队列为空
	{
		return false;
	}
	else
	{
		Vertex<T, E>* current = _first->_vnext;
		_first->_vnext = current->_vnext;
		vertex->_classHour = current->_classHour;
		vertex->_name = current->_name;
		vertex->_number = current->_number;
		vertex->_semester = current->_semester;
		delete current;
		return true;
	}
}



//测试，用于输出所有的队列结点
template<class T, class E>
void Queue<T, E>::printNode()
{
	Vertex<T, E>* current = _first->_vnext;
	while (current)
	{
		cout << current->_number << " ";
		current = current->_vnext;
	}
	cout << endl;
}


//课程表类
template<class T, class E>
class Timetable
{
private:

	static const int _halfDay = 2;
	static const int _semesterNumber = 8;         //学期个数
	static const int _workdays = 5;              //工作日个数
	static const int _x = 11;
	static const int _y = 6;                    //画一个11*6的数组
	Vertex<T, E>** _semesters;                 	//工作日链表数组
	T** _schedule;                               //每一天共用一个课程表

	Vertex<T, E>** _threeClasses;                //三节的大课
	Vertex<T, E>** _twoClasses;                  //两节的小课

protected:
	void initSchedule();
	//安排并输出课程到文件
	void outputToWindow(E semester);
	void outputToFile(E semester);
	void cleanClasses();
	void adjustClasses();
	bool arrangeClass(Vertex<T, E>*& vertex, E num);                            //插入两节课
	bool isFull()const;                        //判断某一天的课表是否被排满

public:
	Timetable();
	~Timetable();
	void insertClasses(Queue<T, E>& queue);								//插入拓扑序列对应的课表
	void insertClass(T number, T name, E classHour, E semester);       //插入已经安排好的课表
	void arrangeCourses();

};

template<class T, class E>
void Timetable<T, E>::initSchedule()
{
	//数组的初始化
	for (int i = 0; i < _x; i++)
	{
		for (int j = 0; j < _y; j++)
		{
			_schedule[i][j] = " ";
		}
	}
	//星期的初始化
	_schedule[0][1] = "星期一";
	_schedule[0][2] = "星期二";
	_schedule[0][3] = "星期三";
	_schedule[0][4] = "星期四";
	_schedule[0][5] = "星期五";
	//课程的初始化
	_schedule[1][0] = "第一节";
	_schedule[2][0] = "第二节";
	_schedule[3][0] = "第三节";
	_schedule[4][0] = "第四节";
	_schedule[5][0] = "第五节";
	_schedule[6][0] = "第六节";
	_schedule[7][0] = "第七节";
	_schedule[8][0] = "第八节";
	_schedule[9][0] = "第九节";
	_schedule[10][0] = "第十节";
}

template<class T, class E>
Timetable<T, E>::Timetable()
{
	try
	{
		//new 相应的成员
		_semesters = new Vertex<T, E> *[_semesterNumber];
		for (int i = 0; i < _semesterNumber; i++)
		{
			_semesters[i] = new Vertex<T, E>;
		}

		_schedule = new T * [_x];
		for (int i = 0; i < _x; i++)
		{
			_schedule[i] = new T[_y];
		}
		initSchedule();

		_threeClasses = new Vertex<T, E> *[_halfDay];
		for (int i = 0; i < _halfDay; i++)
		{
			_threeClasses[i] = new Vertex<T, E>[_workdays];
		}

		_twoClasses = new Vertex<T, E> *[_halfDay];
		for (int i = 0; i < _halfDay; i++)
		{
			_twoClasses[i] = new Vertex<T, E>[_workdays];
		}
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法创建课程表" << endl << ba.what() << endl;
		end();
		exit(1);
	}
}

template<class T, class E>
Timetable<T, E>::~Timetable()
{
	Vertex<T, E>* current;
	Vertex<T, E>* temp;
	for (int i = 0; i < _x; i++)
	{
		delete[]_schedule[i];
	}
	delete[]_schedule;
	for (int j = 0; j < _semesterNumber; j++)
	{
		current = _semesters[j]->_vnext;
		while (current)
		{
			temp = current;
			current = current->_vnext;
			delete temp;
		}
		delete _semesters[j];
	}
	delete[]_semesters;

	for (int i = 0; i < _halfDay; i++)
	{
		delete[]_threeClasses[i];
	}
	delete[]_threeClasses;

	for (int i = 0; i < _halfDay; i++)
	{
		delete[]_twoClasses[i];
	}
	delete[]_twoClasses;
}

template<class T, class E>
bool Timetable<T, E>::isFull()const
{
	for (int i = 0; i < _halfDay; i++)
	{
		for (int j = 0; j < _workdays; j++)
		{
			if (("" == _twoClasses[i][j]._number) || ("" == _threeClasses[i][j]._number))
			{
				return false;
			}
		}
	}
	return true;
}

template<class T, class E>
bool Timetable<T, E>::arrangeClass(Vertex<T, E>*& vertex, E number)                            //插入两节课
{
	if (isFull())
	{
		return false;
	}
	int num = 0, day = 0, i;
	Vertex<T, E>** temp, ** anotherTemp;
	bool tag = false;
	if (2 == number)
	{
		temp = _twoClasses;
		anotherTemp = _threeClasses;
	}
	else if (3 == number)
	{
		temp = _threeClasses;
		anotherTemp = _twoClasses;
	}
	else
	{
		return false;
	}
	while (day != _workdays)
	{
		if (0 == num)//边界测试
		{
			for (i = 0; i < _halfDay; i++)
			{
				//不能和相邻两天重复
				if (("" == temp[i][num]._number) && (temp[0][num + 1]._number != vertex->_number) && (temp[1][num + 1]._number != vertex->_number)
					&& (anotherTemp[0][num + 1]._number != vertex->_number) && (anotherTemp[1][num + 1]._number != vertex->_number))
				{
					//不能和当天的课程重复
					if ((temp[1 - i][num]._number != vertex->_number) && (anotherTemp[0][num]._number != vertex->_number) && (anotherTemp[1][num]._number != vertex->_number))
					{
						temp[i][num]._number = vertex->_number;
						temp[i][num]._name = vertex->_name;
						day = _workdays - 1;
						tag = true;
						break;
					}
				}
			}
			num = (num + 2) % 5;
			day++;
		}
		else if (4 == num)
		{
			for (i = 0; i < _halfDay; i++)
			{
				if (("" == temp[i][num]._number) && (temp[0][num - 1]._number != vertex->_number) && (temp[1][num - 1]._number != vertex->_number)
					&& (anotherTemp[0][num - 1]._number != vertex->_number) && (anotherTemp[1][num - 1]._number != vertex->_number))
				{
					if ((temp[1 - i][num]._number != vertex->_number) && (anotherTemp[0][num]._number != vertex->_number) && (anotherTemp[1][num]._number != vertex->_number))
					{
						temp[i][num]._number = vertex->_number;
						temp[i][num]._name = vertex->_name;
						day = _workdays - 1;
						tag = true;
						break;
					}
				}
			}
			num = (num + 2) % 5;
			day++;
		}
		else
		{
			for (i = 0; i < _halfDay; i++)
			{
				if (("" == temp[i][num]._number) && (temp[0][num + 1]._number != vertex->_number) && (temp[1][num + 1]._number != vertex->_number)
					&& (temp[0][num - 1]._number != vertex->_number) && (temp[1][num - 1]._number != vertex->_number)
					&& (anotherTemp[0][num - 1]._number != vertex->_number) && (anotherTemp[1][num - 1]._number != vertex->_number)
					&& (anotherTemp[0][num + 1]._number != vertex->_number) && (anotherTemp[1][num + 1]._number != vertex->_number))
				{
					if ((temp[1 - i][num]._number != vertex->_number) && (anotherTemp[0][num]._number != vertex->_number) && (anotherTemp[1][num]._number != vertex->_number))
					{
						temp[i][num]._number = vertex->_number;
						temp[i][num]._name = vertex->_name;
						day = _workdays - 1;
						tag = true;
						break;
					}
				}
			}
			num = (num + 2) % 5;
			day++;
		}
	}

	return tag;
}

template<class T, class E>
void Timetable<T, E>::insertClasses(Queue<T, E>& queue)
{
	try
	{
		Vertex<T, E>* temp = new Vertex<T, E>;
		while (queue.pop(temp))
		{
			if ((temp->_semester <= 8) && (temp->_semester > 0))    //保证课程安排在第1到第八学期
			{
				Vertex<T, E>* current = _semesters[temp->_semester - 1];
				while (current->_vnext)
				{
					current = current->_vnext;
				}
				Vertex<T, E>* newNode = new Vertex<T, E>(temp);
				current->_vnext = newNode;
			}
		}
		delete temp;
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法生成课表" << endl << ba.what() << endl;
	}
}

template<class T, class E>
void Timetable<T, E>::insertClass(T number, T name, E classHour, E semester)  //插入学期数已定的课程
{

	Vertex<T, E>* current = _semesters[semester - 1];
	try
	{
		while (current->_vnext)
		{
			current = current->_vnext;
		}
		Vertex<T, E>* newNode = new Vertex<T, E>(number, name, classHour, semester);
		current->_vnext = newNode;
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法创建课程表" << endl << ba.what() << endl;
	}
}

template<class T, class E>
void Timetable<T, E>::cleanClasses()
{
	for (int i = 0; i < _halfDay; i++)             //清空临时数组
	{
		for (int j = 0; j < _workdays; j++)
		{
			_threeClasses[i][j]._name.clear();
			_twoClasses[i][j]._name.clear();

			_threeClasses[i][j]._number.clear();
			_twoClasses[i][j]._number.clear();
		}
	}

	for (int i = 1; i < _x; i++) //清空结果数组
	{
		for (int j = 1; j < _y; j++)
		{
			_schedule[i][j].clear();
		}
	}
}

template<class T, class E>
void Timetable<T, E>::adjustClasses()
{
	for (int i = 0; i < _halfDay; i++)
	{
		for (int j = 0; j < _workdays; j++)
		{
			if (_threeClasses[i][j]._number != "")
			{
				for (int k = 3; k <= 5; k++)
				{
					_schedule[k + i * 5][j + 1] = _threeClasses[i][j]._number;
				}
			}
			if (_twoClasses[i][j]._number != "")
			{
				for (int k = 1; k <= 2; k++)
				{
					_schedule[k + i * 5][j + 1] = _twoClasses[i][j]._number;
				}
			}
		}
	}
}

template<class T, class E>
void Timetable<T, E>::arrangeCourses()
{
	bool isFail = false;
	for (int i = 0; i < _semesterNumber; i++)  //按学期进行排课
	{
		Vertex<T, E>* current = _semesters[i];
		while (current->_vnext)
		{
			switch (current->_vnext->_classHour)
			{
			case 2:
			{
				if (!arrangeClass(current->_vnext, 2))
				{
					isFail = true;
				}
				break;
			}
			case 3:
			{
				if (!arrangeClass(current->_vnext, 3))
				{
					isFail = true;
				}
				break;
			}
			case 4:
			{
				if ((!arrangeClass(current->_vnext, 2)) || (!arrangeClass(current->_vnext, 2)))
				{
					isFail = true;
				}
				break;
			}
			case 5:
			{
				if ((!arrangeClass(current->_vnext, 3)) || (!arrangeClass(current->_vnext, 2)))
				{
					isFail = true;
				}
				break;
			}
			case 6:
			{
				if ((!arrangeClass(current->_vnext, 3)) || (!arrangeClass(current->_vnext, 3)))
				{
					if ((!arrangeClass(current->_vnext, 2)) || (!arrangeClass(current->_vnext, 2)) || (!arrangeClass(current->_vnext, 2)))
					{
						isFail = true;
					}
				}

				break;
			}
			default:           //出现问题,直接退出
			{
				break;
			}
			}
			if (!isFail)
			{
				current = current->_vnext;
			}
			else           //出现插入不成功情况
			{
				if (i == _semesterNumber - 1)
				{
					cerr << "无法在周末排课" << endl;
					return;
				}
				else
				{
					Vertex<T, E>* temp = current->_vnext;
					current->_vnext = temp->_vnext;

					temp->_vnext = _semesters[i + 1]->_vnext;
					_semesters[i + 1]->_vnext = temp;
					isFail = false;
				}
			}

		}
		adjustClasses();           //将结果放在数组中
		outputToFile(i);           //将结果输出到文件
		outputToWindow(i);         //将结果输出到屏幕
		cleanClasses();            //清空辅助数组的值
	}
}

template<class T, class E>
void Timetable<T, E>::outputToWindow(E semester)
{
	cout << "第" << (semester + 1) << "学期课表:" << endl;
	for (int i = 0; i < _x; i++)
	{
		for (int j = 0; j < _y; j++)
		{
			cout << _schedule[i][j] << "\t";
		}
		cout << endl;
		if ((0 == i) || (2 == i) || (5 == i) || (7 == i) || (10 == i))
		{
			cout << "-------------------------------------------------------------------" << endl;
		}
	}
	cout << endl;
}

template<class T, class E>
void Timetable<T, E>::outputToFile(E semester)
{
	fstream fout("outputFile.txt", ios_base::out | ios_base::app);        //把结果写入outputFile.txt,只追加
	fout.setf(ios_base::left);
	fout << "第" << (semester + 1) << "学期课表:" << endl;
	for (int i = 0; i < _x; i++)
	{
		for (int j = 0; j < _y; j++)
		{
			fout << _schedule[i][j] << "\t";
		}
		fout << endl;
		if ((0 == i) || (2 == i) || (5 == i) || (7 == i) || (10 == i))
		{
			fout << "-------------------------------------------------------------------" << endl;
		}
	}
	fout << endl;
	fout.flush();
	fout.close();
}


#endif