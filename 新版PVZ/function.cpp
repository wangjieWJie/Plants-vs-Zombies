#define _CRT_SECURE_NO_DEPRECATE 1
#include"head.h"


IMAGE map;            //刚开始我为了使用方便，用的是一个 IMAGE* 指针，结果没初始化，郁闷了一下午，被大佬吵了一顿
IMAGE Bar;            //我确实推崇定义伴随初始化一起，但是这个指针我是真的不知道要给他初始化一个什么东西，所以就改用了变量表示

void Initmap()
{
	initgraph(1080, 900, 1);    //创建游戏（图形）窗口


	std::cout << "正在初始化地图界面...\n" << "正在加载图片...\n";
	loadimage(&map, "PCT/map.png", 1080, 828);           //加载背景图片
	std::cout << "地图背景加载成功！！！\n";
	loadimage(&Bar, "PCT/bar.png",150,600);        

	 //开始准备绘图
	BeginBatchDraw();		//批量绘图 暂不输出           //开始缓冲，即把下面的内容先不显示在屏幕上，而是先缓存在内存中
	putimage(0, 20, &map);
	putimage(100, 0, &Bar);
	EndBatchDraw();         //结束批量绘图模式，将中间的图片一次性绘制出来                //结束双缓冲，把内存中的内容一次性打印到屏幕上去





}
