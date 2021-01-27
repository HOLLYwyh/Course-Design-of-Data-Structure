#include "04_1953608_WuYinghao.h"

template<class T>
int getIcp(T data)        //��ȡջ��ֵ
{
	int result;
	switch (data) 
	{
	case '=':
	{
		result = 0;
		break;
	}
	case '(':
	{
		result = 8;
		break;
	}
	case '+':
	case'-':
	{
		result = 2;
		break;
	}
	case '*':
	case'/':
	case'%':
	{
		result = 4;
		break;
	}
	case '^':
	{
		result = 6;
		break;
	}
	case ')':
	{
		result = 1;
		break;
	}
	default: 
	{
		result = -1;     //����Ƿ��������
		break;
	}
	}
	return result;
}

template<class T>
int getIsp(T data)       //��ȡջ��ֵ
{
	int result;
	switch (data)
	{
	case '=':
	{
		result = 0;
		break;
	}
	case '(':
	{
		result = 1;
		break;
	}
	case'+':
	case'-':
	{
		result = 3;
		break;
	}
	case'*':
	case'/':
	case'%':
	{
		result = 5;
		break;
	}
	case'^':
	{
		result = 7;
		break;
	}
	case')':
	{
		result = 8;
		break;
	}
	default:
	{
		result = -1;
		break;
	}
	}
	return result;
}

template<class T>
bool isNumber(T data)                           //�ж�һ���ַ��ǲ�������
{
	if ((data >= '0') && (data <= '9'))
		return true;
	else
		return false;
}

template<class T>
bool isPlusOrMinus(T data)                        //�ж��ǲ���������
{
	if (('+' == data) || ('-' == data))
		return true;
	else
		return false;
}

template<class T>
bool isMathSign(T data)
{
	if (('*' == data) || ('/' == data) || ('%' == data)
		|| ('^' == data) || ('(' == data) || (')' == data)||('='==data))
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
bool isPoint(T data)                     //�ж��ǲ���С����
{
	return ('.' == data) ? true : false;
}

bool inToPost(Queue<char>& infix_queue,Stack<char>&stack,Queue<char>& postfix_queue)             //����ջ����׺�ַ���ת��Ϊ��׺�ַ���
{ 
	int length = infix_queue.getQueueLength();
	int begin;                                  //ѭ����ʼλ��
	char frontChar;                            //��ǰ����Ԫ��ǰһ��Ԫ�ص�dataֵ
	char temp;                                 //�ݴ����Ԫ��
	char data;                                 //ջ��Ԫ�ص�ֵ
	Queue<char>tempQueue;                      //�ݴ�С�����м�ֵ�Ķ���
	Queue<char>tempQueuInt;                    //�ݴ��������ֵĶ���
	if (!infix_queue.getQueueLength())           //��׺����Ϊ��
	{
		return false;
	}
	else
	{
		stack.push('=');              //��һ��ջ��Ԫ��'='
		//����Ϊ����һ��Ԫ�ص�ֵ
		if (isNumber(infix_queue.getTopData()))
		{
			frontChar = infix_queue.getTopData();
			begin = 0;
		}
		else
		{
			begin = 1;
			infix_queue.pop(temp);
		    if (isPoint(temp))           //��С���㣬�Ƿ�
			{
				return false;
			}
			else if (isPlusOrMinus(temp))      //��������
			{
				frontChar = temp;
				postfix_queue.push(temp, true);
			}
			else if ('('==temp)  //��������
			{
				frontChar = temp;
				stack.push(temp);
			}
			else                             //��������
			{	
				return false;
			}
		}
		

		//�Ų�����Ԫ��
		for (int i = begin; i < length; i++)  
		{
			infix_queue.pop(temp);
			if (isNumber(temp))                //�Ǹ�����
			{
				int num = 1;   //��¼������ֵ�����λ��
				char queue_data;     //�ݴ�������������λ������
				frontChar = temp;
				while (isNumber(infix_queue.getTopData()))
				{
					infix_queue.pop(queue_data);
					i++;
					frontChar = queue_data;
					tempQueue.push(queue_data);
					num++;
				}
				postfix_queue.push(temp, false, 0,num);
				while (tempQueue.pop(queue_data))
				{
					postfix_queue.push(queue_data);
				}
			}
			//��'+'��'-'
			else if (isPlusOrMinus(temp))      
			{
				//ǰһ���ַ������ֻ���')'��һ���ǼӼ���
			if (isNumber(frontChar) || (')' == frontChar))           
			{
				data = stack.getTopData();
				frontChar = temp;
				if (getIcp(temp) > getIsp(data))    //��ջ
				{
					stack.push(temp);
				}
				else if (getIcp(temp) < getIsp(data))
				{
					while (getIcp(temp) <= getIsp(data))
					{
						if (getIcp(temp) == getIsp(data))  //���������ź������ŵ����
						{
							stack.pop(data);
							break;
						}
						else
						{
							stack.pop(data);
							postfix_queue.push(data);
							data = stack.getTopData();
						}
					}
					if ((getIcp(temp) > getIsp(data)) && (temp != ')'))
					{
						stack.push(temp);
					}
				}
				else                   //ֻ������'('��')'����������'='
				{
					stack.pop(data);     //ɾ��ջ����'('
				}
			}
			//��������
			else            
			{
				frontChar = temp;
				postfix_queue.push(temp, true);
			}
			}
			//��������ѧ����
			else if (isMathSign(temp))       
			{
			data = stack.getTopData();
			frontChar = temp;
			if (getIcp(temp) > getIsp(data))    //��ջ
			{
				stack.push(temp);
			}
			else if (getIcp(temp) < getIsp(data))
			{
				while (getIcp(temp) <= getIsp(data))
				{

					if (getIcp(temp) == getIsp(data))
					{
						stack.pop(data);
						break;
					}
					else
					{
						stack.pop(data);
						postfix_queue.push(data);
						data = stack.getTopData();
					}
				}
				/*if ((getIcp(temp) > getIsp(data)) && (temp != ')'))
				{
					stack.push(temp);
				}*/
				if ((getIcp(temp) > getIsp(data)))
				{
					if (temp != ')')
					{
						stack.push(temp);
					}
					else
					{
						if (data != '(')
						{
							return false;
						}
					}
				}
			}
			else                   
			{
				stack.pop(data);
			}
			}
			//��С����
			else if (isPoint(temp))
			{
			int num = 0;                 //���ڼ���С������Ƶ�λ��
			char queue_data;           //�ݴ�С����������
			while (isNumber(infix_queue.getTopData()))
			{
				infix_queue.pop(queue_data);
				i++;
				frontChar = queue_data;
				tempQueue.push(queue_data);
				num++;
			}
			postfix_queue.push(temp, false, num);
			while (tempQueue.pop(queue_data))
			{
				postfix_queue.push(queue_data);
			}
			}
			else                            //���벻�Ϸ���
			{
			return false;
			}
		}

		return true;
	}

}

bool calculate(Stack<double>&stack,Queue<char>&queue)
{
	QueueNode<char> temp;   //��ʾ���н��
	char sign='+';  //��ʾ����λ
	char data=' ';  //��ʾ����
	int number=0;    //С����һ��������λ
	int symbol=1;    //��ʾ����λ
	double num1, num2, stack_elem = 0, result = 0;

	if (queue.isEmpty())
	{
		return false;
	}

	while (!queue.isEmpty())
	{
		queue.pop(temp);
		//��һ����ѧ���ŵ�����������,��ջ������
		if ((isMathSign(temp.getData())) ||((isPlusOrMinus(temp.getData()))&&(!temp.isSign())))
		{
			if (stack.pop(num2)&&stack.pop(num1))        //�ܹ�������ջ���˳�������,ע����ջ�Ƿ���
			{
				switch (temp.getData())                
				{
				case '+':
				{
					result = num1 + num2;
					stack.push(result);
					break;
				}
				case '-':
				{
					result = num1 - num2;
					stack.push(result);
					break;
				}
				case '*':
				{
					result = num1 * num2;
					stack.push(result);
					break;
				}
				case'/':
				{
					if (num2 == 0)
					{
						cerr << "0����������" << endl;
						return false;
					}
					else
					{
						result = num1 / num2;
						stack.push(result);
						break;
					}
				}
				case'%':
				{
					if (num2 == 0)
					{
						cerr << "0����������" << endl;
						return false;
					}
					else
					{
						result = fmod(num1, num2);
						stack.push(result);
						break;
					}
				}
				case'^':
				{
					result = pow(num1, num2);
					stack.push(result);
					break;
				}
				default:
				{
					return false;
				}
				}
			}
			else
			{
				return false;
			}
		}
		//��һ��������(����λ)
		else if(temp.isSign())
		{
			if (isNumber(queue.getTopData()))        //��һ��Ԫ��������
			{
				switch (temp.getData())
				{
				case'+':
				{
					symbol = 1;
					break;
				}
				case'-':
				{
					symbol = -1;
					break;
				}
				default:
				{
					return false;
				}
				}
			}
			else              //��һ��Ԫ�ز������֣�˵����������
			{
				return false;
			}
		}
		//��һ������
		else if (isNumber(temp.getData()))
		{
			int int_num = temp.getIntNum();
			data = temp.getData();
			stack_elem += static_cast<double>(data - '0') * pow(10, (int_num-1));
			for (int i =int_num-2;i>=0; i--)  //������������
			{
				queue.pop(data);
				stack_elem += static_cast<double>(data - '0') * pow(10, i);
			}
			if (!isPoint(queue.getTopData()))       //������һ��Ԫ�ز���С����,������������
			{
				stack_elem *= symbol;
				stack.push(stack_elem);
				stack_elem = 0;         //��λ����
				symbol = 1;
			}
			else                                   //������һ����С����
			{
				queue.pop(temp);                 //ɾȥС����,���С������Ƶ�λ��
				for (int i = 1; i <=temp.getBitNum(); i++)
				{
					queue.pop(data);                 
					stack_elem += static_cast<double>(pow(10, -1 *i)* (data-'0'));
				}
				
				stack_elem *= symbol;
				stack.push(stack_elem);
				stack_elem = 0;             //��λ����
				symbol = 1;
			}
		}
		//��С����
		else if (isPoint(temp.getData()))
		{
		//��������£�С��������������ֵ�ʱ��ɾ������������˵�����ִ���
		return false;
		}
		//���϶����ǣ��Ǳ�Ȼ�ǳ�����
		else
		{
		return false;
		}
	}
	return true;
}

int main()      //����һ�����У��Ժ�����ѭ��
{
	char ch=' ';					//����������ַ���
	double result=0;					//������
	Stack<char> char_stack;			//ջ����׺ת��׺ʱ�洢����
	Stack<double> double_stack;     //ջ�����ڴ�����Ľ��
	Queue<char> infix_queue;		//��׺���ʽ
	Queue<char> postfix_queue;		//��׺���ʽ

	cout << "****************************************************" << endl;
	cout << "��ӭʹ�ô�ϵͳ������׺�������ʽ!" << endl;
	cout << "ע��:\n***1.����=�Խ�������***\n***2.����������ʱ������Ӣ�����ţ�����ʹ����������***\n";
	cout << "***3.���ΪС����,����Ϊ6λ***\n***4.����С����ʱ��Ӧ������������,��.1Ϊ�Ƿ�����***\n";
	cout << "****************************************************" << endl;
	cout << "**************************" << endl;
	cout<<"��������ʽ:" << endl;            //��ʼ����ӭ����
	cout << "**************************" << endl;
	
	while (true)
	{
		//��ÿһ������֮ǰ�Ƚ�����յ� ����
		char_stack.clear();
		double_stack.clear();
		infix_queue.clear();
		postfix_queue.clear();

		cin >> ch;
		while (ch != '=')   //�õ���׺���ʽ
		{
			infix_queue.push(ch);
			cin >> ch;
		}
		infix_queue.push('=');   //ת��������
		if (inToPost(infix_queue, char_stack, postfix_queue))           //��׺�ַ���ת����׺�ַ����ɹ�
		{
			if (calculate(double_stack, postfix_queue))           //����ȷ�Ľ��
			{
				result = double_stack.getTopData();
				cout << "�����:" << result << endl;
			}
			else
			{
				cerr << "\n������ı��ʽ���ڴ�������ֹ��һ�μ���\n" << endl;
			}
		}
		else        //ת��ʧ��
		{
			cerr << "\n������ı��ʽ���ڴ�������ֹ��һ�μ���\n" << endl;
		}


		//�ж�ѭ����ֹ����
		cout << "�Ƿ����(y,n)?"<<endl;
		char tag;
		bool end = false;
		cin >> tag;
		while (true)
		{
			if ('y' == tag)
			{
				cout << "**************************" << endl;
				cout << "��������ʽ:" << endl;            //��ʼ����ӭ����
				cout << "**************************" <<endl;
				break;
			}
			else if ('n' == tag)
			{
				cout << "��лʹ�ñ�ϵͳ,�ټ�!" << endl;
				end = true;
				break;
			}
			else
			{
				cout << "�����������������!!!!" << endl;
				cout << "�Ƿ����(y,n)?" << endl;
				cin >> tag;
			}
		}
		if (end)//�������˳�
		{
			break;
		}
	}
	system("pause");
	return 0;
}

