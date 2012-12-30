#include <iostream>
using namespace std;
#include <windows.h>
#include "Tolle_CBitmap.h"
#include "input.h"

int CBitmap::ShowButton(HDC BackBuffer, int xloc, int yloc, POINT location, HDC bitmap, HBITMAP hbutton, BITMAP button)
{
	char buffer[100];

	SelectObject(bitmap, hbutton);
	TransparentBlt( BackBuffer, xloc, yloc, 
	button.bmWidth, button.bmHeight,
	bitmap, 0, 0, button.bmWidth, button.bmHeight, RGB(0,0,0) );

	static RECT Information;

	SetRect(&Information,xloc,yloc,xloc+button.bmWidth,yloc+button.bmHeight);

	FillRect(BackBuffer,&Information,(HBRUSH)GetStockObject(GRAY_BRUSH));

	if(PtInRect(&Information,location))
	{
		sprintf_s(buffer,"Button");
		TextOut(BackBuffer,600,200,buffer,(int)strlen(buffer));

		if(KEY_DOWN(VK_LBUTTON))
		{
			sprintf_s(buffer,"Pressed");
			TextOut(BackBuffer,600,200,buffer,(int)strlen(buffer));
			DrawText(BackBuffer,"Pressed",-1,&Information, 0);
			return 1;

		}
		else
		{
			DrawText(BackBuffer,"Button",-1,&Information, 0);
		}
	}

	return 0;
}


HBITMAP CBitmap::Load(char* test)
{
	return (HBITMAP)LoadImage(0,test, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

CBitmap::CBitmap()
{
}