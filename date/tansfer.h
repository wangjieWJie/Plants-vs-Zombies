#define _CRT_SECURE_NO_DEPRECATE 1
/*
开发日志
1、创建最基本的游戏背景
2、实现游戏最顶部的工具栏
3、创建游戏中的植物卡片
4、实现拖动卡片出现植物




*/
#include<stdio.h>
#include<graphics.h>    //easy_X图形库

void _putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

#define WIN_WIDTH  900   //窗口宽度
#define WIN_HEIGHT 600   //窗口高度



void Initgame();
void UpdateWindow();
void UserClick();
bool FileExist(const char* name);
