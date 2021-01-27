#include"07_1953608_WuYinghao_Linux.h"

/*
*说明：
*采用优先级队列和Huffman树来实现相关功能
*队列的元素必须是HuffmanNode<T>*类型
*/

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
		else if ((number <= 0) || (number > 10000))
		{
			cerr << "ERROR.输入失败，请输入一个小于10^4的正整数" << endl;
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
	cout << "请输入一个正整数N(1<=N<=10^4),来表示木头的块数" << endl;
	int N;
	cin >> N;
	checkInput(N);
	cout << "请输入每一块木头的长度:" << endl;
	try
	{
		int* data_array = new int[N];
		for (int i = 0; i < N; i++)
		{
			cin >> data_array[i];
			checkInput(data_array[i]);
		}
		HuffmanTree<int>huff(data_array, N);

		cout << "最小的花费为: " << huff.getMinValue(huff.getStart(), 0) << endl;
		delete[] data_array;
	}
	catch (bad_alloc& ba)
	{
		cerr << "系统错误!无法生成最优方案" << endl << ba.what() << endl;
		end();
		exit(1);
	}

	end();
	return 0;
}