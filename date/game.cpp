#define _CRT_SECURE_NO_DEPRECATE 1
#include"tansfer.h"

extern IMAGE ImgBg;  //声明外部符号，这里是将全局变量ImgBg引入进来
extern IMAGE ImgBar; //工具栏
extern enum { Bin, Sunflower, count };
extern IMAGE ImgCards[count];
extern char name[64];
extern int curX, curY;
extern IMAGE* ImgPlants[count][20];
extern int curPlant;




bool FileExist(const char* name)      //用最朴素的方法检测文件是否存在
{ 
	FILE* fp = fopen(name, "r");      // fopen  :打开文件      r 是指 以只读方式打开一个文本文件（详情请看计算机课本）
	if (fp == NULL)                   // NULL   ：空
	{
		return false;
	}
	else
	{
		fclose(fp);                   // fcolse :关闭文件      因为文件打开也浪费资源，所以随手关闭是好习惯
		return true;                    
	}
	//  ！！！！！   在项目属性中把c++的SDL检查关掉才可以用上述函数,否则只能加 _s


}





void Initgame() {


	//加载背景图片
	loadimage(&ImgBg, "PCT/ImgBg.png");   //出现错误，所以在项目属性里面把字符集改成了”多字节字符集“
	
	//创建游戏图形窗口
	initgraph(950, 728,1);

	//更新游戏窗口,加载背景
	//UpdateWindow();

	//创建一个工具栏,并放在合适位置
	loadimage(&ImgBar, "PCT/Bar.png"); 
	//UpdateWindow();
	

	//利用枚举 列出植物，并确定植物个数
	//enum {Bin,Sunflower,count};   //在枚举中，第一个变量=0，也就是说count正好能表示植物的个数，，，巧妙

	//创建一个图形数组，用于存放植物卡片
	//IMAGE ImgCards[count];

	//初始化植物卡片

	//将指针（数列）清零。可以用for循环，但是想要把一个数列连续设置为一个值的时候可以用：
	memset(ImgPlants, 0, sizeof(ImgPlants));

	
	for (int i = 0; i < count; i++)
	{
		//生成植物卡片文件名称
		sprintf_s(name, sizeof(name), "PCT/card/card_%d.png", i);
		loadimage(&ImgCards[i], name);


		//开始导入植物的图片组



		for (int j = 0; j < 20; j++)
		{
			//生成植物文件名称
			sprintf_s(name, sizeof(name), "PCT/plant/%d/%d.png", i, j+1);

			//因为每个植物的图片不一样多，所以首先要判断文件是否存在
			if (FileExist(name))
			{
				ImgPlants[i][j] = new IMAGE;  //因为这个数组被初始化为0；所以直接开始加载图片的话，会导致进程无法加载
				                              //new 是C中的函数，用于分配内存（因为graphics的底层语言就是C所以不用C++中的函数分配内存）
				loadimage(ImgPlants[i][j], name);
			}
			else
			{
				break;
			}
		}

	}
	//UpdateWindow();



}



void UserClick()
{
	ExMessage msg;
	static int status = 0;   //因为鼠标移动过程中要不断调用这个函数，所以为了程序能快速运行，这里的status（状态）用静态变量。


	peekmessage(&msg);  //判断有没有消息（鼠标点击或者移动等等），有消息返回真，没有消息返回假
	//getmessage      与之相似的还有getmessge,不过getmessaeg是读取消息，如果没有消息，程序救护卡住，影响用户体验

	if (peekmessage(&msg))
	{
		if (msg.message == WM_LBUTTONDOWN)   //如果消息是鼠标按下
		{
			if (msg.x > 300 && msg.x < 350 + 52 * count && msg.y>6 && msg.y < 71)
			{
				int index = (msg.x - 300) / 52;      //原理就是....老简单，自己看吧(忽略余数，只看能除几个52（差不多一个卡牌的宽度）)
				status = 1;                     //表示状态，若这条语句执行了，那么status就等于1                                                         //巧妙
				curPlant = index + 1;
				printf("curPlant=%d", curPlant);
			
			}		
		}
		else if (msg.message == WM_MOUSEMOVE  && 1 == status)   //如果是鼠标移动,并且点击下去了
		{
			curX = msg.x;
			curY = msg.y;
		//	printf("X=%d,Y=%d", curX, curY);


		}
		else if (msg.message == WM_LBUTTONUP)      //鼠标松开
		{

		}

	}



}







void UpdateWindow()
{
	BeginBatchDraw();   //开始缓冲，即把下面的内容先不显示在屏幕上，而是先缓存在内存中

	//背景
	putimage(0, 0, &ImgBg);  //0,0 是图片的坐标，窗口左上角是原点，图片左上角是图片的定位点
	//工具栏
	putimage(230, 0, &ImgBar);

	//植物卡片
	for (int i = 0; i < count; i++)
	{
		int x = 305 + i * 52;
		int y = 7;
		putimage(x, y, &ImgCards[i]);
	}

	//渲染 拖动过程中的植物
	if (curPlant > 0)
	{
		//printf("其实我在");
		putimage(curX - 25,curY - 30, ImgPlants[curPlant][0]);     //因为光标在植物的左上角，所以把X，Y减去半个图片的量就使光标指在植物中间了
	}




	EndBatchDraw();   //结束双缓冲，把内存中的内容一次性打印到屏幕上去
}
////;



int main(){

	int a;       //整形 ,证书  4个字节  1000000000000000000000000001

	long ;      //  长整形  

	long long  ;
	
	short ;   //duanzhengxin 
	
	float ;   //浮点型  ， 两位

	double ;    //双精度浮点型   

	unsigned int ;  //无符号位 

	register long ;    //寄存器  内存   CPU   栈溢出
	              //内存




	//scanf("%c





return 0;
}