#pragma once

#include<iostream>
#include<iomanip>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

//初始化
void init();
//重新绘制地图
void reDraw();
//绘制标题
void prtTitle();
//绘制地图
void prtMap();
//映射函数
const char* Data2Char(int iData);
//更新逻辑
void logic();
//接受用户输入函数
void input();
//销毁函数
void destory();