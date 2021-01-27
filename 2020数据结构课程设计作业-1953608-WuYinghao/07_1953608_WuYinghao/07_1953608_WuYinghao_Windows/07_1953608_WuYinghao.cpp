#include"07_1953608_WuYinghao.h"

/*
*˵����
*�������ȼ����к�Huffman����ʵ����ع���
*���е�Ԫ�ر�����HuffmanNode<T>*����
*/

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
		else if ((number <= 0) || (number > 10000))
		{
			cerr << "ERROR.����ʧ�ܣ�������һ��С��10^4��������" << endl;
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
	cout << "������һ��������N(1<=N<=10^4),����ʾľͷ�Ŀ���" << endl;
	int N;
	cin >> N;
	checkInput(N);
	cout << "������ÿһ��ľͷ�ĳ���:" << endl;
	try
	{
		int *data_array = new int[N];
		for (int i = 0; i < N; i++)
		{
			cin >> data_array[i];
			checkInput(data_array[i]);
		}
		HuffmanTree<int>huff(data_array, N);

		cout << "��С�Ļ���Ϊ: "<<huff.getMinValue(huff.getStart(),0) << endl;
		delete[] data_array;
	}
	catch (bad_alloc& ba)
	{
		cerr << "ϵͳ����!�޷��������ŷ���" << endl << ba.what() << endl;
		system("pause");
		exit(1);
	}

	system("pause");
	return 0;	
}