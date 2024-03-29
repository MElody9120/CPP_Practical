#pragma once

#include<graphics.h>
#include<math.h>
#include "Role.h"
#include "MyMap.h"
#include "Mydefine.h"

const int MAP_NUMBER = 30;
const int COINS_NUMBER = 70;
const int SCORE_NUMBER = 5;

class scene
{
private:
	double xBg;//背景坐标
	double yBg;
	int xMap;//地图坐标
	int yMap;
	MyMap map[MAP_NUMBER];
	POINT coins[COINS_NUMBER];
	POINT score[SCORE_NUMBER];
	IMAGE img_bg;
	IMAGE img_map;
	IMAGE img_scenery;
	IMAGE img_coin;
	double scenery_iframe;//帧数
	double coin_iframe;
	double score_iframe[SCORE_NUMBER];
	int world;//第world关
public:
	scene(int world);
	~scene(void);
	MyMap *getMap() { return map; }
	POINT *getCoins() { return coins; }
	void setScorePos(int x, int y);
	void createMap(int world);//创造第world关的地图	
	void createCoin(); //创造第world关的地图
	void action(role *myRole);
	void show();//展示游戏主界面
	bool isEnding(int distance); //以距离作为判断是否到达通关条件的情况
};
 

//此处inline用法的意义为 在C++17 以后 inline 或	inline变量拥有一个属性，即可在程序中拥有多于一次定义，只要每个定义出现在不同的编译单元中
//对于非 static inline 函数和变量 (C++17 起)）且所有定义等同
//使用inline可以防止在既声明又实现的头文件之间相互调用所导致的编译器报错问题，与课本中inline性质无关



/*
#include "scene.h"
#include<graphics.h>
#include"math.h"
#include"role.h"
#include"mydefine.h"

inline scene::scene(int world)
{
	loadimage(&img_bg, "res\\mapsky.bmp", XSIZE, 4 * YSIZE); //读取图片
	loadimage(&img_map, "res\\map.bmp");
	loadimage(&img_scenery, "res\\scenery.bmp");
	loadimage(&img_coin, "res\\ani.bmp");

	//地图坐标设置初始化
	xBg = 0;
	yBg = 0;
	xMap = 0;
	yMap = 0;

	//帧数设置初始化
	scenery_iframe = 1;
	coin_iframe = 1;

	//初始化地图元素
	for (int i = 0; i<MAP_NUMBER; i++)
	{
		map[i].x = 0;
		map[i].y = 0;
		map[i].id = 0;
		map[i].u = 0;
		map[i].xAmount = 0;
		map[i].yAmount = 0;
	}

	//初始化金币元素
	for (int j = 0; j<COINS_NUMBER; j++)
	{
		coins[j].x = 0;
		coins[j].y = 0;
	}
	for (int k = 0; k<SCORE_NUMBER; k++)
	{
		score[k].x = 0;
		score[k].y = 0;
		score_iframe[k] = 0;
	}
	this->world = world; // 用this指针传递world的值（区分成员函数参数与类的数据成员同名的情况

	createCoin();
	createMap(world);
}
inline scene::~scene(void)
{
}

// 以距离作为判断是否到达通关条件的情况
inline bool scene::isEnding(int distance)
{
	switch (world)
	{
	case 1:
		if (distance > 94 * WIDTH)
		{
			return true;
		}
		return false;
	case 2:
		if (distance > 104 * WIDTH)
		{
			return true;
		}
		return false;
	case 3:
		if (distance > 94 * WIDTH)
		{
			return true;
		}
		return false;
	}
	return false;
}

//创造之卷
inline void scene::createMap(int world)
{
	if (world == 1)
	{
		//编辑地图  第1-2个参数X，Y为地图坐标，第3个参数为map id 即采用第几副图的地图块 第4-5个参数分别为地图X,Y轴上的砖块数量
		MyMap m[] = { { 0,9,4,15,3 },{ 18,8,3,9,4 },{ 27,9,3,37,3 },{ 67,9,3,4,3 },{ 74,9,3,1,3 },{ 78,9,3,28,3 },
		{ 10,6,2,4,1 },{ 40,4,2,3,1 },{ 62,6,2,1,1 },{ 65,4,2,5,1 },
		{ 36,7,10,1,1 },{ 45,7,10,1,1 },{ 80,7,10,1,1 },{ 90,7,10,1,1 },
		{ 19,6,11,1,1 },{ 23,6,11,1,1 },{ 32,7,11,1,1 },{ 49,7,11,1,1 },{ 53,7,11,1,1 },{ 57,7,11,1,1 },{ 93,7,11,1,1 },
		{ 101,7,12,1,1 },
		{ 15,10,13,1,1 },{ 64,10,13,1,1 },{ 71,10,13,1,1 },{ 75,10,13,1,1 }
		};
		int i = 0;
		while (m[i].id>0 && m[i].id<15 && i<MAP_NUMBER) //map id 表示采用地图的图形模型
		{
			switch (m[i].id)
			{
			case 1:
			case 3:
			case 4:
			case 5:
				//不同的图形模型拥有不同的摩擦力
			case 6:
				m[i].u = (V_MAX / T1) / G;
				break;
			case 2:
				m[i].u = (V_MAX / T2) / G;
				break;
			default:
				m[i].u = (V_MAX / T3) / G;
				break;
			}
			map[i] = m[i];
			i++;
		}
	}
	else if (world == 2)
	{
		//编辑地图
		MyMap m[] = { { 18,9,2,4,1 },{ 23,6,2,6,1 },{ 25,3,2,3,1 },{ 31,10,2,2,1 },{ 39,7,2,1,1 },{ 39,4,2,1,1 },{ 96,7,2,2,1 },{ 99,5,2,2,1 },{ 102,3,2,12,1 },
		{ 0,10,4,15,2 },{ 38,10,4,10,2 },{ 50,10,4,1,2 },{ 53,10,4,1,2 },{ 56,10,4,1,2 },{ 61,10,4,10,2 },{ 75,10,4,3,2 },{ 82,10,4,11,2 },
		{ 67,9,8,1,1 },{ 68,8,8,1,2 },{ 69,7,8,1,3 },{ 70,6,8,1,4 },{ 75,6,8,1,4, },{ 76,7,8,1,3 },{ 77,8,8,1,2 },
		{ 42,8,11,1,1 },
		{ 111,1,12,1,1 },
		{ 4,8,14,1,1 },{ 9,8,14,1,1 },{ 83,8,14,1,1 },{ 89,8,14,1,1 },
		};
		int i = 0;
		while (m[i].id>0 && m[i].id<15 && i<MAP_NUMBER)
		{
			switch (m[i].id)
			{
			case 1:
			case 3:
			case 4:
			case 5:
			case 6:
				//不同的图形模型拥有不同的摩擦力
				m[i].u = (V_MAX / T1) / G;
				break;
			case 2:
				m[i].u = (V_MAX / T2) / G;
				break;
			default:
				m[i].u = (V_MAX / T3) / G;
				break;
			}
			map[i] = m[i];
			i++;
		}
	}
	else if (world == 3)
	{
		//编辑地图
		MyMap m[] = { { 0,-1,5,104,2 },{ 0,9,5,15,3 },{ 18,8,5,9,4 },{ 27,9,5,37,3 },{ 67,9,5,4,3 },{ 74,9,5,1,3 },{ 78,9,5,28,3 },
		{ 10,6,2,4,1 },{ 18,4,2,44,1 },{ 62,6,2,1,1 },{ 65,4,2,5,1 },
		{ 36,7,10,1,1 },{ 45,7,10,1,1 },{ 80,7,10,1,1 },{ 90,7,10,1,1 },
		{ 19,6,11,1,1 },{ 23,6,11,1,1 },{ 32,7,11,1,1 },{ 49,7,11,1,1 },{ 53,7,11,1,1 },{ 57,7,11,1,1 },{ 93,7,11,1,1 },
		{ 101,7,12,1,1 },
		{ 15,10,13,1,1 },{ 64,10,13,1,1 },{ 71,10,13,1,1 },{ 75,10,13,1,1 }
		};
		int i = 0;
		while (m[i].id>0 && m[i].id<15 && i<MAP_NUMBER)//
		{
			switch (m[i].id)
			{
			case 1:
			case 3:
			case 4:
			case 5:
			case 6:
				//不同的图形模型拥有不同的摩擦力
				m[i].u = (V_MAX / T1) / G;
				break;
			case 2:
				m[i].u = (V_MAX / T2) / G;
				break;
			default:
				m[i].u = (V_MAX / T3) / G;
				break;
			}
			map[i] = m[i];
			i++;
		}
	}
}

//创造金币之卷
inline void scene::createCoin()
{
	if (world == 1)
	{
		POINT p[] = { { 10,5 },{ 11,5 },{ 12,5 },{ 13,5 },{ 66,3 },{ 67,3 },
		{ 68,3 },{ 69,3 },{ 74,5 },{ 74,6 },{ 74,7 },{ 74,8 },
		{ 82,7 },{ 83,8 },{ 84,7 },{ 85,8 },{ 86,7 },{ 87,8 },{ 88,7 },{ 89,8 }
		};
		int i = 0;
		while (i <= sizeof(p) / sizeof(p[0])) //设置硬币
		{
			coins[i].x = p[i].x;
			coins[i].y = p[i].y;
			i++;
		}
	}
	else if (world == 2)
	{
		POINT p[] = { { 25,2 },{ 26,2 },{ 27,2 },{ 32,4 },{ 32,5 },{ 32,6 },{ 32,7 },{ 32,8 },{ 50,6 },{ 53,6 },{ 56,6 } };
		int i = 0;
		while (i <= sizeof(p) / sizeof(p[0]))
		{
			coins[i].x = p[i].x;
			coins[i].y = p[i].y;
			i++;
		}
	}
	else if (world == 3)
	{
		POINT p[] = { { 19,2 },{ 21,2 },{ 23,2 },{ 25,2 },{ 27,2 },{ 29,2 },{ 31,2 },{ 33,2 },{ 35,2 },{ 37,2 },{ 39,2 },{ 41,2 },{ 43,2 },{ 45,2 },{ 47,2 },{ 49,2 },{ 51,2 },{ 53,2 },{ 55,2 },{ 57,2 },{ 59,2 },
		{ 66,3 },{ 67,3 },{ 68,3 },{ 69,3 },{ 74,5 },{ 74,6 },{ 74,7 },{ 74,8 },
		{ 82,7 },{ 83,8 },{ 84,7 },{ 85,8 },{ 86,7 },{ 87,8 },{ 88,7 },{ 89,8 }
		};
		int i = 0;
		while (i <= sizeof(p) / sizeof(p[0]))
		{
			coins[i].x = p[i].x;
			coins[i].y = p[i].y;
			i++;
		}
	}
}

//展现头顶加分情况
inline void scene::setScorePos(int x, int y)
{
	for (int i = 0; i<SCORE_NUMBER; i++)
	{
		if (score[i].x == 0 && score[i].y == 0)
		{
			score[i].x = x;
			score[i].y = y;
			score_iframe[i] = 1;
			break;
		}
	}
}

//主角的运动控制情况，所导致的背景变化情况
inline void scene::action(role *myRole)
{
	//由主角的坐标改变背景和地图的坐标，使主角有向前运动的感觉
	int xmap = xMap;
	xMap = (int)(myRole->getHero())->x0;//获取role里面的原点坐标;
	double bgStep = fabs((myRole->getHero())->vX)*TIME*UNREAL_HEIGHT / REAL_HEIGHT / K_MAP_BG;
	if ((myRole->getHero())->x == XRIGHT && (myRole->getHero())->vX > 0 && xmap != xMap)//如果主角已经到达右边界限且正在向右运动
	{
		xBg -= bgStep;//背景向后移动
	}
}

//控制背景移动
inline void scene::show()
{
	if (xBg <= -img_bg.getwidth())
	{
		xBg = 0;
	}
	yBg = -(world - 1)*YSIZE;
	putimage((int)xBg, (int)yBg, &img_bg);
	putimage(img_bg.getwidth() + (int)xBg, (int)yBg, &img_bg);
	//控制地图移动
	int i = 0;
	while (map[i].id>0 && i<MAP_NUMBER)//map[i]中有数据才参与运算
	{
		for (int j = 0; j<map[i].xAmount; j++)
			for (int k = 0; k<map[i].yAmount; k++)
			{
				int x = xMap + map[i].x*WIDTH + j * WIDTH;
				int y = yMap + map[i].y*HEIGHT + k * HEIGHT;
				int x0 = 0;
				int y0 = (map[i].id - 1)*HEIGHT;
				if (map[i].id>9)
				{
					if (map[i].id == 10)
						putimage(x, y, 2 * WIDTH, 2 * HEIGHT, &img_map, x0, y0);
					else
					{
						y0 = (map[i].id - 11) * 4 * HEIGHT;
						putimage(x, y, 3 * WIDTH, 2 * HEIGHT, &img_scenery, ((int)scenery_iframe - 1) * 3 * WIDTH, y0 + 2 * HEIGHT, SRCAND);
						putimage(x, y, 3 * WIDTH, 2 * HEIGHT, &img_scenery, ((int)scenery_iframe - 1) * 3 * WIDTH, y0, SRCPAINT);
						scenery_iframe += F;
						if (scenery_iframe >= 3)
							scenery_iframe = 1;
					}
				}
				else
					putimage(x, y, WIDTH, HEIGHT, &img_map, x0, y0);
			}
		i++;
	}

	//控制硬币
	coin_iframe += TIME * 7; //金币动态效果的展示
	if ((int)coin_iframe == 5)
	{
		coin_iframe = 1;
	}
	int j = 0;
	while (j<COINS_NUMBER)
	{
		if (coins[j].x != 0)
		{
			int x = coins[j].x*WIDTH;
			int y = coins[j].y*HEIGHT;
			putimage(xMap + x, y, WIDTH, HEIGHT, &img_coin, ((int)coin_iframe - 1)*WIDTH, 9 * HEIGHT, SRCAND);
			putimage(xMap + x, y, WIDTH, HEIGHT, &img_coin, ((int)coin_iframe - 1)*WIDTH, 8 * HEIGHT, SRCPAINT);
		}
		j++;
	}
	//下面代码用于控制吃到硬币的效果
	for (int k = 0; k<SCORE_NUMBER; k++)
	{
		if (score[k].x != 0 && score[k].y != 0)
		{
			score_iframe[k] += TIME * 8;
			if ((int)score_iframe[k] == 5)
			{
				score_iframe[k] = 1;
				score[k].x = 0;
				score[k].y = 0;
			}
			else
			{
				int x = (int)xMap + score[k].x*WIDTH;
				int y = score[k].y*HEIGHT;
				putimage(x, y, WIDTH, HEIGHT, &img_coin, ((int)score_iframe[k] - 1)*WIDTH, 11 * HEIGHT, SRCAND);
				putimage(x, y, WIDTH, HEIGHT, &img_coin, ((int)score_iframe[k] - 1)*WIDTH, 10 * HEIGHT, SRCPAINT);
			}
		}
	}
}
*/