#pragma once
/*
* ����Ŀ����ɭ�ֵ����ݽṹ
* ʵ�ֵĹ���:1.�����¼�ͥ2.������Ů���ֵ�3.ɾ��4.�޸�5.�鿴
* ɭ�ֵĽṹ������Ů���ֵ�
* --�������ڵ�DEBUG�������ڱ����Ϸ����˷ǵݹ��㷨����Ϊ�漰��ָ��ĸ�����ɾ�� --
*/

#ifndef _06_1953608_WUYINGHAO_H_
#define _06_1953608_WUYINGHAO_H_

#include<iostream>
#include<string>
//#include<vld.h>

using namespace std;

//ö�ٱ�ʾ��Ůor�ֵ�
enum  Tag
{
	eChild,
	eSibling
};

template<class T>
class FamilyTree;

template<class T>
class Stack;

//���׽��
template<class T>
class FamilyNode
{
private:
	T _name;        //��������
	FamilyNode<T>* _childNode;			//��ڵ�-��Ů���
	FamilyNode<T>* _siblingNode;		//�ҽڵ�-�ֵܽ��
	FamilyNode<T>* _preSiblingNode;     //ǰ�ֵܽ�� 
	FamilyNode<T>* _next;                //������ջ�е���һ��Ԫ��
	FamilyNode<T>* _parentNode;         //������ָ�򸸽ڵ�
public:
	FamilyNode();
	FamilyNode(T data);
	~FamilyNode();
	T getNodeName() const;
	friend FamilyTree<T>;
	friend Stack<T>;
};

template<class T>
FamilyNode<T>::FamilyNode()
{
	_name = "NONE";
	_childNode = NULL;
	_siblingNode = NULL;
	_preSiblingNode = NULL;
	_parentNode = NULL;
	_next = NULL;
}


template<class T>
FamilyNode<T>::FamilyNode(T data)
{
	_name = data;
	_childNode = NULL;
	_siblingNode = NULL;
	_preSiblingNode = NULL;
	_parentNode = NULL;
	_next = NULL;
}

template<class T>
FamilyNode<T>::~FamilyNode()
{

}

template<class T>
T FamilyNode<T>::getNodeName()const
{
	FamilyNode<T>a;
	FamilyNode<T>b;
	a = b;
	return _name;
}

//����
template<class T>
class FamilyTree
{
private:
	FamilyNode<T>* _first;                               //���׵�����һ�ɴ����_first��_childNodeָ�����У�_silbNodeʼ��Ϊ��

protected:
	void recursionDelete(FamilyNode<T>*node);            //�ݹ�ɾ�����
public:
	FamilyTree();
	~FamilyTree();

	FamilyNode<T>* getNodeByName(T name,FamilyNode<T>* node,bool& tag) ;      //��ѯ��Ϊname�Ľ��
	FamilyNode<T>* getFirstNode()const                                //�������Ƚ�㣨��һ�����õĽ�㣩
	{
		return this->_first->_childNode;
	};
	void insertNode(T target, T name, Tag tag);                          //����Ϊtarget�Ľ�㴦������Ϊname��tag���ͽ��
	void changeNode(T target,T name);                                    //����Ϊtarget�Ľ�������޸�Ϊname
	void insertRoot(T name);                                             //������ڵ�
	void printNode(FamilyNode<T>* number);                               //������number���ֵܺ���Ů
	void deleteNode(FamilyNode<T>* node);
};

template<class T>
FamilyTree<T>::FamilyTree()
{
	try 
	{
		_first = new FamilyNode<T>;
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷���������" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}
}

template<class T>
FamilyTree<T>::~FamilyTree()    //�ݹ�ɾ��
{
	deleteNode(_first);
}

template<class T>
void FamilyTree<T>::deleteNode(FamilyNode<T>* node)    //ɾ��һ������Լ�������������ɾ������������Ů�����������ֵܽ�㣩
{
	if (NULL == node)
	{
		cout << "ɾ��ʧ�ܣ�δ�ҵ�����������" << endl;
		return;
	}
	else
	{
		if (node->_preSiblingNode != NULL)    //�������ֵ�
		{
			node->_preSiblingNode->_siblingNode = node->_siblingNode;
		}
		if (node->_siblingNode != NULL)       //�������ֵ�
		{
			node->_siblingNode->_preSiblingNode = node->_preSiblingNode;
		}
		if ((NULL == node->_preSiblingNode)&&(node->_parentNode!=NULL))      //�ǳ����Ҳ���_first
		{
			node->_parentNode->_childNode = node->_siblingNode;
		}
		recursionDelete(node->_childNode);  
		delete node;
		cout << "��ɾ���˼�ͥ" << endl;
	}
}

template<class T>
void FamilyTree<T>::recursionDelete(FamilyNode<T>* node)           //��������ݹ�ɾ�����
{
	if (NULL == node)
	{
		return;
	}
	else
	{
		recursionDelete(node->_childNode);
		recursionDelete(node->_siblingNode);
		delete node;

	}
}

template<class T>
FamilyNode<T>* FamilyTree<T>::getNodeByName(T name, FamilyNode<T>* node,bool& tag)        //ʹ��ǰ������ĵݹ��㷨��Ŀ��
//���������÷ǵݹ��㷨������ջ���������ͳһ�������鷳
{
	FamilyNode<T>* result=NULL;
	if (NULL == node)  //֤���ǿ�ָ��
	{
		return NULL;
	}
	else
	{
		if (node->_name == name)
		{
			tag = true;
			return node;
		}
		else 
		{
			if (!tag)
			{
			 result=getNodeByName(name, node->_childNode,tag);
			}
			if (!tag)
			{
			result=getNodeByName(name, node->_siblingNode,tag);
			}
		}
		return result;
	}

}

template<class T>
void FamilyTree<T>::insertNode(T target, T name, Tag tag)           //����Ϊtarget�Ľ�㴦������Ϊname��tag���ͽ��
{
	try
	{
		bool flag = false;
		FamilyNode<T>* node = this->getNodeByName(target,this->getFirstNode(),flag);
		if (node != NULL)  //�ҵ�Ŀ��
		{
			FamilyNode<T>* newNode = new FamilyNode<T>(name);

			switch (tag)      //�ж�������ֵܻ��������Ů
			{
			case eChild:
			{
				if (NULL == node->_childNode)       //˵����û�д�����Ů
				{
					newNode->_childNode = node->_childNode;
					node->_childNode = newNode;
					newNode->_parentNode = node;
					break;
				}
				else                            //�Ѿ�����Ů,�����Ů�����ֵܽ��
				{
					FamilyNode<T>* parent = node;
					node = node->_childNode;
					while (node->_siblingNode != NULL)
					{
						node = node->_siblingNode;  //�ߵ����һ���ڵ�
					}
					
					newNode->_siblingNode = node->_siblingNode;
					node->_siblingNode = newNode;
					newNode->_preSiblingNode = node;          //ָ��ǰ�ֵ�
					newNode->_parentNode = parent;
					break;
				}
			}
			case eSibling:
			{
				newNode->_siblingNode = node->_siblingNode;
				node->_siblingNode = newNode;
				newNode->_preSiblingNode = node;   //ָ��ǰ�ֵ�
				newNode->_parentNode = node->_parentNode;
				break;
			}
			default:
			{
				cerr << "����ʧ��";
				delete newNode;
				return;
			}
			}
		}
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷��������" << endl << ba.what() << endl;
	}
}

template<class T>
void FamilyTree<T>::changeNode(T target, T name)                     //����Ϊtarget�Ľ�������޸�Ϊname,�������ܻ����޸�
{
	bool tag = false;
	FamilyNode<T>* result =this->getNodeByName(target, this->getFirstNode(),tag);
	if (NULL == result)
	{
		cerr << "***��ѯ������Ϊ" << name << "����" << endl << endl;
		return;
	}
	else
	{
		result->_name = name;
	}
}

template<class T>
void FamilyTree<T>::insertRoot(T name)
{
	if (_first->_childNode != NULL)          //��������Ѿ�������
	{
		cerr << "���и���㣬�����ٴδ��������" << endl;
		return;
	}
	else
	{
		try
		{
			FamilyNode<T>* newNode = new FamilyNode<T>(name);
			newNode->_childNode = _first->_childNode;
			_first->_childNode = newNode;                         //������㽨����_first��������
			newNode->_parentNode = _first;                        //�������͵�һ��_firstָ��������
		}
		catch (bad_alloc& ba)
		{
			cerr << "�޷����������" << endl << ba.what() << endl;
		}
	}
}

template<class T>
void FamilyTree<T>::printNode(FamilyNode<T>* number)
{
	FamilyNode<T>* child = number->_childNode;
	FamilyNode<T>* sibling = number->_siblingNode;
	FamilyNode<T>* preSibling = number->_preSiblingNode;
	FamilyNode<T>* parent = number->_parentNode;
	if ((NULL == child) && (NULL == sibling)&&(NULL==preSibling)&&((NULL==parent)||(parent==this->_first)))
	{
		cout << "���ź�! " << number->_name << "��û����Ů��Ҳû���ֵܽ���,Ҳû�и�(ĸ)��" << endl;
		return;
	}
	if (child != NULL)
	{
		cout << number->_name << " ����Ů�У�";
		while (child != NULL)
		{
			cout << "  " << child->_name;
			child = child->_siblingNode;
		}
	}
	if ((sibling != NULL) || (preSibling != NULL))
	{
		cout << endl << number->_name << " ���ֵܽ����У�";
		while (sibling != NULL)
		{
			cout << "  " << sibling->_name;
			sibling = sibling->_siblingNode;
		}

		while (preSibling != NULL)
		{
			cout << " " << preSibling->_name;
			preSibling = preSibling->_preSiblingNode;
		}
	}
	if ((parent != NULL) && (parent != this->_first))   //��˫�ף�������ͷָ��_first
	{
		cout << endl << number->_name << "�ĸ�(ĸ)���ǣ�" << parent->_name;
	}
	
	cout << endl;
}


//ջ  �������Ϊջ���
template<class T>
class Stack
{
private:
	FamilyNode<T>* _top;
public:
	Stack();
	~Stack();
	void push(T name);                            //����������ջ     
	void pop();                                   //����.cpp�ĺ���

	friend class FamilyTree<T>;
};

template<class T>
Stack<T>::Stack()
{
	try
	{
		_top = new FamilyNode<T>;
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷���ջ" << endl << ba.what();
		system("pause");
		exit(1);
	}
}

template<class T>
Stack<T>::~Stack()
{
	FamilyNode<T>* current = _top->_next;
	FamilyNode<T>* temp;
	while (current != NULL)
	{
		temp = current;
		current=current->_next;
		delete temp;
	}
	delete _top;
}

template<class T>
void Stack<T>::push(T name)
{
	try
	{
		FamilyNode<T>* newNode = new FamilyNode<T>(name);        
		if (NULL == _top->_next)                           //�ʼ��ʱ��ջΪ��
		{
			newNode->_next = NULL;
			_top->_next = newNode;
		}
		else                                              //�ʼ��ʱ��ջ��Ϊ��
		{
			newNode->_next = _top->_next;
			_top->_next = newNode;
		}
	}
	catch (bad_alloc& ba)
	{
		cerr << "�޷�����ջԪ��" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}
}

template<class T>
void Stack<T>::pop()
{
	if (NULL == _top->_next)              //ջΪ��
	{
		cerr << "ջΪ�գ�����ִ�е�������" << endl;
		return;
	}
	else
	{
		FamilyNode<T>* temp = _top->_next;
		_top->_next = temp->_next;
		cout << temp->_name << " ";
		delete temp;
	}
}

#endif // !_06_1953608_WUYINGHAO_H_
