#include"head.h"



int main()
{
	Initmap();          // 初始化一个关卡地图界面
	load_cards();
	load_plants();

	my_load(easy_zoom_go3,"PCT/zoom/go_3/");    //将一个普通僵尸的第三种走路姿势加载到内存中
	my_load(easy_zoom_wait2,"PCT/zoom/wait_2/");





	while(1)
	{

		click_act();
//		update_windows();
	    Put_image();


	}
	std::cin.get();       //大佬用的 getch 我不会用，就整个这个用吧，大佬说这样更好

	//closegraph();          // 关闭绘图窗口
	return 0;
}


