#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
#endif

#include <windows.h>
#include <windowsx.h>
#include <cstdlib>
#include <ctime>
#include <mmsystem.h>
#include <iostream>
#include <array>
#include "graphics.h"
#include "Input.h"
#include "WindowManager.h"
#include "League.h"
using namespace std;

enum {GENERAL,AGILITY, PASSING, STRENGTH, KICKING, PHYSICAL};
enum {BLOCK, DAUNTLESS, DIRTY_PLAYER, FRENZY, PASS_BLOCK, PRO, SHADOWING, STRIP_BALL, SURE_HANDS, TACKLE, TRIP_UP};

CGraphics* g_Game = 0;
CInput* g_Input = 0;

int gamestate = 0;

HCURSOR cursor;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCmdLine, int iCmdShow) 
{
	srand( time(0) );
	srand(static_cast<unsigned int>(time(NULL)));
	
	BaseLeague Circle_League;

	Win32Wrapper	*g_pWindow;
	HINSTANCE	g_hInstance;
	HWND		wndHandle;
	
	g_hInstance = hInstance;
	
	RECT dimensions;
	dimensions.top		= GetSystemMetrics(SM_CYSCREEN)/4;
	dimensions.left		= GetSystemMetrics(SM_CYSCREEN)/4;
	dimensions.bottom	= GetSystemMetrics(SM_CYSCREEN)/4*3;
	dimensions.right	= GetSystemMetrics(SM_CXSCREEN)/4*3;
	g_pWindow = new Win32Wrapper("RISK bowl","RISK bowl",WS_OVERLAPPEDWINDOW | WS_VISIBLE,&dimensions,g_hInstance);

	wndHandle = g_pWindow->Create();
	g_pWindow->Show();

	g_Game = new CGraphics(GetSystemMetrics(SM_CXSCREEN)/64,GetSystemMetrics(SM_CYSCREEN)/64, wndHandle);
	g_Input = new CInput();
	
	cursor = LoadCursor(NULL, IDC_ARROW);
		
	DWORD pidwin;
	GetWindowThreadProcessId(wndHandle, &pidwin);
	char buffer[600];
	GetWindowThreadProcessId(wndHandle, &pidwin);
	sprintf_s(buffer,"%d",pidwin);
	SetWindowText(wndHandle,buffer);

	g_Game->Init(wndHandle);
	SetCursor(cursor);
	
	MSG msg = {0};
	
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage (&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			g_Input->KeyPressed();
			g_Game->EraseScreen();
			g_Game->SplashScreen();
			
			if(gamestate == 0)
				gamestate = g_Game->Menu(g_pWindow->pt);
			if(gamestate == 1)
				gamestate = g_Game->ChooseTeam(wndHandle, klock,g_pWindow->pt);
			if(gamestate == 3)
				gamestate = g_Game->BuyTeam(g_pWindow->pt);
			if(gamestate == 4)
				gamestate = g_Game->BuyTeam(g_pWindow->pt);
			if(gamestate == 5)
				gamestate = g_Game->Kickoff(wndHandle, g_pWindow->pt);

			g_Game->Render();
		}
	}
	delete g_pWindow;
	delete g_Game;
	delete g_Input;
	return(msg.wParam);
}
