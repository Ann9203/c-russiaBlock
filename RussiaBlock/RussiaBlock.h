#pragma once

#include<iostream>
#include<iomanip>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

//��ʼ��
void init();
//���»��Ƶ�ͼ
void reDraw();
//���Ʊ���
void prtTitle();
//���Ƶ�ͼ
void prtMap();
//ӳ�亯��
const char* Data2Char(int iData);
//�����߼�
void logic();
//�����û����뺯��
void input();
//���ٺ���
void destory();