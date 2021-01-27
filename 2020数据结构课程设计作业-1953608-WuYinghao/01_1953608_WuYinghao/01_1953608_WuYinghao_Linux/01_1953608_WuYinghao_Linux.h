#pragma once
//这是一个头文件，用来存储一个学生类、相关成员函数以及链表类的定义
#ifndef _STUDENT_LINKLIST_
#define _STUDENT_LINKLIST_
#include<iostream>
#include<string>

using namespace std;

void end()
{
	cout << "press a number to end the system" << endl;
	cin.get();
	cin.get();
}
class Student
{
private:

	string _exam_number;                    //考号
	string _name;                           //姓名
	string _gender;                         //性别
	int    _age;                            //年龄
	string _exam_category;                  //报考类别
	Student* link;                          //指向下一个节点的指针

public:

	Student();                             //默认构造函数
	Student(string exam_number, string name, string gender, int age, string exam_category);//通过相关信息建立对象
	~Student();                            //析构函数

	void print();                          //输出学生的相关信息
	string getExamNumber()const;           //返回学生的考号
	string getName() const;               //返回学生的姓名
	string getGender()const;              //返回学生的性别
	int getAge()const;                    //返回学生年龄
	string getExamCategory()const;        //返回学生的报考类别

	void setInformation(int i);             //修改学生的信息

	friend class Linklist;                             //友元类
};

//以下为类成员函数的定义

Student::Student()
{
	_exam_number = "0000";
	_name = "None";
	_gender = "None";
	_age = 0;
	_exam_category = "None";
}

Student::Student(string exam_number, string name, string gender, int age, string exam_category)
	:_exam_number(exam_number), _name(name), _gender(gender),
	_age(age), _exam_category(exam_category)
{
}

Student::~Student()
{

}

void Student::print()
{
	cout << "考号:" << _exam_number << "\t\t姓名:" << _name << "\t\t性别:" << _gender
		<< "\t\t年龄:" << _age << "\t\t报考类别:" << _exam_category << endl;
}

string Student::getExamNumber()const
{
	return _exam_number;
}

string Student::getName()const
{
	return _name;
}

string Student::getGender()const
{
	return _gender;
}

int Student::getAge()const
{
	return _age;
}

string Student::getExamCategory()const
{
	return _exam_category;
}

void Student::setInformation(int i)                //设置学生的信息
{
	switch (i)
	{
	case 0:
	{
		cout << "退出修改" << endl;
		break;
	}
	case 1:
	{
		string number;
		cout << "这是旧的考号： " << getExamNumber() << endl
			<< "请输入新的考号： ";
		cin >> number;
		_exam_number = number;
		cout << endl << "修改考号成功！ " << endl << "这是新的考号： " << getExamNumber() << endl << endl;
		break;
	}
	case 2:
	{
		string name;
		cout << "这是旧的姓名： " << getName() << endl
			<< "请输入新的姓名： ";
		cin >> name;
		_name = name;
		cout << endl << "修改姓名成功！ " << endl << "这是新的姓名： " << getName() << endl << endl;
		break;
	}
	case 3:
	{
		string gender;
		cout << "这是旧的性别： " << getGender() << endl
			<< "请输入新的性别： ";
		cin >> gender;
		_gender = gender;
		cout << endl << "修改性别成功！ " << endl << "这是新的性别： " << getGender() << endl << endl;
		break;
	}
	case 4:
	{
		int age;
		cout << "这是旧的年龄： " << getAge() << endl
			<< "请输入新的年龄： ";
		cin >> age;
		if (cin.fail())
		{
			cerr << endl << "输入有误,请重新输入" << endl;
			break;
		}
		_age = age;
		cout << endl << "修改年龄成功！ " << endl << "这是新的年龄： " << getAge() << endl << endl;
		break;
	}
	case 5:
	{
		string category;
		cout << "这是旧的考试类别： " << getExamCategory() << endl
			<< "请输入新的考试类别： ";
		cin >> category;
		_exam_category = category;
		cout << endl << "修改考试类别成功！ " << endl << "这是新的考试类别： " << getExamCategory() << endl << endl;
		break;
	}
	default:
	{
		cerr << "不能修改这个位置！！！！！" << endl;
		break;
	}
	}
}


//以下为链表的定义

class Linklist
{
private:
	Student* first;                                        //表头指针
public:
	Linklist();                                           //创建一个带有附加头的链表
	~Linklist();                                          //析构函数

	void insertNode(int i, string exam_number, string name, string gender, int age, string exam_category);    //链表的插入
	void deleteNode(int i);							//删除节点
	void changeNode(int i);							//修改节点
	void findNode(int i);							//查找节点
	void printNode()const;								//打印所有节点
	int getLength()const;                           //获得节点长度
};

Linklist::Linklist()
{
	first = new Student;
	Student* addition = new Student;     //附加头
	if (NULL == addition || NULL == first)
	{
		cerr << "创建链表失败";
		end();
		exit(1);
	}
	else
	{
		this->first->link = addition;
		addition->link = NULL;
	}
}

Linklist::~Linklist()
{
	Student* current = this->first;
	while (current->link != NULL)
	{
		Student* temp = current;
		current = current->link;
		delete temp;
	}
	delete current;
}

int Linklist::getLength() const
{
	Student* current = this->first;
	int count = -1;   //因为有附加头
	while (current->link != NULL)
	{
		current = current->link;
		count++;
	}
	return count;
}


void Linklist::insertNode(int i, string exam_number, string name, string gender, int age, string exam_category)
{
	Student* newNode = new Student(exam_number, name, gender, age, exam_category);
	if (NULL == newNode)
	{
		cerr << "创建新节点失败";
		end();
		exit(1);
	}
	else
	{
		Student* current = this->first;
		for (; i > 0; i--)
		{
			current = current->link;
		}
		newNode->link = current->link;
		current->link = newNode;
	}
}


void Linklist::deleteNode(int i)
{
	Student* current = this->first;
	for (; i > 0; i--)
	{
		current = current->link;
	}
	Student* temp = current;
	current = current->link;
	temp->link = current->link;
	delete current;
}

void Linklist::changeNode(int i)
{
	Student* current = this->first;
	for (; i >= 0; i--)
	{
		current = current->link;
	}
	int choose = 0;
	while (true)
	{
		cout << endl << "请选择你需要修改的内容\n1--考号\n2--姓名\n3--性别\n4--年龄\n"
			<< "5--报考类别\n0--退出修改\n";
		cin >> choose;
		if (cin.fail())
		{
			cin.clear();
			cerr << endl << "输入错误，请重新输入" << endl;
			cin.get();
			continue;
		}
		current->setInformation(choose);
		current->print();
		if (0 == choose)
		{
			break;
		}
		cout << endl << "修改成功！！" << endl;
	}
}

void Linklist::findNode(int i)
{
	Student* current = this->first;
	for (; i >= 0; i--)
	{
		current = current->link;
	}
	current->print();

}

void Linklist::printNode()const//打印所有节点
{
	int length = this->getLength();
	int number = 1;
	cout << endl << "总计:" << length << "人" << endl;

	Student* current = this->first->link;
	while (current->link != NULL)
	{
		current = current->link;
		cout << "序号:" << number << "\t\t";
		current->print();
		number++;
	}
}

#endif // !_STUDENT_H_

