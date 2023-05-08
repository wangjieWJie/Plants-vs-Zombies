#define _CRT_SECURE_NO_DEPRECATE 1
#include"head.h"
const int num_cards = 8;
const int num_use_cards = 2;

IMAGE map;            //刚开始我为了使用方便，用的是一个 IMAGE* 指针，结果没初始化，郁闷了一下午，被大佬吵了一顿
IMAGE Bar;            //我确实推崇定义伴随初始化一起，但是这个指针我是真的不知道要给他初始化一个什么东西，所以就改用了变量表示
IMAGE cards[10]{};
char save_name[60]{};
//enum cards_name{bin,flower,count };
//IMAGE card_name[1];


void Initmap()
{
	initgraph(1080, 828, 1);    //创建游戏（图形）窗口

	std::cout << "正在初始化地图界面...\n" << "正在加载图片...\n";
	loadimage(&map, "PCT/map.png", 1080, 828);           //加载背景图片
	std::cout << "地图背景加载成功！！！\n";
	loadimage(&Bar, "PCT/bar.png",500,80);        
}

void load_cards()
{
	std::ofstream of_save_name;
	std::ifstream if_save_name;
	of_save_name.open("save_name.txt");
	if_save_name.open("save_name.txt");
	for (int i = 0; i <= num_cards; i++)
	{
		of_save_name << "PCT/card/card_" << i << ".png\n";         //利用文件操作把 卡片所在的文件地址 储存起来
	}
	for(int i=0;i<num_use_cards;i++)
	{
		//if_save_name >> save_name[0];
		if_save_name.getline(save_name, 60);
		std::cout << "正在加载卡片文件地址 :\n" << save_name[i] << std::endl;

		loadimage(&cards[0], save_name);
	}




}
void Put_image()
{

	//开始准备绘图
	BeginBatchDraw();		//批量绘图 暂不输出           //开始缓冲，即把下面的内容先不显示在屏幕上，而是先缓存在内存中
	putimage(0, 0, &map);
	putimage(280, 0, &Bar);
	for(int i=0;i<num_use_cards;i++)
	{
		std::cout << "正在加载卡片文件 :\n" << save_name[i] << std::endl;
		putimage(310, 10, &cards[i]);
	}


	EndBatchDraw();         //结束批量绘图模式，将中间的图片一次性绘制出来                //结束双缓冲，把内存中的内容一次性打印到屏幕上去



}