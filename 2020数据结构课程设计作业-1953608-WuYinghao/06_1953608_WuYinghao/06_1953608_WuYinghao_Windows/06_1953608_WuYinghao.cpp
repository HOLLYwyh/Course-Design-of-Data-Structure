#include"06_1953608_WuYinghao.h"

//��ӡ��ʼ������
void printsystemTitle()
{
	cout << endl << endl;
	cout << "==================================" << endl;
	cout << "**\t���׹���ϵͳ    \t**" << endl;
	cout << "==================================" << endl;
	cout << "**     ��ѡ��Ҫִ�еĲ��� :\t**" << endl;
	cout << "**\tA --- ���Ƽ���\t\t**" << endl;
	cout << "**\tB --- ��Ӽ�ͥ��Ա\t**" << endl;
	cout << "**\tC --- �鿴��ͥ��Ա��Ϣ  **" << endl;
	cout << "**\tD --- ��ɢ�ֲ���ͥ\t**" << endl;
	cout << "**\tE --- ���ļ�ͥ��Ա����\t**" << endl;
	cout << "**\tF --- �˳�����    \t**" << endl;
	cout << "==================================" << endl;
}

//���Ƽ���  'A'����
template<class T>
void createFamily(FamilyTree<T>& tree)
{
	T target;    //��Ҫ������ͥ���˵�����
	T name;      //��Ů������
	bool tag = false;
	int num;     //��Ů����
	Stack<T> stack;
	cout << "������Ҫ������ͥ���˵�������";
	cin >> target;
	
	if (NULL== tree.getNodeByName(target,tree.getFirstNode(),tag))
	{
		cerr << "***��ѯ������Ϊ" << target << "����" << endl << endl;
		return;
	}
	cout << "������" << target << "�Ķ�Ů������";
	cin >> num;
	
	while ((num <= 0) || (cin.fail()))
	{
		if( (num <= 0)&&(!cin.fail()))    //˵���������һ������
		{
			cerr << "ERROR,������һ��������" << endl;
			cin >> num;
		}
		if (cin.fail())
		{
			cerr << "ERROR.����ʧ��,����������" << endl;;
			cin.clear();
			cin.ignore();
			cin >> num;
		}
	}

	cout << "����������" << target << "�Ķ�Ů��������";
	for (int i = 0; i < num; i++)
	{
		cin >> name;
		tree.insertNode(target, name, eChild);//Ĭ�Ͻ�����Ů
		stack.push(name);
	}
	
	cout << target << "�ĵ�һ��������: " << endl;
	for (int i = 0; i < num; i++)
	{
		stack.pop();
	}
	cout << endl;
}

//��Ӽ�ͥ��Ա  'B'����
template<class T>
void addFamilyNumber(FamilyTree<T>& tree)
{

	T target;    //��Ҫ������ͥ���˵�����
	T name;      //��Ů������
	int num;     //��Ů����
	int flag;    //�ж�������ֵܻ�����������Ů
	bool tag = false;
	Stack<T> stack;
	cout << "������Ҫ��Ӽ�ͥ��Ա���˵�������";
	cin >> target;

	if (tree.getNodeByName(target, tree.getFirstNode(),tag) == NULL)
	{
		cerr << "***��ѯ������Ϊ" << target << "����" << endl<<endl;
		return;
	}
	cout << "������Ҫ��ӵ�����:1-��Ů 2-�ֵ�"<<endl;
	cin >> flag;

	while ((flag <= 0) ||(flag>=3)|| (cin.fail()))
	{
		if (((flag <= 0)||(flag>=3)) && (!cin.fail()) )       //˵���������һ������
		{
			cerr << "ERROR,������1��2!" << endl;
				cin >> flag;
		}
		if (cin.fail())
		{
			cerr << "ERROR.����ʧ��,����������" << endl;;
				cin.clear();
				cin.ignore();
				cin >> flag;
		}
	}

	cout << "������Ҫ��ӳ�Ա�ĸ�����";
	cin >> num;
	while ((num <= 0) || (cin.fail()))
	{
		if ((num <= 0) && (!cin.fail())  )      //˵���������һ������
		{
			cerr << "ERROR,������һ��������" << endl;
				cin >> num;
		}
		if (cin.fail())
		{
			cerr << "ERROR.����ʧ��,����������" << endl;;
				cin.clear();
				cin.ignore();
				cin >> num;
		}
	}

	(flag==1)?(cout << "����������" << target << "�Ķ�Ů��������"):
		(cout<<"����������"<<target<<"���ֵܵ�����");
	for (int i = 0; i < num; i++)
	{
		cin >> name;
		tree.insertNode(target, name, (1 == flag) ? eChild : eSibling);//Ĭ�Ͻ�����Ů
		stack.push(name);
	}

	cout << target << "����ӵĳ�Ա��: "<<endl<<endl;
	for (int i = 0; i < num; i++)
	{
		stack.pop();
	}
	cout << endl;
}

//�鿴��ͥ��Ա��Ϣ  'C'����
template<class T>
void checkFamilyInformation(FamilyTree<T>& tree)     //ֻ�ܲ鿴��ǰ�ڵ���ֵܺͶ�Ů
{
	T name;      //��Ҫ��ѯ������
	bool tag = false;
	cout << "������Ҫ��ѯ���˵�������";
	cin >> name;
	FamilyNode<T>* result = tree.getNodeByName(name, tree.getFirstNode(),tag);

	if (NULL == result)
	{
		cerr << "***��ѯ������Ϊ" << name << "����" << endl << endl;
		return;
	}
	else
	{
		tree.printNode(result);
	}
}

//��ɢ���ּ�ͥ��Ա   'D'����
template<class T>
void deleteFamily(FamilyTree<T>& tree)
{
	T name;             //��Ҫɾ�����˵�����
	bool tag = false;
	cout << "������Ҫɾ�����˵�����: ";
	cin >> name;
	FamilyNode<T>* result = tree.getNodeByName(name, tree.getFirstNode(),tag);
	tree.deleteNode(result);
}

//���ļ�ͥ��Ա����Ϣ    'E'����
template<class T>
void changeMemberInformation(FamilyTree<T>& tree)
{
	T target, name;      //��Ҫ�޸ĵ������Լ�Ŀ�������
	cout << "������Ҫ�޸���Ϣ���˵�����: ";
	cin >> target;
	cout << endl << "�������µ�����:";
	cin >> name;
	tree.changeNode(target, name);
	cout << "�ѳɹ��ؽ�" << target << "�������޸�Ϊ" << name << endl;
}

int main()
{
	printsystemTitle();       //��ӡ��ͷ

	FamilyTree<string> family_tree;
	char flag;
	string ancestor; //���ȵ�����
	
	//��������
	cout << endl << endl << "��δ��������"<<"���Ƚ������ף�"<<endl;
	cout << "���������ȵ�����: ";
	cin >> ancestor;
	cout << endl;
	family_tree.insertRoot(ancestor);
	cout << "�˼��׵�������:" << ancestor << endl;

	//�Լ���ִ�в���
	cout << "������Ҫִ�еĲ���:";
	cin >> flag;
	while (cin.fail())
	{
		cerr << "ERROR.����ʧ��,����������" << endl;;
		cin.clear();
		cin.ignore();
		cin >> flag;
	}

	while (flag != 'F')
	{
		switch (flag)
		{
		  case'A':
		  {
			  createFamily(family_tree);  //���Ƽ���
			  break;
		  }
		  case'B':
		  {
			  addFamilyNumber(family_tree);
			  break;
		  }
		  case'C':
		  {
			  checkFamilyInformation(family_tree);
			  break;
		  }
		  case'D':
		  {
			  deleteFamily(family_tree);
			  break;
		  }
		  case'E':
		  {
			  changeMemberInformation(family_tree);
			  break;
		  }
		  default:
		  {
			cerr << "���������������ȷ�Ĳ������ţ���" << endl;
			break;
		  }
		}

		cout << "������Ҫִ�еĲ���:";
		cin >> flag;
		while (cin.fail())
		{
			cerr << "ERROR.����ʧ��,����������" << endl;;
			cin.clear();
			cin.ignore();
			cin >> flag;
		}
	}

	//ϵͳ���˳�
	cout <<endl<<endl<< "���˳��Լ��׵��޸�" << endl << "��л����ʹ��" << endl << endl;

	cout << endl;
	system("pause");
	return 0;
}