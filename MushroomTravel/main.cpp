//特别鸣谢 15软工 沙子森(sola) 文晓新(Clovin) 刘越(hangxingliu) 的技术帮助与支持

// GitHub 网址 
//https://github.com/unlimitedsola
//https://github.com/Clovin
//https://github.com/hangxingliu

//本游戏基于easyX图形库,需要安装文件包内的EasyX_2018春分版才可运行
//VC6 默认使用的 MBCS 编码，而 VC2008 及高版本 VC 默认使用的 Unicode 编码。以下详细解释这个问题：
//用 char 表示字符时，英文占用一个字节，中文占用两个字节。
//这样有一个严重的问题：两个连续字节，究竟是两个英文字符，还是一个中文字符？
//为了解决这个问题，Unicode 编码诞生了。Unicode 编码不管中文英文都用两个字节表示。
//对于 MBCS 编码，字符变量用 char 定义。
//对于 Unicode 编码中，字符变量用 wchar_t 定义。
//故在Visual Sstudio 高版本中可使用  _T("abc")  或  项目 —> 属性  —> 更改字符集  —> Unicode —> 多字符集 即可
//因为编译本程源码所用编译器的版本是 Visual Studio 2017 采用了 V141 版本的工具集 
// 若要在VS12中运行，修改工具集版本即可

#include<graphics.h>
#include<windows.h>
#include"Mydefine.h"
#include"Control.h"
#include"Role.h"
#include"Scene.h"
#include<time.h>
#include <mmsystem.h> //启用多媒体文件函数msciSendString需要引用此头文件
#pragma comment(lib,"winmm.lib") //配套部分 

//全局变量
int life = LIFE;   //主角有life条生命
int world = 1;     //现在是第world关

int main()
{
	initgraph(XSIZE, YSIZE); // 创建绘图框，以下部分内容的实现均在绘图框内

	control myCtrl;        //定义一个游戏控制
	role myRole(world);    //定义角色
	scene myScene(world);  //定义游戏场景
	myCtrl.gameStart();//游戏的开始界面

					   //添加游戏音乐
	mciSendString("open res\\背景.mp3 alias music_bg", NULL, 0, NULL);//打开音乐并给他起个别名，以后引用只需用别名即可 “music_bg” 为别名 
	mciSendString("open res\\胜利.mp3 alias music_win", NULL, 0, NULL);//MegaloBox~
	mciSendString("open res\\过关.mp3 alias music_passedAll", NULL, 0, NULL);//“过关.mp3”为该文件原名
	mciSendString("open res\\GG.mp3 alias music_end", NULL, 0, NULL);
	mciSendString("play music_bg repeat", NULL, 0, NULL);



	while (true) //以永真循环保证游戏的正常运行(可重复玩）
	{
		//
		//控制层
		//
		int key = myCtrl.getKey(); //获取玩家按下的键                              
		if (key == VIR_RESTART)     //如果游戏过程中选择了“重新开始”
		{
			myScene = scene(world); // 创建关卡世界
			mciSendString("play music_bg from 0", NULL, 0, NULL);
			myRole = role(world); //创建关卡角色
		}
		else if (key == VIR_HOME)   //如果游戏过程中选择了“主菜单”
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			life = LIFE; //初始化生命值
			world = 1; // 初始化关卡
			myRole = role(world); //重新创建关卡世界 
			myScene = scene(world); // 重新创建关卡角色
			myCtrl.gameStart(); //打印游戏开始主界面
			mciSendString("play music_bg from 0", NULL, 0, NULL);
		}
		//
		//角色层
		//
		myRole.action(key, &myScene);
		//
		//背景层
		//
		myScene.action(&myRole);

		if (myRole.isDied())     //如果主角死亡
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			BeginBatchDraw(); // 批量绘图开启！
			myScene.show();
			myRole.show();
			myCtrl.showScore(myRole.getScore());
			myCtrl.showLevel(world);
			EndBatchDraw();//批量绘图结束！，打印上述图形界面
			Sleep(2500);
			life--;
			if (life == 0) //如果主角的生命归零
			{
				mciSendString("play music_end from 0", NULL, 0, NULL);
				myCtrl.showGameOver();
				life = LIFE; // 初始化生命
				world = 1; // 初始化关卡
				myCtrl.gameStart();
				myRole = role(world);
				myScene = scene(world);
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
			else
			{
				myCtrl.showDied(life); // 利用图形界面显示人物有几条命
				myRole = role(world); // 重置角色
				myScene = scene(world); //重置关卡 ，仍为当前未通关关卡
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}
		if (myRole.isPassed())   //如果主角过关
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			if (world == 3)//如果主角通关
			{
				mciSendString("play music_win from 0", NULL, 0, NULL);
				Sleep(2500);
				mciSendString("play music_passedAll from 0", NULL, 0, NULL);
				myCtrl.showPassedAll(); //展现主界面
				life = LIFE; //重新初始化主角生命
				world = 1; //初始化关卡
				myRole = role(world);
				myScene = scene(world);
				myCtrl.gameStart();
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
			else
			{
				mciSendString("play music_win from 0", NULL, 0, NULL);
				Sleep(2500);
				world++; //通关，全局变量关卡+1
				myCtrl.showPassed(world); // 展现还拥有几条生命
				myRole = role(world); // 创建下一关的角色
				myScene = scene(world); //创建下一关的关卡
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}


		//显示画面
		BeginBatchDraw(); //批量绘图界面开启！
		myScene.show();
		myRole.show();
		myCtrl.showScore(myRole.getScore());
		myCtrl.showLevel(world);
		EndBatchDraw(); //批量绘图结束，在绘图框中打印上述绘图

		//延迟 用于控制主角运动(防止主角运动失真)
		Sleep((int)(TIME * 800));
	}
	mciSendString("clase all", NULL, 0, NULL);//关闭所有多媒体音乐文件
	closegraph(); // graphics绘图结束,与initgraph函数配套出现
	return 0;
}