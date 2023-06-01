#include"head.h"
const int num_cards = 8;
const int num_use_cards = 2;
const int MAX_plant_image = 17;
const int ROW = 6, COL = 11;
const int p_speecd = 200;
const int a_speced = 800;

IMAGE map;            //刚开始我为了使用方便，用的是一个 IMAGE* 指针，结果没初始化，郁闷了一下午，被大佬吵了一顿
IMAGE Bar;            //我确实推崇定义伴随初始化一起，但是这个指针我是真的不知道要给他初始化一个什么东西，所以就改用了变量表示
IMAGE shovel;
IMAGE cards[num_cards]{};               //植物的卡片图片
char save_name[60]{};                   //暂时存储各种地址名称的字符串
IMAGE plant_cards[num_cards][25]{};     //植物的所有动态图片
int num_of_plant_image[num_cards]{}; //植物的动态图片有几张，（在加载时顺便算出来的）
ExMessage point;     //ExMessage 是easyX图形库里定义的一个结构体，里面有鼠标按下、移动、松开及鼠标指针当前位置的变量
int curX = point.x;
int curY = point.y;
int curPlant = -1;           //当前的植物的序号
constexpr int p_w = -45;          //用于微调植物放置的位置
constexpr int p_h = -55;          //用于微调植物放置的位置
struct place                 //概念网格
{
	int l = 175; int r = 995;
	int dist = 82;
	int u1 = 95, d1 = 205;
	int u2 = 205, d2 = 305;     //地图每行的长宽高数据
	int u3 = 305, d3 = 405;
	int u4 = 405, d4 = 500;
	int u5 = 500, d5 = 595;
	int x = -1;             //可以放植物的坑位的二元序号
	int y = -1;             //左上角为原点
}pl;

IMAGE* note_plant[ROW][COL]{};    //表示某个坑位上应该长哪个植物，让每个坑位上长出植物，而不是让植物长到某个坑位上去(使用地址操作，效率高，且方便操作)
int note[ROW][COL]{};          //用于记录哪个坑位上已经有植物了。
int note_x[ROW][COL]{};        //记录当前坑位上放置植物的x,y坐标
int note_y[ROW][COL]{};
int note_curPlant[ROW][COL]{}; //用于记录当前坑位的植物是谁
int count[ROW][COL]{};          //计数器

IMAGE bin_go{};                //豆子子弹
IMAGE bin_break{};             //豆子破碎

int value_plant[num_use_cards] = { 100,50 };  //定义每个植物的花费

void Initmap()
{
	initgraph(1080, 675, 1);    //创建游戏（图形）窗口

	std::cout << "正在初始化地图界面...\n" << "正在加载图片...\n";
	loadimage(&map, "PCT/map.png", 1500, 675);           //加载背景图片
	std::cout << "地图背景加载成功！！！\n";
	loadimage(&Bar, "PCT/bar.png",500,80);  
	loadimage(&shovel, "PCT/shovel.png");
	loadimage(&bin_go, "PCT/bin_go.png");
	loadimage(&bin_break, "PCT/bin_break");
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

	for (int i = 0; i < num_use_cards; i++)
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
	//int num_0 = num_a_cards(n);                      //计算一个植物的动态照片能有几张

	std::ofstream plant_o;                                      //开始将一个植物卡片的文件地址写入一个txt文件
	plant_o.open("plant_name.txt");                          
	for (int i = 0; i < num_use_cards; i++)
	{
		for (int j = 0; j < MAX_plant_image; j++)
		{	
			plant_o << "PCT/plant/" << i << "/" << j << ".png\n";
		}
	} 
	plant_o.close();                                      //关闭写入

	std::ifstream plant_i("plant_name.txt");             //开始读取刚刚写完的植物图片文件地址名称

	for (int i = 0; i < num_use_cards; i++)
	{
		for (int j = 0; j <= MAX_plant_image; j++)
		{
			plant_i.getline(save_name, 62);

			std::ifstream test_open(save_name);                     //判断文件是否存在(本来是想写一个判断有几个图片的函数的，但没想到直接这么写
			if(test_open.good())                                    //能少写三个函数(一个算有几个图片的、一个函数当前要加载的植物的序号告诉这个函
			{													//数(这不算一个函数)、一个函数将这个函数运行好几次直到全部植物都运行过了）
				num_of_plant_image[i] += 1;
				loadimage(&plant_cards[i][j], save_name);     
			}
		}
	}
	plant_i.close();
}


void click_act()
{   
	//11111111111111111111111111111111111111111111111111111111111111111111111111111
	if (peekmessage(&point))                          //如果获取到了一个鼠标的消息 
	{
//		std::cout << "get消息\n";
		if (point.message == WM_LBUTTONDOWN)     //如果获得了一个鼠标左键按下的消息
		{
			//std::cout << "左点" << std::endl;
			if (point.x >= 358 && point.x <= 770 && point.y >= 8 && point.y <= 70)      //根据卡牌选择植物
			{
				curPlant = (point.x - 356) / 47;
				std::cout << curPlant << std::endl;
				if (value_plant[curPlant] > your_sunshine)                //判断是否有足够的阳光来种植这个植物
				{
					curPlant = -1;
				}
			}


			else if (point.x > 830 && point.x < 830 + 59 && point.y>20 && point.y < 20 + 90)      //召唤铲子
			{
				curPlant = -2;
				std::cout << "铲子来了" << std::endl;
			}

			if (point.x >= rdom_x && point.y <= rdom_x + 78 && point.y >= mov_y && point.y <= mov_y + 78)   //点击随下落的阳光
			{
				count2 = 0;
				mov_y = -75;
				your_sunshine += 25;
			}
		}
		//2222222222222222222222222222222222222222222222222222222222222222222222222222222
		if ((point.message == WM_LBUTTONDOWN || point.message == WM_LBUTTONUP ) && curPlant != -1 && curPlant < num_use_cards)                     //如果选中了一个植物并且又点击了一次鼠标
		{                                   //这里我增加了一个抬起鼠标就放置植物的判断，结合下面在草坪上抬起鼠标才会改变pl.x的值，所以误打误撞，我实现了既可以点击又可以拖动的操作模式
			if (curPlant != -1 && point.x >= pl.l && point.x <= pl.r && point.y >= pl.u1 && point.y <= pl.d1)          //从上往下第一行
			{
				pl.y = 1;
				pl.x = (point.x - pl.l+pl.dist) / pl.dist;
				std::cout << pl.x << " and " << pl.y << "   pl.dis1 :" << pl.dist << "   上 ：" << pl.u1 << " 下 ：" << pl.d1 << " 左  :" << pl.l << " 右 ：" << pl.r << std::endl;
			}
			else if (curPlant != -1 && point.x >= pl.l && point.x <= pl.r && point.y >= pl.u2 && point.y <= pl.d2)      //第二行
			{
				pl.y = 2;
				pl.x = (point.x - pl.l + pl.dist) / pl.dist;
				std::cout << pl.x << " and " << pl.y << std::endl;
			}
			else if (curPlant != -1 && point.x >= pl.l && point.x <= pl.r && point.y >= pl.u3 && point.y <= pl.d3)      //第三行
			{
				pl.y = 3;
				pl.x = (point.x - pl.l + pl.dist) / pl.dist;
				std::cout << pl.x << " and " << pl.y << std::endl;
			}
			else if (curPlant != -1 && point.x >= pl.l && point.x <= pl.r && point.y >= pl.u4 && point.y <= pl.d4)      //第四行
			{
				pl.y = 4;
				pl.x = (point.x - pl.l + pl.dist) / pl.dist;
				std::cout << pl.x << " and " << pl.y << std::endl;
			}
			else if (curPlant != -1 && point.x >= pl.l && point.x <= pl.r && point.y >= pl.u5 && point.y <= pl.d5)      //第五行
			{
				pl.y = 5;
				pl.x = (point.x - pl.l + pl.dist) / pl.dist;
				std::cout << pl.x << " and " << pl.y << std::endl;
			}

			if (curPlant != -1 && curPlant < num_use_cards && pl.x > 0)                      //将选中的植物放在对应的坑位里
			{
				int p_mid_x = pl.l + pl.dist * (pl.x - 1) + pl.dist / 2 + p_w;
				int p_mid_y = 0;

				switch (pl.y)
				{
				case 1:
					p_mid_y = pl.u1 - (pl.u1 - pl.d1) / 2 + p_h;
					break;
				case 2:
					p_mid_y = pl.u2 - (pl.u2 - pl.d2) / 2 + p_h;
					break;
				case 3:
					p_mid_y = pl.u3 - (pl.u3 - pl.d3) / 2 + p_h;
					break;
				case 4:
					p_mid_y = pl.u4 - (pl.u4 - pl.d4) / 2 + p_h;
					break;
				case 5:
					p_mid_y = pl.u5 - (pl.u5 - pl.d5) / 2 + p_h;
					break;
				default:
					break;
				}

				if (note_plant[pl.y][pl.x] == NULL && curPlant > -1)                     //如果坑位没有植物才能将植物放入坑位
				{
					note_plant[pl.y][pl.x] = &plant_cards[curPlant][0];                   //将这个植物放到他该在的坑位上去
					note_curPlant[pl.x][pl.y] = curPlant;
					note[pl.y][pl.x] = 1;                                              //将这个坑位记录下来
					note_x[pl.y][pl.x] = p_mid_x;
					note_y[pl.y][pl.x] = p_mid_y;

					your_sunshine -= value_plant[curPlant];           //扣除对应阳光币


					//newPNG(NULL, p_mid_x, p_mid_y, &plant_cards[curPlant][0], BLACK);    
					curPlant = -1;
					pl.x = -1;
					pl.y = -1;


				}
				else if (curPlant < -1)                      //使用铲子
				{
					note_plant[pl.y][pl.x] = NULL;           //将这个坑位的植物消除     
					note[pl.y][pl.x] = 0;                    //标志着这个坑位已经没有植物了           
					count[pl.y][pl.x] = 0;					 //将计数器恢复0，免得它一会儿祸害人类（研究了大半天也不知道为什么会有空指针）
					curPlant = -1;
					pl.x = -1;
					pl.y = -1;
				}
			}
		}
	}
}



void Put_image()
{

	//开始准备绘图
	BeginBatchDraw();		//批量绘图 暂不输出           //开始缓冲，即把下面的内容先不显示在屏幕上，而是先缓存在内存中
	putimage(-80, 0, &map);
	putimage(280, 0, &Bar);
	for (int i = 0; i < num_use_cards; i++)           //输出植物卡片图片
	{
		putimage(358 + 50 * i, 8, &cards[i]);
	}
	newPNG(NULL, 830, 20, &shovel, BLACK);


	for (int i = 0; i < ROW; i++)                  //输出动态植物形象
	{
		for (int j = 0; j < COL; j++)
		{
			if (note[i][j] == 1)
			{				
				newPNG(NULL, note_x[i][j], note_y[i][j], note_plant[i][j], BLACK);

				if (count[i][j] < p_speecd * (num_of_plant_image[note_curPlant[i][j]] - 2))
				{
					count[i][j]++;
					if (count[i][j] % p_speecd == 0)                                        //每200次循环更换一张植物照片从而达到缓慢运动的效果
                    {                                                                  //但是不知道是否换个电脑速度就会有所改变
						note_plant[i][j]++;						                                                                                                                            //std::cout << count[i][j] << std::endl;                      //测试时是大功臣，测试完兔死狗烹
					}
				}
				else
				{
					note_plant[i][j] -= (num_of_plant_image[note_curPlant[i][j]] - 2);
					count[i][j] = 0;
				}				
			}
		}
	}


	if (curPlant > -1 && curPlant < num_use_cards)                                    //被选中的植物开始跟着鼠标走
	{
		newPNG(NULL, point.x - 40, point.y - 60, &plant_cards[curPlant][0], BLACK);
	}
	else if (curPlant < -1)
	{
		newPNG(NULL, point.x - 20, point.y - 50, &shovel, BLACK);                    //铲子跟着鼠标走
	}


	random_sun();


	put_text();
	EndBatchDraw();         //结束批量绘图模式，将中间的图片一次性绘制出来                //结束双缓冲，把内存中的内容一次性打印到屏幕上去
}


void put_text()           //输出文本文字
{

	setbkmode(TRANSPARENT);           //显示透明文字
	settextcolor(BLACK);              //设置字体颜色为黑色
	settextstyle(18, 0, "华文行楷");  //设置字体的高、宽（字符的平均宽度.如果为 0,则比例自适应)和字体
	string yourSunshine_ = turn_int_into_char(your_sunshine);        //将一个整数转化为字符串类型
	outtextxy(307, 58, yourSunshine_.c_str());         //输出文字           （使用string类中的 c_str()方法将string类型转化成 char* 类型）

}


//
//void out_plant(int num)
//{
//	BeginBatchDraw();
//	_putimagePNG(point.x, point.y, &plant_cards[num][1]);
//	EndBatchDraw();
//}
                                        //如果把这两个函数放进主函数的循环中去，那么他们就会随着鼠标位置的移动而不断地输出图片，就会导致图片满屏
                                        //所以一定要让会动的图片和不会动的图片一起刷新，这样就能保证新刷出来的图片不管位置在哪都能够被背景图片覆盖
//
//void update_windows()
//{
// rd_x  new
//	BeginBatchDraw();
//	EndBatchDraw();
//}