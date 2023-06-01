#include"head.h"
//此文件用于写植物、僵尸的攻击啊、阳光的产生啊、小推车啊等功能

IMAGE p_sunshine[29]{};
IMAGE sun[24]{};
int rdom_x{};               //随机的阳光的x坐标
int rdom_y{};               //随机的阳光的y坐标
int count2 = 10 * 10000 * 0.2; //计数器  起始值不是0是为了第一个阳光能在开始后不久就能降落下来
float mov_y = -75;           //阳光的起始位置以及以后的运动轨迹
float dfrn{};                //每次下落的间隔


void random_sun() 
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

	if (count2 > 0.4* cycle)
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






void my_load(IMAGE get_in[], string load_name)
{
	int num_0 = num_a_cards(load_name);                      //计算一个植物的动态照片能有几张
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



int num_a_cards(string load_name)
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



int wei_shu(int  a)
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


string turn_int_into_char(int a)
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


