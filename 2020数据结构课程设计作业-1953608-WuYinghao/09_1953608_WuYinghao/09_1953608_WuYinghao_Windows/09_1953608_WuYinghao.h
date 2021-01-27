#pragma once
#ifndef _09_1953608_WUYINGHAO_H_
#define _09_1953608_WUYINGHAO_H_

#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>
using namespace std;

template<class T,class E>
class Graph;
template<class T,class E>
class Queue;
template<class T,class E>
class Timetable;

//������
template<class T,class E>
class Vertex
{
private:
	T _number;            //�γ̱��
	T _name;              //�γ�����
	E _classHour;         //��ʱ��
	E _semester;          //����ѧ��

	Vertex<T, E>* _vnext;    //ָ����һ������
	Vertex<T, E>* _enext;    //ָ����һ���ٽӶ���
	int _inDegree;            //�����
public:
	Vertex(T number = "", T name = "", E classHour = 0, E semester = 0);
	Vertex(Vertex<T, E>* vertex);              //���ƹ��캯��
	~Vertex();

	friend class Graph<T, E>;
	friend class Queue<T, E>;
	friend class Timetable<T, E>;
};

template<class T,class E>
Vertex<T, E>::Vertex(T number,T name,E classHour,E semester)
	:_number(number),_name(name),_classHour(classHour),_semester(semester),
	_vnext(NULL),_enext(NULL),_inDegree(0)
{

}

template<class T,class E>
Vertex<T, E>::Vertex(Vertex<T, E>* vertex)
	:_number(vertex->_number),_name(vertex->_name),_classHour(vertex->_classHour),
	_semester(vertex->_semester),_vnext(NULL),_enext(NULL),_inDegree(vertex->_inDegree)
{

}

template<class T,class E>
Vertex<T, E>::~Vertex()
{

}

//ͼ
template<class T,class E>
class Graph
{
private:
	Vertex<T, E>* _first; 
protected:
	T deleteNode(Vertex<T, E>*& pre);            //ɾ��pre����һ��_enext���
	void adjustInDegree(T number);               //����number�����(--)
public:
	Graph();
	~Graph();
	void topologicalSort(Queue<T,E>& queue);      //��������,�����յĽ������queue��
	bool insertVertex(T number,T name,E classHour,E semester);        //���붥��
	bool insertEdge(T number1, T number2);              //ͨ���κ��������
};

template<class T,class E>
Graph<T, E>::Graph()
{
	try
	{
		_first = new Vertex<T, E>;
	}
	catch (bad_alloc& ba)               
	{
		cerr << "�޷�����ͼ" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}
}
	
template<class T, class E>
Graph<T, E>::~Graph()
{
	Vertex<T, E>* vCurrent=_first->_vnext;
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

template<class T,class E>
bool Graph<T, E>::insertVertex(T number, T name, E classHour, E semester)
{
	Vertex<T, E>* current = _first;
	while (current->_vnext)
	{
		if (current->_vnext->_number == number)
		{
			return false;        //�˽���Ѿ�����,�޷�����ڵ�
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
		cerr << "�޷�����ͼ" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}
}

template<class T,class E>
bool Graph<T, E>::insertEdge(T number1, T number2)
{
	Vertex<T, E>* firstNode=NULL, * secondNode=NULL, * current = _first->_vnext;
	int tag = 0;//��¼�ҵ��Ľ��ĸ���
	while (current)//Ѱ���������number1��number2
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
		else if (current->_number==number2)
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
	if ((!firstNode) || (!secondNode))  //û���ҵ�
	{
		return false;
	}
	else
	{
		current = firstNode;
		while (current->_enext)
		{
			if (current->_enext->_number == number2)  //<number1,number2>�Ѿ�����
			{
				return false;
			}
			else
			{
				current = current->_enext;
			}
		}
		//û���ҵ�<number1,number2>��һ����
		try
		{
			Vertex<T, E>* newNode = new Vertex<T, E>(number2);
			current->_enext = newNode;
			secondNode->_inDegree++;
			return true;
		}
		catch (bad_alloc& ba)
		{
			cerr << "�޷�����ͼ" << endl << ba.what() << endl;
		}
	}

}

template <class T,class E>
T Graph<T, E>::deleteNode(Vertex<T,E>*& pre)  //ɾ��pre����һ��_enext���
{
	if (!pre->_enext)  //��һ�����Ϊ��
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

template<class T,class E>
void Graph<T, E>::adjustInDegree(T number)
{
	Vertex<T, E>* current = _first->_vnext;
	while (current)
	{
		if (current->_number==number)
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

template<class T,class E>
void Graph<T, E>::topologicalSort(Queue<T, E>& queue)       //��������
{
	try
	{
		queue.makeEmpty();//��ն���
		Vertex<T, E>* vCurrent = _first;
		Vertex<T, E>* eCurrent = vCurrent;
		Vertex<T, E>* tempVertex = new Vertex<T, E>;                  //�����ݴ����Ϊ0�Ľ��
		E semester = 0;
		while (_first->_vnext)
		{
			if (!vCurrent->_vnext->_inDegree)           //��һ��������Ϊ0
			{
				Vertex<T, E>* temp = vCurrent->_vnext;        //temp���Ϊ0�Ľ��
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
			if (!vCurrent->_vnext)//�ߵ���β
			{
				vCurrent = _first;  //�ص�����
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
		cerr << "�޷�������������" << endl << ba.what() << endl;
	}
}

//����
template<class T,class E>
class Queue
{
private:
	Vertex<T, E>* _first;
	Vertex<T, E>* _last;
	//����ʹ�ö���Vertex<T,E>��_vnextָ����һ�����н��
public:
	Queue();
	~Queue();
	void makeEmpty();
	void push(Vertex<T,E>* vertex);   
	bool pop(Vertex<T, E>*& vertex);

	
	void printNode();
};

template<class T,class E>
Queue<T, E>::Queue()
{
	try
	{
		_first = new Vertex<T, E>;
		_last = new Vertex<T, E>;
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷�������������" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}
}

template<class T,class E>
Queue<T, E>::~Queue()
{
	makeEmpty();
	delete _first;
	delete _last;
}

template<class T,class E>
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

template<class T,class E>
void Queue<T, E>::push(Vertex<T, E>* vertex)
{
	try
	{
		Vertex<T, E>* newNode = new Vertex<T, E>(vertex);  //�½��������н��
		if (!_first->_vnext)//����Ϊ��
		{
			_first->_vnext = _last->_vnext = newNode;
		}
		else  //���в�Ϊ��
		{
			_last->_vnext->_vnext = newNode;
			_last->_vnext = newNode;
		}
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷�������������" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}
}

template<class T,class E>
bool Queue<T, E>::pop(Vertex<T, E>*& vertex)
{
	if (!_first->_vnext)  //����Ϊ��
	{
		return false;
	}
	else
	{
		Vertex<T, E>* current = _first->_vnext;
		_first->_vnext = current->_vnext;
		vertex->_classHour = current->_classHour;
		vertex->_name = current->_name;
		vertex->_number =current->_number;
		vertex->_semester = current->_semester;
		delete current;
		return true;
	}
}



//���ԣ�����������еĶ��н��
template<class T,class E>
void Queue<T, E>::printNode()
{
	Vertex<T, E>* current=_first->_vnext;
	while (current)
	{
		cout << current->_number << " ";
		current = current->_vnext;
	}
	cout << endl;
}


//�γ̱���
template<class T,class E>
class Timetable
{
private:

	static const int _halfDay = 2;
	static const int _semesterNumber= 8;         //ѧ�ڸ���
	static const int _workdays = 5;              //�����ո���
	static const int _x = 11;
	static const int _y = 6;                    //��һ��11*6������
	Vertex<T, E>** _semesters;                 	//��������������
	T** _schedule;                               //ÿһ�칲��һ���γ̱�

	Vertex<T, E>** _threeClasses;                //���ڵĴ��
	Vertex<T, E>** _twoClasses;                  //���ڵ�С��

protected:
	void initSchedule();
	//���Ų�����γ̵��ļ�
	void outputToWindow(E semester);
	void outputToFile(E semester);
	void cleanClasses();
	void adjustClasses();
	bool arrangeClass(Vertex<T,E>*& vertex,E num);                            //�������ڿ�
	bool isFull()const;                        //�ж�ĳһ��Ŀα��Ƿ�����

public:
	Timetable();
	~Timetable();
	void insertClasses(Queue<T, E>& queue);								//�����������ж�Ӧ�Ŀα�
	void insertClass(T number, T name, E classHour, E semester);       //�����Ѿ����źõĿα�
	void arrangeCourses();    

};

template<class T,class E>
void Timetable<T, E>::initSchedule()
{
	//����ĳ�ʼ��
	for (int i = 0; i < _x; i++)
	{
		for (int j = 0; j < _y; j++)
		{
			_schedule[i][j] = " ";
		}
	}
	//���ڵĳ�ʼ��
	_schedule[0][1] = "����һ";
	_schedule[0][2] = "���ڶ�";
	_schedule[0][3] = "������";
	_schedule[0][4] = "������";
	_schedule[0][5] = "������";
//�γ̵ĳ�ʼ��
_schedule[1][0] = "��һ��";
_schedule[2][0] = "�ڶ���";
_schedule[3][0] = "������";
_schedule[4][0] = "���Ľ�";
_schedule[5][0] = "�����";
_schedule[6][0] = "������";
_schedule[7][0] = "���߽�";
_schedule[8][0] = "�ڰ˽�";
_schedule[9][0] = "�ھŽ�";
_schedule[10][0] = "��ʮ��";
}

template<class T, class E>
Timetable<T, E>::Timetable()
{
	try
	{
		//new ��Ӧ�ĳ�Ա
		_semesters = new Vertex<T, E> * [_semesterNumber];
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

		_threeClasses = new Vertex<T, E> * [_halfDay];
		for (int i = 0; i < _halfDay; i++)
		{
			_threeClasses[i] = new Vertex<T, E>[_workdays];
		}

		_twoClasses = new Vertex<T, E> * [_halfDay];
		for (int i = 0; i < _halfDay; i++)
		{
			_twoClasses[i] = new Vertex<T, E>[_workdays];
		}
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷������γ̱�" << endl << ba.what() << endl;
		system("pause");
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
			if (("" == _twoClasses[i][j]._number)||("" == _threeClasses[i][j]._number))
			{
				return false;
			}
		}
	}
	return true;
}

template<class T, class E>
bool Timetable<T, E>::arrangeClass(Vertex<T, E>*& vertex, E number)                            //�������ڿ�
{
	if (isFull())
	{
		return false;
	}
	int num = 0, day = 0, i;
	Vertex<T, E>** temp,**anotherTemp;
	bool tag = false;
	if(2==number)
	{
		temp = _twoClasses;
		anotherTemp = _threeClasses;
	}
	else if (3== number)
	{
		temp = _threeClasses;
		anotherTemp = _twoClasses;
	}
	else
	{
		return false;
	}
	while (day!=_workdays)
	{
		if (0 == num)//�߽����
		{
			for (i = 0; i < _halfDay; i++)
			{
				//���ܺ����������ظ�
				if ((""==temp[i][num]._number) && (temp[0][num+1]._number!=vertex->_number)&&(temp[1][num + 1]._number != vertex->_number)
					&&(anotherTemp[0][num+1]._number != vertex->_number)&&(anotherTemp[1][num+1]._number != vertex->_number))
				{
					//���ܺ͵���Ŀγ��ظ�
					if ((temp[1-i][num]._number != vertex->_number)&&(anotherTemp[0][num]._number!=vertex->_number)&&(anotherTemp[1][num]._number != vertex->_number))
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
				if (("" == temp[i][num]._number) && (temp[0][num -1]._number != vertex->_number) && (temp[1][num-1]._number != vertex->_number)
					&& (anotherTemp[0][num - 1]._number != vertex->_number) && (anotherTemp[1][num -1]._number != vertex->_number))
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
					&&(temp[0][num-1]._number != vertex->_number)&&(temp[1][num-1]._number != vertex->_number)
					&& (anotherTemp[0][num - 1]._number != vertex->_number) && (anotherTemp[1][num - 1]._number != vertex->_number)
					&& (anotherTemp[0][num +1]._number != vertex->_number) && (anotherTemp[1][num +1]._number != vertex->_number))
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

template<class T,class E>
void Timetable<T, E>::insertClasses(Queue<T, E>& queue)
{
	try
	{
		Vertex<T, E>* temp = new Vertex<T, E>;
		while (queue.pop(temp))
		{
			if ((temp->_semester <= 8) && (temp->_semester > 0))    //��֤�γ̰����ڵ�1���ڰ�ѧ��
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
		cerr << "�޷����ɿα�" << endl << ba.what() << endl;
	}
}

template<class T,class E>
void Timetable<T,E>::insertClass(T number, T name, E classHour, E semester)  //����ѧ�����Ѷ��Ŀγ�
{

	Vertex<T, E>* current=_semesters[semester-1];
	try
	{
		while (current->_vnext)
		{
			current = current->_vnext;
		}
		Vertex<T, E>* newNode = new Vertex<T,E>(number, name, classHour, semester);
		current->_vnext = newNode;
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷������γ̱�" << endl << ba.what() << endl;
	}
}

template<class T,class E>
void Timetable<T, E>::cleanClasses()
{
	for (int i = 0; i < _halfDay; i++)             //�����ʱ����
	{
		for (int j = 0; j < _workdays; j++)
		{
			/*_threeClasses[i][j]._semester = 0;
			_twoClasses[i][j]._semester = 0;*/

			_threeClasses[i][j]._name.clear();
			_twoClasses[i][j]._name.clear();

			_threeClasses[i][j]._number.clear();
			_twoClasses[i][j]._number.clear();
		}
	}

	for (int i = 1; i < _x; i++) //��ս������
	{
		for (int j = 1; j < _y; j++)
		{
			_schedule[i][j].clear();
		}
	}
}

template<class T,class E>
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

template<class T,class E>
void Timetable<T,E>::arrangeCourses()
{
	bool isFail = false;
	for (int i = 0; i < _semesterNumber; i++)  //��ѧ�ڽ����ſ�
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
				if(!arrangeClass(current->_vnext, 3))
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
				if((!arrangeClass(current->_vnext, 3))||(!arrangeClass(current->_vnext, 2)))
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
			default:           //��������,ֱ���˳�
			{
				break;
			}
			}
			if (!isFail)
			{
				current = current->_vnext;
			}
			else           //���ֲ��벻�ɹ����
			{
				if (i == _semesterNumber - 1)
				{
					cerr << "�޷�����ĩ�ſ�" << endl;
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
		adjustClasses();           //���������������
		outputToFile(i);           //�����������ļ�
		outputToWindow(i);         //������������Ļ
		cleanClasses();            //��ո��������ֵ
	}
}

template<class T, class E>
void Timetable<T, E>::outputToWindow(E semester)
{
	cout << "��" << (semester + 1) << "ѧ�ڿα�:" << endl;
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
	fstream fout("outputFile.txt", ios_base::out | ios_base::app);        //�ѽ��д��outputFile.txt,ֻ׷��
	fout.setf(ios_base::left);
	fout << "��" << (semester + 1) << "ѧ�ڿα�:" << endl;
	for (int i = 0; i < _x; i++)
	{
		for (int j = 0; j < _y; j++)
		{
			fout << _schedule[i][j] << "\t";
		}
		fout << endl;
		if ((0==i)||(2 == i) || (5 == i) || (7 == i) || (10 == i))
		{
			fout << "-------------------------------------------------------------------" << endl;
		}
	}
	fout << endl;
	fout.close();
}


#endif