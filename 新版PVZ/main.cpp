#include"head.h"

                    


int main()
{
	//设置好随机数工具
	srand((unsigned int)time(NULL));


	Initmap();          // 初始化一个关卡地图界面
	load_cards();
	load_plants();

	my_load(easy_zoom_go3,"PCT/zoom/go_3/");    //将一个普通僵尸的第三种走路姿势加载到内存中
	my_load(easy_zoom_wait2,"PCT/zoom/wait_2/");   //将一个普通僵尸的第二种等待姿势加载进来
	my_load(p_sunshine, "PCT/sunshine/");         //加载阳光图片
	my_load(sun, "PCT/sun/");         //加载从天而降阳光图片




	while(1)
	{
		random_sun();

		click_act();
//		update_windows();
	    Put_image();


	}
	std::cin.get();       //大佬用的 getch 我不会用，就整个这个用吧，大佬说这样更好

	//closegraph();          // 关闭绘图窗口
	return 0;
}


