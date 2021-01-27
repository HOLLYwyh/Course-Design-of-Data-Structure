#pragma once
/*
* ��Ŀ˵����ʹ�ö��е����ݽṹʵ�ֱ���
*����Ϊ�������зֱ����A���ں�B����
*/

#ifndef _05_1953608_WUYINGHAO_H_
#define _05_1953608_WUYINGHAO_H_

#include<iostream>


using namespace std;

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
	_data = 0;              //Ĭ��ֵ����Ϊ0
	_next = NULL;           //��һ��ָ������Ϊ��
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
	QueueNode<T>* _first;        //��ͷָ��
	QueueNode<T>* _last;         //��βָ��
public:
	Queue();
	~Queue();
	
	bool isEmpty()const;              //�ж϶����Ƿ�Ϊ��
	int  getLength()const;            //��ö��еĳ���
	void inQueue(T data);             //��β���
	void outQueue(T& data);                  //��ͷ����
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
		cerr<<ba.what();
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
		
		if (NULL == _first->_next)           //����Ϊ��
		{
			_first->_next = newNode;
			_last->_next = newNode;
			newNode->_next = NULL;
		}
		else                                 //������������һ��Ԫ��
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
void Queue<T>::outQueue(T & data)
{
	if (NULL == _first->_next)                //����Ϊ��
	{
		cerr << "����Ϊ�գ�����ִ��ɾ������";    
		data = -1;                             //���Ϊ-1,ֱ���˳�  
		return;
	}
	else if(NULL==_first->_next->_next)         //�����н���һ��Ԫ��
	{
		QueueNode<T>* temp = _first->_next;    //ָ����е�Ԫ��
		_first->_next = NULL;
		_last->_next = NULL;
		data = temp->_data;
		delete temp;
	}
	else                                      //Ԫ�صĸ�������һ
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

