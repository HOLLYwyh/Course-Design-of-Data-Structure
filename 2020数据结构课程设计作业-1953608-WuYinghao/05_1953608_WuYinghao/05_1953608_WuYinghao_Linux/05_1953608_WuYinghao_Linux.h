#pragma once
/*
* 项目说明：使用队列的数据结构实现本题
*将分为两个队列分别代表A窗口和B窗口
*/

#ifndef _05_1953608_WUYINGHAO_H_
#define _05_1953608_WUYINGHAO_H_

#include<iostream>


using namespace std;

void end()
{
	cout << "press a number to end the system" << endl;
	cin.get();
	cin.get();
}

template<class T>
class Queue;

template<class T>
class QueueNode
{
private:
	T _data;
	QueueNode<T>* _next;
public:
	QueueNode();
	QueueNode(T data);
	~QueueNode();
	friend class Queue <T>;
};

template<class T>
QueueNode<T>::QueueNode()
{
	_data = 0;              //默认值设置为0
	_next = NULL;           //下一个指针设置为空
}

template<class T>
QueueNode<T>::QueueNode(T data)
{
	_data = data;
	_next = NULL;
}

template<class T>
QueueNode<T>::~QueueNode()
{

}

template<class T>
class Queue
{
private:
	QueueNode<T>* _first;        //队头指针
	QueueNode<T>* _last;         //队尾指针
public:
	Queue();
	~Queue();

	bool isEmpty()const;              //判断队列是否为空
	int  getLength()const;            //获得队列的长度
	void inQueue(T data);             //队尾入队
	void outQueue(T& data);                  //队头出队
};

template<class T>
Queue<T>::Queue()
{
	try
	{
		_first = new QueueNode<T>;
		_last = new QueueNode <T>;
	}
	catch (bad_alloc& ba)
	{
		cerr << ba.what();
		exit(1);
	}
}

template<class T>
Queue<T>::~Queue()
{
	if (_first != NULL)
	{
		QueueNode<T>* current = _first->_next;
		QueueNode<T>* temp;
		while (current != NULL)
		{
			temp = current;
			current = current->_next;
			delete temp;
		}
		delete _first;
		delete _last;
	}
}

template<class T>
void Queue<T>::inQueue(T data)
{
	try
	{
		QueueNode<T>* newNode = new QueueNode<T>(data);

		if (NULL == _first->_next)           //队列为空
		{
			_first->_next = newNode;
			_last->_next = newNode;
			newNode->_next = NULL;
		}
		else                                 //队列中至少有一个元素
		{
			_last->_next->_next = newNode;
			newNode->_next = NULL;
			_last->_next = newNode;
		}

	}
	catch (bad_alloc& ba)
	{
		cerr << ba.what();
	}
}

template<class T>
void Queue<T>::outQueue(T& data)
{
	if (NULL == _first->_next)                //队列为空
	{
		cerr << "队列为空，不能执行删除操作";
		data = -1;                             //序号为-1,直接退出  
		return;
	}
	else if (NULL == _first->_next->_next)         //队列中仅有一个元素
	{
		QueueNode<T>* temp = _first->_next;    //指向仅有的元素
		_first->_next = NULL;
		_last->_next = NULL;
		data = temp->_data;
		delete temp;
	}
	else                                      //元素的个数大于一
	{
		QueueNode<T>* temp = _first->_next;
		_first->_next = temp->_next;
		data = temp->_data;
		delete temp;
	}
}

template<class T>
bool Queue<T>::isEmpty() const
{
	if (NULL == _first->_next)
		return true;
	else
		return false;
}

template<class T>
int Queue<T>::getLength() const
{
	QueueNode<T>* current = _first->_next;
	int count = 0;
	while (current != NULL)
	{
		current = current->_next;
		count++;
	}
	return count;
}

#endif // !_05_1953608_WUYINGHAO_H_

