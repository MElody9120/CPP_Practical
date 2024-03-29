#pragma once
class control
{
private:
	int key; // key作为反应当前用户输入指令以及传递该指令的重要函数
private:
	int GetCommand();//获取玩家输入的命令
	void pauseClick();//暂停游戏
public:
	control();//主控制函数
	~control();//析构函数
	int getKey();//获取玩家按下的键	
	void gameStart();//游戏开始界面
	void showScore(int score);//在游戏界面中打印分数
	void showLevel(int level);//在游戏界面中打印关数
	void showDied(int life);     //播放主角死亡时的动画
	void showGameOver();         //播放游戏结束时的动画
	void showPassed(int word);   //播放主角过关时的动画
	void showPassedAll();        //播放通关时的动画
};




//此处inline用法的意义为 在C++17 以后 inline 或	inline变量拥有一个属性，即可在程序中拥有多于一次定义，只要每个定义出现在不同的编译单元中
//对于非 static inline 函数和变量 (C++17 起)）且所有定义等同
//使用inline可以防止在既声明又实现的头文件之间相互调用所导致的编译器报错问题，与课本中inline性质无关

/*
#include "Control.h"
#include <conio.h>
#include "Mydefine.h"
#include<graphics.h>
#include<cstdlib>
inline control::control()
{
	key = 0;
}
inline control::~control()
{
}
inline int control::getKey()
{
	if (kbhit()) //kbhit()用于判断是否有键盘输入
	{
		key = GetCommand();
	}
	if (key & CMD_ESC)//如果按了暂停键
	{
		pauseClick();//暂停游戏 
	}
	return key;
}
inline int control::GetCommand()
{
	int c = 0;
	if (GetAsyncKeyState(0X25)) //采用虚拟键值表进行键盘读入控制 16进制表示
	{
		c = CMD_LEFT;
	}
	if (GetAsyncKeyState(0X27))
	{
		c |= CMD_RIGHT;
	}
	if (GetAsyncKeyState(0X26))
	{
		c |= CMD_UP;
	}
	if (GetAsyncKeyState(0X28))
	{
		c |= CMD_DOWN;
	}
	if (GetAsyncKeyState(0X18))
	{
		c |= CMD_ESC;
	}
	return c;
}

//暂停界面的图形显示
inline void control::pauseClick()
{
	BeginBatchDraw();
	POINT points[8] = { { XSIZE / 2 - 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 },{ XSIZE / 2 + 45,YSIZE / 3 + 90 },{ XSIZE / 2 - 45,YSIZE / 3 + 90 } };
	setfillcolor(GREEN);
	fillpolygon(points, 4);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "幼圆加粗");
	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	drawtext("Start", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext("Restar", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	drawtext("Main Menu", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	FlushBatchDraw();
	FlushMouseMsgBuffer();//清空鼠标消息队列，否则会出错(PY群里dalao知道鼠标缓冲区最多读取63个鼠标信息，如果超过则不会继续读取
	while (true)
	{
		BeginBatchDraw();
		MOUSEMSG m = GetMouseMsg();//捕捉鼠标。EasyX库函数
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			EndBatchDraw();
			if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y<YSIZE / 3 + 30)//如果选择“回到游戏”，则返回VIR_RETURN
			{
				key = VIR_RETURN;
				return;
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y<YSIZE / 3 + 60)//如果选择“重新开始”，则返回VIR_RESTART
			{
				key = VIR_RESTART;
				return;
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y<YSIZE / 3 + 90)//如果选择“主菜单”，则返回VIR_HOME
			{
				key = VIR_HOME;
				return;
			}
		case WM_MOUSEMOVE:
			RECT r;
			int i;
			for (i = 0; i<3; i++)
			{
				if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + i * 30 && m.y<YSIZE / 3 + 30 + i * 30)
				{
					r.left = XSIZE / 2 - 45;
					r.top = YSIZE / 3 + i * 30;
					r.right = XSIZE / 2 + 45;
					r.bottom = YSIZE / 3 + 30 + i * 30;
					POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
					setfillcolor(RED);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					switch (i)
					{
					case 0:
						drawtext("Start", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					case 1:
						drawtext("Restar", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					case 2:
						drawtext("Main Menu", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
				}
				else
				{
					if (getpixel(XSIZE / 2 - 45 + 1, YSIZE / 3 + i * 30 + 1) == RED)
					{
						r.left = XSIZE / 2 - 45;
						r.top = YSIZE / 3 + i * 30;
						r.right = XSIZE / 2 + 45;
						r.bottom = YSIZE / 3 + 30 + i * 30;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(GREEN);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						switch (i)
						{
						case 0:
							drawtext("Start", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext("Restar", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext("Main Menu", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					FlushBatchDraw();
				}
			}
		}
	}
}

//游戏开始界面的图形演示
inline void control::gameStart()
{
	cleardevice();

	//Menu菜单的背景图
	IMAGE img1;
	loadimage(&img1, "res\\Menu_bg.bmp", XSIZE, 5 * YSIZE);
	putimage(0, -YSIZE, &img1);

	//Menu菜单内容的构造
	settextstyle(40, 0, "幼圆加粗");
	RECT r1 = { 0, 0, XSIZE, YSIZE / 3 };
	drawtext("Mushroom Travel", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(20, 0, "幼圆加粗");
	RECT r2 = { XSIZE / 2 - 45,YSIZE / 3,XSIZE / 2 + 45,YSIZE / 3 + 30 }; rectangle(XSIZE / 2 - 45, YSIZE / 3, XSIZE / 2 + 45, YSIZE / 3 + 30);
	drawtext("Start", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { XSIZE / 2 - 45,YSIZE / 3 + 30,XSIZE / 2 + 45,YSIZE / 3 + 60 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 30, XSIZE / 2 + 45, YSIZE / 3 + 60);
	drawtext("Abstract", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = { XSIZE / 2 - 45,YSIZE / 3 + 60,XSIZE / 2 + 45,YSIZE / 3 + 90 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 60, XSIZE / 2 + 45, YSIZE / 3 + 90);
	drawtext("Operate", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5 = { XSIZE / 2 - 45,YSIZE / 3 + 90,XSIZE / 2 + 45,YSIZE / 3 + 120 }; rectangle(XSIZE / 2 - 45, YSIZE / 3 + 90, XSIZE / 2 + 45, YSIZE / 3 + 120);
	drawtext("Exit", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	bool HOME = true, INTRODUCTION = false, OPERATION = false;//true表示处于当前页面
															  // 分别表示 主界面 介绍界面 操作介绍界面

	MOUSEMSG m; //easyX库中自带的捕捉鼠标函数
	while (HOME) //即处于主界面
	{
		BeginBatchDraw();
		m = GetMouseMsg(); // m 为鼠标捕捉函数的返回值
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			EndBatchDraw();
			if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 && m.y<YSIZE / 3 + 30 && HOME == 1 && INTRODUCTION == 0 && OPERATION == 0)//如果选择“开始游戏”
			{
				HOME = false;
				break;
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 30 && m.y<YSIZE / 3 + 60 && HOME == 1 && OPERATION == 0)//如果选择“游戏介绍”
			{
				INTRODUCTION = true;
				cleardevice();
				rectangle(50, 50, 213, 220);
				outtextxy(52, 52, "Abstract：");
				outtextxy(52, 82, "Super Mushroom");
				outtextxy(52, 132, "powered by");
				outtextxy(52, 152, "Melody && Minnie");
				RECT R1 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("返回", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 60 && m.y<YSIZE / 3 + 90 && HOME == 1 && INTRODUCTION == 0)//如果选择“操作说明”
			{
				OPERATION = true;
				cleardevice();
				rectangle(50, 50, 213, 220);
				outtextxy(52, 52, "operate：");
				outtextxy(52, 72, "Left： ←键");
				outtextxy(52, 92, "Right：→键");
				outtextxy(52, 112, "Jump： ↑键");
				outtextxy(52, 152, "PP：Esc键");
				RECT R2 = { XSIZE - 46,YSIZE - 26,XSIZE - 2,YSIZE - 2 }; rectangle(XSIZE - 46, YSIZE - 26, XSIZE - 2, YSIZE - 2);
				drawtext("返回", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if (m.x > XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + 90 && m.y < YSIZE / 3 + 120 && HOME == 1 && INTRODUCTION == 0 && OPERATION == 0)//如果选择“退出游戏”
			{
				exit(0); //退出游戏
			}
			else if (m.x>XSIZE - 46 && m.x<XSIZE - 3 && m.y>YSIZE - 26 && m.y<YSIZE - 3 && (INTRODUCTION == 1 || OPERATION == 1))//如果选择“返回”
			{
				cleardevice(); //这个函数用于清除屏幕内容。具体内容查看easyX库函数帮助
				HOME = false, INTRODUCTION = false, OPERATION = false;
				gameStart();
			}
			else
			{
				break;
			}
		case WM_MOUSEMOVE: //鼠标移动消息。easyX库自带
			RECT r;
			if (INTRODUCTION == 1 || OPERATION == 1)
			{
				if (m.x>XSIZE - 46 && m.x<XSIZE - 3 && m.y>YSIZE - 26 && m.y<YSIZE - 3)
				{
					r.left = XSIZE - 46;
					r.top = YSIZE - 26;
					r.right = XSIZE - 2;
					r.bottom = YSIZE - 2;
					POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
					setfillcolor(RED);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					drawtext("返回", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else
				{
					if (getpixel(XSIZE - 46 + 1, YSIZE - 26 + 1) == RED)
					{
						r.left = XSIZE - 46;
						r.top = YSIZE - 26;
						r.right = XSIZE - 2;
						r.bottom = YSIZE - 2;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(BLACK);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						drawtext("返回", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}
			}
			else
			{
				for (int i = 0; i<4; i++)
				{
					if (m.x>XSIZE / 2 - 45 && m.x<XSIZE / 2 + 45 && m.y>YSIZE / 3 + i * 30 && m.y<YSIZE / 3 + 30 + i * 30)
					{
						r.left = XSIZE / 2 - 45;
						r.top = YSIZE / 3 + i * 30;
						r.right = XSIZE / 2 + 45;
						r.bottom = YSIZE / 3 + 30 + i * 30;
						POINT points[8] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
						setfillcolor(RED);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						switch (i)
						{
						case 0:
							drawtext("Start", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 1:
							drawtext("Abstract", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
							drawtext("Operate", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 3:
							drawtext("Exit", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
					else
					{
						if (getpixel(XSIZE / 2 - 45 + 1, YSIZE / 3 + i * 30 + 1) == RED)//这个函数用于获取点的颜色.easyX库
						{
							r.left = XSIZE / 2 - 45;
							r.top = YSIZE / 3 + i * 30;
							r.right = XSIZE / 2 + 45;
							r.bottom = YSIZE / 3 + 30 + i * 30;
							POINT points[4] = { { r.left,r.top },{ r.right,r.top },{ r.right,r.bottom },{ r.left,r.bottom } };
							setfillcolor(BLACK);
							fillpolygon(points, 4);
							setbkmode(TRANSPARENT);
							switch (i)
							{
							case 0:
								drawtext("Start", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 1:
								drawtext("Abstract", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 2:
								drawtext("Operate", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							case 3:
								drawtext("Exit", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
								break;
							}
						}
					}
				}
			}
			FlushBatchDraw();
			break;
		default:
			break;
		}
	}
}


inline void control::showScore(int score)
{
	settextstyle(0, 0, "宋体");
	char s1[20] = "SCORE:  ";
	char s2[5];
	itoa(score, s2, 10);//配合 outtextxy 的函数原型 即只接受字符型
	strcat(s1, s2);
	setbkmode(TRANSPARENT);
	outtextxy(10, 10, s1);
	setbkmode(OPAQUE);
}

inline void control::showLevel(int level)
{
	settextstyle(0, 0, "宋体");
	char s1[20] = "LEVEL:  ";
	char s2[2];
	itoa(level, s2, 10);//配合 outtextxy 的函数原型 即只接受字符型
	strcat(s1, s2);
	setbkmode(TRANSPARENT);
	outtextxy(XSIZE - 90, 10, s1);
	setbkmode(OPAQUE);
}

inline void control::showDied(int life)
{
	cleardevice();
	char s1[20] = "Life just have:  ";
	char s2[2];
	itoa(life, s2, 10);//配合 outtextxy 的函数原型 即只接受字符型
	outtextxy(XSIZE / 2 - 63, YSIZE / 3, s1);
	outtextxy(XSIZE / 2 - 10, YSIZE / 2 - 20, s2);
	Sleep(2000);
}

inline void control::showGameOver()
{
	IMAGE img;
	loadimage(&img, "res\\home.bmp", XSIZE, 5 * YSIZE);
	putimage(0, -YSIZE, &img);
	Sleep(6500);
}

inline void control::showPassed(int world)
{
	cleardevice();
	char s1[20] = "LEVEL:  ";
	char s2[2];
	itoa(world, s2, 10);//配合 outtextxy 的函数原型 即只接受字符型
	outtextxy(XSIZE / 2 - 20, YSIZE / 3, s1);
	outtextxy(XSIZE / 2, YSIZE / 2 - 10, s2);
	Sleep(2000);
}

inline void control::showPassedAll()
{
	IMAGE img;
	loadimage(&img, "res\\home.bmp", XSIZE, 5 * YSIZE);
	putimage(0, -3 * YSIZE, &img);
	Sleep(7800);
}
*/