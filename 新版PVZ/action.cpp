#include"head.h"
//此文件用于写植物、僵尸的攻击啊、阳光的产生啊、小推车啊等功能

IMAGE p_sunshine[29]{};
IMAGE sun[24]{};
int rdom_x{};               //随机的阳光的x坐标
int rdom_y{};               //随机的阳光的y坐标
int count2{};              //计数器

void random_sun() 
{
	static int cycle = 10 * 10000;                //计数器循环周期

	srand((unsigned int)time(NULL));

	static float mov_y = -10;
	static float dfrn{};

	struct the_rand
	{
		int lx = 193, rx = 953;
		int uy = 154, dy = 564;         //表示产生阳光的范围
	}r; 
	if(count2==88)
	{
		rdom_x = rand() % (r.rx - r.lx) + r.lx;
		rdom_y = rand() % (r.dy - r.uy) + r.uy;

		mov_y = -10;
		dfrn = (rdom_y - mov_y) / 150;
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
		//std::cout << (count2 / 1000) % 22 << std::endl;
		std::cout << mov_y << std::endl;
		newPNG(NULL, rdom_x, mov_y, &sun[(count2 / 500) % 22], BLACK);   //每11000次改变一张图片
	}

}