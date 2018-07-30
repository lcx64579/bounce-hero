/*
	Bounce Hero
	GreatSeal 制作
	
	说明：一个打砖块小游戏。使用GDI绘图。

	操作：
		← →		左右移动板子
		ESC		退出
		Enter	开始游戏，或失败时重来
		B		彩蛋。直接胜利。
*/


// bh.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "bh.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32TUT02, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32TUT02));

    MSG msg;

	Init();

    // 主消息循环: 
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Main();

	}

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32TUT02));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = /*MAKEINTRESOURCEW(IDC_WIN32TUT02);*/NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, /*szTitle*/_T("Bounce Hero"), WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_DEFWIDTH, WINDOW_DEFHEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ghWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            /*int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }*/
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//主初始化。
int Init(void) {

	//随机数发生器初始化。
	srand(GetTickCount());

	//申明笔刷和笔。
	penWhite = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	penBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	brushBlack = CreateSolidBrush(RGB(0, 0, 0));
	brushGreen = CreateSolidBrush(RGB(0, 255, 0));
	brushWhite = CreateSolidBrush(RGB(255, 255, 255));
	brushYellow = CreateSolidBrush(RGB(255, 255, 0));
	brushRed = CreateSolidBrush(RGB(255, 0, 0));

	return 0;
}

//初始化整个游戏的数据。
int MainInit(void) {

	//所有方块都存在。
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			isBlockExist[i][j] = true;
		}
	}

	//初始化球的位置。
	xBall = WINDOW_DEFWIDTH / 2;
	yBall = PEDAL_Y - BALL_START_ABOVE_PEDAL;
	dxBall = rand() % BALL_START_VELOCITY_X - BALL_START_VELOCITY_X;
	dyBall = BALL_START_VELOCITY_Y;

	//初始化板的位置。
	xPedal = WINDOW_DEFWIDTH / 2;

	//初始化计分板数据。
	lastCount = 100;
	lastLife = LIFE_LIMIT;

	BEEP();

	gameState = GAMESTATE_RUNNING;

	return 0;
}

//游戏逻辑主函数。由主循环调用。
int Main(void) {

	DWORD startTime = GetTickCount();		//锁定游戏到30fps。  ---step.1

	switch (gameState)
	{

	case GAMESTATE_MENU: {

		//按下Enter开始游戏。
		if (KEYDOWN(VK_RETURN)) {
			gameState = GAMESTATE_ERASEMENU;
			MainInit();
		}

		break;
	}

	case GAMESTATE_ERASEMENU: {

		//NOTHING

		break;
	}

	case GAMESTATE_RUNNING: {

		//彩蛋。
		if (KEYDOWN(0x42)) gameState = GAMESTATE_WIN;	//按下B键直接胜利

		//玩家是否已经胜利或失败？
		if (lastCount <= 0) gameState = GAMESTATE_WIN;
		if (lastLife < 0) gameState = GAMESTATE_LOST;

		//移动板子的逻辑。外加防止移出屏幕。
		if (KEYDOWN(VK_LEFT)) xPedal -= PEDAL_VELOCITY;
		if (KEYDOWN(VK_RIGHT)) xPedal += PEDAL_VELOCITY;
		if (xPedal < PEDAL_WIDTH / 2) xPedal = PEDAL_WIDTH / 2;
		if (xPedal > WINDOW_DEFWIDTH - 20 - PEDAL_WIDTH / 2) xPedal = WINDOW_DEFWIDTH - 20 - PEDAL_WIDTH / 2;

		//小球在边界的反弹逻辑。
		xBall += dxBall;
		if (xBall < BALL_RADIUS / 2 || xBall > WINDOW_DEFWIDTH - 20 - BALL_RADIUS / 2){
			dxBall = -dxBall;
			xBall += dxBall;
		}
		yBall += dyBall;
		if (yBall < UPPER_SEPARATE_LINE_Y + BALL_RADIUS / 2) {
			dyBall = -dyBall;
			yBall += dyBall;
		}

		//丢球逻辑。
		if (yBall > WINDOW_DEFHEIGHT - 40 - BALL_RADIUS / 2) {		//-40来修正问题：标题栏占用的大量空间导致游戏区域实际上比窗口更往下。
			lastLife--;		//减损一条生命
			rt_DrawBallLost();		//减损生命时的特效

			//复原球和板的位置
			xBall = WINDOW_DEFWIDTH / 2;
			yBall = PEDAL_Y - BALL_START_ABOVE_PEDAL;
			dxBall = rand() % BALL_START_VELOCITY_X - BALL_START_VELOCITY_X;
			dyBall = BALL_START_VELOCITY_Y;
			xPedal = WINDOW_DEFWIDTH / 2;
		}
		
		//接到球时，根据球击打在板上的位置（相对于中心点的偏移touchOffset）来决定弹回的方向。
		if (yBall + BALL_RADIUS > PEDAL_Y - PEDAL_HEIGHT / 2 && yBall - BALL_RADIUS < PEDAL_Y + PEDAL_HEIGHT / 2
			&& xBall + BALL_RADIUS > xPedal - PEDAL_WIDTH / 2 && xBall - BALL_RADIUS < xPedal + PEDAL_WIDTH / 2) {
			int touchOffset = xBall - xPedal;
			dyBall = -dyBall;
			dxBall = touchOffset / 3;
		}

		//球是否击中了方块？如果击中了，计分板剩余方块数字减一，删掉那个方块，并反弹球。
		int posx = BLOCK_DRAWORIGIN_X, posy = BLOCK_DRAWORIGIN_Y;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (isBlockExist[i][j]) {
					if (yBall + BALL_RADIUS >= posy - BLOCK_HEIGHT / 2 && yBall - BALL_RADIUS <= posy + BLOCK_HEIGHT / 2
						&& xBall + BALL_RADIUS >= posx - BLOCK_WIDTH / 2 && xBall - BALL_RADIUS <= posx + BLOCK_WIDTH / 2) {
						
						//计分板剩余方块数字减一
						lastCount--;
						
						//删掉那个方块
						isBlockExist[i][j] = false;

						BEEP();

						//反弹球
						if (yBall + BALL_RADIUS <= posy - BLOCK_HEIGHT / 2 + 4 || yBall - BALL_RADIUS >= posy + BLOCK_HEIGHT / 2 - 4) {
							dyBall = -dyBall;
						}
						if (xBall + BALL_RADIUS <= posx - BLOCK_WIDTH / 2 + 5 || xBall - BALL_RADIUS >= posx + BLOCK_WIDTH / 2 - 5) {
							dxBall = -dxBall;
						}

					}
				}
				posx = posx + BLOCK_WIDTH + BLOCK_GAP;
			}
			posx = BLOCK_DRAWORIGIN_X;
			posy = posy + BLOCK_HEIGHT + BLOCK_GAP;
		}

		break;
	}

	case GAMESTATE_WIN: {

		//NOTHING

		break;
	}

	case GAMESTATE_LOST: {

		//按下Enter重开。
		if (KEYDOWN(VK_RETURN)) {
			gameState = GAMESTATE_ERASEMENU;
			MainInit();
		}

		break;
	}

	default:
		break;
	}

	//任何时候，按下ESC退出。
	if (KEYDOWN(VK_ESCAPE)) PostMessage(ghWnd, WM_CLOSE, 0, 0);

	//前往绘制界面。
	DrawWindow();

	while (GetTickCount() - startTime < 33);		//锁定游戏到30fps。  ---step.2  1000ms / 30fps = 33ms/f.

	return 0;
}

//界面绘制主函数。由 Main() 调用。
int DrawWindow(void) {

	char buffer[80];

	HDC hdc = GetDC(ghWnd);

	switch (gameState)
	{

	case GAMESTATE_MENU: {

		//绘制主菜单。
		SetTextColor(hdc, RGB(0, 255, 0));	//绿色
		SetBkColor(hdc, RGB(0, 0, 0));		//黑底
		SetBkMode(hdc, OPAQUE);
		sprintf(buffer, "BOUNCE HERO");
		TextOutA(hdc, 250, 130, buffer, strlen(buffer));
		sprintf(buffer, "Press <ENTER> to start...");
		TextOutA(hdc, 220, 300, buffer, strlen(buffer));

		break;
	}

	//擦除主菜单界面，准备游戏界面的绘制
	case GAMESTATE_ERASEMENU: {

		//原本是通过用黑色字重写整个标题界面的方法来实现擦除，后来决定改用黑色矩形盖掉整个界面。
		/*SetTextColor(hdc, RGB(0, 0, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, TRANSPARENT);
		sprintf(buffer, "BOUNCE HERO");
		TextOutA(hdc, 250, 130, buffer, strlen(buffer));
		sprintf(buffer, "Press <ENTER> to Start...");
		TextOutA(hdc, 220, 300, buffer, strlen(buffer));
		sprintf(buffer, "YOU LOST!");
		TextOutA(hdc, 260, 130, buffer, strlen(buffer));
		sprintf(buffer, "Press <Enter> to Try Again...");
		TextOutA(hdc, 220, 300, buffer, strlen(buffer));*/
		
		gameState = GAMESTATE_RUNNING;	//尴尬的现实。这行代码放在Main()中的相应位置时不知为何逻辑上不正确。

	}

	case GAMESTATE_RUNNING: {

		int posx = BLOCK_DRAWORIGIN_X, posy = BLOCK_DRAWORIGIN_Y;

		//擦除整个界面准备重绘
		SelectObject(hdc, (HGDIOBJ)brushBlack);
		SelectObject(hdc, (HGDIOBJ)penBlack);
		Rectangle(hdc, 0, 0, WINDOW_DEFWIDTH, WINDOW_DEFHEIGHT);

		//上方一条分割计分板与游戏区的白线
		SelectObject(hdc, (HGDIOBJ)penWhite);
		MoveToEx(hdc, 0, UPPER_SEPARATE_LINE_Y, nullptr);
		LineTo(hdc, WINDOW_DEFWIDTH, 40);

		//绘制仍然存在的方块
		SelectObject(hdc, (HGDIOBJ)brushGreen);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (isBlockExist[i][j]) {
					Rectangle(hdc, posx - BLOCK_WIDTH / 2, posy - BLOCK_HEIGHT / 2, posx + BLOCK_WIDTH / 2, posy + BLOCK_HEIGHT / 2);
				}
				posx = posx + BLOCK_WIDTH + BLOCK_GAP;
			}
			posx = BLOCK_DRAWORIGIN_X;
			posy = posy + BLOCK_HEIGHT + BLOCK_GAP;
		}
		
		//绘制玩家操纵的板
		SelectObject(hdc, (HGDIOBJ)brushYellow);
		Rectangle(hdc, xPedal - PEDAL_WIDTH / 2, PEDAL_Y - PEDAL_HEIGHT / 2, xPedal + PEDAL_WIDTH / 2, PEDAL_Y + PEDAL_HEIGHT / 2);

		//绘制球
		SelectObject(hdc, (HGDIOBJ)brushWhite);
		Ellipse(hdc, xBall - BALL_RADIUS, yBall - BALL_RADIUS, xBall + BALL_RADIUS, yBall + BALL_RADIUS);

		//绘制计分板和生命
		SetTextColor(hdc, RGB(0, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, OPAQUE);
		sprintf(buffer, "Last Block : %d   ", lastCount);
		TextOutA(hdc, 20, 10, buffer, strlen(buffer));
		sprintf(buffer, "Life            : %d   ", lastLife);
		TextOutA(hdc, 20, 25, buffer, strlen(buffer));

		break;
	}

	case GAMESTATE_WIN: {

		SelectObject(hdc, (HGDIOBJ)brushBlack);
		SelectObject(hdc, (HGDIOBJ)penBlack);
		Rectangle(hdc, 0, 0, WINDOW_DEFWIDTH, WINDOW_DEFHEIGHT);

		//原本是通过用黑色字重写整个计分板的方法来实现擦除，后来决定改用黑色矩形盖掉整个界面。
		/*SetTextColor(hdc, RGB(0, 0, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, OPAQUE);

		sprintf(buffer, "Last Block : %d   ", lastCount);
		TextOutA(hdc, 20, 10, buffer, strlen(buffer));
		sprintf(buffer, "Lost Ball   : %d   ", lastLife);
		TextOutA(hdc, 20, 25, buffer, strlen(buffer));*/

		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, OPAQUE);

		sprintf(buffer, "YOU WIN!");
		TextOutA(hdc, 260, 130, buffer, strlen(buffer));
		sprintf(buffer, "Press <ESC> to Quit...");
		TextOutA(hdc, 220, 300, buffer, strlen(buffer));

		break;
	}

	case GAMESTATE_LOST: {

		SelectObject(hdc, (HGDIOBJ)brushBlack);
		SelectObject(hdc, (HGDIOBJ)penBlack);
		Rectangle(hdc, 0, 0, WINDOW_DEFWIDTH, WINDOW_DEFHEIGHT);

		//原本是通过用黑色字重写整个计分板的方法来实现擦除，后来决定改用黑色矩形盖掉整个界面。
		/*SetTextColor(hdc, RGB(0, 0, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, OPAQUE);

		sprintf(buffer, "Last Block : %d   ", lastCount);
		TextOutA(hdc, 20, 10, buffer, strlen(buffer));
		sprintf(buffer, "Lost Ball   : %d   ", lastLife);
		TextOutA(hdc, 20, 25, buffer, strlen(buffer));*/

		SetTextColor(hdc, RGB(255, 30, 30));
		SetBkColor(hdc, RGB(0, 0, 0));
		SetBkMode(hdc, OPAQUE);

		sprintf(buffer, "YOU LOST!");
		TextOutA(hdc, 260, 130, buffer, strlen(buffer));
		sprintf(buffer, "Press <Enter> to Try Again...");
		TextOutA(hdc, 220, 300, buffer, strlen(buffer));

		break;
	}

	default:
		break;
	}

	ReleaseDC(ghWnd, hdc);

	return 0;
}

//损失一条生命时，屏幕闪红特效的绘制。
int rt_DrawBallLost(void) {

	HDC hdc = GetDC(ghWnd);
	
	SelectObject(hdc, (HGDIOBJ)brushRed);
	SelectObject(hdc, (HGDIOBJ)penBlack);
	Rectangle(hdc, 0, 0, WINDOW_DEFWIDTH, WINDOW_DEFHEIGHT);
	Sleep(50);
	SelectObject(hdc, (HGDIOBJ)brushBlack);
	Rectangle(hdc, 0, 0, WINDOW_DEFWIDTH, WINDOW_DEFHEIGHT);

	ReleaseDC(ghWnd, hdc);

	return 0;
}