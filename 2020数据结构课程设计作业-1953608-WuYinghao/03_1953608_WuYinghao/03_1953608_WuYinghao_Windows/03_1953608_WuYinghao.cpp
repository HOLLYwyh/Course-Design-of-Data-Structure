#include"03_1953608_WuYinghao.h"

int main()
{
	initgraph(1080, 720);     //����ҳ���С
	setbkcolor(GREEN);       //���ñ���ɫ
	cleardevice();           //�ñ���ɫ�����Ļ
	{
		Maze<char> maze;        //�����Թ�
		maze.printMaze();       //��Ӧ�Թ�
		maze.runMaze(maze.in_x,maze.in_y);         //Ѱ�����·��
		maze.printPath();       //��ӡ���յ�·�� 
	}
	system("pause");
	closegraph();			// �ر�ͼ�ν���
	return 0;

}