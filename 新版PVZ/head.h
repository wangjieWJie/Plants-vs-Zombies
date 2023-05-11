/*
基于之前的一点C语言思路，完全自己研究的
每一个字母都是血汗
*/
#include<iostream>
#include<fstream>
#include<graphics.h>
#include<cstring>



void Initmap();           //加载背景图
void load_cards();        //加载卡片图片
void load_plants();         
//void load_all_plants();//将植物图片加载到内存中保存着以备以后使用
//int num_a_cards(int);                   //计算某个植物由几个图片构成
void Put_image();          //输出上述图片
void click_act();           //接受鼠标信息并做出相关反应
void out_plant(int num);       //接受植物序号并加载相关植物图片
void update_windows();





//其他一些工具
void newPNG(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor);     //透明化PNG贴图



