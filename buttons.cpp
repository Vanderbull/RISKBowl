#include <iostream>
using namespace std;
#include <windows.h>
#include "buttons.h"
#include "input.h"
#include "Tolle_CBitmap.h"

bool CButtons::Button(HDC BackBuffer, char* caption,POINT location, HDC bitmap, HBITMAP hbutton, BITMAP button)
{
	SelectObject(bitmap, hbutton);
	TransparentBlt( BackBuffer, 250, 590, 
	button.bmWidth, button.bmHeight,
	bitmap, 0, 0, button.bmWidth, button.bmHeight, RGB(0,0,0) );
	return true;
}

bool CButtons::CreateButton(HDC BackBuffer, RECT size, char* caption, POINT location)
{
	FillRect(BackBuffer,&size,(HBRUSH)GetStockObject(GRAY_BRUSH));
	if(!KEY_DOWN(VK_LBUTTON))
		DrawText(BackBuffer,caption,-1,&size, 0);

	return true;
}

bool CButtons::Trigger(HDC BackBuffer, RECT size, char* caption, POINT location) const
{
	if(PtInRect(&size,location) && KEY_DOWN(VK_LBUTTON))
		DrawText(BackBuffer,caption,-1,&size, 0);
	return false;
}



CButtons::CButtons()
{
}
