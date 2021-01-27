#include "04_1953608_WuYinghao.h"

template<class T>
int getIcp(T data)        //获取栈外值
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
		result = -1;     //输入非法的运算符
		break;
	}
	}
	return result;
}

template<class T>
int getIsp(T data)       //获取栈内值
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
bool isNumber(T data)                           //判断一个字符是不是数字
{
	if ((data >= '0') && (data <= '9'))
		return true;
	else
		return false;
}

template<class T>
bool isPlusOrMinus(T data)                        //判断是不是正负号
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
bool isPoint(T data)                     //判断是不是小数点
{
	return ('.' == data) ? true : false;
}

bool inToPost(Queue<char>& infix_queue,Stack<char>&stack,Queue<char>& postfix_queue)             //借助栈将中缀字符串转换为后缀字符串
{ 
	int length = infix_queue.getQueueLength();
	int begin;                                  //循环开始位置
	char frontChar;                            //当前队列元素前一个元素的data值
	char temp;                                 //暂存队列元素
	char data;                                 //栈顶元素的值
	Queue<char>tempQueue;                      //暂存小数点中间值的队列
	Queue<char>tempQueuInt;                    //暂存整数部分的队列
	if (!infix_queue.getQueueLength())           //中缀队列为空
	{
		return false;
	}
	else
	{
		stack.push('=');              //第一个栈内元素'='
		//以下为检测第一个元素的值
		if (isNumber(infix_queue.getTopData()))
		{
			frontChar = infix_queue.getTopData();
			begin = 0;
		}
		else
		{
			begin = 1;
			infix_queue.pop(temp);
		    if (isPoint(temp))           //是小数点，非法
			{
				return false;
			}
			else if (isPlusOrMinus(temp))      //是正负号
			{
				frontChar = temp;
				postfix_queue.push(temp, true);
			}
			else if ('('==temp)  //是左括号
			{
				frontChar = temp;
				stack.push(temp);
			}
			else                             //其他符号
			{	
				return false;
			}
		}
		

		//排查后面的元素
		for (int i = begin; i < length; i++)  
		{
			infix_queue.pop(temp);
			if (isNumber(temp))                //是个数字
			{
				int num = 1;   //记录这个数字的整数位数
				char queue_data;     //暂存整数部分其他位的内容
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
			//是'+'或'-'
			else if (isPlusOrMinus(temp))      
			{
				//前一个字符是数字或是')'则一定是加减号
			if (isNumber(frontChar) || (')' == frontChar))           
			{
				data = stack.getTopData();
				frontChar = temp;
				if (getIcp(temp) > getIsp(data))    //进栈
				{
					stack.push(temp);
				}
				else if (getIcp(temp) < getIsp(data))
				{
					while (getIcp(temp) <= getIsp(data))
					{
						if (getIcp(temp) == getIsp(data))  //遇到左括号和右括号的情况
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
				else                   //只可能是'('与')'或者是两个'='
				{
					stack.pop(data);     //删除栈顶的'('
				}
			}
			//是正负号
			else            
			{
				frontChar = temp;
				postfix_queue.push(temp, true);
			}
			}
			//是其他数学符号
			else if (isMathSign(temp))       
			{
			data = stack.getTopData();
			frontChar = temp;
			if (getIcp(temp) > getIsp(data))    //进栈
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
			//是小数点
			else if (isPoint(temp))
			{
			int num = 0;                 //用于计算小数点控制的位数
			char queue_data;           //暂存小数点后的数字
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
			else                            //输入不合法的
			{
			return false;
			}
		}

		return true;
	}

}

bool calculate(Stack<double>&stack,Queue<char>&queue)
{
	QueueNode<char> temp;   //表示队列结点
	char sign='+';  //表示符号位
	char data=' ';  //表示数据
	int number=0;    //小数点一共包含几位
	int symbol=1;    //表示符号位
	double num1, num2, stack_elem = 0, result = 0;

	if (queue.isEmpty())
	{
		return false;
	}

	while (!queue.isEmpty())
	{
		queue.pop(temp);
		//是一个数学符号但不是正负号,退栈，操作
		if ((isMathSign(temp.getData())) ||((isPlusOrMinus(temp.getData()))&&(!temp.isSign())))
		{
			if (stack.pop(num2)&&stack.pop(num1))        //能够正常从栈中退出两个数,注意退栈是反的
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
						cerr << "0不能做除数" << endl;
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
						cerr << "0不能做除数" << endl;
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
		//是一个正负号(符号位)
		else if(temp.isSign())
		{
			if (isNumber(queue.getTopData()))        //下一个元素是数字
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
			else              //下一个元素不是数字，说明存在问题
			{
				return false;
			}
		}
		//是一个数字
		else if (isNumber(temp.getData()))
		{
			int int_num = temp.getIntNum();
			data = temp.getData();
			stack_elem += static_cast<double>(data - '0') * pow(10, (int_num-1));
			for (int i =int_num-2;i>=0; i--)  //计算整数部分
			{
				queue.pop(data);
				stack_elem += static_cast<double>(data - '0') * pow(10, i);
			}
			if (!isPoint(queue.getTopData()))       //数字下一个元素不是小数点,计算整数部分
			{
				stack_elem *= symbol;
				stack.push(stack_elem);
				stack_elem = 0;         //复位操作
				symbol = 1;
			}
			else                                   //数字下一个是小数点
			{
				queue.pop(temp);                 //删去小数点,获得小数点控制的位数
				for (int i = 1; i <=temp.getBitNum(); i++)
				{
					queue.pop(data);                 
					stack_elem += static_cast<double>(pow(10, -1 *i)* (data-'0'));
				}
				
				stack_elem *= symbol;
				stack.push(stack_elem);
				stack_elem = 0;             //复位操作
				symbol = 1;
			}
		}
		//是小数点
		else if (isPoint(temp.getData()))
		{
		//正常情况下，小数点会在遇到数字的时候被删除，若出现则说明出现错误
		return false;
		}
		//以上都不是，那必然是出错了
		else
		{
		return false;
		}
	}
	return true;
}

int main()      //先做一次运行，稍后再做循环
{
	char ch=' ';					//用于输入的字符串
	double result=0;					//计算结果
	Stack<char> char_stack;			//栈，中缀转后缀时存储内容
	Stack<double> double_stack;     //栈，用于存放最后的结果
	Queue<char> infix_queue;		//中缀表达式
	Queue<char> postfix_queue;		//后缀表达式

	cout << "****************************************************" << endl;
	cout << "欢迎使用此系统计算中缀算数表达式!" << endl;
	cout << "注意:\n***1.输入=以结束输入***\n***2.在输入括号时请输入英文括号，请勿使用中文括号***\n";
	cout << "***3.结果为小数的,精度为6位***\n***4.输入小数的时候应输入整数部分,如.1为非法输入***\n";
	cout << "****************************************************" << endl;
	cout << "**************************" << endl;
	cout<<"请输入表达式:" << endl;            //初始化欢迎界面
	cout << "**************************" << endl;
	
	while (true)
	{
		//在每一次输入之前先进行清空的 操作
		char_stack.clear();
		double_stack.clear();
		infix_queue.clear();
		postfix_queue.clear();

		cin >> ch;
		while (ch != '=')   //得到中缀表达式
		{
			infix_queue.push(ch);
			cin >> ch;
		}
		infix_queue.push('=');   //转换结束符
		if (inToPost(infix_queue, char_stack, postfix_queue))           //中缀字符串转换后缀字符串成功
		{
			if (calculate(double_stack, postfix_queue))           //有正确的结果
			{
				result = double_stack.getTopData();
				cout << "结果是:" << result << endl;
			}
			else
			{
				cerr << "\n您输入的表达式存在错误，已终止这一次计算\n" << endl;
			}
		}
		else        //转换失败
		{
			cerr << "\n您输入的表达式存在错误，已终止这一次计算\n" << endl;
		}


		//判断循环终止条件
		cout << "是否继续(y,n)?"<<endl;
		char tag;
		bool end = false;
		cin >> tag;
		while (true)
		{
			if ('y' == tag)
			{
				cout << "**************************" << endl;
				cout << "请输入表达式:" << endl;            //初始化欢迎界面
				cout << "**************************" <<endl;
				break;
			}
			else if ('n' == tag)
			{
				cout << "感谢使用本系统,再见!" << endl;
				end = true;
				break;
			}
			else
			{
				cout << "输入错误，请重新输入!!!!" << endl;
				cout << "是否继续(y,n)?" << endl;
				cin >> tag;
			}
		}
		if (end)//真正的退出
		{
			break;
		}
	}
	system("pause");
	return 0;
}

