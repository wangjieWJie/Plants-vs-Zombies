#include"head.h"

int main()
{
	Initmap();          // 初始化一个关卡地图界面
	load_cards();
	load_plants();
	Put_image();

	while(1)
	{

		click_act();
		//update_windows();


	}
	std::cin.get();       //大佬用的 getch 我不会用，就整个这个用吧，大佬说这样更好

	//closegraph();          // 关闭绘图窗口
	return 0;
}


