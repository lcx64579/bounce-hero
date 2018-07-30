#pragma once

#include "resource.h"

//宏。

//按键函数。
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//游戏状态机。
#define GAMESTATE_MENU			0
#define GAMESTATE_RUNNING		1
#define GAMESTATE_WIN			2
#define GAMESTATE_LOST			3
#define GAMESTATE_ERASEMENU		10

//屏幕大小。
#define WINDOW_DEFWIDTH			640
#define WINDOW_DEFHEIGHT		480

//计分板与游戏区分割线的位置
#define UPPER_SEPARATE_LINE_Y	40

//方块。
#define BLOCK_WIDTH				40
#define BLOCK_HEIGHT			10
#define BLOCK_GAP				10
#define BLOCK_DRAWORIGIN_X		75
#define BLOCK_DRAWORIGIN_Y		50

//球。
#define BALL_RADIUS				5
#define BALL_START_VELOCITY_X	10
#define BALL_START_VELOCITY_Y	-6
#define BALL_START_ABOVE_PEDAL	30

//板子。
#define PEDAL_Y					400
#define PEDAL_HEIGHT			10
#define PEDAL_WIDTH				60
#define PEDAL_VELOCITY			10

//生命最大值。
#define LIFE_LIMIT				4

//声音。
////API实现。但是声音很蠢。
#define BEEP()					MessageBeep(0)
////Beep函数实现。但是会造成Beep时卡顿。
//#define BEEP()					Beep(440,200)

//全局句柄
HWND ghWnd;

//笔刷和画笔
HPEN penWhite, penBlack;
HBRUSH brushBlack, brushGreen, brushWhite, brushYellow, brushRed;

//状态机
int gameState;

//球
int xBall, yBall, dxBall, dyBall;

//板
int xPedal;

//方块存在状态
bool isBlockExist[10][10];

//统计
int lastCount, lastLife;

//函数
int Init(void);
int MainInit(void);
int Main(void);
int DrawWindow(void);
int rt_DrawBallLost(void);
