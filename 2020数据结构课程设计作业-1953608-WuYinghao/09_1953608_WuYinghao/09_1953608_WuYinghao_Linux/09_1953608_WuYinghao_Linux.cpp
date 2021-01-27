//1.使用拓扑排序完成课程排布
//2.自定义一个课程表类,将拓扑序列以及有顺序要求的课程排好课
//3.从文件读入数据，并将其写出到文件中

/*注意：需要检测classHour的大小(可能涉及数组的越界),这些在从文件读取信息的时候就要考虑*/

/*
* input文档说明(以及排课说明)：
*1.一共分为4列，通过空格或制表符区分,为防止数组溢出,最后会将所有的字符全部存在先修课程中
*2.对于学期数已经确定的课程,不能安排先修课
*3.对于课时数和学期数进行了范围检测
*4.在建边的时候,当且仅当边的两个顶点都在图中才会建边。所以不合格的文件输入就无法建边
* eg(c03的先修课程是c02,若图中没有创建结点c02,则不能插入<c02,c03>这条边,所以在文件中c02的课程一定要先于c03出现,否则建边不成功)
* 5.每门课的学时只考虑2 3 4 5 6这五种学分的设置(与实际情况相结合)
*/

#include "09_1953608_WuYinghao_Linux.h"

bool checkClassHour(int classHour)               //检查课时数
{
	return ((classHour <= 1) || (classHour >= 7)) ? false : true;
}

bool checkSemester(int semester)                //检查学期数
{
	return ((semester >= 0) && (semester <= 8)) ? true : false;
}

int main()
{
	ofstream fout;					//写入文件
	ifstream fin;					//从文件中读取
	const int parameterNumber = 5;
	int lineNumber = 0;				//行数
	int columnNumber = 0;			//列数
	int classHour, semester;        //课时数与学期数

	string courseStr[parameterNumber];  //课号 课程名称 课时 上课时间 先修课程
	Graph<string, int> graph;           //图
	Timetable<string, int> timetable;   //时间表
	Queue<string, int> queue;           //暂存数据的队列


	fout.open("outputFile.txt");        //把结果写入outputFile.txt
	fin.open("inputFile.txt");          //从inputFile.txt中读

	

	if (!fin)                           //判断是否成功打开文件
	{
		cerr << "无法打开文件inputFile.txt" << endl;
		end();
		exit(0);
	}

	cout << "已成功打开inputFile.txt和outputFile.txt文件" << endl;

	//读取文件
	string line;  //按行读取文件

	fout << "inputFile:" << endl;
	cout << "inputFile:" << endl;
	while (getline(fin, line))
	{
		line += '\n';      //因为gitline得到的字符串是不含换行符的,所以需要将换行符不在结果的末尾
		cout << line << endl;        //输出到屏幕
		fout << line << endl;        //输出到文件
		if (lineNumber)              //不输出第一行
		{
			//进行输入操作
			for (int i = 0; i < line.size(); i++)
			{
				if ((line[i] != ' ') && (line[i] != '\t'))
				{
					if (4 == columnNumber)
					{
						//剩余所有读入先修课程中
						for (; i < line.size(); i++)
						{
							courseStr[columnNumber] += line[i];
						}
					}
					else
					{
						while ((line[i] != ' ') && (line[i] != '\t') && (line[i] != '\n'))
						{
							courseStr[columnNumber] += line[i];
							i++;
						}
						columnNumber++;
					}

				}
			}
			//格式转换
			classHour = atoi(courseStr[2].c_str());           //课时数
			semester = atoi(courseStr[3].c_str());            //学期数
			if ((checkClassHour(classHour)) && (checkSemester(semester)))
			{
				//已经安排好学期数
				if (semester > 0)
				{
					//直接入表不入图
					timetable.insertClass(courseStr[0], courseStr[1], classHour, semester);
				}
				//由系统自定义的学期
				else
				{
					//入表不入图
					graph.insertVertex(courseStr[0], courseStr[1], classHour, semester);
					//以下为建边操作
					string vertex_end;
					for (int i = 0; i < courseStr[4].size(); i++)
					{
						if ((' ' == courseStr[4][i]) || ('\n' == courseStr[4][i]))
						{
							graph.insertEdge(vertex_end, courseStr[0]);
							vertex_end.clear();
						}
						else
						{
							vertex_end += courseStr[4][i];
						}
					}
				}
			}
			else
			{
				cerr << "出现错误,排课终止" << endl;
				fout << "出现错误,排课终止" << endl;
				fout.close();
				fin.close();
				end();
				exit(0);
			}
		}
		//更改相关设置
		lineNumber++;           //读取的行数++";
		for (int j = 0; j < parameterNumber; j++)
		{
			courseStr[j].clear();
		}

		columnNumber = 0;
		//更改相关设置
	}
	//读取文件结束

	cout << "outputFile:" << endl;//文件的输出
	fout << "outputFile:" << endl;//文件的输出

	//拓扑排序
	graph.topologicalSort(queue);
	
	//插入其他课程
	timetable.insertClasses(queue);
	//排课
	timetable.arrangeCourses();

	
	fin.close();
	fout.close();
	cout << "已关闭outputFile.txt和inputFile.txt" << endl;
	end();
	return 0;
}


