#include"Student_Linklist.h"

//��cpp����main��������ʾ�����йصĺ���

/*������ʼ������*/
void initSystem(Linklist& student_list)
{
	int number;
	cout << "����ϵͳ��δ���������Ƚ���������Ϣϵͳ��" << endl << endl;
	cout << "�����뿼�������� ";
	cin >> number;
	if (number <= 0)
	{
		cerr << "�޷�����������Ϣϵͳ����!\n���Զ��˳�ϵͳ������\n";
		system("pause");
		exit(0);
		
	}
	cout << endl << "���������뿼���Ŀ��ţ��������Ա������Լ��������" << endl;
	string exam_number, name, gender, exam_category;
	int age;
	for (int i = 1; i <= number; i++)
	{
		cin >> exam_number >> name >> gender;
		cin >> age;                                             //�ж�����(����)�������Ƿ���ȷ
		if (cin.fail())
		{
			cin.clear();
			cout <<endl<< "��������������Զ�����������Ϊ18"<<endl;
			age = 18;
			cin.get();
		}
		cin>> exam_category;

		student_list.insertNode(i, exam_number, name, gender, age, exam_category);
	}
	student_list.printNode();
}

/*���ݴ���--����*/
void insertList(Linklist& student_list)
{
	cout << endl << "���濪ʼִ�в������:" << endl;
	cout << "��������Ҫ���뿼����λ��(����һ������0������):";

	int number;
	cin >> number;
	if (cin.fail())
	{
		cin.clear();
		cerr<< endl << "�����������������" << endl;
		cin.get();
		return;
	}
	int length = student_list.getLength();

	if (number <= 0)
	{
		cerr << endl << "���ܲ����ڸ�����0λ����" << endl << "����ʧ��" << endl;
		return;
	}
	else if (number > length + 1)
	{
		cerr << endl << "����λ�ô������г���" << endl << "����ʧ��" << endl;
		return;
	}
	else
	{
		cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估������𣡣�" << endl;

		string exam_number, name, gender, exam_category;
		int age;
		cin >> exam_number >> name >> gender >> age >> exam_category;
		student_list.insertNode(number, exam_number, name, gender, age, exam_category);
		cout << endl << "����ɹ�����" << endl;
		student_list.printNode();
	}
}

/*���ݴ���--ɾ��*/
void deleteList(Linklist& student_list)
{
	cout << endl << "���濪ʼִ��ɾ������:" << endl;
	cout << "��������Ҫɾ��������λ��(����һ������0������):";
	int number;
	cin >> number;
	if (cin.fail())
	{
		cin.clear();
		cerr << endl << "�����������������" << endl;
		cin.get();
		return;
	}
	int length = student_list.getLength();

	if (number<= 0)
	{
		cerr << endl << "����ɾ��������0λ���ϵ�����"<<endl<<"ɾ��ʧ��"<<endl;
		return;
	}
	else if (number> length)
	{
		cerr << endl << "ɾ��λ�ô������г���"<<endl<<"ɾ��ʧ��"<<endl;
		return;
	}
	else
	{
		student_list.deleteNode(number);
		cout << endl << "ɾ���ɹ�����" << endl;
		student_list.printNode();
	}
}

/*���ݴ���--����*/
void findList(Linklist& student_list)
{
	cout << endl << "���濪ʼִ�в��Ҳ���:" << endl;
	cout << "��������Ҫ���ҿ�����λ��(����һ������0������):";
	int number;
	cin >> number;

	if (cin.fail())
	{
		cin.clear();
		cerr << endl << "�����������������" << endl;
		cin.get();
		return;
	}
	int length = student_list.getLength();
	if (number <= 0)
	{
		cerr << endl<<"���ܲ��Ҹ�����0λ���ϵ�����" << endl << "��ѯʧ��" << endl;
		return;
	}
	else if (number> length)
	{
		cerr << endl << "����λ�ô������г���" << endl << "��ѯʧ��" << endl;
		return;
	}
	else
	{
		student_list.findNode(number);
		cout << endl << "��ѯ�ɹ�����" << endl;
	}
}

/*���ݴ���--�޸�*/
void changeList(Linklist& student_list)
{
	cout << endl << "���濪ʼִ���޸����ݲ���:" << endl;
	cout << "��������Ҫ�޸����ݵĿ�����λ��(����һ������0������):";
	int number;
	cin >> number;

	if (cin.fail())
	{
		cin.clear();
		cerr << endl << "�����������������" << endl;
		cin.get();
		return;
	}
	int length =student_list.getLength();
	if (number <= 0)
	{
		cerr << endl<<"�����޸ĸ�����0λ���ϵ�����" << endl << "�޸�ʧ��" << endl;;
		return;
	}
	else if (number> length)
	{
		cerr << endl<< "�޸�λ�ô������г���" << endl << "�޸�ʧ��" << endl;
		return;
	}
	student_list.changeNode(number);
	
}

/*���ݴ������*/
void processSytem(Linklist& student_list)
{
	while (true)
	{
		char flag = '1';
		cout<< endl << "1--���룬2--ɾ����3--����"
			<< endl << "4--�޸ģ�5--ͳ�ƣ�0--�˳�" << endl
		    << "��ѡ����Ҫ���еĲ�����";
		cin >> flag;
		switch (flag)
		{
		case '1':
		{
			insertList(student_list);
			break;
		}
		case '2':
		{
			deleteList(student_list);
			break;
		}
		case '3':
		{
			findList(student_list);
			break;
		}
		case'4':
		{
			changeList(student_list);
			break;
		}
		case'5':
		{
			student_list.printNode();
			break;
		}
		case'0':
		{
			cout << endl << "!!��лʹ�ñ�ϵͳ!!" << endl;
			break;
		}
		default:
			break;
		}
		if ('0' == flag)
			break;
	}

}


int main()
{

	Linklist student_list;
	initSystem(student_list);   //��ʼ��ϵͳ
	processSytem(student_list); /*���ݴ������*/
	system("pause");
	return 0;
}