#ifndef TOLLE_CBITMAP_H
#define TOLLE_CBITMAP_H

class CBitmap
{
private:

protected:

public:

	int ShowButton(HDC BackBuffer, int xloc, int yloc, POINT location, HDC bitmap, HBITMAP hbutton, BITMAP button);
	HBITMAP Load(char* test);
	CBitmap::CBitmap();
	~CBitmap() {};
};
#endif