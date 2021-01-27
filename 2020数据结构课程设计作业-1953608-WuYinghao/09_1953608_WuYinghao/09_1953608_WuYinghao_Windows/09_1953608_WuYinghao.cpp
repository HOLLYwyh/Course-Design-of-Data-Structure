//1.ʹ������������ɿγ��Ų�
//2.�Զ���һ���γ̱���,�����������Լ���˳��Ҫ��Ŀγ��źÿ�
//3.���ļ��������ݣ�������д�����ļ���

/*ע�⣺��Ҫ���classHour�Ĵ�С(�����漰�����Խ��),��Щ�ڴ��ļ���ȡ��Ϣ��ʱ���Ҫ����*/

/*
* input�ĵ�˵��(�Լ��ſ�˵��)��
*1.һ����Ϊ4�У�ͨ���ո���Ʊ������,Ϊ��ֹ�������,���Ὣ���е��ַ�ȫ���������޿γ���
*2.����ѧ�����Ѿ�ȷ���Ŀγ�,���ܰ������޿�
*3.���ڿ�ʱ����ѧ���������˷�Χ���
*4.�ڽ��ߵ�ʱ��,���ҽ����ߵ��������㶼��ͼ�вŻὨ�ߡ����Բ��ϸ���ļ�������޷�����
* eg(c03�����޿γ���c02,��ͼ��û�д������c02,���ܲ���<c02,c03>������,�������ļ���c02�Ŀγ�һ��Ҫ����c03����,���򽨱߲��ɹ�)
* 5.ÿ�ſε�ѧʱֻ����2 3 4 5 6������ѧ�ֵ�����(��ʵ���������)
*/

#include "09_1953608_WuYinghao.h"

bool checkClassHour(int classHour)               //����ʱ��
{
	return ((classHour <= 1)||(classHour>=7)) ? false : true;
}

bool checkSemester(int semester)                //���ѧ����
{ 
	return ((semester >= 0) && (semester <= 8)) ? true : false;
}

int main()
{
	ofstream fout;					//д���ļ�
	ifstream fin;					//���ļ��ж�ȡ
	const int parameterNumber = 5;
	int lineNumber = 0;				//����
	int columnNumber = 0;			//����
	int classHour, semester;        //��ʱ����ѧ����

	string courseStr[parameterNumber];  //�κ� �γ����� ��ʱ �Ͽ�ʱ�� ���޿γ�
	Graph<string, int> graph;           //ͼ
	Timetable<string, int> timetable;   //ʱ���
	Queue<string, int> queue;           //�ݴ����ݵĶ���


	fout.open("outputFile.txt");        //�ѽ��д��outputFile.txt
	fin.open("inputFile.txt");          //��inputFile.txt�ж�

	if (!fin)                           //�ж��Ƿ�ɹ����ļ�
	{
		cerr << "�޷����ļ�inputFile.txt";
		system("pause");
		exit(0);
	}
	cout << "�ѳɹ���inputFile.txt��outputFile.txt�ļ�" << endl;
	
	//��ȡ�ļ�
	string line;  //���ж�ȡ�ļ�
	fout << "inputFile:" << endl;
	cout << "inputFile:" << endl;
	//��ȡ�ļ�
	while (getline(fin, line))
	{
		line += '\n';      //��Ϊgitline�õ����ַ����ǲ������з���,������Ҫ�����з����ڽ����ĩβ
		cout << line << endl;        //�������Ļ
		fout << line << endl;        //������ļ�
		if (lineNumber)              //�������һ��
		{
			//�����������
			for (int i=0;i<line.size();i++)
			{
				if ((line[i] != ' ') && (line[i] != '\t'))
				{
					if (4 == columnNumber)
					{
						//ʣ�����ж������޿γ���
						for (;i < line.size(); i++)
						{
							courseStr[columnNumber] += line[i];
						}
					}
					else
					{
						while ((line[i] != ' ') && (line[i] != '\t')&&(line[i]!='\n'))            
						{
							courseStr[columnNumber] += line[i];
							i++;
						}
						columnNumber++;
					}
					
				}
			}
			//��ʽת��
			classHour = atoi(courseStr[2].c_str());           //��ʱ��
			semester = atoi(courseStr[3].c_str());            //ѧ����
			if ((checkClassHour(classHour)) && (checkSemester(semester)))
			{
				//�Ѿ����ź�ѧ����
				if (semester > 0)       
				{
					//ֱ�������ͼ
					timetable.insertClass(courseStr[0], courseStr[1], classHour, semester);
				}
				//��ϵͳ�Զ����ѧ��
				else
				{
					//�����ͼ
					graph.insertVertex(courseStr[0], courseStr[1], classHour, semester);
					//����Ϊ���߲���
					string vertex_end;
					for (int i = 0; i < courseStr[4].size(); i++)
					{
						if ((' '== courseStr[4][i])||('\n'==courseStr[4][i]))
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
				cerr << "���ִ���,�ſ���ֹ" << endl;
				fout << "���ִ���,�ſ���ֹ" << endl;
				fout.close();
				fin.close();
				system("pause");
				exit(1);
			}
		}
		//�����������
		lineNumber++;           //��ȡ������++";
		for (int j = 0; j < parameterNumber; j++)
		{
			courseStr[j].clear();
		}
		columnNumber = 0;
		//�����������
	}
	//��ȡ�ļ�����

	cout << "outputFile:" << endl;//�ļ������
	fout << "outputFile:" << endl;//�ļ������

	//��������
	graph.topologicalSort(queue);
	//���������γ�
	timetable.insertClasses(queue);
	//�ſ�
	timetable.arrangeCourses();


	fout.close();
	fin.close();
	cout << "�ѹر�outputFile.txt��inputFile.txt" << endl;
	system("pause");
	return 0;
}


