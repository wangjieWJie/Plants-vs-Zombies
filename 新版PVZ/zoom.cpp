//上一个源文件写了好多东西
//觉得有点乱，所以将僵尸写到这个文件里面来
//而且我觉得要为以后早做点打算，把功能尽量做成可以传参的函数
//方便以后直接调用就可以了

#include"head.h"







void my_load(string load_name)
{
	int num_0 = num_a_cards(load_name);                      //计算一个植物的动态照片能有几张
	std::cout << num_0 << std::endl;
	//std::ofstream plant_o;                                      //开始将一个植物卡片的文件地址写入一个txt文件
	//plant_o.open("plant_name.txt");
	//for (int i = 0; i < num_use_cards; i++)
	//{
	//	for (int j = 0; j < MAX_plant_image; j++)
	//	{
	//		plant_o << "PCT/plant/" << i << "/" << j << ".png\n";
	//	}
	//}
	//plant_o.close();                                      //关闭写入

	//std::ifstream plant_i("plant_name.txt");             //开始读取刚刚写完的植物图片文件地址名称

	//for (int i = 0; i < num_use_cards; i++)
	//{
	//	for (int j = 0; j <= MAX_plant_image; j++)
	//	{
	//		plant_i.getline(save_name, 62);

	//		std::ifstream test_open(save_name);                     //判断文件是否存在(本来是想写一个判断有几个图片的函数的，但没想到直接这么写
	//		if (test_open.good())                                    //能少写三个函数(一个算有几个图片的、一个函数当前要加载的植物的序号告诉这个函
	//		{													//数(这不算一个函数)、一个函数将这个函数运行好几次直到全部植物都运行过了）
	//			num_of_plant_image[i] += 1;
	//			loadimage(&plant_cards[i][j], save_name);
	//		}
	//	}
	//}
	//plant_i.close();




}



int num_a_cards(string load_name)
{
	string all_of_this = "23";
	string type_name = ".png";
	string char_num = "      ";
	bool make_break = 1;

	std::cout << make_break << std::endl;

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
	delete [ws] one_num;
	std::cout << the_char << std::endl;
	return the_char;
}






