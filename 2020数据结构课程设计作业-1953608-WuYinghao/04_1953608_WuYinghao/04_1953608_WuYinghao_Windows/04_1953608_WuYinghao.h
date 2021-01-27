#pragma once
#ifndef _04_1953608_WUYINGHAO_H_
#define _04_1953608_WUYINGHAO_H_

/*
*题目四：算术表达式求解，输入一个中缀表达式，输出其结果
*采用栈和队列的数据结构先将中缀表达式转换为后缀表达式，再进行运算
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
class StackNode             //栈结点
{
private:   
	T _data;                //存放的数据
	bool _isSign;           //用于判断这个符号是不是正负号
	StackNode<T>* _next;    //栈的下一个元素
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
class Stack                //栈
{
private:
	StackNode<T>* _top;              //栈顶指针
public:
	Stack();
	~Stack();
	void push(const T data,bool isSign=false);
    bool pop(T& data);
	T getTopData()const { return (_top->_next) ? _top->_next->_data : '\0'; };              //获取栈顶元素的值
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
		cerr << "无法创建栈" << endl << ba.what() << endl;
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
		cerr << "无法创建栈结点" << endl << ba.what() << endl;
	}
}

template<class T>
bool Stack<T>::pop(T& data)
{
	if (!_top->_next)    //栈空
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
class QueueNode            //队结点
{
private:
	T _data;
	bool _isSign;
	QueueNode<T>* _next;
	int _bit_num;         //只用于记录小数点所保持的位数
	int _int_num;         //用于记录整数部分的位数
public:
	QueueNode();
	QueueNode(T data,bool isSign=false,int bit_num=0,int int_num=1); //参数分别为数据、是否为正负号、小数位数、整数位数
	~QueueNode();

	bool isSign()const { return _isSign; };        //判断是不是正负号
	int getBitNum()const { return _bit_num; };     //返回小数点包含的位数
	T getData()const { return _data; };            //返回数据的内容
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
	QueueNode<T>* _top;          //队头指针
	QueueNode<T>* _last;         //队尾指针
public:
	Queue();
	~Queue();
	void push(const T data,bool isSign=false,int bit_num=0,int int_num=1);
	bool pop(T &data);
	bool pop(QueueNode<T>& node);
	int getQueueLength()const;       //获取当前队列的长度
	T getTopData()const { return (_top->_next) ? _top->_next->_data : ' '; };              //获取队首元素的值
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
		cerr << "无法创建队列" << endl << ba.what() << endl;
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
		//队尾插入
		if (!_top->_next)  //队列为空
		{
			_top->_next = newNode;
			newNode->_next = NULL;
			_last->_next = newNode;   //插入第一个结点
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
		cout << "无法创建队列结点" << endl << ba.what();
	}
}

template<class T>
bool Queue<T>::pop(T& data)
{
	if (!this->_top->_next)						 //如果队列为空
	{
		return false;
	}
	else
	{
		QueueNode<T>* temp = _top->_next;
		if (!temp->_next)						 //队列只有一个结点
		{
			_top->_next = _last->_next = NULL;
			data = temp->_data;
			delete temp;
			return true;
		}
		else                                      //队列不只有一个结点                  
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
	if (!this->_top->_next)						 //如果队列为空
	{
		return false;
	}
	else
	{
		QueueNode<T>* temp = _top->_next;
		if (!temp->_next)						 //队列只有一个结点
		{
			_top->_next = _last->_next = NULL;
			node.setBitNum(temp->_bit_num);
			node.setData(temp->_data);
			node.setSign(temp->_isSign);
			node.setIntNum(temp->_int_num);
			delete temp;
			return true;
		}
		else                                      //队列不只有一个结点                  
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
