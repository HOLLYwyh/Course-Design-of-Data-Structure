/*
*ʹ��ͼ�����鼯����������ɴ���
*/

#include "08_1953608_WuYinghao.h"

void printTitle()
{
	cout << "**      �������ģ��ϵͳ      **" << endl
		<< "================================" << endl
		<< "        A--������������        " << endl
		<< "        B--��ӵ����ı�        " << endl
		<< "        C--������С������      " << endl
		<< "        D--��ʾ��С������      " << endl
		<< "        E--�˳�  ����         " << endl
		<< "================================" << endl;
}

void checkInput(int& number)
{
	while (true)
	{
		if (cin.fail())
		{
			cerr << "ERROR.����ʧ��,����������" << endl;;
			cin.clear();
			cin.ignore();
			cin.get();
			cin >> number;
		}
		else if (number <= 1)
		{
			cerr << "ERROR.����ʧ�ܣ�������һ������1��������" << endl;
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
			cerr << "ERROR.����ʧ��,����������" << endl;;
			cin.clear();
			cin.ignore();
			cin.get();
			cin >> number;
		}
		else if (number <= 0)
		{
			cerr << "ERROR.����ʧ�ܣ�������һ��������" << endl;
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
	Queue<char, double> result;            //�������Ľ���Ķ���
	Graph<char, double> graph;             //ͼ
	printTitle();                       //��ӡ��ͷ
	char flag;                          //�����ж�ִ�����ֲ���
	int vertexNum;                      //�������
	bool tag_B = false;                  //�жϲ���B�Ƿ�ִ�й�
	bool tag_C = false;                 //�жϲ���C�Ƿ�ִ�й�
	bool tag_D = false;                 //�жϲ���D�Ƿ�ִ�й�

	cout << "��ѡ�����: ";
	cin >> flag;
	while (true)
	{
		switch (flag)
		{
		case 'A':                    //����ϵͳ
		{
			if (graph.isSet())       //ͼ�Ѿ�����
			{
				cout<< "��ϵͳ�Ѿ�����,�޷����½���" << endl;
				break;
			}
			else
			{
				cout << "�����붥��ĸ���: ";
				cin >> vertexNum;
				checkInput(vertexNum);
				cout << "��������������������(�������ַ���ʾ):" << endl;
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
			if (!tag_B)                 //B����û�б�ִ�й�
			{
				if (graph.isSet())
				{
					char vertex1 = ' ', vertex2 = ' ';
					double value; int num = 0;
					cout << "�������������κ�һ������Ϊ?(Ӣ��)ʱ,������ֹ.(ע��Ȩֵ����Ϊ������)" << endl;
					while (true)
					{
						cout << "��" << (num + 1) << "����,�������������㼰��:" << endl;
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
							cout << "�޷�������һ����,����������" << endl;
						}
					}
					tag_B = true;
					break;
				}
				else
				{
					cout << "ϵͳ��δ������ȫ,����������" << endl;
					break;
				}
			}
			else
			{
				cout << "�Ѿ�������ߣ������ٴ�����" << endl;
				break;
			}
		}
		case'C':
		{
			if (!tag_C)
			{
				if ((graph.isSet()) && (graph.createMinTree(result)))       //�Ѿ�������С������
				{
					cout << "�Ѿ�������С������" << endl;
					tag_C = true;
					break;
				}
				else
				{
					cout << "ϵͳ��û�й�����ȫ,����������С������" << endl;
					break;
				}
			}
			else
			{
				cout << "��С�������Ѵ���,�����ظ�����" << endl;
				break;
			}
		}
		case'D':
		{
			if (!tag_D)
			{
				if (graph.isSet() && (result.isSet()))       //�Ѿ�������С������,�Ѿ��������·��
				{
					result.printNode();
					tag_D = true;
					break;
				}
				else
				{
					cout << "ϵͳ��û�й�����ȫ,����������С������" << endl;
					break;
				}
			}
			else
			{
				cout << "�Ѿ��������С������,�����ٴ����" << endl;
				break;
			}
		}
		case 'E':
		{
			cout << "���˳���ϵͳ����л����ʹ��" << endl;
			break;
		}
		default:
		{
			cout << "������������������" << endl;
		}
		}
		if ('E' == flag)
		{
			break;
		}
		else
		{
			cout << "��ѡ�����: ";
			cin >> flag;
		}
	}

	system("pause");
	return 0;
}