#pragma once

#ifndef  _08_1953608_WUYINGHAO_H_
#define  _08_1953608_WUYINGHAO_H_

#include<iostream>

using namespace std;

template<class T,class E>
class EdgeNode;

template<class T,class E>
class Graph;

template<class T,class E>
class Queue;

template<class T,class E>
class UFSet;

//顶点类
template<class T,class E>       
class VertexNode
{
private:
	T _name;                //此顶点的名字
	VertexNode<T,E>* _next;   //下一个顶点
public:
	VertexNode(T name=0);
	~VertexNode();

	friend class EdgeNode<T,E>;//友元类，边
										
	friend class Graph<T,E>; //友元类，图
 
	friend class UFSet<T,E>;  //友元类，并查集
};

template<class T,class E>
VertexNode<T,E>::VertexNode(T name)
	:_name(name),_next(NULL)
{

}

template<class T,class E>
VertexNode<T,E>::~VertexNode()
{

}

//边类
template<class T,class E>
class EdgeNode
{
private:
	T _vertex_name_1;          //第一个顶点的名字
	T _vertex_name_2;          //第二个顶点的名字
	E _value;                  //当前边的权值
	EdgeNode<T, E>* _next;     //下一个图结点
public:
	EdgeNode(T name1=0,T name2=0,E value=0); 
	EdgeNode(EdgeNode<T, E>* edge);
	~EdgeNode();
	void printEdge();

	friend class Graph<T,E>;          //友元类，图
	friend class Queue<T,E>;          //友元类，队列
	friend class UFSet<T, E>;         //友元类，并查集
};

template<class T,class E>
EdgeNode<T, E>::EdgeNode(T name1,T name2,E value)
	:_vertex_name_1(name1),_vertex_name_2(name2),_value(value)
	,_next(NULL)
{

}

template<class T,class E>
EdgeNode<T, E>::EdgeNode(EdgeNode<T,E>* edge)
	:_vertex_name_1(edge->_vertex_name_1),_vertex_name_2(edge->_vertex_name_2),
	_value(edge->_value),_next(NULL)
{
	//需要把_next的值设置为NULL
}

template<class T,class E>
EdgeNode<T, E>::~EdgeNode()
{

}

template<class T,class E>
void EdgeNode<T, E>::printEdge()
{
	cout << this->_vertex_name_1 << "--(" << this->_value << ")->" << this->_vertex_name_2 << endl;
}

//图类
template<class T,class E>
class Graph
{
private:
	VertexNode<T,E>* _vertex_first;                 //顶点链表
	EdgeNode<T, E>* _edge_first;                  //边列表
	int vertex_num;                               //顶点的个数
protected:
	bool findVertex(T vertex) const;                   //查找名为vertex的结点是否存在 
	bool findMinEdge(EdgeNode<T, E>*& edge);              //寻找最短边
public:
	Graph(int length=0);
	~Graph();
	bool insertVertex(T vertex1);                       //插入一个名为vertex的顶点
	bool insertEdge(T vertex1, T vertex2, E value);     //用现有的两个顶点vertex1和vertex2来构造一个权值为value的边
	bool createMinTree(Queue<T,E>& queue);                               //生成最小生成树
	bool isSet()const { return(!(NULL == this->_vertex_first->_next)); };                                //是否已经创建图

	friend class UFSet<T,E>;
};

template<class T,class E>
Graph<T, E>::Graph(int length)
	:vertex_num(length)
{
	try
	{
		_vertex_first = new VertexNode<T,E>;
		_edge_first = new EdgeNode<T, E>;
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法创建树" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}
}

template<class T,class E>
Graph<T, E>::~Graph()
{
	//删除顶点链表
	VertexNode<T,E>* v_current = _vertex_first;
	VertexNode<T,E>* v_temp;
	while (v_current)
	{
		v_temp = v_current;
		v_current = v_current->_next;
		delete v_temp;
	}
	//删除边链表
	EdgeNode<T, E>* e_current = _edge_first;
	EdgeNode<T, E>* e_temp;
	while (e_current)
	{
		e_temp = e_current;
		e_current = e_current->_next;
		delete e_temp;
	}

}

template<class T,class E>
bool Graph<T, E>::findVertex(T vertex) const
{
	VertexNode<T,E>* current = _vertex_first->_next;
	while (current)
	{
		if (current->_name == vertex)
		{
			return true;
		}
		else
		{
			current = current->_next;
		}
	}
	return false;
}

template<class T,class E>
bool Graph<T, E>::insertVertex(T vertex)
{
	if (!findVertex(vertex))      //如果没有查到这个结点
	{
		try
		{
			VertexNode<T,E>* newNode=new VertexNode<T,E>(vertex);
			newNode->_next = _vertex_first->_next;
			_vertex_first->_next = newNode;
			vertex_num++;
			return true;
		}
		catch (bad_alloc& ba)
		{
			cerr<<"无法创建顶点"<<endl<<ba.what()<<endl;
			system("pause");
			exit(1);
		}
	}
	else
	{
		return false;
	}
}

template<class T,class E>
bool Graph<T, E>::insertEdge(T vertex1, T vertex2, E value)
{
	if (vertex1 != vertex2)
	{
		if ((findVertex(vertex1)) && (findVertex(vertex2)))   //同时找到了两个结点
		{
			try
			{
				EdgeNode<T, E>* newNode = new EdgeNode<T, E>(vertex1, vertex2, value);
				newNode->_next = _edge_first->_next;
				_edge_first->_next = newNode;
				return true;
			}
			catch (bad_alloc& ba)
			{
				cerr << "无法创建边" << endl << ba.what() << endl;
				system("pause");
				exit(1);
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

template<class T,class E>
bool Graph<T, E>::findMinEdge(EdgeNode<T, E>*& edge)
{
	EdgeNode<T, E>* current = _edge_first->_next;
	EdgeNode<T, E>* pre = _edge_first;
	EdgeNode<T, E>* min;
	EdgeNode<T, E>* min_pre;
	if (!current)       //边为空
	{
		return false;
	}
	else
	{
		min = current;
		min_pre = pre;

		pre = pre->_next;
		current = current->_next;
		while (current)
		{
			if (current->_value < min->_value)
			{
				min = current;
				min_pre = pre;
				pre = pre->_next;
				current = current->_next;
			}
			else
			{
				pre = pre->_next;
				current = current->_next;
			}
		}
		edge->_vertex_name_1 = min->_vertex_name_1;
		edge->_vertex_name_2 = min->_vertex_name_2;
		edge->_value = min->_value;
		edge->_next = min->_next;

		min_pre->_next = min->_next;
		delete min;      //删除最小值结点
		return true;
	}
}

template<class T,class E>
bool Graph<T,E>::createMinTree(Queue<T,E>& queue)
{
	EdgeNode<T, E>* minEdge=new EdgeNode<T,E>;//最小边
	EdgeNode<T, E>* edge = this->_edge_first;
	UFSet<T,E> ufset( vertex_num,this);
    
	while(!ufset.isConnected())
	{
		if (!findMinEdge(minEdge))   //找不到最小边
		{
			delete minEdge;
			return false;
		}
		else
		{
			if (ufset.merge(minEdge))     //合并成功，入队
			{
				queue.push(minEdge);
			}
		}
	}
	delete minEdge;
	return true;
}

//以边结点为内容的队列
template<class T, class E>    
class Queue 
{
private:
	EdgeNode<T, E>* _first;
	EdgeNode<T, E>* _last;
public:
	Queue();
	~Queue();
	void push(EdgeNode<T, E>* edge);
	bool pop(EdgeNode<T,E>* & edge);
	void printNode();
	bool isSet()const { return(!(NULL == _first->_next)); };
};

template<class T,class E>
Queue<T, E>::Queue()
{
	try
	{
		_first = new EdgeNode<T, E>;
		_last = new EdgeNode<T, E>;
		_first->_next = _last->_next = NULL;
		_first->_vertex_name_1 = _first->_vertex_name_2 =
		_last->_vertex_name_1 = _last->_vertex_name_2 = ' ';
		_first->_value = _last->_value = 0;
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法正常工作" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}
}

template<class T,class E>
Queue<T, E>::~Queue()
{
	EdgeNode<T, E>* current = _first->_next;
	EdgeNode<T, E>* temp;
	while (current)
	{
		temp = current;
		current = current->_next;
		delete temp;
	}
	delete _first;
	delete _last;
}

template<class T,class E>
void Queue<T, E>::push(EdgeNode<T, E>* edge)
{
	try
	{
		EdgeNode<T, E>* newNode = new EdgeNode<T, E>(edge);
		if (!_first->_next)   //一开始队列为空
		{
			_first->_next = newNode;
			_last->_next = newNode;
		}
		else         //队列不为空
		{
			_last->_next->_next = newNode;
			_last->_next = newNode;
		}
	}
	catch (bad_alloc& ba)
	{
		cerr << "系统发生错误" <<endl<< ba.what() << endl;
		system("pause");
		exit(1);
	}
}

template<class T,class E>
bool Queue<T, E>::pop(EdgeNode<T,E>* & node)
{
	EdgeNode<T, E>* current = _first->_next;
	if (!current)     //队列为空
	{
		return false;
	}
	else if(!current->_next)          //队列只有一个元素
	{
		node->_value = current->_value;
		node->_vertex_name_1 = current->_vertex_name_1;
		node->_vertex_name_2 = current->_vertex_name_2;
		delete current;
		_first->_next = _last->_next = NULL;
		return true;
	}
	else
	{
		node->_value = current->_value;
		node->_vertex_name_1 = current->_vertex_name_1;
		node->_vertex_name_2 = current->_vertex_name_2;
		_first->_next = current->_next;
		delete current;
		return true;
	}
}

template<class T,class E>
void Queue<T, E>::printNode()
{
	EdgeNode<T, E>* node=new EdgeNode<T,E>;
	while (pop(node))
	{
		node->printEdge();
	}
	delete node;
}

//并查集
template<class T,class E>
class UFSet
{
private:
	int max_length;
	int* parent_array;
	T* data_array;
protected:
	bool  getNodePos(T name,int &pos);
public:
	UFSet();
	UFSet(int length,Graph<T,E>*graph);
	~UFSet();
	bool merge(EdgeNode<T,E>*& node);
	bool isConnected()const;          //所有的结点是否均被连接起来0
};

template<class T,class E>
UFSet<T,E>::UFSet()
	:max_length(1)
{
	parent_array = new int[max_length];
	data_array = new int[max_length];
}

template<class T,class E>
UFSet<T,E>::UFSet(int length, Graph<T, E>* graph)
{
	if (length <= 0)
	{
		cerr << "无法创建并查集" << endl;
		system("pause");
		exit(1);
	}
	try
	{
		max_length = length;
		parent_array = new int[length];
		for (int i = 0; i < length; i++)
		{
			parent_array[i] = -1;          //数组的初始化
		}
		data_array = new T[length];
	    VertexNode<T,E>* current = graph->_vertex_first->_next;
		for (int i = 0; i < length; i++)
		{
			data_array[i] = current->_name;
			current = current->_next;
		}
	}
	catch (bad_alloc& ba)
	{
		cerr << "无法创建并查集" << endl << ba.what();
		system("pause");
		exit(1);
	}
}

template<class T,class E>
UFSet<T,E>::~UFSet()
{
	delete []data_array;
	delete []parent_array;
}

template<class T,class E>
bool UFSet<T,E>::getNodePos(T name,int & pos)             
{
	for (int i = 0; i < max_length; i++)
	{
		if (name == data_array[i])
		{
			pos = i;
			return true;
		}
	}
	return false;
}

template<class T,class E>
bool UFSet<T,E>::isConnected()const            
{
	int num = 0;
	for (int i = 0; i < max_length; i++)
	{
		if (parent_array[i] < 0)
		{
			num++;
		}
	}
	if (1 == num)         //所有的结点都连接在一个并查集中
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T,class E>
bool UFSet<T,E>::merge(EdgeNode<T,E>*& node)
{
	int current, first, second;
	if ((getNodePos(node->_vertex_name_1, first)) && (getNodePos(node->_vertex_name_2, second)))       //两个位置都找到了
	{
		if (first >= 0)    //寻找根结点
		{
			while (parent_array[first] >= 0)  
			{
				first = parent_array[first];
			}
		}
		if (second >= 0)  //寻找根结点
		{
			while (parent_array[second] >= 0)
			{
				second = parent_array[second];
			}
		}

		if (first != second)  //根结点不相同
		{

			if (parent_array[first] <= parent_array[second])    //first上的元素比较多,或相等,把second合并到first上
			{
				parent_array[first] += parent_array[second];
				parent_array[second] = first;
			}
			else
			{
				parent_array[second] += parent_array[first];
				parent_array[first] = second;
			}
			return true;
		}
		else         //两个结点是同根的
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

#endif // ! _08_1953608_WUYINGHAO_H_

