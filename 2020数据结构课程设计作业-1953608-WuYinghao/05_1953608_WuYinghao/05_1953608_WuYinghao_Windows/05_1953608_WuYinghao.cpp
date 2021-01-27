#include"05_1953608_WuYinghao.h"

int main()
{
	int customer_num;        //�˿͵�������
	int order;               //Ԫ�ص����
	int temp;                //�����ݴ����Ԫ�ص�ֵ
	Queue<int> queue_A;
	Queue<int> queue_B;
	Queue<int> queue_result;     //Ϊ�������⣬�����������Ŀ��ַ������ڰѽ�����ڽ����������
	cout << "\t\t*******************************************" << endl
		<< "\t\t��ӭ��������ҵ��������A��B����ҵ�񴰿�" << endl << endl
		<< "\t\t�����뵱ǰ�˿�������" << endl
		<< "\t\t";
	

	//�����⣬��֤�������������
	
	while (true)
	{
		cin >> customer_num;
		if (cin.fail())
		{
			cerr << "\t\tERROR.����ʧ��,����������" << endl<<"\t\t";
			cin.clear();
			cin.ignore();
			cin.get();
		}
		else if (customer_num <= 0)
		{
			cerr << "\t\tERROR.����������Ǹ���,����������" << endl << "\t\t";
		}
		else if (customer_num > 1000)
		{
			cerr << "\t\tERROR.���������ܳ���1000,����������" << endl << "\t\t";
		}
		else
			break;
	}

	cout << "\t\t������" << customer_num << "���˿͵����:" << endl << "\t\t";
	for (int i = 0; i < customer_num; i++)
	{
		while (true)
		{
			cin >> order;
			if (cin.fail())
			{
				cerr << "\t\tERROR.����ʧ��,����������" << endl << "\t\t";
				cin.clear();
				cin.ignore();
				cin.get();
			}
			else if (order <= 0)
			{
				cerr << "\t\tERROR.��ű���Ϊ������,����������" << endl << "\t\t";
			}
			else
				break;
		}
		if (order % 2)     //order��������ȥA����
		{
			queue_A.inQueue(order);
		}
		else

		{
			queue_B.inQueue(order);
		}
	}


	cout << "\t\tҵ������ɵ�˳���ǣ�";
	while ((!queue_A.isEmpty()) && (!queue_B.isEmpty()))//���������о���Ϊ��ʱ
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

	if (queue_A.isEmpty())               //����A��
	{
		int b_length = queue_B.getLength();
		int temp;
		for (int i = 0; i < b_length; i++)
		{
			queue_B.outQueue(temp);
			queue_result.inQueue(temp);
		}
	}
	if (queue_B.isEmpty())             //����B��
	{
		int a_length = queue_A.getLength();
		int temp;
		for (int i = 0; i < a_length; i++)
		{
			queue_A.outQueue(temp);
			queue_result.inQueue(temp);
		}
	}

	for (int i = 0; i < customer_num; i++)    //���ݵ����
	{
		queue_result.outQueue(temp);
		if (queue_result.isEmpty())
			cout << temp;
		else
			cout << temp << ' ';
	}

	cout << endl << "\t\t*******************************************" << endl;


	system("pause");
		return 0;
}