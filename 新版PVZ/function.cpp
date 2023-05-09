#include"head.h"
const int num_cards = 8;
const int num_use_cards = 2;

IMAGE map;            //刚开始我为了使用方便，用的是一个 IMAGE* 指针，结果没初始化，郁闷了一下午，被大佬吵了一顿
IMAGE Bar;            //我确实推崇定义伴随初始化一起，但是这个指针我是真的不知道要给他初始化一个什么东西，所以就改用了变量表示
IMAGE cards[num_cards]{};
char save_name[60]{};
//enum cards_name{bin,flower,count };
//IMAGE card_name[1];
IMAGE plant_cards[num_cards][25]{};
ExMessage point;     //ExMessage 是easyX图形库里定义的一个结构体，里面有鼠标按下、移动、松开及鼠标指针当前位置的变量
int curX = point.x;
int curY = point.y;

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
	for (int i = 0; i < num_use_cards; i++)
	{
		of_save_name << "PCT/card/card_" << i << ".png\n";         //利用文件操作把 卡片所在的文件地址 储存起来
	}
	of_save_name.close();                                          //不把out的文件关闭了，in的文件就没法正常使用
	for(int i=0;i<num_use_cards;i++)
	{
		//if_save_name >> save_name[0];
		if_save_name.getline(save_name, 60);                        //我自我认为这个方法及其复杂，优化的空间还有很大
		std::cout << "正在加载卡片文件地址 :\n" << save_name << std::endl;

		loadimage(&cards[i], save_name);
	}
	if_save_name.close();
}


void load_plants()
{
	int num_0 = num_a_cards(0);
	std::ofstream of_save_name;
	of_save_name.open("save_name.txt");
	for (int i = 0; i < num_use_cards; i++)
	{
		for (int j = 0; j < num_0; j++)
		{
			std::ofstream card;
			card.open("plant_name.txt");



		}
		of_save_name << "PCT/plant/" << i<<"/"<<j << ".png\n";
	}
	of_save_name.close();     

	std::ifstream if_save_name;
	if_save_name.open("save_name.txt");
	for (int i = 0; i < num_use_cards; i++)
	{
		if_save_name.getline(save_name, 60);                       
		std::cout << "正在加载植物图片文件地址 :\n" << save_name << std::endl;      //相同的方法，纯纯复制粘贴，后悔但当时没封装以个函数

		//loadimage(&plant_cards[i], save_name);
	}
	if_save_name.close();


}

int num_a_cards(int num)
{



	return 0;
}

void Put_image()
{

	//开始准备绘图
	BeginBatchDraw();		//批量绘图 暂不输出           //开始缓冲，即把下面的内容先不显示在屏幕上，而是先缓存在内存中
	putimage(0, 0, &map);
	putimage(280, 0, &Bar);
	for(int i=0;i<num_use_cards;i++)
	{
		std::cout << "正在加载卡片文件 :\n" << save_name << std::endl;
		putimage(358 + 50 * i, 8, &cards[i]);
	}


	EndBatchDraw();         //结束批量绘图模式，将中间的图片一次性绘制出来                //结束双缓冲，把内存中的内容一次性打印到屏幕上去
}



void click_act()
{
	//std::cout << "等待接受消息\n";
	if (peekmessage(&point))                           //如果获取到了一个鼠标的消息
	{
//		std::cout << "get消息\n";
		if (point.message == WM_LBUTTONDOWN)     //如果获得了一个鼠标左键按下的消息
		{
			//std::cout << "左点" << std::endl;
			if (point.x >= 358 && point.x <= 770 && point.y >= 8 && point.y <= 70)
			{
				int tmp = (point.x - 356) / 47;
				//std::cout << tmp;
				out_plant(tmp);
			}
		}


	}



}



void out_plant(int num)
{




}



void update_windows()
{



}