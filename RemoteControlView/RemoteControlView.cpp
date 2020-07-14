// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>


#define keyCode(x) x-32

#define FPS_TIMER 1000/24  //24fps

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Windows Remote Control Study Application");

HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK DigProc(HWND, UINT, WPARAM, LPARAM);

HBITMAP ScreenCapture(HWND);
HBITMAP ScreenCapture2(HWND);

HBRUSH g_hbrBackground = NULL;
static RECT clientRect;
static int windowWidth;
static int windowHeight;
static int fpsTemp = 0;
static int fps = 0;
BOOL CALLBACK DigProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int msgboxID;

	HDC hdc;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_CREATE:
		//안불림
		break;
	case WM_KEYDOWN:
		MessageBox(hWnd, L"!!!", L"!!", NULL);
		break;
	case WM_INITDIALOG:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MessageBox(hWnd, L"!~~~!!", L"!!", NULL);


		EndPaint(hWnd, &ps);
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	case WM_CTLCOLORDLG:
		return (LONG)g_hbrBackground;
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, RGB(255, 255, 255));
		SetBkMode(hdcStatic, TRANSPARENT);
		return (LONG)g_hbrBackground;
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			msgboxID = MessageBox(hWnd, L"OK 버튼이 눌러졌습니다. 프로그램을 종료할까요?", L"정보", MB_YESNO);

			if (msgboxID == 6) EndDialog(hWnd, 0);
			break;
		case IDCANCEL:
			msgboxID = MessageBox(hWnd, L"CANCEL 버튼이 눌러졌습니다. 프로그램을 종료할까요?", L"정보", MB_YESNO);

			if (msgboxID == 6) EndDialog(hWnd, 0);
			break;
		}
		break;

	case WM_DESTROY:
		DeleteObject(g_hbrBackground);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HDC hMemDC, backDC;
	BITMAP bmp;

	static HBITMAP hBit = NULL;
	static HBITMAP tempBitMap;

	static HANDLE hTimer;


	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		if (hBit != NULL) {
			//MessageBox(hWnd, L"@@@@", L"!!", NULL);			

			hMemDC = CreateCompatibleDC(hdc);//더블버퍼링을 위한 main DC
			backDC = CreateCompatibleDC(hdc);//더블버퍼링을 위한 back DC

			tempBitMap = (HBITMAP)SelectObject(backDC, hBit);// 캡쳐한 hBit비트맵과 backDC 연결
			GetObject(hBit, sizeof(BITMAP), &bmp);//hBit의 비트맵 정보를 bmp에 저장
			SelectObject(hMemDC, hBit);

			BitBlt(backDC, 0, 0, bmp.bmWidth, bmp.bmHeight, hMemDC, 0, 0, SRCCOPY);//backDC에 hMemDC의 이미지 복사		

			BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, backDC, 0, 0, SRCCOPY);//화면에 backDC 이미지를 복사


			DeleteObject(SelectObject(backDC, tempBitMap));
			DeleteObject(hBit);
			DeleteDC(backDC);
			DeleteDC(hMemDC);
			fpsTemp++;
			hBit = NULL;
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:

		EndPaint(hWnd, &ps);
		//
		//switch (wParam) {
		//case keyCode('x'):
		//	//MessageBox(hWnd, (LPCWSTR)bb, L"Title", NULL);
		//	hBit = ScreenCapture(hWnd);
		//	//DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DigProc);
		//	break;
		//case VK_LEFT:
		//	x -= 8;
		//	break;
		//case VK_RIGHT:
		//	x += 8;
		//	break;
		//case VK_UP:
		//	y -= 8;
		//	break;
		//case VK_DOWN:
		//	y += 8;
		//	break;
		//}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_SIZE:
		/* hwndEdit is the handle of the edit control window */
		//clientRect.right = 
	{
		/*WCHAR buffer[32];
		int rrr = (int)LOWORD(lParam);
		int ttt = (int)HIWORD(lParam);
		wsprintf(buffer, L"%d %d", rrr, ttt);
		MessageBox(NULL, (LPCWSTR)buffer, L"Display", MB_ICONINFORMATION);
		MoveWindow(hWnd, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);*/
		clientRect.right = LOWORD(lParam);
		clientRect.bottom = HIWORD(lParam);
		switch (wParam)
		{
		case SIZE_MAXHIDE:
			break;

		case SIZE_MAXSHOW:
			break;

		case SIZE_MINIMIZED:
			break;

		case SIZE_MAXIMIZED:
			break;

		case SIZE_RESTORED:
			break;
		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		SetProcessDPIAware();
		windowWidth = GetSystemMetrics(SM_CXSCREEN);
		windowHeight = GetSystemMetrics(SM_CYSCREEN);

		/*
		https://docs.microsoft.com/ko-kr/dotnet/framework/ui-automation/ui-automation-and-screen-scaling
		★★전체 프로세스 dpi가 인식되므로 프로세스에 속하는 모든 창이 실제 크기로 유지된다. ★★
		서피스 프로 등 고해상도에서 200%등의 스케일링이 되어있는경우 GetSystemMetrics를 이용하여도 해상도 크기를 정상적으로 가져오지 못한다.(서피스 프로에서 200%사용시 1920
		API call 보다 매니패스트를 이용한 방법을 권장한다고 한다.(https://msdn.microsoft.com/ko-kr/C9488338-D863-45DF-B5CB-7ED9B869A5E2),1080으로 가져옴)
		그렇기 때문에 이 함수를 사용하여 논리적 좌표가 아닌 실제 좌표를 사용하게된다.
		*/

		hTimer = (HANDLE)SetTimer(hWnd, 1, FPS_TIMER, NULL);//보여줄 윈도우, 타이머ID, 타이머시간1000=1초, 함수 PROC, NULL로해도됨 wm_timer로 들어옴
		(HANDLE)SetTimer(hWnd, 2, 1000, NULL);
		break;
	case WM_TIMER:
		switch (wParam) {//wParam = 타이머ID

		case 1:// Refresh 타이머
			hBit = ScreenCapture(hWnd);
			InvalidateRect(hWnd, NULL, FALSE);//세번째 인자는 지우고 그릴지 FALSE = 안지움   ==>paint불림
			break;
		case 2:// FPS 타이머
			fps = fpsTemp;
			fpsTemp = 0;
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}


	return 0;
}
void KeyPress() {
	if (GetAsyncKeyState(VK_LEFT)) {

	}
	if (GetAsyncKeyState(VK_RIGHT)) {

	}
}
HBITMAP WindowCapture(HWND hWnd)

{

	HDC hScrDC, hMemDC;

	HBITMAP hBitmap;

	RECT rt;

	GetWindowRect(GetForegroundWindow(), &rt);

	//GetWindowRect(GetForegroundWindow(), &rt);//이건 활성중인 창 크기 가져올때사용 다른창 클릭하면 그창 사이즈로 변함
	//GetWindowRect(hWnd, &rt);//현재 창 사이즈 및 위치
	//GetWindowRect(GetActiveWindow(), &rt);//활성 창 정보

	rt.left = max(0, rt.left);

	rt.right = min(rt.right, GetSystemMetrics(SM_CXSCREEN));

	rt.top = max(0, rt.top);

	rt.bottom = min(rt.bottom, GetSystemMetrics(SM_CYSCREEN));



	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);



	hMemDC = CreateCompatibleDC(hScrDC);



	hBitmap = CreateCompatibleBitmap(hScrDC, rt.right - rt.left, rt.bottom - rt.top);



	SelectObject(hMemDC, hBitmap);



	BitBlt(hMemDC, 0, 0, rt.right - rt.left, rt.bottom - rt.top, hScrDC, rt.left, rt.top, SRCCOPY);



	DeleteDC(hMemDC);

	DeleteDC(hScrDC);

	InvalidateRect(hWnd, NULL, TRUE);



	return hBitmap;

}
HBITMAP ScreenCapture(HWND hWnd)

{

	HDC hScrDC, hMemDC;

	HBITMAP hBitmap;

	hScrDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);

	hMemDC = CreateCompatibleDC(hScrDC);

	hBitmap = CreateCompatibleBitmap(hScrDC, windowWidth, windowHeight);

	SelectObject(hMemDC, hBitmap);
	SetStretchBltMode(hMemDC, HALFTONE);// 이미지를 축소나 확대를 경우 생기는 손실을 보정해 주는 함수 HALFTONE이 성능 가장 좋은듯

	FillRect(hMemDC, &clientRect, (HBRUSH)GetStockObject(WHITE_BRUSH)); //하얀색으로 색 칠하기(default=black)	

	//BitBlt(hMemDC, 0, 0, rt.right, rt.bottom,hScrDC,0, 0, SRCCOPY);//가운데 2개인자 공유bmp와 같은사이즈로 표시
	int bmpHeight = (clientRect.right * windowHeight) / windowWidth;


	/* 가로 세로 비율에 따른 이미지 출력 사이즈 변경 */
	if (bmpHeight < clientRect.bottom) {// 아래로 창이 길어 질 때
		StretchBlt(hMemDC, 0, clientRect.bottom / 2 - bmpHeight / 2, clientRect.right, bmpHeight, hScrDC, 0, 0, windowWidth, windowHeight, SRCCOPY);//이미지 사이즈를 변경	
		//windowWidth:windowHeight=rt.right:y
		//bmpHeight = (rt.right*windowHeight)/windowWidth;
	}
	else {
		int bmpWidth = (clientRect.bottom * windowWidth) / windowHeight;
		StretchBlt(hMemDC, clientRect.right / 2 - bmpWidth / 2, 0, bmpWidth, clientRect.bottom, hScrDC, 0, 0, windowWidth, windowHeight, SRCCOPY);//이미지 사이즈를 변경
	}

	/* FPS 텍스트 출력 */
	SetTextAlign(hMemDC, TA_CENTER);
	TCHAR s[10];
	_stprintf(s, _T("%d FPS"), fps);
	TextOut(hMemDC, clientRect.right / 2, 20, s, lstrlen(s));

	DeleteDC(hMemDC);

	DeleteDC(hScrDC);

	return hBitmap;

}

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)//진입점
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//배경 색
	wcex.hbrBackground = NULL;//배경색 설정 안함
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	// Store instance handle in our global variable
	hInst = hInstance;

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
	// 500, 100: initial size (width, length)
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow(hWnd,
		nCmdShow);

	UpdateWindow(hWnd);

	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}