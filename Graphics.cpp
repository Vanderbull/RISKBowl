#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

#include <windows.h>
#include "graphics.h"
#include "Input.h"
#include "defines.h"
#include "grid.h"
#include "Tolle_CBase.h"
#include "Tolle_CMatrix.h"
#include "Tolle_CScatter.h"
#include "CGridCell.h"
#pragma comment(lib,"msimg32.lib")	// for TransparentBlt() used below



// Main handle to device context
HDC gDC = 0;
// Handle to BackBuffer context
HDC	BackBuffer = 0;	
// Handle to unknown
HDC BitmapDC = 0;

HBITMAP BackBuffer_bmp = 0;
HBITMAP Old_bmp = 0;
HGDIOBJ oldBitmapDCBmp = 0;

grid_t *combat_grid = new grid_t;

RECT rect;

Base *b = new Derived();
Tolle_CBase *b2 = new Derived2();

extern CButtons *active_icon = 0;

static HBITMAP hGraphics[26];
static BITMAP Graphics[26];
static RECT choices[100];
static RECT boarding[10000];
static RECT turn_button;
static BOOL fDragRect;
static int team = 1;
static bool turn;

HBRUSH NewBrush = CreateSolidBrush(RGB(250, 25, 5));
HBRUSH tempBrush[255];

HBITMAP hcurrent = 0;
BITMAP current;
RECT curr = {0,0,0,0};
static bool place_ball = true;
static bool active;
static bool carrier = false;
static bool team_choosen = false;
static bool colli = false;
static bool home_set = false;
static bool blitz = false;
static bool pass = false;

static int toss_winner = 0;
static int first_players_turns = 0;
static int second_players_turns = 0;
static int ball_carrier = 0;
static int first_players_score = 0;
static int second_players_score = 0;
static int temp_field[1000];
static int team_number = NONE;
static int star_player_points[24];
int rows = 15;
int cols = 26;
int wisdom_word = 0;
std::vector<Point3D> Pointy3D;
CBitmap* Bitmap = 0;
fstream file_op("c:\\test_file.txt", ios::out);

data datarec;

bool CGraphics::read(string filename)
{
	HANDLE filehandle;
	BOOL success;
	DWORD  numwrite;
	int x;

	// open existing file for reading
	filehandle = CreateFile(filename.c_str(),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	
	if(filehandle == INVALID_HANDLE_VALUE)
	{
		file_op << "failed to open and read the file " << filename.c_str() << endl;
		return false;
	}

	x=0;
	do
	{
		success = ReadFile(filehandle,&datarec,sizeof(data), &numwrite,0);
	}
	while((x++<10) && success);

	CloseHandle(filehandle);
	return true;
}

bool CGraphics::write(string filename)
{
	HANDLE filehandle;
	BOOL success;
	DWORD  numwrite;
	int x;
	
	//open file
	filehandle = CreateFile(filename.c_str(),GENERIC_READ | GENERIC_WRITE,0,0,TRUNCATE_EXISTING,0,0);
	if(filehandle == INVALID_HANDLE_VALUE)
	{
		file_op << "- failed to open " << filename.c_str() << " log file for writing\n";
		return false;
	}
	else
	{
		file_op << "- opened " << filename.c_str() << " log file for writing\n";
	}
	
	x=0;

	do
	{
		//ostringstream oss;
		//oss << "Lineman" << x;
		//datarec.type = oss.str();
		//datarec.tile_brush[x] = CreateSolidBrush(RGB(0, 255, 0));
		success = WriteFile(filehandle,&datarec,sizeof(data), &numwrite,0);
		if(!success)
		{
			file_op << "- writing " << filename.c_str() << " data failed\n";
		}
		else
		{
			file_op << "- writing " << filename.c_str() << " data succeded\n";
		}
	}
	while((x++<10) && success);

	CloseHandle(filehandle);
	return true;
}

bool CGraphics::GFI()
{
	int temp = 0;
	temp = rand()%6 +1;
	if(temp == 1)
		return false;
	else
		return true;
}

bool CGraphics::Init(HWND hwnd)
{
	GetClientRect(hwnd,&client_window);
  Grid<int> myIntGrid; // declares a grid that stores ints
  myIntGrid.setElementAt(0, 0, 10);
  int x = myIntGrid.getElementAt(0, 0);

  Grid<int> grid2(myIntGrid);
  Grid<int> anotherIntGrid = grid2;

  Grid<int>* myGridp = new Grid<int>();
  myGridp->setElementAt(0, 0, 10);
  x = myGridp->getElementAt(0, 0);

  delete myGridp;

	//RECT client_window;
	//GetClientRect(hwnd,&client_window);

	if(!(gDC = GetDC(main_window_handle)))
		error();

	main_window_handle = hwnd;

	BackBuffer = CreateCompatibleDC(gDC);

	BackBuffer_bmp = CreateCompatibleBitmap(gDC, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	
	Old_bmp = (HBITMAP)SelectObject(BackBuffer, BackBuffer_bmp);

	SetTextColor(BackBuffer,RGB(255,0,0));
	SetBkColor(BackBuffer,RGB(0,0,0));
	SetBkMode(BackBuffer,OPAQUE);

	//int x_size = 14;
	//int y_size = 26;
	//float zoom = 10.0;
	//std::vector< vector<grid_node> > v_grid;
	//vector<grid_node> row(x_size);

	//for( int i = 0; i < y_size; i++ )
	//{
	//	for(int j = 0; j < row.size(); j++)
	//	{
	//		row[j].name = "Nimbus";
	//		row[j].solid = rand()%2;
	//		row[j].x = 	j*zoom*3;
	//		row[j].y = i*zoom*3;
	//	}
	//	v_grid.push_back(row);
	//}

 // for (int i = 1; i < v_grid.size(); i++)       // loops through each row of vy
 // {
	//	for (int j = 1; j < v_grid[i].size(); j++)
	//	{// loops through each element of each row
	//		if(v_grid[i][j].solid != 0)
	//		{
	//			SetRect(&datarec.box[i][j],v_grid[i][j].x-zoom,v_grid[i][j].y-zoom,v_grid[i][j].x+zoom,v_grid[i][j].y+zoom);
	//			//RECT test = {v_grid[i][j].x,v_grid[i][j].y,v_grid[i][j].x+zoom,v_grid[i][j].y+zoom};
	//			FillRect(BackBuffer,&datarec.box[i][j],(HBRUSH)GetStockObject(WHITE_BRUSH));
	//			SetPixelV(BackBuffer,v_grid[i][j].x,v_grid[i][j].y,RGB(0,rand()%255,0));
	//			file_op << v_grid[i][j].solid;
	//			//file_op << v_grid[i][j].name << "," << v_grid[i][j].solid << ",";
	//			Render();
	//		}
	//		else
	//		{
	//			file_op << " ";
	//		}
	//	}// prints the jth element of the ith row
	//	file_op << endl;
	//} 
	//file_op.close();
	//SplashScreen();
	//Render();
	//PostQuitMessage(0);
	for(int temp = 0; temp < 24; temp++)
	{
		datarec.player_movement_left[temp] = 6;
	}
	for(int temp = 0; temp < 255; temp++)
	{
		tempBrush[temp] = CreateSolidBrush(RGB(temp, temp, rand()%255));
		datarec.tile_brush[temp] = CreateSolidBrush(RGB(temp, temp, rand()%255));
	}

	read("c:\\data2.txt");
	//write("c:\\data.txt");
	for(int temp = 0; temp < 255; temp++)
	{
		//DeleteObject(tempBrush[temp]);
		DeleteObject(datarec.tile_brush[temp]);
	}

	wisdom_word = rand()%15 +1;

	//read();
	
	////////////////////////////////////////////////////////////
	// Initializing weather for 365 days                      //
	////////////////////////////////////////////////////////////
	Weather day[365]; // instantiate Weather object for 365 days
  
	// declare array of base-class pointers and initialize
  // each element to a derived-class type
  Base *array[ 365 ];
  // polymorphically invoke function print
  for ( int i = 0; i < 365; i++ )
	{
		array[ i ] = &day[i];
		file_op << array[ i ]->print();
	}
	array[0]->Image();
	/////////////////////////////////////////////////////////////

	string streng = "not set";

  file_op << GFI();

	fstream file_ip("did_you_know.txt", ios::in);

	int temp = 0;
	GetClientRect(main_window_handle,&rect);

	while(temp != wisdom_word)
	{
		++temp;
		getline(file_ip,streng,'#');
	}

	DrawText(BackBuffer,streng.c_str(),-1,&rect, DT_LEFT);
	BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);

	file_ip.close();

	Bitmap = new CBitmap();

	hGraphics[0] = 0;

	hGraphics[LOGO] = Bitmap->Load("pics/menuback.bmp");
	hGraphics[TEAMLOGOS128] = Bitmap->Load("pics/teamlogos/teamlogos128.bmp");
	hGraphics[FIELD_BLIZZARD] = Bitmap->Load("pics/fields/plain/field_blizzard copy.bmp");
	hGraphics[CUBE] = Bitmap->Load("pics/skavenfigure.bmp");
	hGraphics[BUTTON] = Bitmap->Load("pics/buttons/button1.bmp");
	hGraphics[LIGHTING] = Bitmap->Load("pics/lighting.bmp");
	hGraphics[ORCTEAM] = Bitmap->Load("pics/orcfigure.bmp");
	hGraphics[DARKELFTEAM] = Bitmap->Load("pics/darkelfteam.bmp");
	hGraphics[DWARFTEAM] = Bitmap->Load("pics/dwarfteam.bmp");
	hGraphics[HIGHELFTEAM] = Bitmap->Load("pics/highelfteam.bmp");
	hGraphics[HUMANTEAM] = Bitmap->Load("pics/humanteam.bmp");
	hGraphics[SKAVENTEAM] = Bitmap->Load("pics/skaventeam.bmp");
	hGraphics[BOARD] = Bitmap->Load("pics/figs/board.bmp");
	hGraphics[SKAVEN_L] = Bitmap->Load("pics/figs/skaven_l.bmp");
	hGraphics[SKAVEN_SV] = Bitmap->Load("pics/figs/skaven_sv.bmp");
	hGraphics[SKAVEN_T] = Bitmap->Load("pics/figs/skaven_t.bmp");
	hGraphics[SKAVENS] = Bitmap->Load("pics/figs/skaven.bmp");
	hGraphics[MENU_BACK] = Bitmap->Load("pics/menuback.bmp");
	hGraphics[19] = Bitmap->Load("pics/frame-base copy.bmp");
	hGraphics[STARCHART] = Bitmap->Load("pics/starchart.bmp");
	hGraphics[21] = Bitmap->Load("pics/scoreboard.bmp");
	hGraphics[22] = Bitmap->Load("pics/fog.bmp");
	hGraphics[23] = Bitmap->Load("pics/sball.bmp");
	hGraphics[24] = Bitmap->Load("pics/lightningbolt.bmp");
	delete Bitmap;

	GetObject(hGraphics[0],sizeof(BITMAP),&Graphics[1]);
	GetObject(hGraphics[LOGO],sizeof(BITMAP), &Graphics[1]);
	GetObject(hGraphics[TEAMLOGOS128],sizeof(BITMAP), &Graphics[2]);
	GetObject(hGraphics[FIELD_BLIZZARD],sizeof(BITMAP), &Graphics[3]);
	GetObject(hGraphics[CUBE],sizeof(BITMAP), &Graphics[4]);
	GetObject(hGraphics[BUTTON],sizeof(BITMAP), &Graphics[5]);
	GetObject(hGraphics[LIGHTING],sizeof(BITMAP), &Graphics[6]);
	GetObject(hGraphics[ORCTEAM],sizeof(BITMAP), &Graphics[7]);
	GetObject(hGraphics[DARKELFTEAM],sizeof(BITMAP), &Graphics[8]);
	GetObject(hGraphics[DWARFTEAM],sizeof(BITMAP), &Graphics[9]);
	GetObject(hGraphics[HIGHELFTEAM],sizeof(BITMAP), &Graphics[10]);
	GetObject(hGraphics[HUMANTEAM],sizeof(BITMAP), &Graphics[11]);
	GetObject(hGraphics[SKAVENTEAM],sizeof(BITMAP), &Graphics[12]);
	GetObject(hGraphics[BOARD],sizeof(BITMAP), &Graphics[13]);
	GetObject(hGraphics[SKAVEN_L],sizeof(BITMAP), &Graphics[14]);
	GetObject(hGraphics[SKAVEN_SV],sizeof(BITMAP), &Graphics[15]);
	GetObject(hGraphics[SKAVEN_T],sizeof(BITMAP), &Graphics[16]);
	GetObject(hGraphics[SKAVEN],sizeof(BITMAP), &Graphics[17]);
	GetObject(hGraphics[MENU_BACK],sizeof(BITMAP), &Graphics[18]);
	GetObject(hGraphics[19],sizeof(BITMAP), &Graphics[19]);
	GetObject(hGraphics[STARCHART],sizeof(BITMAP), &Graphics[20]);
	GetObject(hGraphics[21],sizeof(BITMAP), &Graphics[21]);	
	GetObject(hGraphics[22],sizeof(BITMAP), &Graphics[22]);
	GetObject(hGraphics[23],sizeof(BITMAP), &Graphics[23]);
	GetObject(hGraphics[24],sizeof(BITMAP), &Graphics[24]);

	BitmapDC = CreateCompatibleDC(BitmapDC);
	oldBitmapDCBmp = GetCurrentObject(BitmapDC, OBJ_BITMAP);

	SelectObject(BitmapDC,hGraphics[BOARD]);

	int i = 0;
	for(y = 0; y < cols; y++)
	{
		for(x = 0; x < rows; x++)
		{
			SetRect(&boarding[x+i],  x*cols,y*cols,x*cols+cols,y*cols+cols);
		}
		i += cols - 1;
	}
	for(int temp = 0; temp < 1000; temp++)
		{
			temp_field[temp] = 0;
		}

	grid_node2 grider;
	grider.name = "";
	grider.solid = true;
	grider.x = 10.0;
	grider.y = 10.0;
	grid_node2 *temp_grid_node2(&grider);

	temp_grid_node2->x = 30.0;
	temp_grid_node2->y = 30.0;
	b2->active_node(temp_grid_node2);
	b2->Grid(client_window.right/30,client_window.bottom/30,30.0, hGraphics[10]);
	b2->Init(BackBuffer);
	//Matrix m(10,10);
 //  m(5,8) = 106.15;
 //  std::cout << m(5,8);

	
	return true;
}

bool CGraphics::Reset()
{
	return true;
}

// Notice: Finished
void CGraphics::EraseScreen()
{
	ValidateRect(main_window_handle,&rect);
	GetClientRect(main_window_handle,&rect);
	FillRect(BackBuffer, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
}

//Notice: Finished(disabled)
void CGraphics::SplashScreen()
{
	while(Splash)
	{
		SelectObject(BitmapDC,hGraphics[LOGO]);
		
		TransparentBlt( BackBuffer, 0, 0, 
			Graphics[1].bmWidth, Graphics[1].bmHeight,
			BitmapDC, 0, 0, Graphics[1].bmWidth, Graphics[1].bmHeight, RGB(0,0,0) );

		SelectObject(BitmapDC, oldBitmapDCBmp);

		POINT p = {0};
		GetCursorPos(&p);

		RECT test = {100,50,300,200};

		CreateButton(BackBuffer,test,"Caption",p);

		Trigger(BackBuffer,test,"Trigger",p);

		BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);
	
		if(KEY_DOWN(VK_RETURN))
		Splash = false;
	}
}

void CGraphics::About()
{
	EraseScreen();

	SelectObject(BitmapDC,hGraphics[LOGO]);
		
	TransparentBlt( BackBuffer, GetSystemMetrics(SM_CXSCREEN)/4, GetSystemMetrics(SM_CYSCREEN)/4, 
		Graphics[1].bmWidth, Graphics[1].bmHeight,
		BitmapDC, 0, 0, Graphics[1].bmWidth, Graphics[1].bmHeight, RGB(0,0,0) );

	SelectObject(BitmapDC, oldBitmapDCBmp);

	string streng = "not set";
	fstream file_ip("hall_of_fame.txt", ios::in);

	//int temp = 0;
	GetClientRect(main_window_handle,&rect);
	getline(file_ip,streng,'#');
	DrawText(BackBuffer,streng.c_str(),-1,&rect, DT_LEFT);
	BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);

	file_ip.close();
}

bool CGraphics::Render()
{
	SelectObject(BitmapDC, oldBitmapDCBmp);
	BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);
	return true;
}

int CGraphics::BuyTeam(POINT Mouse_Loc)
{
	RECT PlayerStats;
	RECT Player2Stats;
	//RECT Information = {300,600,1200,1200};

	PlayerStats.bottom = 100;
	PlayerStats.top = 0;
	PlayerStats.left =	600;
	PlayerStats.right = 800;

	Player2Stats.bottom = 300;
	Player2Stats.top = 0;
	Player2Stats.left =	800;
	Player2Stats.right = 940;
	
	SelectObject(BitmapDC,hGraphics[13]);

	int xmax = Graphics[13].bmWidth;
	int ymax = Graphics[13].bmHeight;

	xmax = xmax / 139;
	ymax = ymax / 147;

	for(y = 0; y < ymax; y++)
	{
		for(x = 0; x < xmax; x++)
		{
			TransparentBlt( BackBuffer, x*139, y*147, 139, 147,
			BitmapDC, x*139, y*147,139, 147, RGB(0,0,0) );
		}
	}

	SetRect(&choices[0],0,0,139,147);
	SetRect(&choices[1],139,0,278,147);
	SetRect(&choices[2],278,1,417,147);
	SetRect(&choices[3],417,1,556,147);
	SetRect(&choices[4],0,130,130,260);
	SetRect(&choices[5],130,130,260,260);
	SetRect(&choices[6],260,130,390,260);
	SetRect(&choices[7],390,130,520,260);
	SetRect(&choices[8],0,260,130,390);
	SetRect(&choices[9],130,260,260,390);
	SetRect(&choices[10],260,260,390,390);
	SetRect(&choices[11],390,260,520,390);
	SetRect(&choices[12],10,390,130,520);

	SetRect(&choices[0],0,0,139,147);
	SetRect(&choices[2],139,0,278,147);
	SetRect(&choices[3],278,1,417,147);
	SetRect(&choices[4],417,1,556,147);

	SetRect(&choices[9],   0,260,130,390);
	SetRect(&choices[10],130,260,260,390);
	SetRect(&choices[11],260,260,390,390);
	SetRect(&choices[12],390,260,520,390);
	SetRect(&choices[13],10,390,130,520);
	
	SetRect(&choices[5],  0,130,130,260);
	SetRect(&choices[6],130,130,260,260);
	SetRect(&choices[7],260,130,390,260);
	SetRect(&choices[8],390,130,520,260);



	SelectObject(BitmapDC, hcurrent);
	TransparentBlt( BackBuffer, 550, 250, 
	139, current.bmHeight,
	BitmapDC, curr.left, 0, 139, current.bmHeight, RGB(0,0,0) );

	if(KEY_DOWN(VK_LBUTTON))
	{
		if(PtInRect(&choices[0],Mouse_Loc))
		{
			curr = choices[0];
			hcurrent = hGraphics[13];
			current = Graphics[13];
			fDragRect = true;

			//Coach->Pay(BackBuffer,50,Mouse_Loc,true);
		}
		if(PtInRect(&choices[2],Mouse_Loc))
		{
			curr = choices[2];
			hcurrent = hGraphics[13];
			current = Graphics[13];
			fDragRect = true;

			//Coach->Pay(BackBuffer,50,Mouse_Loc,true);
		}
		if(PtInRect(&choices[3],Mouse_Loc))
		{
			curr = choices[3];
			hcurrent = hGraphics[13];
			current = Graphics[13];
			fDragRect = true;

			//Coach->Pay(BackBuffer,50,Mouse_Loc,true);
		}
		if(PtInRect(&choices[4],Mouse_Loc))
		{
			curr = choices[4];
			hcurrent = hGraphics[13];
			current = Graphics[13];
			fDragRect = true;

			//Coach->Pay(BackBuffer,50,Mouse_Loc,true);
		}

	}

	if(PtInRect(&choices[0],Mouse_Loc))
	{
		//Coach->ShowPaymentButton(BackBuffer, "Recruit", Mouse_Loc, BitmapDC, hGraphics[5],Graphics5);
		DrawText(BackBuffer,"Skaven Storm Vermin\n"
							"Qty: 0-12\n"
							"Cost: 90,000 gps\n"
							"MA: 7\n"
							"ST: 3\n"
							"AG: 3\n"
							"AV: 8\n"
							"Skills: Block",-1,&Player2Stats, 0);
		
		fDragRect = true;
		return 3;
	}
	if(PtInRect(&choices[2],Mouse_Loc))
	{
		//Coach->ShowPaymentButton(BackBuffer, "Recruit",Mouse_Loc, BitmapDC, hGraphics[5],Graphics5);
		DrawText(BackBuffer,"Skaven Linemen\n"
							"Qty: 0-12\n"
							"Cost: 50,000 gps\n"
							"MA: 7\n"
							"ST: 3\n"
							"AG: 3\n"
							"AV: 7\n"
							"Skills: None",-1,&Player2Stats, 0);
		fDragRect = true;
		return 3;
	}
	if(PtInRect(&choices[3],Mouse_Loc))
	{
		//Coach->ShowPaymentButton(BackBuffer, "Recruit",Mouse_Loc, BitmapDC, hGraphics[5],Graphics5);
		DrawText(BackBuffer,"Skaven Gutter Runner"
							"Qty: 0-12\n"
							"Cost: 50,000 gps\n"
							"MA: 9\n"
							"ST: 2\n"
							"AG: 4\n"
							"AV: 7\n"
							"Skills: Dodge",-1,&Player2Stats, 0);
		fDragRect = true;
		return 3;
	}
	if(PtInRect(&choices[4],Mouse_Loc))
	{
		//Coach->ShowPaymentButton(BackBuffer, "Recruit",Mouse_Loc, BitmapDC, hGraphics[5],Graphics5);
		DrawText(BackBuffer,"Skaven Thrower\n"
							"Qty: 0-12\n"
							"Cost: 70,000 gps\n"
							"MA: 7\n"
							"ST: 3\n"
							"AG: 3\n"
							"AV: 7\n"
							"Skills: Shure Hands"
							"		 Pass"
							,-1,&Player2Stats, 0);
		fDragRect = true;
		return 3;
	}
	
//	Coach->ShowPaymentButton(BackBuffer, "Buy Team",Mouse_Loc, BitmapDC, hGraphics[5],Graphics[5]);

	if( Bitmap->ShowButton(BackBuffer, 100, 100, Mouse_Loc, BitmapDC, hGraphics[5],Graphics[5]) )
		return 3;
	
	return 3;
}

//Notice: Currently being work on
int CGraphics::ChooseTeam(HWND hwnd, float frames,POINT pt)
{
	RECT accept_button;
	//RECT client_window;
	//GetClientRect(hwnd,&client_window);
	SetRect(&accept_button,client_window.right-200,client_window.bottom-40,client_window.right,client_window.bottom);

	//Notice: checks to see if the accept button is choosen
	//Issues: Unknown
	if(KEY_DOWN(VK_LBUTTON))
	{
		if(PtInRect(&accept_button,pt))
		{
			return 5; // gamestate for playing
		}
	}
	
	SelectObject(BitmapDC,hGraphics[TEAMLOGOS128]);

	TransparentBlt( BackBuffer, 0, 0, client_window.right, client_window.bottom, BitmapDC, 0, 0, Graphics[TEAMLOGOS128].bmWidth, Graphics[TEAMLOGOS128].bmHeight, RGB(0,0,0) );

if(PtInRect(&accept_button,pt))
	{
		SelectObject(BitmapDC,hGraphics[BUTTON]);
		TransparentBlt( BackBuffer, accept_button.left-15, accept_button.top-15, Graphics[BUTTON].bmWidth, Graphics[BUTTON].bmHeight/2, BitmapDC, 0, 32, Graphics[BUTTON].bmWidth, Graphics[BUTTON].bmHeight/2, RGB(0,0,0) );
	}
else
{
		SelectObject(BitmapDC,hGraphics[BUTTON]);

		TransparentBlt( BackBuffer, accept_button.left-15, accept_button.top-15, Graphics[BUTTON].bmWidth, Graphics[BUTTON].bmHeight/2, BitmapDC,0 , 0, Graphics[BUTTON].bmWidth, Graphics[BUTTON].bmHeight/2, RGB(0,0,0) );
}
DrawText(BackBuffer,"Press to choose team",-1,&accept_button, 0);

	//Notice: down know where curr is declared, and this shows the choice made graphically
	//Issues: paints the choice in the upper left corner at the beginning before any choice is made
	SelectObject(BitmapDC, hGraphics[6]);
	TransparentBlt( BackBuffer, curr.left, curr.top, client_window.right/4, client_window.bottom/4,
		BitmapDC, 0, 0, Graphics[6].bmWidth, Graphics[6].bmHeight, RGB(0,0,0) );

	//Notice: this is the topleft most choice
	SetRect(&choices[0] , 0 , 0 ,  client_window.right/4,  Graphics[2].bmHeight/4);

	//Notice: these are top row choices
	SetRect(&choices[1], client_window.right/4   , 0, (client_window.right/4)*2,  client_window.bottom/4);
	SetRect(&choices[2], client_window.right/4*2 , 0, client_window.right/4*3,  client_window.bottom/4);
	SetRect(&choices[3], client_window.right/4*3 , 0, client_window.right/4*4,  client_window.bottom/4);

	// Notice: these are left column choices
	SetRect(&choices[4], 0, client_window.bottom/4    , client_window.right/4,  client_window.bottom/4*2);
	SetRect(&choices[5], 0, client_window.bottom/4*2  , client_window.right/4,  client_window.bottom/4*3);
	SetRect(&choices[6], 0, client_window.bottom/4*3  , client_window.right/4,  client_window.bottom/4*4);

	grid_t gt_data;
	RECT rect;
	int tilesize = 5;
	int location = 500;
	bool did = false;


	combat_grid->height = 256 ; //rows
	combat_grid->width = 256; //col
	//	combat_grid->grid_node = new grid_node_t[256];
	static int ho = 0;
	if(ho== 0)
		for (int x=0;x<combat_grid->width;x++)
		{
			for (int y=0;y<combat_grid->height;y++)
			{
				combat_grid->grid_node[x][y] = new grid_node_t;
				combat_grid->grid_node[x][y]->solid = true;
				ho = 6;
			}
		}
	 for (int n=0;n<70;n++)
	 {
	   for (int m=0;m<130;m++)
		 {
			 if(combat_grid->grid_node[n][m]->solid == false)
				 SetPixelV(BackBuffer,location + n*tilesize,m*tilesize,RGB(0,255,0));
			 if( pt.x == location + n*tilesize )
				if( pt.y == m*tilesize )
				{
					FillRect(BackBuffer,&accept_button,(HBRUSH)GetStockObject(GRAY_BRUSH));
					combat_grid->grid_node[n][m]->solid = false;
					did = true;
				}
		 }
	 }

 	 b->Cursor(BackBuffer,pt);
	 if(did)
	 {
		 b->Raster_Line(BackBuffer,pt.x-10,pt.y-10 ,pt.x+10, pt.y-10);
		 b->Raster_Line(BackBuffer,pt.x+10,pt.y-10 ,pt.x+10, pt.y+10);
		 b->Raster_Line(BackBuffer,pt.x+10,pt.y+10 ,pt.x-10, pt.y+10);
		 b->Raster_Line(BackBuffer,pt.x-10,pt.y+10 ,pt.x-10, pt.y-10);
	 }

 if(pt.x < 235 && pt.y < 235 && pt.x > 1 && pt.y > 1)
	 SetRect(&rect,  gt_data.board[pt.x-20][0], gt_data.board[0][pt.y-20], gt_data.board[pt.x + 20][0], gt_data.board[0][pt.y+20]);
 FillRect(BackBuffer, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	//Notice: Prints the choice when howering over it
	//Issues: Needs names for teams and possible other info
	//        Could be evolved to draw a temporary box over the howering item
	for(int tmp = 0; tmp < 14; tmp++)
	{
		if(PtInRect(&choices[tmp],pt))
		{
			switch(tmp)
			{
			case 0:	DrawText(BackBuffer,"Unknown 1",-1,&defines_rect, 0); break;
			case 1:	DrawText(BackBuffer,"Unknown 2",-1,&defines_rect, 0); break;
			case 2:	DrawText(BackBuffer,"Unknown 3",-1,&defines_rect, 0); break;
			case 3:	DrawText(BackBuffer,"Unknown 4",-1,&defines_rect, 0); break;
			case 4:	DrawText(BackBuffer,"Unknown 5",-1,&defines_rect, 0); break;
			case 5:	DrawText(BackBuffer,"Unknown 6",-1,&defines_rect, 0); break;
			case 6:	DrawText(BackBuffer,"Unknown 7",-1,&defines_rect, 0); break;
			case 7:	DrawText(BackBuffer,"Unknown 8",-1,&defines_rect, 0); break;
			case 8:	DrawText(BackBuffer,"Unknown 9",-1,&defines_rect, 0); break;
			case 9:	DrawText(BackBuffer,"Unknown 10",-1,&defines_rect, 0); break;
			case 10:	DrawText(BackBuffer,"Unknown 11",-1,&defines_rect, 0); break;
			case 11:	DrawText(BackBuffer,"Unknown 12",-1,&defines_rect, 0); break;
			case 12:	DrawText(BackBuffer,"Unknown 13",-1,&defines_rect, 0); break;
			case 13:	DrawText(BackBuffer,"Unknown 14",-1,&defines_rect, 0); break;
			default: DrawText(BackBuffer,"Unknown error",-1,&defines_rect, 0); break;
			}
		}
	}

	for(int tmp = 0; tmp < 14; tmp++)
	{
		if(KEY_DOWN(VK_LBUTTON))
		{	
			if(PtInRect(&choices[tmp],pt))
			{
				switch(tmp)
				{
				case 0:	home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 1:	home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 2:	home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 3:	home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 4:	home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 5:	home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 6:	home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 7:	home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 8:	home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 9:	home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 10: home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 11: home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 12: home_set = true; team_choosen = true; team_number = SKAVEN;break;
				case 13: home_set = true; team_choosen = true; team_number = SKAVEN;break;
				default: DrawText(BackBuffer,"Unknown error",-1,&defines_rect, 0); break;
				}
				curr = choices[tmp];
			}
		}
	}
	return 1;
}

int CGraphics::Menu(POINT pty)
{
	std::array<CGridCell,390> BBPitch;
	int NodeIndex = 0;
	
	for(int y=0; y < (26*16); y+=16)
	{
		for(int x=0; x < (15*16); x+=16)
		{
			BBPitch.at(NodeIndex).mCellID = NodeIndex;
			BBPitch.at(NodeIndex).PosX = x;
			BBPitch.at(NodeIndex).PosY = y;
			NodeIndex++;
		}
	}
		for(int i= 0; i < 390; i++)
		{
				RECT Rectangle;
				SetRect(&Rectangle,BBPitch.at(i).PosX,BBPitch.at(i).PosY,BBPitch.at(i).PosX + 16,BBPitch.at(i).PosY +16);

				FillRect(BackBuffer,&Rectangle,(HBRUSH)GetStockObject(GRAY_BRUSH));
				if(PtInRect(&Rectangle,pty))
				{
					FillRect(BackBuffer,&Rectangle,(HBRUSH)GetStockObject(WHITE_BRUSH));
				}
		}
	// Issues: Must make the menu check to see which flick that is active else
	// it will trigger coach team every time as they are layered upon each other.
	int new_button_top = (GetSystemMetrics(SM_CYSCREEN)/10)*2;
	int new_button_bottom = (GetSystemMetrics(SM_CYSCREEN)/10)*6;
	int new_button_left = (GetSystemMetrics(SM_CXSCREEN)/10)*4;
	int new_button_right = (GetSystemMetrics(SM_CXSCREEN)/10)*6;
	//int new_button_width = 200;
	int new_button_height = 40;

	SetRect(&choices[0],new_button_left,new_button_top,new_button_right,new_button_bottom);
	SetRect(&choices[1],new_button_left,new_button_top + new_button_height,new_button_right,new_button_bottom +new_button_height);
	SetRect(&choices[2],new_button_left,new_button_top +new_button_height*2,new_button_right,new_button_bottom +new_button_height*2);

	FillRect(BackBuffer,&choices[0],(HBRUSH)GetStockObject(GRAY_BRUSH));
	FillRect(BackBuffer,&choices[1],(HBRUSH)GetStockObject(WHITE_BRUSH));
	FillRect(BackBuffer,&choices[2],(HBRUSH)GetStockObject(LTGRAY_BRUSH));

	DrawText(BackBuffer,"Coach Team",-1,&choices[0], DT_SINGLELINE | DT_CENTER);
	DrawText(BackBuffer,"Exit",-1,&choices[1], DT_SINGLELINE | DT_CENTER);
	DrawText(BackBuffer,"About",-1,&choices[2], DT_SINGLELINE | DT_CENTER);

	SelectObject(BitmapDC, hcurrent);
	TransparentBlt( BackBuffer, 550, 250, 
	current.bmWidth, current.bmHeight,
	BitmapDC, 0, 0, current.bmWidth, current.bmHeight, RGB(0,0,0) );

	//char buffer[100];
	
	if(KEY_DOWN(VK_LBUTTON))
	{
		if(PtInRect(&choices[0],pty))
		{
			curr = choices[0];
			SetRect(&curr,0,0,0,0);
			return 1;
		}
		if(PtInRect(&choices[1],pty))
		{
			curr = choices[1];
			PostQuitMessage(0);
			return 2;
		}
		if(PtInRect(&choices[2],pty))
		{
			curr = choices[2];
			return 4;
		}
		if(PtInRect(&choices[3],pty))
		{
			curr = choices[3];
			SplashScreen();
		}
	}

	if(PtInRect(&choices[0],pty))
	{
		curr = choices[0];
		FillRect(BackBuffer,&choices[0],(HBRUSH)GetStockObject(GRAY_BRUSH));
		DrawText(BackBuffer,"Coach Team",-1,&choices[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	if(PtInRect(&choices[1],pty))
	{
		curr = choices[1];
		FillRect(BackBuffer,&choices[1],(HBRUSH)GetStockObject(WHITE_BRUSH));
		DrawText(BackBuffer,"Exit Game",-1,&choices[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	if(PtInRect(&choices[2],pty))
	{
		curr = choices[2];
		FillRect(BackBuffer,&choices[2],(HBRUSH)GetStockObject(LTGRAY_BRUSH));
		DrawText(BackBuffer,"About",-1,&choices[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	return 0;
}

int CGraphics::Kickoff(HWND hwnd, POINT musi)
{
	//CScatter *Scattra;
	//Scattra->length();
	/*RECT client_window;*/
	GetClientRect(hwnd,&client_window);

	//b2->Grid(client_window.right/30,client_window.bottom/30,30.0);
	string temp_name = b2->v_grid[0][0].name;
	b2->Draw();
	grid_node2 grider;
	grider.name = "";
	grider.solid = true;
	grider.x = 10.0;
	grider.y = 10.0;
	grid_node2 *temp_grid_node2(&grider);

	temp_grid_node2->x = musi.x;
	temp_grid_node2->y = musi.y;
	b2->Check(temp_grid_node2);

	b2->SetBitmap(hGraphics[9],3,3);
	//SelectObject(BitmapDC, b2->v_grid[1][1].picture);
	//TransparentBlt( BackBuffer, 0, 0, 
	//Graphics[9].bmWidth, Graphics[9].bmHeight,
	//BitmapDC, 0, 0, Graphics[9].bmWidth, Graphics[9].bmHeight, RGB(0,0,0) );
//	b2->v_grid[0][0].picture

	if(KEY_DOWN(VK_SPACE))
	{
	b2->Grid(rand()%10+5,rand()%10+5,10.0, hGraphics[10]);
	}

	b2->Print();
	Line_list list;
	list.test(0,0);
	
	int linelist[12][4];
	//linelist[0][0] = 0;
	//linelist[0][1] = 1; 
	//linelist[1][0] = 2;
	//linelist[1][1] = 3;

	//linelist[2][0] = 0;
	//linelist[2][1] = 2; 
	//linelist[3][0] = 1;
	//linelist[3][1] = 3;

	//linelist[4][0] = 4;
	//linelist[4][1] = 5; 
	//linelist[5][0] = 6;
	//linelist[5][1] = 7;

	//linelist[6][0] = 4;
	//linelist[6][1] = 6; 
	//linelist[7][0] = 5;
	//linelist[7][1] = 7;

	//linelist[8][0] = 0;
	//linelist[8][1] = 4; 
	//linelist[9][0] = 1;
	//linelist[9][1] = 5; 
	//linelist[10][0] = 2;
	//linelist[10][1] = 6; 
	//linelist[11][0] = 3;
	//linelist[11][1] = 7;

	Point3D Points[] =
	{
			 Point3D( 600.0, 200.0, -20.0 ),//0
			 Point3D( 640.0, 200.0, -20.0 ), //1
			 Point3D( 600.0, 480.0, -20.0 ), //2
			 Point3D( 640.0, 480.0, -20.0 ), //3

			 Point3D( 600.0, 200.0, 20.0 ), //4
			 Point3D( 640.0, 200.0, 20.0 ), //5 
			 Point3D( 600.0, 480.0, 20.0 ), //6
			 Point3D( 640.0, 480.0, 20.0 ), //7
	};

	//for(int i = 0; i < 12; i++)
	//{ b->Raster_Line3D(BackBuffer,b->projection(Points[ list.test(i,0) ]),b->projection(Points[ list.test(i,1) ]));
	//}


	// Notice: Writing all the game data to file for analysis and such.
	// Issues: None known
	if(KEY_DOWN(VK_SNAPSHOT))
	{
		write("c:\\data2.txt");
		file_op << "Reading and writing data to file" << endl;
		write("c:\\data.txt");
		read("c:\\data.txt");
	}
	
	return 5;
}

void CGraphics::error()
{
	file_op << "\n#Some error occured - ";
	PostQuitMessage(0);
}

CGraphics::CGraphics(int x, int y, HWND hwnd)
{
	main_window_handle = 0;
	if(!(gDC = GetDC(main_window_handle)))
		error();

	main_window_handle = hwnd;

	BackBuffer = CreateCompatibleDC(gDC);

	//BackBuffer_bmp = CreateCompatibleBitmap(gDC, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	//
	//Old_bmp = (HBITMAP)SelectObject(BackBuffer, BackBuffer_bmp);

	SetTextColor(BackBuffer,RGB(255,0,0));
	SetBkColor(BackBuffer,RGB(0,0,0));
	SetBkMode(BackBuffer,OPAQUE);
	////read();
	//
	//string streng = "not set";

 // file_op << GFI();

	//fstream file_ip("did_you_know.txt", ios::in);

	//int temp = 0;
	GetClientRect(main_window_handle,&rect);

	//while(temp != wisdom_word)
	//{
	//	++temp;
	//	getline(file_ip,streng,'#');
	//}

	DrawText(BackBuffer,"dlydrl",-1,&rect, DT_LEFT);
	BitBlt(gDC, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), BackBuffer, 0, 0, SRCCOPY);
}

CGraphics::~CGraphics()
{
	file_op.close();
	ReleaseDC(main_window_handle,gDC);
	//delete Coach;
	DeleteDC(gDC);
}