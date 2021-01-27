#include"06_1953608_WuYinghao_Linux.h"

//打印初始化界面
void printsystemTitle()
{
	cout << endl << endl;
	cout << "==================================" << endl;
	cout << "**\t家谱管理系统    \t**" << endl;
	cout << "==================================" << endl;
	cout << "**     请选择要执行的操作 :\t**" << endl;
	cout << "**\tA --- 完善家谱\t\t**" << endl;
	cout << "**\tB --- 添加家庭成员\t**" << endl;
	cout << "**\tC --- 查看家庭成员信息  **" << endl;
	cout << "**\tD --- 解散局部家庭\t**" << endl;
	cout << "**\tE --- 更改家庭成员姓名\t**" << endl;
	cout << "**\tF --- 退出程序    \t**" << endl;
	cout << "==================================" << endl;
}

//完善家谱  'A'操作
template<class T>
void createFamily(FamilyTree<T>& tree)
{
	T target;    //需要建立家庭的人的姓名
	T name;      //子女的姓名
	bool tag = false;
	int num;     //子女人数
	Stack<T> stack;
	cout << "请输入要建立家庭的人的姓名：";
	cin >> target;

	if (NULL == tree.getNodeByName(target, tree.getFirstNode(), tag))
	{
		cerr << "***查询不到名为" << target << "的人" << endl << endl;
		return;
	}
	cout << "请输入" << target << "的儿女人数：";
	cin >> num;

	while ((num <= 0) || (cin.fail()))
	{
		if ((num <= 0) && (!cin.fail()))    //说明输入的是一个整数
		{
			cerr << "ERROR,请输入一个正整数" << endl;
			cin >> num;
		}
		if (cin.fail())
		{
			cerr << "ERROR.输入失败,请重新输入" << endl;;
			cin.clear();
			cin.ignore();
			cin >> num;
		}
	}

	cout << "请依次输入" << target << "的儿女的姓名：";
	for (int i = 0; i < num; i++)
	{
		cin >> name;
		tree.insertNode(target, name, eChild);//默认建立子女
		stack.push(name);
	}

	cout << target << "的第一代子孙是: " << endl;
	for (int i = 0; i < num; i++)
	{
		stack.pop();
	}
	cout << endl;
}

//添加家庭成员  'B'操作
template<class T>
void addFamilyNumber(FamilyTree<T>& tree)
{

	T target;    //需要建立家庭的人的姓名
	T name;      //子女的姓名
	int num;     //子女人数
	int flag;    //判断是添加兄弟还是添加添加子女
	bool tag = false;
	Stack<T> stack;
	cout << "请输入要添加家庭成员的人的姓名：";
	cin >> target;

	if (tree.getNodeByName(target, tree.getFirstNode(), tag) == NULL)
	{
		cerr << "***查询不到名为" << target << "的人" << endl << endl;
		return;
	}
	cout << "请输入要添加的类型:1-子女 2-兄弟" << endl;
	cin >> flag;

	while ((flag <= 0) || (flag >= 3) || (cin.fail()))
	{
		if (((flag <= 0) || (flag >= 3)) && (!cin.fail()))       //说明输入的是一个整数
		{
			cerr << "ERROR,请输入1或2!" << endl;
			cin >> flag;
		}
		if (cin.fail())
		{
			cerr << "ERROR.输入失败,请重新输入" << endl;;
			cin.clear();
			cin.ignore();
			cin >> flag;
		}
	}

	cout << "请输入要添加成员的个数：";
	cin >> num;
	while ((num <= 0) || (cin.fail()))
	{
		if ((num <= 0) && (!cin.fail()))      //说明输入的是一个整数
		{
			cerr << "ERROR,请输入一个正整数" << endl;
			cin >> num;
		}
		if (cin.fail())
		{
			cerr << "ERROR.输入失败,请重新输入" << endl;;
			cin.clear();
			cin.ignore();
			cin >> num;
		}
	}

	(flag == 1) ? (cout << "请依次输入" << target << "的儿女的姓名：") :
		(cout << "请依次输入" << target << "的兄弟的姓名");
	for (int i = 0; i < num; i++)
	{
		cin >> name;
		tree.insertNode(target, name, (1 == flag) ? eChild : eSibling);//默认建立子女
		stack.push(name);
	}

	cout << target << "新添加的成员是: " << endl << endl;
	for (int i = 0; i < num; i++)
	{
		stack.pop();
	}
	cout << endl;
}

//查看家庭成员信息  'C'操作
template<class T>
void checkFamilyInformation(FamilyTree<T>& tree)     //只能查看当前节点的兄弟和儿女
{
	T name;      //需要查询的名字
	bool tag = false;
	cout << "请输入要查询的人的姓名：";
	cin >> name;
	FamilyNode<T>* result = tree.getNodeByName(name, tree.getFirstNode(), tag);

	if (NULL == result)
	{
		cerr << "***查询不到名为" << name << "的人" << endl << endl;
		return;
	}
	else
	{
		tree.printNode(result);
	}
}

//解散部分家庭成员   'D'操作
template<class T>
void deleteFamily(FamilyTree<T>& tree)
{
	T name;             //需要删除的人的姓名
	bool tag = false;
	cout << "请输入要删除的人的姓名: ";
	cin >> name;
	FamilyNode<T>* result = tree.getNodeByName(name, tree.getFirstNode(), tag);
	tree.deleteNode(result);
}

//更改家庭成员的信息    'E'操作
template<class T>
void changeMemberInformation(FamilyTree<T>& tree)
{
	T target, name;      //需要修改的名字以及目标的名字
	cout << "请输入要修改信息的人的姓名: ";
	cin >> target;
	cout << endl << "请输入新的姓名:";
	cin >> name;
	tree.changeNode(target, name);
	cout << "已成功地将" << target << "的名称修改为" << name << endl;
}

int main()
{
	printsystemTitle();       //打印表头

	FamilyTree<string> family_tree;
	char flag;
	string ancestor; //祖先的名称

	//创建祖先
	cout << endl << endl << "尚未建立家谱" << "请先建立家谱！" << endl;
	cout << "请输入祖先的姓名: ";
	cin >> ancestor;
	cout << endl;
	family_tree.insertRoot(ancestor);
	cout << "此家谱的祖先是:" << ancestor << endl;

	//对家谱执行操作
	cout << "请输入要执行的操作:";
	cin >> flag;
	while (cin.fail())
	{
		cerr << "ERROR.输入失败,请重新输入" << endl;;
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
			createFamily(family_tree);  //完善家谱
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
			cerr << "输入错误，请输入正确的操作代号！！" << endl;
			break;
		}
		}

		cout << "请输入要执行的操作:";
		cin >> flag;
		while (cin.fail())
		{
			cerr << "ERROR.输入失败,请重新输入" << endl;;
			cin.clear();
			cin.ignore();
			cin >> flag;
		}
	}

	//系统的退出
	cout << endl << endl << "已退出对家谱的修改" << endl << "感谢您的使用" << endl << endl;

	cout << endl;
	end();
	return 0;
}