#pragma once
#ifndef _07_1953608_WUYINGHAO_H_
#define _07_1953608_WUYINGHAO_H_

#include<iostream>

using namespace std;

static const int defaultSize = 10000;             //��������ֵ
template<class T>
class HuffmanTree;
template<class T>
class Queue;


//Huffman���
template<class T>
class HuffmanNode
{
private:
	HuffmanNode<T>* _leftChild;
	HuffmanNode<T>* _rightChild;
	//���ڶ���֮�е�ָ��
	HuffmanNode<T>* _next;
	HuffmanNode<T>* _front;
	T _data;
public:
	HuffmanNode(T data=0);
	~HuffmanNode();
	bool operator<(HuffmanNode<T>& node);
	friend class HuffmanTree<T>;
	friend class Queue<T>;
};

template<class T>
HuffmanNode<T>::HuffmanNode(T data)
	:_leftChild(NULL),_rightChild(NULL),
	_data(data),_next(NULL),_front(NULL)
{

}


template<class T>
HuffmanNode<T>::~HuffmanNode()
{

}


template<class T>
bool HuffmanNode<T>::operator<(HuffmanNode<T>& node)
{
	return (this->_data < node._data) ? true : false;
}

//Huffman��
template<class T>
class HuffmanTree
{
private:
	HuffmanNode<T>* _root;
	T _min_value;
protected:
	void deleteNode(HuffmanNode<T>* node);
public:
	HuffmanTree();
	HuffmanTree(T data[],int num);
	~HuffmanTree();
	T getMinValue(HuffmanNode<T>* node,int height);
	HuffmanNode<T>* getStart() { return _root->_next; };
};

template<class T>
HuffmanTree<T>::HuffmanTree()
	:_root(NULL),_min_value(0)
{

}

template<class T>
HuffmanTree<T>::HuffmanTree(T data[], int num)
{
	_min_value = 0;
	_root = NULL;
	_root = new HuffmanNode<T>;
	Queue<HuffmanNode<T>*> queue;
	HuffmanNode<T>* first, *second;
	for (int i = 0; i < num; i++)
	{
		try
		{
			HuffmanNode<T>* newNode = new HuffmanNode<T>(data[i]);
			queue.push(newNode);
		}
		catch (bad_alloc& ba)
		{
			cerr << "�޷����������" << endl << ba.what() << endl;
		}
	}
	
	if (1 == num)
	{
		try
		{
			queue.pop(first);
			HuffmanNode<T>* parent = new HuffmanNode<T>;
			parent->_data = first->_data;
			parent->_leftChild = first;
			parent->_rightChild = NULL;
			_root->_next= parent;
		}
		catch (bad_alloc& ba)
		{
			cerr << "�޷��������ڵ�" << endl << ba.what() << endl;
		}
	}
	for (int j = 0; j < num - 1; j++)
	{
		queue.pop(first);
		queue.pop(second);
		try
		{
			HuffmanNode<T>* parent = new HuffmanNode<T>;
			parent->_leftChild = first;
			parent->_rightChild = second;
			parent->_data = first->_data + second->_data;;
			queue.push(parent);
			_root->_next=parent;
		}
		catch (bad_alloc& ba)
		{
			cerr << "�޷��������ڵ�" << endl << ba.what() << endl;
		}
	}
}

template<class T>
void HuffmanTree<T>::deleteNode(HuffmanNode<T>*node)
{
	if (!node)
	{
		return;
	}
	else
	{
		deleteNode(node->_leftChild);
		deleteNode(node->_rightChild);
		delete node;
	}
}

template<class T>
HuffmanTree<T>::~HuffmanTree()
{
	deleteNode(this->getStart());
	delete _root;
}

template<class T>
T HuffmanTree<T>::getMinValue(HuffmanNode<T>*node,int height)
{
	if (!node)              //��ǰ���Ϊ��
	{
		return 0;
	}
	else if ((!node->_leftChild) && (!node->_rightChild))
	{
		_min_value += node->_data*height;
		return _min_value;
	}
	else
	{
		height++;
		getMinValue(node->_leftChild,height);
		getMinValue(node->_rightChild,height);
		return _min_value;

	}
}


//��Huffman���ΪԪ�ص�˫�˶���
template<class T>
class Queue
{
private:
	HuffmanNode<T>* _top;  //����ָ��
	HuffmanNode<T>* _last;
protected:
	void sort();
public:
	Queue();
	~Queue();
	void push(T data);
	bool pop(T& data);
};

template<class T>
Queue<T>::Queue()
{
	try
	{
		_top = new HuffmanNode<T>;
		_last = new HuffmanNode<T>;
		_top->_next = _top->_front = _last->_next = _last->_front = NULL;
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷��������ȼ�����" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}
}

template<class T>
Queue<T>::~Queue()
{
	HuffmanNode<T>* current = _top->_next;
	HuffmanNode<T>* temp;
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
void Queue<T>::sort()
{
	HuffmanNode<T>* current = _top->_next;
	HuffmanNode<T>* target = _last->_next;
	T current_data = current->_data;
	T target_data = target->_data;
	while (*current_data<*target_data)
	{
		current = current->_next;
		current_data = current->_data;
	}
	if (current!= _last->_next)     //���������һ��λ�ã������ƶ�
	{
		HuffmanNode<T>* temp = _last->_next->_front;  //�ݴ����Ķ�β���
		current->_front->_next = _last->_next;
		_last->_next->_front = current->_front;
		current->_front = _last->_next;
		_last->_next->_next = current;

		temp->_next = NULL;
		_last->_next = temp;
	
	}
}


template<class T>
void Queue<T>::push(T data)
{
	try
	{

		HuffmanNode<T>* newNode = new HuffmanNode<T>(data);
		if (!_top->_next)          //�������Ϊ��
		{
			newNode->_next = _top->_next;
			newNode->_front = _top;
			_top->_next = newNode;
			_last->_next = newNode;
		}
		else                         //���в�Ϊ��
		{
			newNode->_next = NULL;
			newNode->_front = _last->_next;
			_last->_next->_next = newNode;
			_last->_next = newNode;
		}
		sort();
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷������ȼ������в���Ԫ��" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}
}

template<class T>
bool Queue<T>::pop(T& data)
{
	if (!_top->_next)    //����Ϊ��
	{
		return false;
	}
	else
	{
		HuffmanNode<T>* current = _top->_next;
		if (_last->_next == current)//����ֻ��һ�����
		{
			_top->_next = _last->_next = NULL;
			data = current->_data;
			delete current;
		}
		else
		{
			_top->_next = current->_next;
			current->_next->_front = _top;
			data = current->_data;
			delete current;
		}
		
		return true;
	}
}



#endif
