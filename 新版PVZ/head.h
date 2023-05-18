/*
基于之前的一点C语言思路，完全自己研究的
每一个字母都是血汗

以下是日志：
根据之前的经验，输出了地图，选项栏，植物卡片等元素
使用文件I/O进行了植物的提前加载
初步写出了鼠标点击控制系统
实现了选中的图片跟随鼠标运动而运动
更换了地图文件，使用了没有透视的地图文件，虽然不专业，但爷的轻狂已经结束了
将地图图片网格化，从而实现了再选中植物的前提下，能够计算再次点击鼠标时，植物位于地图的哪个区块
实现了将植物卡片静态放置在想要放置的区块位置
发现正版植物大战僵尸是按住拖动植物，松手放置植物，进行整改
增加了松手放置植物的功能，原本的点击放置的功能保留
改变了植物放置的思路，让坑位来保存对应植物的信息，便于操控
调整了putImage 函数的运行顺序，并将用于将植物信息保存到坑位的模块放置到了点击响应函数中，明确了各个函数的功能
动态植物：增加了每200次循环都将改换一张植物照片的功能
新增加了一个 if 语句，如果坑位没有植物，才能将下一个植物放进去

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



