#include "WindowManager.h"
//#include "DirectInputManager.h"

LRESULT CALLBACK Win32Wrapper::stWinProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	// This does two things:
	// 1.) If the window is being created, it calls SetWindowLong on the window to store the 	
	//		pointer to the window.
	// 2.) Otherwise, it gets the pointer to the window and calls that instance's WinProc

	Win32Wrapper* pWnd;

	if (uMsg == WM_NCCREATE) 
	{
		SetWindowLong(hWnd, GWL_USERDATA, (long)((LPCREATESTRUCT(lParam))->lpCreateParams));
	}

	pWnd = (Win32Wrapper *)GetWindowLong(hWnd, GWL_USERDATA);

	if (pWnd)
	{
		return pWnd->WinProc(hWnd, uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

HWND Win32Wrapper::Create()
{
	WNDCLASS WndCls;

	WndCls.style			= CS_HREDRAW | CS_VREDRAW;
	WndCls.lpfnWndProc	= (WNDPROC)stWinProc;
	WndCls.cbClsExtra		= 0;
	WndCls.cbWndExtra		= 0;
	WndCls.hInstance		= m_hInstance;
	WndCls.hIcon			= 0;
	WndCls.hCursor		= LoadCursor(NULL, IDC_ARROW);
	WndCls.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	WndCls.lpszMenuName	= NULL;
	WndCls.lpszClassName	= m_pClassName;
	RegisterClass(&WndCls);

	m_hWnd = CreateWindow(m_pClassName, 
							 m_pWindowTitle, 
							 m_dwStyles,
							 m_pRect->left, 
							 m_pRect->top, 
							 m_pRect->right-m_pRect->left, 
							 m_pRect->bottom-m_pRect->top, 
							 0, 
							 0, 
							 m_hInstance, 
							 (void *)this);

	if (!m_hWnd)
	{
     PostQuitMessage(0);
		 return false;
	}
	else
	{
		return m_hWnd;
	}
}

BOOL Win32Wrapper::Show() 
{
	ShowWindow(m_hWnd,SW_SHOW);
	UpdateWindow(m_hWnd);

	return true;
}

Win32Wrapper::Win32Wrapper(char *ClassName, char *WindowTitle, DWORD dwStyles, RECT *rect, HINSTANCE hInstance)
{
	m_pClassName		= ClassName;
	m_pWindowTitle	= WindowTitle;
	m_pRect					= rect;
	m_hInstance			= hInstance;
	m_dwStyles			= dwStyles;

	RECT desktopRect;

	GetWindowRect(GetDesktopWindow(),&desktopRect);

	int wWidth	=	m_pRect->right	-	m_pRect->left;
	int wHeight	=	m_pRect->bottom	-	m_pRect->top;

	m_pRect->left	=	((desktopRect.right	-	desktopRect.left)	-	wWidth)		/2;
	m_pRect->right	=	((desktopRect.right	-	desktopRect.left)	+	wWidth)		/2;
	m_pRect->top	=	((desktopRect.bottom -	desktopRect.top)	-	wHeight)	/2;
	m_pRect->bottom	=	((desktopRect.bottom -	desktopRect.top)	+	wHeight)	/2;
}

Win32Wrapper::~Win32Wrapper ()
{
	if ( m_hWnd )
	{
 		DestroyWindow( m_hWnd );
	}

  m_hWnd = NULL;
}

LRESULT CALLBACK Win32Wrapper::WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if( LOWORD( wParam ) == WA_INACTIVE )
	{
		bRun = false;
	}
	else
	{
		bRun = false;
	}

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;
	case WM_MOUSEMOVE:
	{
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
	} break;
	case WM_LBUTTONDOWN:
		{
		//DI& DIManager = DI::getInstance();
		//DIManager.LButton = true;
		}
		break;
	case WM_LBUTTONUP:
		{
		//DI& DIManager = DI::getInstance();
		//DIManager.LButton = false;
		}
		break;

	default:
		{
		//DI& DIManager = DI::getInstance();
		//DIManager.LButton = false;
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	}
	return 0;
}