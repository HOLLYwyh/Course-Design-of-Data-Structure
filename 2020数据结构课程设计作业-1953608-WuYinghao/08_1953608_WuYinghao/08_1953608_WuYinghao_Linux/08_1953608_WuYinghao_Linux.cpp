/*
*使用图、并查集、队列来完成此题
*/

#include "08_1953608_WuYinghao_Linux.h"

void printTitle()
{
	cout << "**      电网造价模拟系统      **" << endl
		<< "================================" << endl
		<< "        A--创建电网顶点        " << endl
		<< "        B--添加电网的边        " << endl
		<< "        C--构造最小生成树      " << endl
		<< "        D--显示最小生成树      " << endl
		<< "        E--退出  程序         " << endl
		<< "================================" << endl;
}

void checkInput(int& number)
{
	while (true)
	{
		if (cin.fail())
		{
			cerr << "ERROR.输入失败,请重新输入" << endl;;
			cin.clear();
			cin.ignore();
			cin.get();
			cin >> number;
		}
		else if (number <= 1)
		{
			cerr << "ERROR.输入失败，请输入一个大于1的正整数" << endl;
			cin >> number;
		}
		else
		{
			break;
		}
	}
}

void checkInput(double& number)
{
	while (true)
	{
		if (cin.fail())
		{
			cerr << "ERROR.输入失败,请重新输入" << endl;;
			cin.clear();
			cin.ignore();
			cin.get();
			cin >> number;
		}
		else if (number <= 0)
		{
			cerr << "ERROR.输入失败，请输入一个正整数" << endl;
			cin >> number;
		}
		else
		{
			break;
		}
	}
}

int main()
{
	Queue<char, double> result;            //保存最后的结果的队列
	Graph<char, double> graph;             //图
	printTitle();                       //打印开头
	char flag;                          //用于判断执行哪种操作
	int vertexNum;                      //顶点个数
	bool tag_B = false;                  //判断操作B是否被执行过
	bool tag_C = false;                 //判断操作C是否被执行过
	bool tag_D = false;                 //判断操作D是否被执行过

	cout << "请选择操作: ";
	cin >> flag;
	while (true)
	{
		switch (flag)
		{
		case 'A':                    //建立系统
		{
			if (graph.isSet())       //图已经建立
			{
				cout << "此系统已经建立,无法重新建立" << endl;
				break;
			}
			else
			{
				cout << "请输入顶点的个数: ";
				cin >> vertexNum;
				checkInput(vertexNum);
				cout << "请依次输入各顶点的名称(名称用字符表示):" << endl;
				char vertex;
				for (int i = 0; i < vertexNum; i++)
				{
					cin >> vertex;
					graph.insertVertex(vertex);
				}
				cout << endl;
				break;
			}
		}
		case'B':
		{
			if (!tag_B)                 //B操作没有被执行过
			{
				if (graph.isSet())
				{
					char vertex1 = ' ', vertex2 = ' ';
					double value; int num = 0;
					cout << "当两个顶点中任何一个名称为?(英文)时,输入终止.(注意权值必须为正整数)" << endl;
					while (true)
					{
						cout << "第" << (num + 1) << "条边,请输入两个顶点及边:" << endl;
						cin >> vertex1 >> vertex2 >> value;

						checkInput(value);
						if (('?' == vertex1) || ('?' == vertex2))
						{
							break;
						}

						if (graph.insertEdge(vertex1, vertex2, value))
						{
							num++;
						}
						else
						{
							cout << "无法建立这一条边,请重新输入" << endl;
						}
					}
					tag_B = true;
					break;
				}
				else
				{
					cout << "系统尚未建立完全,请重新输入" << endl;
					break;
				}
			}
			else
			{
				cout << "已经输入过边，不能再次输入" << endl;
				break;
			}
		}
		case'C':
		{
			if (!tag_C)
			{
				if ((graph.isSet()) && (graph.createMinTree(result)))       //已经建立最小生成树
				{
					cout << "已经生成最小生成树" << endl;
					tag_C = true;
					break;
				}
				else
				{
					cout << "系统还没有构造完全,不能生成最小生成树" << endl;
					break;
				}
			}
			else
			{
				cout << "最小生成树已存在,不能重复构造" << endl;
				break;
			}
		}
		case'D':
		{
			if (!tag_D)
			{
				if (graph.isSet() && (result.isSet()))       //已经建立最小生成树,已经建立最短路径
				{
					result.printNode();
					tag_D = true;
					break;
				}
				else
				{
					cout << "系统还没有构造完全,不能生成最小生成树" << endl;
					break;
				}
			}
			else
			{
				cout << "已经输入过最小生成树,不能再次输出" << endl;
				break;
			}
		}
		case 'E':
		{
			cout << "已退出此系统，感谢您的使用" << endl;
			break;
		}
		default:
		{
			cout << "输入有误，请重新输入" << endl;
		}
		}
		if ('E' == flag)
		{
			break;
		}
		else
		{
			cout << "请选择操作: ";
			cin >> flag;
		}
	}

	end();
	return 0;
}