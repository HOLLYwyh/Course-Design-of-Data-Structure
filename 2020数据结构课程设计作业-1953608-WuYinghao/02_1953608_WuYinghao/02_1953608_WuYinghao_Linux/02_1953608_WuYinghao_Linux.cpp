/*
* 此文件用于存储main()函数以及其他重要的函数
* 本题使用双向链表
*/
#include"02_1953608_WuYinghao_Linux.h"


int main()
{
	linkList<unsigned int>lists[2];

	cout <<endl<< "**************************************************************************" << endl;
	cout << "\t\t请输入两个非降序序列（输入-1以结束一个序列）" << endl;
	cout << "**************************************************************************" << endl;

	for (int i = 0; i <= 1; i++)                 //数据的输入
	{
		cout << endl << "请输入第" << i + 1 << "个序列（非降序排列）" << endl;
		int data = 0;
		cin >> data;
		while (data != -1)
		{
			if (cin.fail())
			{
				cerr << "ERROR.输入失败,请重新输入" << endl;;
				cin.clear();
				cin.ignore();
				cin.get();
			}
			else if (data <= 0)
			{
				cerr << "ERROR.输入失败，请重新输入" << endl;
			}
			else if (static_cast<unsigned int>(data) < lists[i].getFinalData())
			{
				cerr << "ERROR.输入失败.输入的数必须构成非降序排列，请重新输入" << endl;
			}
			else if (static_cast<unsigned int>(data) >= lists[i].getFinalData())
			{
				lists[i].append(data);
			}
			cin >> data;
		}
		cout << "序列" << i + 1 << ":" << endl;
		lists[i].printResult();
	}

	/*做交集*/
	lists[0].intersect(lists[1]);
	cout << endl << "结果:" << endl;
	lists[0].printResult();

	cout << endl << "**************************************************************************" << endl;
	cout << "\t\t\t操作结束，欢迎使用" << endl;
	cout << "**************************************************************************" << endl;

	end();

	return 0;
}