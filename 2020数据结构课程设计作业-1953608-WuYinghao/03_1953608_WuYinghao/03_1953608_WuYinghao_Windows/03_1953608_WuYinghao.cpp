#include"03_1953608_WuYinghao.h"

int main()
{
	initgraph(1080, 720);     //创建页面大小
	setbkcolor(GREEN);       //设置背景色
	cleardevice();           //用背景色清空屏幕
	{
		Maze<char> maze;        //创建迷宫
		maze.printMaze();       //答应迷宫
		maze.runMaze(maze.in_x,maze.in_y);         //寻找最短路径
		maze.printPath();       //打印最终的路径 
	}
	system("pause");
	closegraph();			// 关闭图形界面
	return 0;

}