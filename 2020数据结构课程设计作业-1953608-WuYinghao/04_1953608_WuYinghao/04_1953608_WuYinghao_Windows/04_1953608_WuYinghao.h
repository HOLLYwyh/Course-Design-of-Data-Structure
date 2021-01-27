#pragma once
#ifndef _04_1953608_WUYINGHAO_H_
#define _04_1953608_WUYINGHAO_H_

/*
*��Ŀ�ģ��������ʽ��⣬����һ����׺���ʽ���������
*����ջ�Ͷ��е����ݽṹ�Ƚ���׺���ʽת��Ϊ��׺���ʽ���ٽ�������
*/
#include<iostream>
#include<cmath>

using namespace std;

template<class T>
class Stack;

template<class T>
class QueueNode;

template<class T>
class Queue;

template<class T>
class StackNode             //ջ���
{
private:   
	T _data;                //��ŵ�����
	bool _isSign;           //�����ж���������ǲ���������
	StackNode<T>* _next;    //ջ����һ��Ԫ��
public:
	StackNode();
	StackNode(T data,bool _isSign=false);
	~StackNode();
	friend class Stack<T>;
	friend class QueueNode<T>;
};

template<class T>
StackNode<T>::StackNode()
	:_data(0),_next(NULL),_isSign(false)
{

}

template<class T>
StackNode<T>::StackNode(T data,bool isSign)
	:_data(data),_next(NULL),_isSign(isSign)
{

}

template<class T>
StackNode<T>::~StackNode()
{

}

template<class T>
class Stack                //ջ
{
private:
	StackNode<T>* _top;              //ջ��ָ��
public:
	Stack();
	~Stack();
	void push(const T data,bool isSign=false);
    bool pop(T& data);
	T getTopData()const { return (_top->_next) ? _top->_next->_data : '\0'; };              //��ȡջ��Ԫ�ص�ֵ
	void clear();
};

template<class T>
Stack<T>::Stack()
{
	try
	{
		_top = new StackNode<T>;
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷�����ջ" << endl << ba.what() << endl;
		exit(1);
		system("pause");
	}
}

template<class T>
Stack<T>::~Stack()
{
	StackNode<T>* current = _top->_next;
	StackNode<T>* temp;
	while (current)
	{
		temp = current;
		current = current->_next;
		delete temp;
	}
	delete _top;
}

template<class T>
void Stack<T>::push(const T data,bool isSign)
{
	try
	{
		StackNode<T>* newNode = new StackNode<T>(data,isSign);
		newNode->_next = _top->_next;
		_top->_next = newNode;
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷�����ջ���" << endl << ba.what() << endl;
	}
}

template<class T>
bool Stack<T>::pop(T& data)
{
	if (!_top->_next)    //ջ��
	{
		return false;
	}
	StackNode<T>* current = _top->_next;
	_top->_next = current->_next;
	data = current->_data;

	delete current;
	return true;
}

template<class T>
void Stack<T>::clear()
{
	StackNode<T>* current = _top->_next;
	StackNode<T>* temp;
	while (current)
	{
		temp = current;
		current = current->_next;
		delete temp;
	}
	_top->_next = NULL;
}

template<class T>
class QueueNode            //�ӽ��
{
private:
	T _data;
	bool _isSign;
	QueueNode<T>* _next;
	int _bit_num;         //ֻ���ڼ�¼С���������ֵ�λ��
	int _int_num;         //���ڼ�¼�������ֵ�λ��
public:
	QueueNode();
	QueueNode(T data,bool isSign=false,int bit_num=0,int int_num=1); //�����ֱ�Ϊ���ݡ��Ƿ�Ϊ�����š�С��λ��������λ��
	~QueueNode();

	bool isSign()const { return _isSign; };        //�ж��ǲ���������
	int getBitNum()const { return _bit_num; };     //����С���������λ��
	T getData()const { return _data; };            //�������ݵ�����
	int getIntNum()const { return _int_num; };

	void setData(T data) { _data = data; };
	void setBitNum(int num) { _bit_num = num; };
	void setSign(bool sign) { _isSign = sign; };
	void setIntNum(int num) { _int_num = num; };

	friend class Queue<T>;
	friend class StackNode<T>;
};

template<class T>
QueueNode<T>::QueueNode()
	:_data(0), _next(NULL), _isSign(false), _bit_num(0),_int_num(1)
{

}

template<class T>
QueueNode<T>::QueueNode(T data,bool isSign,int bit_num,int int_num)
	:_data(data),_next(NULL),_isSign(isSign),_bit_num(bit_num),_int_num(int_num)
{

}

template<class T>
QueueNode<T>::~QueueNode()
{

}

template<class T>
class Queue
{
private:
	QueueNode<T>* _top;          //��ͷָ��
	QueueNode<T>* _last;         //��βָ��
public:
	Queue();
	~Queue();
	void push(const T data,bool isSign=false,int bit_num=0,int int_num=1);
	bool pop(T &data);
	bool pop(QueueNode<T>& node);
	int getQueueLength()const;       //��ȡ��ǰ���еĳ���
	T getTopData()const { return (_top->_next) ? _top->_next->_data : ' '; };              //��ȡ����Ԫ�ص�ֵ
	bool isEmpty()const { return(_top->_next) ? false : true; };
	void clear();
};

template<class T>
Queue<T>::Queue()
{
	try
	{
		_top = new QueueNode<T>;
		_last = new QueueNode<T>;
		_top->_next = NULL;
		_last->_next = NULL;
	}
	catch(bad_alloc& ba)
	{
		cerr << "�޷���������" << endl << ba.what() << endl;
	}
}

template<class T>
Queue<T>::~Queue()
{
	QueueNode<T>* current = _top->_next;
	QueueNode<T>* temp;

	while (current)
	{
		temp = current;
		current = current->_next;
		delete temp;
	}

	delete _top;
	delete _last;
}

template<class T>
void Queue<T>::push(const T data,bool isSign,int bit_num,int int_num)
{
	try
	{
		QueueNode<T>* newNode = new QueueNode<T>(data,isSign,bit_num,int_num);
		//��β����
		if (!_top->_next)  //����Ϊ��
		{
			_top->_next = newNode;
			newNode->_next = NULL;
			_last->_next = newNode;   //�����һ�����
		}
		else
		{
			_last->_next->_next = newNode;
			newNode->_next = NULL;
			_last->_next = newNode;
		}

	}
	catch(bad_alloc &ba)
	{
		cout << "�޷��������н��" << endl << ba.what();
	}
}

template<class T>
bool Queue<T>::pop(T& data)
{
	if (!this->_top->_next)						 //�������Ϊ��
	{
		return false;
	}
	else
	{
		QueueNode<T>* temp = _top->_next;
		if (!temp->_next)						 //����ֻ��һ�����
		{
			_top->_next = _last->_next = NULL;
			data = temp->_data;
			delete temp;
			return true;
		}
		else                                      //���в�ֻ��һ�����                  
		{
			_top->_next = temp->_next;
			data = temp->_data;
			delete temp;
			return true;
		}
	}
}

template<class T>
bool Queue<T>::pop(QueueNode<T>& node)
{
	if (!this->_top->_next)						 //�������Ϊ��
	{
		return false;
	}
	else
	{
		QueueNode<T>* temp = _top->_next;
		if (!temp->_next)						 //����ֻ��һ�����
		{
			_top->_next = _last->_next = NULL;
			node.setBitNum(temp->_bit_num);
			node.setData(temp->_data);
			node.setSign(temp->_isSign);
			node.setIntNum(temp->_int_num);
			delete temp;
			return true;
		}
		else                                      //���в�ֻ��һ�����                  
		{
			_top->_next = temp->_next;
			node.setBitNum(temp->_bit_num);
			node.setData(temp->_data);
			node.setSign(temp->_isSign);
			node.setIntNum(temp->_int_num);
			delete temp;
			return true;
		}
	}
}

template<class T>
int Queue<T>::getQueueLength()const
{
	int num = 0;
	QueueNode<T>* current = _top->_next;
	while (current)
	{
		num++;
		current = current->_next;
	}
	return num;
}

template<class T>
void Queue<T>::clear()
{
	QueueNode<T>* current = _top->_next;
	QueueNode<T>* temp;
	while (current)
	{
		temp = current;
		current = current->_next;
		delete temp;
	}
	_top->_next = NULL;
	_last->_next = NULL;
}

#endif // !_04_1953608_WUYINGHAO_H_
