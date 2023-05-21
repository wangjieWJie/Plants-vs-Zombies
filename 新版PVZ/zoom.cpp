//上一个源文件写了好多东西
//觉得有点乱，所以将僵尸写到这个文件里面来
//而且我觉得要为以后早做点打算，把功能尽量做成可以传参的函数
//方便以后直接调用就可以了

#include"head.h"

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
	delete [ws] one_num;
	std::cout << the_char << std::endl;
	return the_char;
}






