#pragma once

#include "resource.h"

//�ꡣ

//����������
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//��Ϸ״̬����
#define GAMESTATE_MENU			0
#define GAMESTATE_RUNNING		1
#define GAMESTATE_WIN			2
#define GAMESTATE_LOST			3
#define GAMESTATE_ERASEMENU		10

//��Ļ��С��
#define WINDOW_DEFWIDTH			640
#define WINDOW_DEFHEIGHT		480

//�Ʒְ�����Ϸ���ָ��ߵ�λ��
#define UPPER_SEPARATE_LINE_Y	40

//���顣
#define BLOCK_WIDTH				40
#define BLOCK_HEIGHT			10
#define BLOCK_GAP				10
#define BLOCK_DRAWORIGIN_X		75
#define BLOCK_DRAWORIGIN_Y		50

//��
#define BALL_RADIUS				5
#define BALL_START_VELOCITY_X	10
#define BALL_START_VELOCITY_Y	-6
#define BALL_START_ABOVE_PEDAL	30

//���ӡ�
#define PEDAL_Y					400
#define PEDAL_HEIGHT			10
#define PEDAL_WIDTH				60
#define PEDAL_VELOCITY			10

//�������ֵ��
#define LIFE_LIMIT				4

//������
////APIʵ�֡����������ܴ���
#define BEEP()					MessageBeep(0)
////Beep����ʵ�֡����ǻ����Beepʱ���١�
//#define BEEP()					Beep(440,200)

//ȫ�־��
HWND ghWnd;

//��ˢ�ͻ���
HPEN penWhite, penBlack;
HBRUSH brushBlack, brushGreen, brushWhite, brushYellow, brushRed;

//״̬��
int gameState;

//��
int xBall, yBall, dxBall, dyBall;

//��
int xPedal;

//�������״̬
bool isBlockExist[10][10];

//ͳ��
int lastCount, lastLife;

//����
int Init(void);
int MainInit(void);
int Main(void);
int DrawWindow(void);
int rt_DrawBallLost(void);
