#include"01_1953608_WuYinghao_Linux.h"

//此cpp包含main函数与显示界面有关的函数

/*创建初始化界面*/
void initSystem(Linklist& student_list)
{
	int number;
	cout << "考生系统尚未建立，请先建立考生信息系统！" << endl << endl;
	cout << "请输入考生人数： ";
	cin >> number;
	if (number <= 0)
	{
		cerr << "无法建立考生信息系统！！!\n已自动退出系统！！！\n";
		end();
		exit(0);

	}
	cout << endl << "请依次输入考生的考号，姓名，性别，年龄以及报考类别" << endl;
	string exam_number, name, gender, exam_category;
	int age;
	for (int i = 1; i <= number; i++)
	{
		cin >> exam_number >> name >> gender;
		cin >> age;                                             //判断年龄(整型)的输入是否正确
		if (cin.fail())
		{
			cin.clear();
			cout << endl << "年龄输入错误，已自动将年龄设置为18" << endl;
			age = 18;
			cin.get();
		}
		cin >> exam_category;

		student_list.insertNode(i, exam_number, name, gender, age, exam_category);
	}
	student_list.printNode();
}

/*数据处理--插入*/
void insertList(Linklist& student_list)
{
	cout << endl << "下面开始执行插入操作:" << endl;
	cout << "请输入你要插入考生的位置(输入一个大于0的整数):";

	int number;
	cin >> number;
	if (cin.fail())
	{
		cin.clear();
		cerr << endl << "输入错误，请重新输入" << endl;
		cin.get();
		return;
	}
	int length = student_list.getLength();

	if (number <= 0)
	{
		cerr << endl << "不能插入在负数或0位置上" << endl << "插入失败" << endl;
		return;
	}
	else if (number > length + 1)
	{
		cerr << endl << "插入位置大于现有长度" << endl << "插入失败" << endl;
		return;
	}
	else
	{
		cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！！" << endl;

		string exam_number, name, gender, exam_category;
		int age;
		cin >> exam_number >> name >> gender >> age >> exam_category;
		student_list.insertNode(number, exam_number, name, gender, age, exam_category);
		cout << endl << "插入成功！！" << endl;
		student_list.printNode();
	}
}

/*数据处理--删除*/
void deleteList(Linklist& student_list)
{
	cout << endl << "下面开始执行删除操作:" << endl;
	cout << "请输入你要删除考生的位置(输入一个大于0的整数):";
	int number;
	cin >> number;
	if (cin.fail())
	{
		cin.clear();
		cerr << endl << "输入错误，请重新输入" << endl;
		cin.get();
		return;
	}
	int length = student_list.getLength();

	if (number <= 0)
	{
		cerr << endl << "不能删除负数或0位置上的内容" << endl << "删除失败" << endl;
		return;
	}
	else if (number > length)
	{
		cerr << endl << "删除位置大于现有长度" << endl << "删除失败" << endl;
		return;
	}
	else
	{
		student_list.deleteNode(number);
		cout << endl << "删除成功！！" << endl;
		student_list.printNode();
	}
}

/*数据处理--查找*/
void findList(Linklist& student_list)
{
	cout << endl << "下面开始执行查找操作:" << endl;
	cout << "请输入你要查找考生的位置(输入一个大于0的整数):";
	int number;
	cin >> number;

	if (cin.fail())
	{
		cin.clear();
		cerr << endl << "输入错误，请重新输入" << endl;
		cin.get();
		return;
	}
	int length = student_list.getLength();
	if (number <= 0)
	{
		cerr << endl << "不能查找负数或0位置上的内容" << endl << "查询失败" << endl;
		return;
	}
	else if (number > length)
	{
		cerr << endl << "查找位置大于现有长度" << endl << "查询失败" << endl;
		return;
	}
	else
	{
		student_list.findNode(number);
		cout << endl << "查询成功！！" << endl;
	}
}

/*数据处理--修改*/
void changeList(Linklist& student_list)
{
	cout << endl << "下面开始执行修改数据操作:" << endl;
	cout << "请输入你要修改数据的考生的位置(输入一个大于0的整数):";
	int number;
	cin >> number;

	if (cin.fail())
	{
		cin.clear();
		cerr << endl << "输入错误，请重新输入" << endl;
		cin.get();
		return;
	}
	int length = student_list.getLength();
	if (number <= 0)
	{
		cerr << endl << "不能修改负数或0位置上的内容" << endl << "修改失败" << endl;;
		return;
	}
	else if (number > length)
	{
		cerr << endl << "修改位置大于现有长度" << endl << "修改失败" << endl;
		return;
	}
	student_list.changeNode(number);

}

/*数据处理面板*/
void processSytem(Linklist& student_list)
{
	while (true)
	{
		char flag = '1';
		cout << endl << "1--插入，2--删除，3--查找"
			<< endl << "4--修改，5--统计，0--退出" << endl
			<< "请选择您要进行的操作：";
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
			cout << endl << "!!感谢使用本系统!!" << endl;
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
	initSystem(student_list);   //初始化系统
	processSytem(student_list); /*数据处理界面*/
	end();
	return 0;
}