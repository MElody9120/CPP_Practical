#pragma once
#include<graphics.h>
#include "MyMap.h"
#include"Mydefine.h"
#include"Enemy.h"

const int ENEMY_TOTE = 30; //敌人数量
const int BOMB_NUMBER = 5; 

class scene;

struct Hero
{
	int x;//主角的当前坐标（在屏幕上的坐标）
	int y;
	double xx;//主角的坐标（double型）
	double yy;
	double x0;//原点坐标
	double vX;//速度
	double vY;
	int turn;//主角运动的方向
	POINT direction; //主角面向的方向
	bool isFly;//主角是否在空中
	bool died;//主角是否死亡
	bool ending;//主角是否马上就要过关
	bool passed;//主角是否过关
};

class role
{
private:
	int world;
	int KEY;
	scene *myScene; //创建地图
	Hero myHero;//定义一个主角
	Enemy myEnemy[ENEMY_TOTE];//定义若干敌人
	POINT bombs[BOMB_NUMBER];//定义若干爆炸点
	IMAGE img_hero; // 定义图像对象
	IMAGE img_enemy;
	IMAGE img_showBomb;
	int hero_iframe;//用于控制主角、敌人和爆炸的加载帧（加载第几副图，以帧数进行控制来图片的刷新达成动态演示）
	double enemy_iframe;
	double bomb_iframe[BOMB_NUMBER];
	int score;//分数展示
	MyMap *touchMap(int x, int y, scene *myScene);//用于表示人物是否接触地图边缘（判断移动背景的重要过程
	POINT *touchCoins(int x, int y, scene *myScene);//用于表示人物是否吃到金币
	Enemy *touchEnemy(int x, int y, Enemy *emy);//用于表示人物是否接触敌人
	bool isTouch(POINT *p1, POINT *p2);//用于判断人物是否在地图中(对于判断人物掉入陷阱死亡判断有关键作用
	void setBomb(int x, int y);//用于展示爆炸效果
public:
	role(int world);
	~role() {};
	Hero *getHero()  //传递坐标信息(指针大法好
	{ 
		return &myHero;
	}
	bool isDied()
	{ 
		return myHero.died;
	}
	bool isPassed() 
	{ 
		return myHero.passed;
	}
	void createEnemy(int world);
	void show(); //用于控制人物的帧数完成人物动态效果
	void action(int KEY, scene *myScene); //用于反应人物的动作行为
	int getScore() 
	{
		return score;
	}
};


//此处inline用法的意义为 在C++17 以后 inline 或	inline变量拥有一个属性，即可在程序中拥有多于一次定义，只要每个定义出现在不同的编译单元中
//对于非 static inline 函数和变量 (C++17 起)）且所有定义等同
//使用inline可以防止在既声明又实现的头文件之间相互调用所导致的编译器报错问题，与课本中inline性质无关

/*
#include "Role.h"
#include<graphics.h>
#include"Mydefine.h"
#include<math.h>
#include"Rule.h"
#include<conio.h>
#include"Enemy.h"
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")   //给游戏添加音乐要用到它



inline role::role(int world)
{
	//以下为角色部分
	myHero.x = X0; //采用宏定义常量进行初始
	myHero.y = X0;
	myHero.xx = myHero.x; //赋予主角当前坐标的位置(初始化的位置
	myHero.yy = myHero.y;
	myHero.x0 = 0; //将人物的信息初始化
	myHero.vX = 0;
	myHero.vY = 0;
	myHero.turn = 1; //主角的运动方向为正向
	myHero.direction.x = 0; //主角面向的方向
	myHero.direction.y = 0;
	myHero.isFly = true; //bool型变量很好的反应了人物当前的状态
	myHero.died = false;
	myHero.ending = false;
	myHero.passed = false;

	//以下用于动画展示以及界面人物展示
	hero_iframe = 1; //用于控制主角打开图片的帧数
	enemy_iframe = 1;
	score = 0;
	loadimage(&img_hero, "res\\role.bmp");
	loadimage(&img_enemy, "res\\ani.bmp");
	loadimage(&img_showBomb, "res\\ani.bmp");

	for (int i = 0; i<ENEMY_TOTE; i++)
	{
		myEnemy[i].x = 0;
		myEnemy[i].y = 0;
		myEnemy[i].turn = 0;
	}
	for (int j = 0; j<BOMB_NUMBER; j++)
	{
		bombs[j].x = 0;
		bombs[j].y = 0;
		bomb_iframe[j] = 0;
	}


	createEnemy(world); //创造世界,乌拉乌拉

	mciSendString("open res\\死亡.mp3 alias music_died", NULL, 0, NULL);
	mciSendString("open res\\跳.mp3 alias music_jump", NULL, 0, NULL);
	mciSendString("open res\\金币.mp3 alias music_coin", NULL, 0, NULL);
	mciSendString("open res\\踩敌人.mp3 alias music_tread", NULL, 0, NULL);
}


//以下用为创建敌人
inline void role::createEnemy(int world)
{
	if (world == 1)
	{
		Enemy emy[] = { { 3,8,1 },{ 18,7,-1 },{ 25,7,1 },{ 28,8,-1 },{ 33,8,-1 },{ 39,8,1 },{ 68,3,1 },{ 66,8,-1 },{ 81,6,1 },{ 92,6,1 } };
		//创建敌人的属性 第一二个参数为敌人的坐标,第三个参数为敌人的运动方向
		int i = 0;
		//将创造出来的敌人传递给myEnemy函数达成控制敌人的具体行为以及动态展示
		while (i <= sizeof(emy) / sizeof(emy[0]))
		{
			myEnemy[i].x = emy[i].x*WIDTH;//以像素点进行传递
			myEnemy[i].y = emy[i].y*HEIGHT;
			myEnemy[i].turn = emy[i].turn;
			i++;
		}
	}
	else if (world == 2)
	{
		Enemy emy[] = { { 18,8,1 },{ 24,5,1 },{ 28,5,-1 },{ 44,9,1 },{ 99,4,1 },{ 99,8,1 } };
		int i = 0;
		while (i <= sizeof(emy) / sizeof(emy[0]))
		{
			myEnemy[i].x = emy[i].x*WIDTH;
			myEnemy[i].y = emy[i].y*HEIGHT;
			myEnemy[i].turn = emy[i].turn;
			i++;
		}
	}
	else if (world == 3)
	{
		Enemy emy[] = { { 25,3,-1 },{ 31,3,1 },{ 39,3,-1 },{ 50,3,-1 },{ 68,3,1 },{ 66,8,-1 },{ 86,8,1 } };
		int i = 0;
		while (i <= sizeof(emy) / sizeof(emy[0]))
		{
			myEnemy[i].x = emy[i].x*WIDTH;
			myEnemy[i].y = emy[i].y*HEIGHT;
			myEnemy[i].turn = emy[i].turn;
			i++;
		}
	}
}

//用于设置爆炸效果
inline void role::setBomb(int x, int y)
{
	for (int i = 0; i<BOMB_NUMBER; i++)
	{
		if (bombs[i].x == 0 && bombs[i].y == 0)
		{
			bombs[i].x = x;
			bombs[i].y = y;
			bomb_iframe[i] = 1;
			break;
		}
	}
}

//用于判断人物是否在地图中(对于判断人物掉入陷阱死亡判断有关键作用
inline bool role::isTouch(POINT *p1, POINT *p2)
{
	for (int i = 0; i<4; i++)//如果主角4个顶点有一个顶点在地图内，则判断为接触到地图
	{
		if (p1[i].x >= p2[0].x && p1[i].y >= p2[0].y && p1[i].x <= p2[1].x  &&  p1[i].y <= p2[1].y)
		{
			return true;
		}
	}
	return false;
}



//总体思路是判断主角的四个顶点(以像素点的位置进行判断)
//是否至少有一个在地图内，有，则判断为主角碰撞到地图
inline MyMap *role::touchMap(int x, int y, scene *myScene)
{
	int xmap = (int)myHero.x0;
	POINT r[4];//主角4个顶点的坐标（比主角小一圈）
	r[0].x = -xmap + x + 1;
	r[0].y = y + 1;
	r[1].x = -xmap + x + WIDTH - 1;
	r[1].y = y + 1;
	r[2].x = -xmap + x + 1;
	r[2].y = y + HEIGHT - 1;
	r[3].x = -xmap + x + WIDTH - 1;
	r[3].y = y + HEIGHT - 1;


	//以getMap的返回值用于判断地图情况
	int i = 0;
	while (myScene->getMap()[i].id>0 && myScene->getMap()[i].id<11 && i<MAP_NUMBER)//条件：地图存在且为前10种地图
	{
		POINT m[2];//地图左上角顶点和右下角顶点的坐标

		m[0].x = myScene->getMap()[i].x*WIDTH;
		m[0].y = myScene->getMap()[i].y*HEIGHT;

		//以id作为地图块之间的区分（id 为地图块的模型图
		if (myScene->getMap()[i].id == 10)//id为10的地图要大些
		{
			m[1].x = myScene->getMap()[i].x*WIDTH + myScene->getMap()[i].xAmount * 2 * WIDTH;
			m[1].y = myScene->getMap()[i].y*HEIGHT + myScene->getMap()[i].yAmount * 2 * HEIGHT;
		}
		else
		{
			m[1].x = myScene->getMap()[i].x*WIDTH + myScene->getMap()[i].xAmount*WIDTH;
			m[1].y = myScene->getMap()[i].y*HEIGHT + myScene->getMap()[i].yAmount*HEIGHT;
		}
		if (isTouch(r, m))//如果两个矩形相交，则碰撞
		{
			return &(myScene->getMap()[i]);
		}
		i++;
	}
	return NULL;
}
inline POINT *role::touchCoins(int x, int y, scene *myScene)
{
	//总体思路是判断主角的四个顶点是否至少有一个在硬币内，有，则判断为主角碰吃到硬币
	int xmap = (int)myHero.x0;
	POINT r[4];//主角4个顶点的坐标（比主角小一圈）
	r[0].x = -xmap + x + 1;
	r[0].y = y + 1;
	r[1].x = -xmap + x + WIDTH - 1;
	r[1].y = y + 1;
	r[2].x = -xmap + x + 1;
	r[2].y = y + HEIGHT - 1;
	r[3].x = -xmap + x + WIDTH - 1;
	r[3].y = y + HEIGHT - 1;
	int i = 0;
	while (i<COINS_NUMBER)
	{
		POINT m[2];//硬币左上角顶点和右下角顶点的坐标

		m[0].x = myScene->getCoins()[i].x*WIDTH;
		m[0].y = myScene->getCoins()[i].y*HEIGHT;
		m[1].x = m[0].x + WIDTH;
		m[1].y = m[0].y + HEIGHT;
		if (isTouch(r, m))//如果两个矩形相交，则碰撞
			return &(myScene->getCoins()[i]);
		i++;
	}
	return NULL;
}


//以下用于判断角色踩怪的情况
inline Enemy *role::touchEnemy(int x, int y, Enemy *emy)
{
	//总体思路是判断主角的四个顶点是否至少有一个在地图内，有，则判断为主角碰撞到敌人
	int xmap = (int)myHero.x0;
	POINT r[4];//主角4个顶点的坐标（比主角小一圈）
	r[0].x = -xmap + x + 1;
	r[0].y = y + 1;
	r[1].x = -xmap + x + WIDTH - 1;
	r[1].y = y + 1;
	r[2].x = -xmap + x + 1;
	r[2].y = y + HEIGHT - 1;
	r[3].x = -xmap + x + WIDTH - 1;
	r[3].y = y + HEIGHT - 1;
	int i = 0;
	while (i<ENEMY_TOTE)//条件：存在敌人
	{
		if (emy[i].turn != 0)
		{
			POINT m[2];//敌人左上角顶点和右下角顶点的坐标
			m[0].x = emy[i].x;
			m[0].y = emy[i].y;
			m[1].x = m[0].x + WIDTH;
			m[1].y = m[0].y + HEIGHT;
			if (isTouch(r, m))//如果两个矩形相交，则碰撞
			{
				return &emy[i];
			}
		}
		i++;
	}
	return NULL;
}


//以下用于完成图片的动态演示
inline void role::show()
{
	//下面代码用于控制主角的步伐，使主角给人的感觉更像在走路
	//改变主角加载图片的第几帧
	int rolePos = -(int)myHero.x0 + myHero.x;//主角的位置
	if (rolePos / STEP % 2 == 0 && rolePos / STEP % 4 != 0)
	{
		hero_iframe = 2;
	}
	else if (rolePos / STEP % 4 == 0)
	{
		hero_iframe = 1;
	}


	//控制主角的方向
	if (myHero.direction.x == 1)
	{
		myHero.turn = 1;
	}
	else if (myHero.direction.x == -1)
	{
		myHero.turn = -1;
	}
	if (myHero.died == true)
	{
		putimage(myHero.x, myHero.y, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, HEIGHT, SRCAND);
		putimage(myHero.x, myHero.y, WIDTH, HEIGHT, &img_hero, 2 * WIDTH, 0, SRCPAINT);
		//参数 SRCAND SRCPAINT 均为三元光栅操作码，详情参见easyX库函数帮助文档
	}
	else
	{
		if (myHero.turn == 1)
		{
			putimage(myHero.x, myHero.y, WIDTH, HEIGHT, &img_hero, (hero_iframe - 1)*WIDTH, HEIGHT, SRCAND);
			putimage(myHero.x, myHero.y, WIDTH, HEIGHT, &img_hero, (hero_iframe - 1)*WIDTH, 0, SRCPAINT);
			//参数 SRCAND SRCPAINT 均为三元光栅操作码，详情参见easyX库函数帮助文档
		}
		else
		{
			putimage(myHero.x, myHero.y, WIDTH, HEIGHT, &img_hero, (hero_iframe - 1)*WIDTH + 3 * WIDTH, HEIGHT, SRCAND);
			putimage(myHero.x, myHero.y, WIDTH, HEIGHT, &img_hero, (hero_iframe - 1)*WIDTH + 3 * WIDTH, 0, SRCPAINT);
			//参数 SRCAND SRCPAINT 均为三元光栅操作码，详情参见easyX库函数帮助文档
		}
	}
	//下面代码用于控制敌人的步伐，使敌人给人的感觉更像在走路
	//改变敌人加载图片的第几帧
	enemy_iframe += TIME * 5;
	if ((int)enemy_iframe == 3)
	{
		enemy_iframe = 1;
	}
	int i = 0;
	while (i<ENEMY_TOTE)
	{
		if (myEnemy[i].turn != 0)
		{
			putimage((int)myHero.x0 + myEnemy[i].x, myEnemy[i].y, WIDTH, HEIGHT, &img_enemy, ((int)enemy_iframe - 1)*WIDTH, HEIGHT, SRCAND);
			putimage((int)myHero.x0 + myEnemy[i].x, myEnemy[i].y, WIDTH, HEIGHT, &img_enemy, ((int)enemy_iframe - 1)*WIDTH, 0, SRCPAINT);
			//参数 SRCAND SRCPAINT 均为三元光栅操作码，详情参见easyX库函数帮助文档
		}
		i++;
	}

	//下面代码用于控制爆炸效果
	for (int j = 0; j<BOMB_NUMBER; j++)
	{
		if (bombs[j].x != 0 && bombs[j].y != 0)
		{
			bomb_iframe[j] += TIME * 10;
			if ((int)bomb_iframe[j] == 5)
			{
				bomb_iframe[j] = 1;
				bombs[j].x = 0;
				bombs[j].y = 0;
			}
			else
			{
				putimage((int)myHero.x0 + bombs[j].x - WIDTH / 2, bombs[j].y - HEIGHT / 2, 2 * WIDTH, 2 * HEIGHT, &img_showBomb, ((int)bomb_iframe[j] - 1) * 2 * WIDTH, 6 * HEIGHT, SRCAND);
				putimage((int)myHero.x0 + bombs[j].x - WIDTH / 2, bombs[j].y - HEIGHT / 2, 2 * WIDTH, 2 * HEIGHT, &img_showBomb, ((int)bomb_iframe[j] - 1) * 2 * WIDTH, 4 * HEIGHT, SRCPAINT);
				//参数 SRCAND SRCPAINT 均为三元光栅操作码，详情参见easyX库函数帮助文档
			}
		}
	}
}


//以下用于反应键盘操作与地图元素之间的联系
inline void role::action(int KEY, scene *myScene)
{
	myHero.direction.x = 0;//=0表示主角不面向任意个方向
	myHero.direction.y = 0;
	double a = 0;//主角运动的加速度和摩擦力给予的加速度
	double a1 = 0;
	MyMap *map = NULL;
	if ((KEY&CMD_UP) && myHero.isFly == false && myHero.ending == false)//只有当主角没有在空中且主角没过关的时候允许按上升键
	{
		mciSendString("play music_jump from 0", NULL, 0, NULL);
		myHero.isFly = true;//表示主角在空中
		myHero.vY = -sqrt(2 * G*REAL_HEIGHT);
	}
	if (myHero.isFly == true)
	{
		myHero.yy = myHero.yy - (-rule::move(myHero.vY, TIME, G)*UNREAL_HEIGHT / REAL_HEIGHT);//move函数返回单位时间（T）内，主角上升或下降的高度
		myHero.y = (int)myHero.yy;
		map = touchMap(myHero.x, myHero.y + 1, myScene);
		if (map != NULL)
		{
			if (myHero.vY > 0)//表示当主角接触地面时
			{
				myHero.isFly = false;
			}
			myHero.vY = 0;
			myHero.y = (myHero.y + HEIGHT / 2) / HEIGHT * HEIGHT;//运用“+HEIGHT/2”，表示主角的中心
			myHero.yy = myHero.y;
			myHero.direction.y += 1;
		}
		if (myHero.vY>0)
		{
			Enemy *emy = touchEnemy(myHero.x, myHero.y, myEnemy);
			if (emy != NULL)//如果主角踩到敌人
			{
				mciSendString("play music_tread from 0", NULL, 0, NULL);
				score += 5;
				//记下爆炸点的坐标
				setBomb(emy->x, emy->y);
				emy->x = 0;
				emy->y = 0;
				emy->turn = 0;
			}
			if (myHero.y>YSIZE)
			{
				myHero.died = true; //角色死亡
				mciSendString("play music_died from 0", NULL, 0, NULL);
			}
		}
	}
	else
	{
		map = touchMap(myHero.x, myHero.y + 1, myScene);
		if (map == NULL)//如果主角没有碰到地图，及在空中
		{
			myHero.isFly = true;
		}
	}
	if (KEY&CMD_DOWN)
	{
	}

	//运动状态的判断
	if (KEY&CMD_LEFT && myHero.ending == false)
	{
		a -= A_ROLE;
		myHero.direction.x -= 1;
	}
	if (KEY&CMD_RIGHT || myHero.ending == true)
	{
		a += A_ROLE;
		myHero.direction.x += 1;
	}

	//以下代码处理主角水平方向上的运动
	if (myHero.vX*a <= 0 && myHero.vX != 0)
	{
		int k = -(int)(myHero.vX / fabs(myHero.vX));//k代表加速度的方向
		if (map == NULL)
		{
			a1 = 0;
		}
		else
		{
			a1 = k * G*map->u;//由物理公式：a=mg*u/g得出
		}
	}
	double tmp = myHero.vX;
	double H = rule::move(myHero.vX, TIME, a + a1)*UNREAL_HEIGHT / REAL_HEIGHT;
	if (tmp*myHero.vX < 0)
	{
		myHero.vX = 0;
	}
	myHero.xx = myHero.xx + H; //位置
	myHero.x = (int)myHero.xx; //实际位置
	if (myScene->isEnding(-(int)myHero.x0 + myHero.x))//如果主角马上过关
	{
		myHero.ending = true;
	}
	if (myHero.x > XSIZE) //依靠达到绘图框右端点判断是否通关
	{
		myHero.passed = true;
	}
	if (touchMap(myHero.x, myHero.y, myScene) != NULL)
	{
		if (myHero.x > XRIGHT) //用于修正主角所在位置的图像显示
		{
			myHero.x = XRIGHT;
		}
		else
		{
			myHero.x = (int)(myHero.xx - H);
		}
		myHero.xx = myHero.x;
		myHero.vX = 0;
		a = 0;
		a1 = 0;
	}
	if (fabs(myHero.vX) > V_MAX)  //用于修正主角的最大速度
	{
		myHero.vX = myHero.vX / fabs(myHero.vX)*V_MAX;
	}
	//判断出主角是否超出左右界限
	if (myHero.x<XLEFT)  //用于修正主角所在位置的图像显示
	{
		myHero.x = XLEFT;
		myHero.xx = myHero.x;
		myHero.vX = 0;
		a = 0;
	}
	else if (myHero.x>XRIGHT && myHero.ending == false)
	{
		myHero.x0 -= (myHero.x - XRIGHT);
		myHero.x = XRIGHT;
		myHero.xx = myHero.x;
	}



	//以下程序控制敌人的运动
	int i = 0;
	if ((int)(enemy_iframe * 100) % 2 == 0)//控制敌人运动的刷新频率
	{
		while (i<ENEMY_TOTE)
		{
			if (myEnemy[i].turn != 0)
			{
				myEnemy[i].x += myEnemy[i].turn*ENEMY_STEP;
				int x1 = (int)myHero.x0 + myEnemy[i].x;
				int y1 = myEnemy[i].y;
				int x2 = (int)myHero.x0 + myEnemy[i].x + myEnemy[i].turn*WIDTH;
				int y2 = myEnemy[i].y + 1;
				if (touchMap(x1, y1, myScene) != NULL || touchMap(x2, y2, myScene) == NULL)//如果敌人碰到墙壁或者没有踩在陆地上，则敌人向相反方向运动
				{
					myEnemy[i].turn *= -1;
				}
			}
			i++;
		}
	}



	//以下代码判断主角是否吃到金币，若吃到则把金币的坐标记下
	POINT *p = touchCoins(myHero.x, myHero.y, myScene);
	if (p != NULL)
	{
		mciSendString("play music_coin from 0", NULL, 0, NULL);
		score += 10;
		myScene->setScorePos(p->x, p->y); //设置金币坐标
		p->x = 0; // 消除金币(代表吃了金币后金币的消失
		p->y = 0;
	}


	//以下代码判断主角是否撞到敌人
	Enemy *emy = touchEnemy(myHero.x, myHero.y, myEnemy);
	if (emy != NULL && myHero.vY <= 0)//如果主角碰到但不踩到敌人
	{
		myHero.died = true;
		mciSendString("play music_died from 0", NULL, 0, NULL);
	}
}*/




