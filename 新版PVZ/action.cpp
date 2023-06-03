#include"head.h"
//此文件用于写植物、僵尸的攻击啊、阳光的产生啊、小推车啊等功能

IMAGE p_sunshine[29]{};     
IMAGE sun[24]{};
int rdom_x{};               //随机的阳光的x坐标
int rdom_y{};               //随机的阳光的y坐标
int count2 = 10 * 10000 * 0.2; //计数器  起始值不是0是为了第一个阳光能在开始后不久就能降落下来
float mov_y = -75;           //阳光的起始位置以及以后的运动轨迹
float dfrn{};                //每次下落的间隔


void random_sun()                                      //随机降落阳光
{
	const int cycle = 10 * 10000;                //计数器循环周期

	srand((unsigned int)time(NULL));

	struct the_rand
	{
		int lx = 193, rx = 953;
		int uy = 154, dy = 564;         //表示随机产生阳光的范围
	}r; 
	if (count2 == (0.4 * cycle) - 2)
	{
		rdom_x = rand() % (r.rx - r.lx) + r.lx;       //随机确定一个阳光下落的终点位置
		rdom_y = rand() % (r.dy - r.uy) + r.uy;

		mov_y = -75;                          //重置初始位置和下落速度
		dfrn = (rdom_y - mov_y) / 110;        // 110 表示下落速度，越小下落越快
	}

	count2++;
	count2 = count2 >= cycle ? 0 : count2;
	//std::cout << count2 << std::endl;

	if (count2 > 0.4 * cycle && note_sunshine == 0)
	{
		if (count2 % 250 == 0 && mov_y <= rdom_y)      //每350次执行一次
		{
			mov_y += dfrn;
		}
		//std::cout << mov_y << std::endl;
		newPNG(NULL, rdom_x, mov_y, &sun[(count2 / 500) % 22], BLACK);   //每11000次改变一张图片
	}

}





IMAGE easy_zoom_go3[19]{};
IMAGE easy_zoom_wait2[25]{};






void my_load(IMAGE get_in[], string load_name)              //加载 load_name 文件夹里所有的 .PNG 图片到get_in数组里
{
	int num_0 = num_a_cards(load_name);                    
	std::cout << num_0 << std::endl;
	string all_of_this = "23";
	string type_name = ".png";
	string char_num = "      ";
	int num_count = 0;
	while (num_0)
	{
		char_num = turn_int_into_char(num_count);
		all_of_this = load_name + char_num + type_name;
		loadimage(&get_in[num_count], all_of_this.c_str());          // c_str() 是 ctring 提供的一种方法，能够将string类型转换成 char* 类型返回。
		num_count++;
		num_0--;
	}
}



int num_a_cards(string load_name)                      //接收图片的文件夹位置名称，并返回这个文件夹里有几张 .PNG 图片
{
	string all_of_this = "23";
	string type_name = ".png";
	string char_num = "      ";
	bool make_break = 1;

	int the_num_a_card = 0;
	while (make_break)
	{
		std::ifstream this_test;
		char_num = turn_int_into_char(the_num_a_card);                  //用这个办法最多可以转换0~9之内的数，两位数就不行了，     
		all_of_this = load_name + char_num + type_name;   //所以我们还需要一个整型转换字符串的函数，其中应该还包含一个计算位数的函数（详见 第五章编程题）                      
		std::cout << all_of_this << std::endl;
		this_test.open(all_of_this);

		make_break = this_test.good();
		this_test.close();
		the_num_a_card++;
	}
	the_num_a_card--;
	return the_num_a_card;
}

//int num_a_cards(IMAGE tupianshuzu[])                //计算有几张图片的、接收图片数组的重载
//{
//	bool make_break = 1;
//
//	int the_num_a_card = 0;
//
//	IMAGE* IBegin = 
//		
//	return the_num_a_card;
//}



int wei_shu(int  a)           //计算一个整数有几位的函数
{
	if (a == 0)
	{
		return 1;
	}
	int ws = 0;
	int b = a;
	while (b)
	{
		b /= 10;
		ws++;
	}
	return ws;

}


string turn_int_into_char(int a)              //将一个整数转化为string字符串的函数     ，  如果需要char* 型 则需要用 .c_str() 方法进行转换
{
	int ws = wei_shu(a);
	int* one_num = new int[ws];
	string the_char{};
	string a_num{};
	for (int i = 0; i < ws; i++)
	{
		one_num[ws - i - 1] = a % 10;
		a /= 10;
	}
	for (int i = 0; i < ws; i++)
	{
		the_char += ('0' + one_num[i]);
	}
	delete[ws] one_num;
	//std::cout << the_char << std::endl;
	return the_char;
}



//   移动        速度        细分几步   起点X          起点Y          终点X        终点Y    要移动的图片组      数组的最大下标   运行到最后要修改的标志型参量
void move_it(int speece, int Npart, int pl_startX, int pl_startY, int pl_endX, int pl_endY, IMAGE img_object[], int img_num, int* note)
{

	static float dfrnX = (pl_startX - pl_endX) / Npart;
	static float dfrnY = (pl_startY - pl_endY) / Npart;

	static int m_count{};

	static int pl_mX = pl_startX;        
	static int pl_mY = pl_startY;

	if(m_count>=0)
	{
		if (m_count % speece == 0)
		{
			newPNG(NULL, pl_mX, pl_mY, &img_object[m_count % img_num + 1], BLACK);

			pl_mX += dfrnX;
			pl_mY += dfrnY;

		}
		m_count++;
		m_count > Npart* speece ? m_count : -1;              //循环 Npart 次之后将 m_count
		if (m_count == -1)
		{
			*note = 0;
		}
	}

}


//不接收标志的重载
void move_it(int speece, int Npart, int pl_startX, int pl_startY, int pl_endX, int pl_endY, IMAGE img_object[], int img_num)
{

	static float dfrnX = (pl_startX - pl_endX) / Npart;
	static float dfrnY = (pl_startY - pl_endY) / Npart;

	static int m_count{};

	static int pl_mX = pl_startX;
	static int pl_mY = pl_startY;

	if (m_count >= 0)
	{
		if (m_count % speece == 0)
		{
			newPNG(NULL, pl_mX, pl_mY, &img_object[m_count % img_num + 1], BLACK);

			pl_mX += dfrnX;
			pl_mY += dfrnY;

		}
		m_count++;
		m_count > Npart* speece ? m_count : -1;              //循环 Npart 次之后将 m_count

	}

}


//没有细分步的函数重载  de  只接收一张图片的  重载
void move_it(int speece,  int pl_startX, int pl_startY, int pl_endX, int pl_endY, IMAGE img_object)
{

	static float dfrnX = (pl_startX - pl_endX) / 66;
	static float dfrnY = (pl_startY - pl_endY) / 66;

	static int m_count{};

	static int pl_mX = pl_startX;
	static int pl_mY = pl_startY;

	if (m_count >= 0)
	{
		if (m_count % speece == 0)
		{
			newPNG(NULL, pl_mX, pl_mY, &img_object, BLACK);

			pl_mX += dfrnX;
			pl_mY += dfrnY;

		}
		m_count++;
		m_count > 66* speece ? m_count : -1;              //循环 Npart 次之后将 m_count
	}
}



