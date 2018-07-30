/*
	Bounce Hero
	GreatSeal ����
	
	˵����һ����ש��С��Ϸ��ʹ��GDI��ͼ��

	������
		�� ��		�����ƶ�����
		ESC		�˳�
		Enter	��ʼ��Ϸ����ʧ��ʱ����
		B		�ʵ���ֱ��ʤ����
*/


// bh.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "bh.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
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

    // TODO: �ڴ˷��ô��롣

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32TUT02, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32TUT02));

    MSG msg;

	Init();

    // ����Ϣѭ��: 
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            /*int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
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
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
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

// �����ڡ������Ϣ�������
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

//����ʼ����
int Init(void) {

	//�������������ʼ����
	srand(GetTickCount());

	//������ˢ�ͱʡ�
	penWhite = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	penBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	brushBlack = CreateSolidBrush(RGB(0, 0, 0));
	brushGreen = CreateSolidBrush(RGB(0, 255, 0));
	brushWhite = CreateSolidBrush(RGB(255, 255, 255));
	brushYellow = CreateSolidBrush(RGB(255, 255, 0));
	brushRed = CreateSolidBrush(RGB(255, 0, 0));

	return 0;
}

//��ʼ��������Ϸ�����ݡ�
int MainInit(void) {

	//���з��鶼���ڡ�
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			isBlockExist[i][j] = true;
		}
	}

	//��ʼ�����λ�á�
	xBall = WINDOW_DEFWIDTH / 2;
	yBall = PEDAL_Y - BALL_START_ABOVE_PEDAL;
	dxBall = rand() % BALL_START_VELOCITY_X - BALL_START_VELOCITY_X;
	dyBall = BALL_START_VELOCITY_Y;

	//��ʼ�����λ�á�
	xPedal = WINDOW_DEFWIDTH / 2;

	//��ʼ���Ʒְ����ݡ�
	lastCount = 100;
	lastLife = LIFE_LIMIT;

	BEEP();

	gameState = GAMESTATE_RUNNING;

	return 0;
}

//��Ϸ�߼�������������ѭ�����á�
int Main(void) {

	DWORD startTime = GetTickCount();		//������Ϸ��30fps��  ---step.1

	switch (gameState)
	{

	case GAMESTATE_MENU: {

		//����Enter��ʼ��Ϸ��
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

		//�ʵ���
		if (KEYDOWN(0x42)) gameState = GAMESTATE_WIN;	//����B��ֱ��ʤ��

		//����Ƿ��Ѿ�ʤ����ʧ�ܣ�
		if (lastCount <= 0) gameState = GAMESTATE_WIN;
		if (lastLife < 0) gameState = GAMESTATE_LOST;

		//�ƶ����ӵ��߼�����ӷ�ֹ�Ƴ���Ļ��
		if (KEYDOWN(VK_LEFT)) xPedal -= PEDAL_VELOCITY;
		if (KEYDOWN(VK_RIGHT)) xPedal += PEDAL_VELOCITY;
		if (xPedal < PEDAL_WIDTH / 2) xPedal = PEDAL_WIDTH / 2;
		if (xPedal > WINDOW_DEFWIDTH - 20 - PEDAL_WIDTH / 2) xPedal = WINDOW_DEFWIDTH - 20 - PEDAL_WIDTH / 2;

		//С���ڱ߽�ķ����߼���
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

		//�����߼���
		if (yBall > WINDOW_DEFHEIGHT - 40 - BALL_RADIUS / 2) {		//-40���������⣺������ռ�õĴ����ռ䵼����Ϸ����ʵ���ϱȴ��ڸ����¡�
			lastLife--;		//����һ������
			rt_DrawBallLost();		//��������ʱ����Ч

			//��ԭ��Ͱ��λ��
			xBall = WINDOW_DEFWIDTH / 2;
			yBall = PEDAL_Y - BALL_START_ABOVE_PEDAL;
			dxBall = rand() % BALL_START_VELOCITY_X - BALL_START_VELOCITY_X;
			dyBall = BALL_START_VELOCITY_Y;
			xPedal = WINDOW_DEFWIDTH / 2;
		}
		
		//�ӵ���ʱ������������ڰ��ϵ�λ�ã���������ĵ��ƫ��touchOffset�����������صķ���
		if (yBall + BALL_RADIUS > PEDAL_Y - PEDAL_HEIGHT / 2 && yBall - BALL_RADIUS < PEDAL_Y + PEDAL_HEIGHT / 2
			&& xBall + BALL_RADIUS > xPedal - PEDAL_WIDTH / 2 && xBall - BALL_RADIUS < xPedal + PEDAL_WIDTH / 2) {
			int touchOffset = xBall - xPedal;
			dyBall = -dyBall;
			dxBall = touchOffset / 3;
		}

		//���Ƿ�����˷��飿��������ˣ��Ʒְ�ʣ�෽�����ּ�һ��ɾ���Ǹ����飬��������
		int posx = BLOCK_DRAWORIGIN_X, posy = BLOCK_DRAWORIGIN_Y;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (isBlockExist[i][j]) {
					if (yBall + BALL_RADIUS >= posy - BLOCK_HEIGHT / 2 && yBall - BALL_RADIUS <= posy + BLOCK_HEIGHT / 2
						&& xBall + BALL_RADIUS >= posx - BLOCK_WIDTH / 2 && xBall - BALL_RADIUS <= posx + BLOCK_WIDTH / 2) {
						
						//�Ʒְ�ʣ�෽�����ּ�һ
						lastCount--;
						
						//ɾ���Ǹ�����
						isBlockExist[i][j] = false;

						BEEP();

						//������
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

		//����Enter�ؿ���
		if (KEYDOWN(VK_RETURN)) {
			gameState = GAMESTATE_ERASEMENU;
			MainInit();
		}

		break;
	}

	default:
		break;
	}

	//�κ�ʱ�򣬰���ESC�˳���
	if (KEYDOWN(VK_ESCAPE)) PostMessage(ghWnd, WM_CLOSE, 0, 0);

	//ǰ�����ƽ��档
	DrawWindow();

	while (GetTickCount() - startTime < 33);		//������Ϸ��30fps��  ---step.2  1000ms / 30fps = 33ms/f.

	return 0;
}

//����������������� Main() ���á�
int DrawWindow(void) {

	char buffer[80];

	HDC hdc = GetDC(ghWnd);

	switch (gameState)
	{

	case GAMESTATE_MENU: {

		//�������˵���
		SetTextColor(hdc, RGB(0, 255, 0));	//��ɫ
		SetBkColor(hdc, RGB(0, 0, 0));		//�ڵ�
		SetBkMode(hdc, OPAQUE);
		sprintf(buffer, "BOUNCE HERO");
		TextOutA(hdc, 250, 130, buffer, strlen(buffer));
		sprintf(buffer, "Press <ENTER> to start...");
		TextOutA(hdc, 220, 300, buffer, strlen(buffer));

		break;
	}

	//�������˵����棬׼����Ϸ����Ļ���
	case GAMESTATE_ERASEMENU: {

		//ԭ����ͨ���ú�ɫ����д�����������ķ�����ʵ�ֲ����������������ú�ɫ���θǵ��������档
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
		
		gameState = GAMESTATE_RUNNING;	//���ε���ʵ�����д������Main()�е���Ӧλ��ʱ��֪Ϊ���߼��ϲ���ȷ��

	}

	case GAMESTATE_RUNNING: {

		int posx = BLOCK_DRAWORIGIN_X, posy = BLOCK_DRAWORIGIN_Y;

		//������������׼���ػ�
		SelectObject(hdc, (HGDIOBJ)brushBlack);
		SelectObject(hdc, (HGDIOBJ)penBlack);
		Rectangle(hdc, 0, 0, WINDOW_DEFWIDTH, WINDOW_DEFHEIGHT);

		//�Ϸ�һ���ָ�Ʒְ�����Ϸ���İ���
		SelectObject(hdc, (HGDIOBJ)penWhite);
		MoveToEx(hdc, 0, UPPER_SEPARATE_LINE_Y, nullptr);
		LineTo(hdc, WINDOW_DEFWIDTH, 40);

		//������Ȼ���ڵķ���
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
		
		//������Ҳ��ݵİ�
		SelectObject(hdc, (HGDIOBJ)brushYellow);
		Rectangle(hdc, xPedal - PEDAL_WIDTH / 2, PEDAL_Y - PEDAL_HEIGHT / 2, xPedal + PEDAL_WIDTH / 2, PEDAL_Y + PEDAL_HEIGHT / 2);

		//������
		SelectObject(hdc, (HGDIOBJ)brushWhite);
		Ellipse(hdc, xBall - BALL_RADIUS, yBall - BALL_RADIUS, xBall + BALL_RADIUS, yBall + BALL_RADIUS);

		//���ƼƷְ������
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

		//ԭ����ͨ���ú�ɫ����д�����Ʒְ�ķ�����ʵ�ֲ����������������ú�ɫ���θǵ��������档
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

		//ԭ����ͨ���ú�ɫ����д�����Ʒְ�ķ�����ʵ�ֲ����������������ú�ɫ���θǵ��������档
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

//��ʧһ������ʱ����Ļ������Ч�Ļ��ơ�
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