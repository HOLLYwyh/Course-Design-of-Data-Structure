/*
* ���ļ����ڴ洢main()�����Լ�������Ҫ�ĺ���
* ����ʹ��˫������
*/
#include"link.h"

int main()
{
	linkList<unsigned int>lists[2];

	cout << "**************************************************************************"<< endl;
	cout << "\t\t�����������ǽ������У�����-1�Խ���һ�����У�" << endl;
	cout << "**************************************************************************" << endl;

	for (int i = 0; i <= 1; i++)                 //���ݵ�����
	{
		cout <<endl<< "�������" << i+1<< "�����У��ǽ������У�" << endl;
		int data = 0;	
		cin >> data;
		while (data != -1)
		{
			if (cin.fail())
			{
				cerr << "ERROR.����ʧ��,����������" << endl;;
			cin.clear();
			cin.ignore();
			cin.get();
			}
			else if (data <= 0)
			{
				cerr << "ERROR.����ʧ�ܣ�����������" << endl;
			}
			else if (static_cast<unsigned int>(data) < lists[i].getFinalData())
			{
				cerr << "ERROR.����ʧ��.����������빹�ɷǽ������У�����������" << endl;
			}
			else if (static_cast<unsigned int>(data) >= lists[i].getFinalData())
			{
				lists[i].append(data);
			}
			cin >> data;
		}
		cout <<"����" << i+1 << ":" << endl;
		lists[i].printResult();
	}

/*������*/
	lists[0].intersect(lists[1]);
	cout << endl<<"���:" << endl;
	lists[0].printResult();

	cout << endl<< "**************************************************************************" << endl;
	cout << "\t\t\t������������ӭʹ��" << endl;
	cout << "**************************************************************************" << endl;

	system("pause");
	return 0;
}