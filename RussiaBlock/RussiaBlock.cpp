#include"pch.h"
#include "RussiaBlock.h"



const int c_mw = 15; //地图款
const int c_mh = 20; //地图搞
const int c_sh = c_mh + 3; //显示区域的搞 包括title

int blocktype = 0; //方块种类
int blockangle = 0; //方块的角度
int bx = 0; //方块x坐标
int by = 0; //方块y坐标

int keyDown = 0; //当前按下的键
int ticke = 0; //方块计数器
const int ticker = 5; //方块总计数

bool g_bEng; //游戏是否结束


//0 -> " ", 1 -> "█", 2 -> "□", 地图数据<->地图符号

//地图数组
int mapData[c_mh][c_mw]= 
{
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
};

//所有方块 所有角度
const int allblocks[7][4][4][4]=
{
	/*1.长条*/
	{
			{
				0, 0, 0, 0,
				1, 1, 1, 1,
				0, 0, 0, 0,
				0, 0, 0, 0
			},
			{
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0
			},
			{
				0, 0, 0, 0,
				1, 1, 1, 1,
				0, 0, 0, 0,
				0, 0, 0, 0
			},
			{
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0,
				0, 1, 0, 0
			}
		},
		/*2.方块*/
	{
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		}
	},
	/*3.凸型*/
	{
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			1, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			1, 1, 0, 0,
			0, 1, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 0, 0, 0,
			1, 1, 1, 0,
			0, 1, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0
		}
	},
	/*4.Z型*/
	{
		{
			0, 0, 0, 0,
			1, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0
		},
		{
			0, 0, 0, 0,
			1, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			0, 1, 1, 0,
			0, 1, 0, 0
		}
	},
	/*5.反Z型*/
	{
		{
			0, 0, 0, 0,
			0, 0, 1, 1,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0
		},
		{
			0, 0, 0, 0,
			0, 0, 1, 1,
			0, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0
		}
	},
	/*6.L型*/
	{
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 1,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			0, 0, 1, 0,
			0, 1, 1, 0
		},
		{
			0, 0, 0, 0,
			1, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 0, 0,
			0, 1, 0, 0
		}
	},
	/*7.反L型*/
	{
		{
			0, 0, 0, 0,
			0, 0, 1, 0,
			1, 1, 1, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 0, 1, 0,
			0, 0, 1, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 1, 1,
			0, 1, 0, 0,
			0, 0, 0, 0
		},
		{
			0, 0, 0, 0,
			0, 1, 0, 0,
			0, 1, 0, 0,
			0, 1, 1, 0
		}
	}
};

const char* pchs[] = {" ","█", "□" };

//生成新的方块
void newAblock()
{
	blocktype = rand() % 7;
	blockangle = 0;
	bx = 6;
	by = -4;

}

DWORD WINAPI getKeyDown(void* _key)
{
	while (1)
	{
		int code = _getch();
		*(int*)_key = code;
	}
}
//初始化函数
void init()
{
	//为rand产生伪随机数
	srand(unsigned(time(0)));
	newAblock();
	//按键处理
	//创建线程, 将按键存储到keyDown变量中保存
	CreateThread(0, 0,getKeyDown, &keyDown, 0, 0);
}

void reDraw()
{	
	//清屏重新绘制
	system("cls");
	prtTitle();
	prtMap();

}

//绘制标题
void prtTitle()
{
	cout << "******************************" << endl;
	cout << "*         葡萄牙方块         *" << endl;
	cout << "******************************" << endl;
}

//绘制地图
void prtMap()
{
	for (int i = 0; i < c_mh; i++)
	{
		for (int  j = 0; j < c_mw; j++)
		{
			//得到当前地图数据
			const char* pch = Data2Char(mapData[i][j]);
			//判断方块是否正在下落的方块中
			int relay = i - by;
			int relax = j - bx;

			if (relax>=0 && relax <= 3 && relay >= 0 && relay <=3)
			{
				if (allblocks[blocktype][blockangle][relay][relax] == 1)
				{
					pch = "█";
				}
				
			}
			cout << setw(2) << pch;
		}
		cout << endl;
	}
}

//映射函数
const char* Data2Char(int iData)
{
	const char* pch = " ";
	switch (iData)
	{
	case 1:
		pch = "█";
		break;
	case 2:
		pch = "□";
		break;
	default:
		break;
	}
	return pch;
}

//逻辑更新
void logic()
{
	if (ticke++ >= ticker)
	{
		//不断向下移动
		by += 1;
		ticke = 0;
	}
}

//用户输入
void input()
{
	int code = keyDown;
	switch (code)
	{
	case'A':
	case'a':
		//向左移动
		bx -= 1;
		break;
	case 'D':
	case 'd':
		//向右移动
		bx += 1;
		break;
	case 'W':
	case'w':
		//旋转角度变化
		blockangle = (blockangle + 1) % 4;
		break;
	case 'S':
	case 's':
		//向下移动
		by += 1;
		break;

	default:
		break;
	}
	keyDown = 0;
}

void destory()
{
}

int main()
{
	HANDLE hOutput;
	COORD coord = { 0,0 };
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int beginTime = GetTickCount();

	init();
	while (1)
	{
		if (GetTickCount() - 1000 / 6 >= beginTime)
	
		{
			SetConsoleCursorPosition(hOutput, coord);
			reDraw();
			logic();
			input();
			Sleep(33);
			if (g_bEng)
			{
				break;
			}
			beginTime = GetTickCount();
		}
		
	}
	cin.get();
	destory();
}

