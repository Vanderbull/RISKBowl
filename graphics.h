#include <string>
using namespace std;
#include "buttons.h"
#include "Base.h"
//#include "Base2.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

class CGraphics : public CButtons
{
private:

	HWND main_window_handle;
	RECT client_window;
	//int Row;
	//int Col;

	//int MenuChoiceOne;

	//int counterx;
	//int countery;
	//int counterz;
	//int targetpaint;
	
public:

	//bool collission;
	
	void error();
	void SplashScreen();
	void About();
	void EraseScreen();
	void RenderCollisionObjects();
	void Menu();
	void Release();

	//bool ShowMenu;
	bool Splash;
	bool Init(HWND hwnd);
	bool Render();
	bool Reset();
	bool read(string filename);
	bool write(string filename);
	bool GFI();

	int ChooseTeam(HWND hwnd, float frames,POINT test);
	int BuyTeam(POINT mouse);
	int Kickoff(HWND hwnd, POINT musi);
	int Menu(POINT PointerLocation);

	CGraphics::CGraphics(int x, int y, HWND hwnd);
	~CGraphics();
};
#endif