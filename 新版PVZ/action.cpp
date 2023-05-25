#include"head.h"
//此文件用于写植物、僵尸的攻击啊、阳光的产生啊、小推车啊等功能

IMAGE p_sunshine[29]{};
int rd_x{};               //随机的阳光的x坐标
int rd_y{};               //随机的阳光的y坐标
int count2{};              //计数器
void random_sun() 
{
	unsigned seed;
	seed = time(0);
	srand(seed);

	struct the_rand
	{
		int lx = 193, rx = 953;
		int ly = 154, dy = 564;         //表示产生阳光的范围
	}r; 
	if(count2==0)
	{
		rd_x = rand() % (953 - 193) + 193;
		rd_y = rand() % (564 - 154) + 154;
	}

	count2++;
	count2 = count2 >= 10000 ? 0 : count2;
	std::cout << count2 << std::endl;
}