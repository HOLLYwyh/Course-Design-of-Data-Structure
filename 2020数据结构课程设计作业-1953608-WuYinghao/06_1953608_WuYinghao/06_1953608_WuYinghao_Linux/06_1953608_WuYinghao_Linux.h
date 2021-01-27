#pragma once
/*
* 本项目采用森林的数据结构
* 实现的功能:1.建立新家庭2.插入子女或兄弟3.删除4.修改5.查看
* 森林的结构是左子女右兄弟
* --经过长期的DEBUG，最终在遍历上放弃了非递归算法，因为涉及到指针的复制与删除 --
*/

#ifndef _06_1953608_WUYINGHAO_H_
#define _06_1953608_WUYINGHAO_H_

#include<iostream>
#include<string>
//#include<vld.h>

using namespace std;

void end()
{
	cout << "press a number to end the system" << endl;
	cin.get();
	cin.get();
}

//枚举表示子女or兄弟
enum  Tag
{
	eChild,
	eSibling
};

template<class T>
class FamilyTree;

template<class T>
class Stack;

//家谱结点
template<class T>
class FamilyNode
{
private:
	T _name;        //结点的名称
	FamilyNode<T>* _childNode;			//左节点-子女结点
	FamilyNode<T>* _siblingNode;		//右节点-兄弟结点
	FamilyNode<T>* _preSiblingNode;     //前兄弟结点 
	FamilyNode<T>* _next;                //新增，栈中的下一个元素
	FamilyNode<T>* _parentNode;         //新增，指向父节点
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

//家谱
template<class T>
class FamilyTree
{
private:
	FamilyNode<T>* _first;                               //家谱的内容一律存放在_first的_childNode指针域中，_silbNode始终为空

protected:
	void recursionDelete(FamilyNode<T>* node);            //递归删除结点
public:
	FamilyTree();
	~FamilyTree();

	FamilyNode<T>* getNodeByName(T name, FamilyNode<T>* node, bool& tag);      //查询名为name的结点
	FamilyNode<T>* getFirstNode()const                                //返回祖先结点（第一个有用的结点）
	{
		return this->_first->_childNode;
	};
	void insertNode(T target, T name, Tag tag);                          //在名为target的结点处插入名为name的tag类型结点
	void changeNode(T target, T name);                                    //将名为target的结点名称修改为name
	void insertRoot(T name);                                             //插入根节点
	void printNode(FamilyNode<T>* number);                               //输出结点number的兄弟和子女
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
		cerr << "无法创建家谱" << endl << ba.what() << endl;
		end();
		exit(1);
	}
}

template<class T>
FamilyTree<T>::~FamilyTree()    //递归删除
{
	deleteNode(_first);
}

template<class T>
void FamilyTree<T>::deleteNode(FamilyNode<T>* node)    //删除一个结点以及它的左子树（删除它和它的子女，保留它的兄弟结点）
{
	if (NULL == node)
	{
		cout << "删除失败，未找到此姓名的人" << endl;
		return;
	}
	else
	{
		if (node->_preSiblingNode != NULL)    //存在左兄弟
		{
			node->_preSiblingNode->_siblingNode = node->_siblingNode;
		}
		if (node->_siblingNode != NULL)       //存在右兄弟
		{
			node->_siblingNode->_preSiblingNode = node->_preSiblingNode;
		}
		if ((NULL == node->_preSiblingNode) && (node->_parentNode != NULL))      //是长子且不是_first
		{
			node->_parentNode->_childNode = node->_siblingNode;
		}
		recursionDelete(node->_childNode);
		delete node;
		cout << "已删除此家庭" << endl;
	}
}

template<class T>
void FamilyTree<T>::recursionDelete(FamilyNode<T>* node)           //后序遍历递归删除结点
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
FamilyNode<T>* FamilyTree<T>::getNodeByName(T name, FamilyNode<T>* node, bool& tag)        //使用前序遍历的递归算法找目标
//本来是想用非递归算法，但是栈结点和树结点统一起来较麻烦
{
	FamilyNode<T>* result = NULL;
	if (NULL == node)  //证明是空指针
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
				result = getNodeByName(name, node->_childNode, tag);
			}
			if (!tag)
			{
				result = getNodeByName(name, node->_siblingNode, tag);
			}
		}
		return result;
	}

}

template<class T>
void FamilyTree<T>::insertNode(T target, T name, Tag tag)           //在名为target的结点处插入名为name的tag类型结点
{
	try
	{
		bool flag = false;
		FamilyNode<T>* node = this->getNodeByName(target, this->getFirstNode(), flag);
		if (node != NULL)  //找到目标
		{
			FamilyNode<T>* newNode = new FamilyNode<T>(name);

			switch (tag)      //判断是添加兄弟还是添加子女
			{
			case eChild:
			{
				if (NULL == node->_childNode)       //说明还没有创建子女
				{
					newNode->_childNode = node->_childNode;
					node->_childNode = newNode;
					newNode->_parentNode = node;
					break;
				}
				else                            //已经有子女,添加子女结点的兄弟结点
				{
					FamilyNode<T>* parent = node;
					node = node->_childNode;
					while (node->_siblingNode != NULL)
					{
						node = node->_siblingNode;  //走到最后一个节点
					}

					newNode->_siblingNode = node->_siblingNode;
					node->_siblingNode = newNode;
					newNode->_preSiblingNode = node;          //指向前兄弟
					newNode->_parentNode = parent;
					break;
				}
			}
			case eSibling:
			{
				newNode->_siblingNode = node->_siblingNode;
				node->_siblingNode = newNode;
				newNode->_preSiblingNode = node;   //指向前兄弟
				newNode->_parentNode = node->_parentNode;
				break;
			}
			default:
			{
				cerr << "插入失败";
				delete newNode;
				return;
			}
			}
		}
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法创建结点" << endl << ba.what() << endl;
	}
}

template<class T>
void FamilyTree<T>::changeNode(T target, T name)                     //将名为target的结点名称修改为name,后续可能还有修改
{
	bool tag = false;
	FamilyNode<T>* result = this->getNodeByName(target, this->getFirstNode(), tag);
	if (NULL == result)
	{
		cerr << "***查询不到名为" << name << "的人" << endl << endl;
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
	if (_first->_childNode != NULL)          //根结点上已经有内容
	{
		cerr << "已有根结点，不能再次创建根结点" << endl;
		return;
	}
	else
	{
		try
		{
			FamilyNode<T>* newNode = new FamilyNode<T>(name);
			newNode->_childNode = _first->_childNode;
			_first->_childNode = newNode;                         //将根结点建立在_first的左结点上
			newNode->_parentNode = _first;                        //将根结点和第一个_first指针相连接
		}
		catch (bad_alloc& ba)
		{
			cerr << "无法创建根结点" << endl << ba.what() << endl;
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
	if ((NULL == child) && (NULL == sibling) && (NULL == preSibling) && ((NULL == parent) || (parent == this->_first)))
	{
		cout << "很遗憾! " << number->_name << "既没有子女，也没有兄弟姐妹,也没有父(母)亲" << endl;
		return;
	}
	if (child != NULL)
	{
		cout << number->_name << " 的子女有：";
		while (child != NULL)
		{
			cout << "  " << child->_name;
			child = child->_siblingNode;
		}
	}
	if ((sibling != NULL) || (preSibling != NULL))
	{
		cout << endl << number->_name << " 的兄弟姐妹有：";
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
	if ((parent != NULL) && (parent != this->_first))   //有双亲，但不是头指针_first
	{
		cout << endl << number->_name << "的父(母)亲是：" << parent->_name;
	}

	cout << endl;
}


//栈  以树结点为栈结点
template<class T>
class Stack
{
private:
	FamilyNode<T>* _top;
public:
	Stack();
	~Stack();
	void push(T name);                            //用于类外入栈     
	void pop();                                   //用于.cpp的函数

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
		cerr << "无法建栈" << endl << ba.what();
		end();
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
		current = current->_next;
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
		if (NULL == _top->_next)                           //最开始的时候栈为空
		{
			newNode->_next = NULL;
			_top->_next = newNode;
		}
		else                                              //最开始的时候栈不为空
		{
			newNode->_next = _top->_next;
			_top->_next = newNode;
		}
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法创建栈元素" << endl << ba.what() << endl;
		end();
		exit(1);
	}
}

template<class T>
void Stack<T>::pop()
{
	if (NULL == _top->_next)              //栈为空
	{
		cerr << "栈为空，不能执行弹出操作" << endl;
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
