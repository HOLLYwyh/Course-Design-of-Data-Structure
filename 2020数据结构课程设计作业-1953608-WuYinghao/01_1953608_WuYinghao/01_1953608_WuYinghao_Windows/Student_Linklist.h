#pragma once
//����һ��ͷ�ļ��������洢һ��ѧ���ࡢ��س�Ա�����Լ�������Ķ���
#ifndef _STUDENT_LINKLIST_
#define _STUDENT_LINKLIST_
#include<iostream>
#include<string>

using namespace std;
class Student
{
private:

	string _exam_number;                    //����
	string _name;                           //����
	string _gender;                         //�Ա�
	int    _age;                            //����
	string _exam_category;                  //�������
	Student* link;                          //ָ����һ���ڵ��ָ��

public:

	Student();                             //Ĭ�Ϲ��캯��
	Student(string exam_number, string name, string gender, int age, string exam_category);//ͨ�������Ϣ��������
	~Student();                            //��������

	void print();                          //���ѧ���������Ϣ
	string getExamNumber()const;           //����ѧ���Ŀ���
	string getName() const;               //����ѧ��������
	string getGender()const;              //����ѧ�����Ա�
	int getAge()const;                    //����ѧ������
	string getExamCategory()const;        //����ѧ���ı������

	void setInformation(int i);             //�޸�ѧ������Ϣ

	friend class Linklist;                             //��Ԫ��
};

//����Ϊ���Ա�����Ķ���

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
	cout << "����:" << _exam_number << "\t\t����:" << _name << "\t\t�Ա�:" << _gender
		<< "\t\t����:" << _age << "\t\t�������:" << _exam_category << endl;
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

void Student::setInformation(int i)                //����ѧ������Ϣ
{
	switch (i)
	{
	  case 0:
	   {
	     cout << "�˳��޸�"<<endl;
	     break; 
	   }
	  case 1:
	  {
		  string number;
		  cout << "���ǾɵĿ��ţ� " << getExamNumber() << endl
			  << "�������µĿ��ţ� ";
		  cin >> number;
		  _exam_number = number;
		  cout << endl<<"�޸Ŀ��ųɹ��� " << endl << "�����µĿ��ţ� " << getExamNumber() << endl << endl;
		  break;
	  }
	  case 2:
	  {
		  string name;
		  cout << "���Ǿɵ������� " << getName() << endl
			  << "�������µ������� ";
		  cin >> name;
		  _name= name;
		  cout << endl << "�޸������ɹ��� " << endl << "�����µ������� " << getName() << endl << endl;
		  break;
	  }
	  case 3:
	  {
		  string gender;
		  cout << "���Ǿɵ��Ա� " << getGender()<< endl
			  << "�������µ��Ա� ";
		  cin >> gender;
		  _gender = gender;
		  cout << endl << "�޸��Ա�ɹ��� " << endl << "�����µ��Ա� " << getGender() << endl << endl;
		  break;
	  }
	  case 4:
	  {
		  int age;
		  cout << "���Ǿɵ����䣺 " << getAge() << endl
			  << "�������µ����䣺 ";
		  cin >> age;
		  if (cin.fail())
		  {
			  cerr << endl << "��������,����������" << endl;
			  break;
		  }
		  _age = age;
		  cout << endl << "�޸�����ɹ��� " << endl << "�����µ����䣺 " << getAge() << endl << endl;
		  break;
	  }
	  case 5:
	  {
		  string category;
		  cout << "���ǾɵĿ������ " << getExamCategory() << endl
			  << "�������µĿ������ ";
		  cin >> category;
		  _exam_category = category;
		  cout << endl << "�޸Ŀ������ɹ��� " << endl << "�����µĿ������ " << getExamCategory() << endl << endl;
		  break;
	  }
	  default:
	  {
		  cerr << "�����޸����λ�ã���������"<<endl;
		  break;
	  }
	}
}


//����Ϊ����Ķ���

class Linklist
{
private:
	Student* first;                                        //��ͷָ��
public:
	Linklist();                                           //����һ�����и���ͷ������
	~Linklist();                                          //��������

	void insertNode(int i, string exam_number, string name, string gender, int age, string exam_category);    //����Ĳ���
	void deleteNode(int i);							//ɾ���ڵ�
	void changeNode(int i);							//�޸Ľڵ�
	void findNode(int i);							//���ҽڵ�
	void printNode()const;								//��ӡ���нڵ�
	int getLength()const;                           //��ýڵ㳤��
};

Linklist::Linklist()
{
	first = new Student;
	Student* addition = new Student;     //����ͷ
	if (NULL == addition||NULL==first)
	{
		cerr << "��������ʧ��";
		system("pause");
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
	int count = -1;   //��Ϊ�и���ͷ
	while (current->link != NULL)
	{
		current = current->link;
		count++;
	}
	return count;
}


void Linklist:: insertNode(int i, string exam_number, string name, string gender, int age, string exam_category)   
{
	Student* newNode = new Student(exam_number,name,gender,age,exam_category);
	if (NULL == newNode)
	{
		cerr << "�����½ڵ�ʧ��";
		system("pause");
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
		cout << endl << "��ѡ������Ҫ�޸ĵ�����\n1--����\n2--����\n3--�Ա�\n4--����\n"
			<< "5--�������\n0--�˳��޸�\n";
		cin >> choose;
		if (cin.fail())
		{
			cin.clear();
			cerr << endl << "�����������������" << endl;
			cin.get();
			continue;
		}
		current->setInformation(choose);
		current->print();
		if (0 == choose)
		{
			break;
		}
		cout << endl << "�޸ĳɹ�����" << endl;
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

void Linklist::printNode()const//��ӡ���нڵ�
{
	int length = this->getLength();
	int number = 1;
	cout <<endl<< "�ܼ�:" << length << "��" << endl;
	
	Student* current = this->first->link;
	while (current->link != NULL)
	{
		current = current->link;
		cout << "���:" << number << "\t\t";
		current->print();
		number++;
	}
}

#endif // !_STUDENT_H_

