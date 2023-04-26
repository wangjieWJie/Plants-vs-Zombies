#define _CRT_SECURE_NO_DEPRECATE 1

#include"tansfer.h"

	//创建一个图形变量
	IMAGE ImgBg;
	//创建一个工具栏
	IMAGE ImgBar;
	//利用枚举 列出植物，并确定植物个数
	enum { Bin, Sunflower, count };
	//创建植物卡片
	IMAGE ImgCards[count];
	//创建植物卡片名称储存位置
	char name[64];
	//当前选中的植物在移动过程中的坐标
	int curX, curY;
	//创建植物的图像
	IMAGE* ImgPlants[count][20];    //因为每个植物的图片组数都不一样，所以用指针表示
	//当前选中的植物
	int curPlant = 0;         //0表示没有选中，1表示选中了第一种植物,2表示选中了第二种植物.....




int main()
{


	//初始化游戏窗口
	Initgame();

	while (1)
	{


		UserClick();
		UpdateWindow();
	}
	//所有游戏和应用都是一个死循环直至退出
	//因为循环导致updatewindow一直在工作，有因为他是一步一步的打印图片，所以会导致窗口闪烁，这时候就要在updatewindow里面加上一个双缓冲



	system("pause");

	return 0;
}