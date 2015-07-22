#include <windows.h>
#include <windowsx.h>

class Win32Wrapper {

public:

	Win32Wrapper(char *ClassName, char *WindowTitle, DWORD dwStyles, RECT *rect, HINSTANCE hInstance);
	virtual ~Win32Wrapper();

	HWND Create();
	BOOL Show();
	HWND					m_hWnd;
	// Static general purpose Window Processor for all instances of this class
	static LRESULT CALLBACK stWinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// The actual window processor for this class (called by the static)
	virtual LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool bRun;
	POINT pt;

private:
	
	HINSTANCE				m_hInstance;
	DWORD					m_dwStyles;
	RECT					*m_pRect;
	char					*m_pClassName;
	char					*m_pWindowTitle;	
};
