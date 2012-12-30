#ifndef CBUTTONS_H
#define CBUTTONS_H

#include "Tolle_CBitmap.h"

class CBitmap;

class CButtons : public CBitmap
{
private:

public:

	bool Button(HDC BackBuffer, char* caption, POINT location, HDC bitmap, HBITMAP hbutton, BITMAP button);
	bool CreateButton(HDC BackBuffer, RECT size, char* caption, POINT location);
	virtual bool Trigger(HDC BackBuffer, RECT size, char* caption, POINT location) const;
	CButtons();
	~CButtons() {};
};
#endif