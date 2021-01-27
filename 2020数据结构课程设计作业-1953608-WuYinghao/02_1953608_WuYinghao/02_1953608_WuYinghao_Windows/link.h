#pragma once
#ifndef _LINK_H_
#define _LINK_H_
/*
* ���ļ����ڴ洢������Ķ����Լ����Ա�����Ķ���
* ע�⣺������Ŀ���Ѿ�˵����Ҫʹ�������������Ǵ�ϵͳ��ʹ��ģ��
*/


#include<iostream>
using namespace std;

template <class T>
class linkList;

template<class T>
class linkNode       //����࣬���������Ҫ��ɲ���
{
private:
	T _data;       //�������ϵ�ֵ
    linkNode<T>* _rLink;      //ָ����һ�����
	linkNode<T>* _lLink;      //ָ��ǰһ�����

public:
	friend class linkList<T>;       //������Ԫ��
	linkNode();                     //Ĭ�Ϲ��캯����Ĭ����int���͵�0
	linkNode(T number);             //���������Ĺ���      
	~linkNode();                    //��������
};

template<class T>
linkNode<T>::linkNode()
{
	_data = 0;               //Ĭ����int���͵�0
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
class linkList                        //�˴��������и���ͷ
{
private:
	linkNode<T>* _first;                //ͷָ�룬���ڲ�ѯ
	linkNode<T>* _last;                 //βָ�룬���ڶ�β����
public:
	linkList();                             //���캯��
	~linkList();                            //��������
	void append(T data);                               //������β������Ԫ��
	void intersect(linkList<T>& list);                 //������������
	void deleteNode(linkNode<T>* cur_node);            //ɾ���Ӵ˽ڵ������н��
	void printResult();                                      //���Ĵ�ӡ����
	bool isEmpty() const;                              //�ж������Ƿ�Ϊ��
	T getFinalData() const;                 //��������ĩβ����ֵ
};

template<class T>
linkList<T>::linkList()
{
	linkNode<T>* addition = new linkNode<T>;
	_first = new linkNode<T>;
	_last = new linkNode<T>;
	if (NULL == addition||NULL==_first||NULL==_last)
	{
		cerr << "�޷����������ڵ�ָ��ָ��";
		system("pause");
		exit(1);
	}
	else
	{
		addition->_data = 0;    //����ͷ��Ĭ��ֵ
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
linkList<T>::~linkList()                               //����ɾ������
{
	linkNode<T>* current = this->_first->_rLink;     //ֱ��ָ�򸽼�ͷ
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
		cerr << "�޷������˽��";
		system("pause");
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
	//�����Ѿ����˸���ͷ��㣬���Բ����ǵ�һ������ɾ����ֻ���⿼�����һ������ɾ��
	if (cur_node->_rLink == NULL)   //ɾ���������һ�����
	{
		cur_node->_lLink->_rLink = NULL;
		delete cur_node;
	}
	else            //ɾ�������м�Ľ��
	{
		cur_node->_lLink->_rLink = cur_node->_rLink;
		cur_node->_rLink->_lLink = cur_node->_lLink;
		delete cur_node;
	}
}

template<class T>
void linkList<T>::intersect(linkList<T>& list)
{
	linkNode<T>* p_1 = this->_first->_rLink->_rLink;         //���Ľ������p_1����Ӧ��������
	linkNode<T>* p_2 = list._first->_rLink->_rLink;
	while ((p_1 != NULL) && (p_2 != NULL))
	{
		if (p_1->_data == p_2->_data)
		{
			p_1 = p_1->_rLink;
			p_2 = p_2->_rLink;
		}
		else if (p_1->_data>p_2->_data)
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
	* �ȽϽ���֮��һ������һ�������Ȳ�ѯ������
	* ��������һ�Ƚ�������Ӱ��ʵ�ʵĽ��
	* ����������Ƚ�������Ҫ������һ������Ĳ���ɾ��
	*/
	if (NULL == p_2)//������Ƚ���
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
	linkNode<T>* cur = this->_first->_rLink->_rLink;   //ָ�򸽼�ͷ����һ�����
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
		linkNode<T>* cur = this->_first->_rLink->_rLink;   //ָ�򸽼�ͷ����һ�����
		while (cur != NULL)
		{
			if (cur != _last)
			{
				cout << cur->_data << " ";
				cur = cur->_rLink;
			}
			else
				cout << cur->_data <<endl<<endl;
		}
	}
}

template<class T>
T linkList<T>::getFinalData()const
{
	return this->_last->_rLink->_data;
}

#endif
