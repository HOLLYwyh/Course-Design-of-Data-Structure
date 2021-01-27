#pragma once
#ifndef _LINK_H_
#define _LINK_H_
/*
* 此文件用于存储链表类的定义以及其成员函数的定义
* 注意：尽管题目中已经说明需要使用正整数，但是此系统仍使用模板
*/


#include<iostream>
#include <unistd.h>

using namespace std;

void end()
{
	cout << "press a number to end the system" << endl;
	cin.get();
	cin.get();
}

template <class T>
class linkList;

template<class T>
class linkNode       //结点类，是链表的重要组成部分
{
private:
	T _data;       //链表结点上的值
	linkNode<T>* _rLink;      //指向下一个结点
	linkNode<T>* _lLink;      //指向前一个结点

public:
	friend class linkList<T>;       //结点的友元类
	linkNode();                     //默认构造函数，默认是int类型的0
	linkNode(T number);             //给定参数的构造      
	~linkNode();                    //析构函数
};

template<class T>
linkNode<T>::linkNode()
{
	_data = 0;               //默认是int类型的0
	_lLink = NULL;
	_rLink = NULL;
}

template<class T>
linkNode<T>::~linkNode()
{
}

template <class T>
linkNode<T>::linkNode(T data)
{
	_data = data;
	_lLink = NULL;
	_rLink = NULL;
}


template<class T>
class linkList                        //此处的链表含有附加头
{
private:
	linkNode<T>* _first;                //头指针，用于查询
	linkNode<T>* _last;                 //尾指针，用于队尾插入
public:
	linkList();                             //构造函数
	~linkList();                            //析构函数
	void append(T data);                               //在链表尾部插入元素
	void intersect(linkList<T>& list);                 //做交集的运算
	void deleteNode(linkNode<T>* cur_node);            //删除从此节点后的所有结点
	void printResult();                                      //最后的打印操作
	bool isEmpty() const;                              //判断链表是否为空
	T getFinalData() const;                 //返回链表末尾的数值
};

template<class T>
linkList<T>::linkList()
{
	linkNode<T>* addition = new linkNode<T>;
	_first = new linkNode<T>;
	_last = new linkNode<T>;
	if (NULL == addition || NULL == _first || NULL == _last)
	{
		cerr << "无法创建链表内的指针指针";
		end();
		exit(1);
	}
	else
	{
		addition->_data = 0;    //附加头的默认值
		addition->_rLink = NULL;
		addition->_lLink = NULL;

		this->_first->_data = 0;
		this->_first->_rLink = addition;
		this->_first->_lLink = NULL;

		this->_last->_data = 0;
		this->_last->_rLink = addition;
		this->_last->_lLink = NULL;
	}

}

template <class T>
linkList<T>::~linkList()                               //向右删除链表
{
	linkNode<T>* current = this->_first->_rLink;     //直接指向附加头
	linkNode<T>* temp = NULL;
	while (current != NULL)
	{
		temp = current;
		current = current->_rLink;
		delete temp;
	}
	delete _first;
	delete _last;
}

template<class T>
void linkList<T>::append(T data)
{
	linkNode<T>* newNode = new linkNode<T>(data);

	if (NULL == newNode)
	{
		cerr << "无法创建此结点";
		end();
		exit(1);
	}
	else
	{
		newNode->_rLink = _last->_rLink->_rLink;
		_last->_rLink->_rLink = newNode;
		newNode->_lLink = _last->_rLink;
		_last->_rLink = newNode;
	}
}

template<class T>
void linkList<T>::deleteNode(linkNode<T>* cur_node)
{
	//由于已经有了附加头结点，所以不考虑第一个结点的删除，只额外考虑最后一个结点的删除
	if (cur_node->_rLink == NULL)   //删除的是最后一个结点
	{
		cur_node->_lLink->_rLink = NULL;
		delete cur_node;
	}
	else            //删除的是中间的结点
	{
		cur_node->_lLink->_rLink = cur_node->_rLink;
		cur_node->_rLink->_lLink = cur_node->_lLink;
		delete cur_node;
	}
}

template<class T>
void linkList<T>::intersect(linkList<T>& list)
{
	linkNode<T>* p_1 = this->_first->_rLink->_rLink;         //最后的结果存在p_1所对应的链表中
	linkNode<T>* p_2 = list._first->_rLink->_rLink;
	while ((p_1 != NULL) && (p_2 != NULL))
	{
		if (p_1->_data == p_2->_data)
		{
			p_1 = p_1->_rLink;
			p_2 = p_2->_rLink;
		}
		else if (p_1->_data > p_2->_data)
		{
			p_2 = p_2->_rLink;
		}
		else if (p_1->_data < p_2->_data)
		{
			linkNode<T>* current = p_1;
			p_1 = p_1->_rLink;
			deleteNode(current);
		}
	}
	/*
	* 比较结束之后一定会有一个链表先查询结束，
	* 若是链表一先结束，不影响实际的结果
	* 若是链表二先结束，需要把链表一多出来的部分删除
	*/
	if (NULL == p_2)//链表二先结束
	{
		while (p_1 != NULL)
		{
			linkNode<T>* current = p_1;
			p_1 = p_1->_rLink;
			deleteNode(current);
		}
	}
}

template<class T>
bool linkList<T>::isEmpty() const
{
	linkNode<T>* cur = this->_first->_rLink->_rLink;   //指向附加头的下一个结点
	if (NULL == cur)
		return true;
	else
		return false;
}

template<class T>
void linkList<T>::printResult()
{
	if (this->isEmpty())
		cout << "NULL" << endl;
	else
	{
		linkNode<T>* cur = this->_first->_rLink->_rLink;   //指向附加头的下一个结点
		while (cur != NULL)
		{
			if (cur != _last)
			{
				cout << cur->_data << " ";
				cur = cur->_rLink;
			}
			else
				cout << cur->_data << endl << endl;
		}
	}
}

template<class T>
T linkList<T>::getFinalData()const
{
	return this->_last->_rLink->_data;
}

#endif
