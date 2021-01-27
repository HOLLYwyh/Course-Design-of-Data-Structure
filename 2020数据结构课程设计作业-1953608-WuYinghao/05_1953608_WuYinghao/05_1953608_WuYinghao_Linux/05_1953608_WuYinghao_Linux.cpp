#include"05_1953608_WuYinghao_Linux.h"

int main()
{
	int customer_num;        //顾客的总人数
	int order;               //元素的序号
	int temp;                //用于暂存出队元素的值
	Queue<int> queue_A;
	Queue<int> queue_B;
	Queue<int> queue_result;     //为满足题意，避免最后输出的空字符，现在把结果存在结果队列里面
	cout << "\t\t*******************************************" << endl
		<< "\t\t欢迎办理银行业务，现在有A，B两个业务窗口" << endl << endl
		<< "\t\t请输入当前顾客总数：" << endl
		<< "\t\t";


	//输入检测，保证输入的是正整数

	while (true)
	{
		cin >> customer_num;
		if (cin.fail())
		{
			cerr << "\t\tERROR.输入失败,请重新输入" << endl << "\t\t";
			cin.clear();
			cin.ignore();
			cin.get();
		}
		else if (customer_num <= 0)
		{
			cerr << "\t\tERROR.总人数必须非负数,请重新输入" << endl << "\t\t";
		}
		else if (customer_num > 1000)
		{
			cerr << "\t\tERROR.总人数不能超过1000,请重新输入" << endl << "\t\t";
		}
		else
			break;
	}

	cout << "\t\t请输入" << customer_num << "个顾客的序号:" << endl << "\t\t";
	for (int i = 0; i < customer_num; i++)
	{
		while (true)
		{
			cin >> order;
			if (cin.fail())
			{
				cerr << "\t\tERROR.输入失败,请重新输入" << endl << "\t\t";
				cin.clear();
				cin.ignore();
				cin.get();
			}
			else if (order <= 0)
			{
				cerr << "\t\tERROR.序号必须为正整数,请重新输入" << endl << "\t\t";
			}
			else
				break;
		}
		if (order % 2)     //order是奇数，去A窗口
		{
			queue_A.inQueue(order);
		}
		else

		{
			queue_B.inQueue(order);
		}
	}


	cout << "\t\t业务处理完成的顺序是：";
	while ((!queue_A.isEmpty()) && (!queue_B.isEmpty()))//当两个队列均不为空时
	{
		queue_A.outQueue(temp);
		queue_result.inQueue(temp);
		if (!queue_A.isEmpty())
		{
			queue_A.outQueue(temp);
			queue_result.inQueue(temp);
		}
		queue_B.outQueue(temp);
		queue_result.inQueue(temp);
	}

	if (queue_A.isEmpty())               //队列A空
	{
		int b_length = queue_B.getLength();
		int temp;
		for (int i = 0; i < b_length; i++)
		{
			queue_B.outQueue(temp);
			queue_result.inQueue(temp);
		}
	}
	if (queue_B.isEmpty())             //队列B空
	{
		int a_length = queue_A.getLength();
		int temp;
		for (int i = 0; i < a_length; i++)
		{
			queue_A.outQueue(temp);
			queue_result.inQueue(temp);
		}
	}

	for (int i = 0; i < customer_num; i++)    //数据的输出
	{
		queue_result.outQueue(temp);
		if (queue_result.isEmpty())
			cout << temp;
		else
			cout << temp << ' ';
	}

	cout << endl << "\t\t*******************************************" << endl;


	end();
	return 0;
}