#include <vector>
#include <math.h>
#include <list>
using namespace std;
#include "Tolle_CBitmap.h"

#define PI 3.14

int BBPitch[15][26];

typedef struct griden
{
	int solid;
	string name;
	float x;
	float y;
} grid_node;

typedef struct
{
	char type;
	int color;
	bool solid;
} grid_node_t;

typedef struct
{
	grid_node_t *grid_node[256][256];
	int board[256][256];
	int height;
	int width;
} grid_t;

template <class T>
T Add(T a, T b) //C++ function template sample
{
  return a+b;
}

template<class T> 
class Team
{
private:
	T *p; int size;
public:
	Team(int s) : size(s){ p=new T[size]; }
	~Team() { delete [] p; }
};

template<class T> class grid
{
private:
    T *p; int w,h;

public:
    grid(int width,int height) : w(width),h(height) { p=new T[w*h]; }
    ~grid(){ delete [] p; }

    T &operator()(int x,int y){ return p[(y*width)+x]; }
    const T &operator()(int x,int y) const { return p[(y*width)+x]; }
};

class Line_list {
public:
	std::vector< vector<int> > v_list;
	vector<int> row;
	Line_list()
	{
		vector<int> row(12);
		for( int i = 0; i < 4; i++ )
		{
			for(int j = 0; j < row.size(); j++)
			{
				row[j] = rand()%7;
			}
			v_list.push_back(row);
		}
	}
	int test(int a, int b) 
	{
		return v_list[b][a];
	}
};

class Point {
    int _x, _y;
 
  public:
    Point() {
      _x = _y = 0;
    }
    Point(const int xval, const int yval) {
      _x = xval;
      _y = yval;
    }
    Point(const Point &from) {
      _x = from._x;
      _y = from._y;
    }

    ~Point() { /* Nothing to do! */ }
 
    void setX(const int val);
    void setY(const int val);
    int getX() { return _x; }
    int getY() { return _y; }
  };

class Point3D : public Point {
    int _z;
  
  public:
    Point3D() {
      setX(0);
      setY(0);
      _z = 0;
    }
    Point3D(
      const int x, 
      const int y, 
      const int z) : Point(x, y) {
        _z = z;
    }

    ~Point3D() { /* Nothing to do */ }

    int getZ() { return _z; }
    void setZ(const int val) { _z = val; }
  };

class Point_storage {
public:
	std::vector<Point3D> *v_points;
	
  Point_storage() {
		v_points->push_back(Point3D(500.0,200,-20.0));
		v_points->push_back(Point3D(540.0,200.0,-20.0));
		v_points->push_back(Point3D(500.0,400.0,-20.0));
		v_points->push_back(Point3D(540.0,400.0,-20.0));
	}
	Point3D test(int p) 
	{
		return v_points->at(1);
	}
};

class arrayoftype
{
public:
	int *data;
	arrayoftype(int xsize, int ysize)
	{
		data = new int[xsize];
	}
	~arrayoftype()
	{
		if(data!=NULL) delete[] data;
	}
};

class Base
{
public:
    Base()
    {
        cout<<"Base class constructor"<<endl;
    }

		virtual string print() = 0; // pure virtual
		virtual int average(int turns) = 0; // pure virtual
		virtual HBITMAP Image() = 0; // pure virtual
		virtual RECT *Grid(HDC g,int x_size, int y_size) = 0; // pure virtual
		virtual void Cursor(HDC g, POINT p) = 0; // pure virtual
		virtual void movement_left(HDC g, int moves[24]) = 0;
		virtual void ball_location(HDC g, int location) = 0;
		virtual void Raster_Line(HDC g, double x1, double y1, double x2, double y2) = 0;
		virtual void lineCircle(HDC g, int x1, int y1, int radius) = 0;
		virtual void Raster_Line3D(HDC g, Point start, Point stop) = 0;
		virtual Point3D projection(Point3D vertex) = 0;
		virtual int sgn (long a)= 0;
		virtual void status(HDC g, string text) = 0;
		virtual void Scatter() = 0;
		virtual void player(HDC g, int x, int y) = 0;

    virtual ~Base ()
    {
        cout<<"Base class Destructor"<<endl;
    }
};

class Derived : virtual public Base
{
private:
	RECT active_item;
			list<string> SS;
public:
	RECT box;
	RECT test[4500];

    Derived()
    {
        cout<<"Derived class constructor"<<endl;
    }

		string print()
		{

			return "Derived";
		}

		int average(int turns)
		{
			if(turns <= 8)
			{
				return 5;
			}
			else if(turns <= 16)
			{
				return 5;
			}
			else if(turns > 16)
			{
				return 0;
			}
			else return -1;
		}

		HBITMAP Image()
		{
			return 0;
		}

		RECT *Grid(HDC g,int x_size, int y_size)
		{
			//int x_size = 16;
			//int y_size = 26;
			float zoom = 10.0;
			std::vector< vector<grid_node> > v_grid;
			vector<grid_node> row(x_size);

			for( int i = 0; i < y_size; i++ )
			{
				for(int j = 0; j < row.size(); j++)
				{
					row[j].name = "Nimbus";
					row[j].solid = 1;
					row[j].x = 	j*zoom*2;
					row[j].y = i*zoom*2;
				}
				v_grid.push_back(row);
			}

			for (int i = 0; i < v_grid.size(); i++)       // loops through each row of vy
			{
				for (int j = 0; j < v_grid[i].size(); j++)
				{// loops through each element of each row
					if(v_grid[i][j].solid != 0)
					{
						SetPixelV(g,v_grid[i][j].x,v_grid[i][j].y,RGB(0,rand()%255,0));
					}
				}// prints the jth element of the ith row
			}
			return test;
		}

		void Cursor(HDC g, POINT p)
		{
						for( int x = 0; x < GetSystemMetrics(SM_CXSCREEN); x++ )
							SetPixelV(g, x, p.y,RGB(0,255,0));
							for( int y = 0; y < GetSystemMetrics(SM_CYSCREEN); y++ )
								SetPixelV(g, p.x, y,RGB(0,255,0));
		}

		void movement_left(HDC g, int moves[24])
		{
			char buffer[100];
			for( int x = 0; x < 24; x++ )
			{
				sprintf_s(buffer,"Player %d - moves left - %d\n", x, moves[x]);
				TextOut(g,GetSystemMetrics(SM_CXSCREEN)-200,250+x*15,buffer,strlen(buffer));
				//for( int x = 0; x < 24; x++ )
					for( int y = 0; y < (moves[x]*10); y++ )
							SetPixelV(g, 400 + x, y,RGB(0,255,0));
			}
		}

		void ball_location(HDC g, int location)
		{
			char buffer[100];
			for( int x = 0; x < 2; x++ )
			{
			sprintf_s(buffer,"Location %d\n", location);
			TextOut(g,GetSystemMetrics(SM_CXSCREEN)-300,450,buffer,strlen(buffer));
			}
		}

		void status(HDC g, string text)
		{
				list<string>::const_iterator cii;

				int temp[5] = {0};
		if(text != "")
		{
			SS.push_front(text);
			temp[SS.size()] = rand()%100;
		}
	int rak = 0;
		for(cii=SS.begin(); cii!=SS.end(); cii++)
   {
			rak++;
		 char buffer[100];
		 string test;
		 test = *cii;
		 sprintf_s(buffer,"Location: %s",test);
		 TextOut(g,GetSystemMetrics(SM_CXSCREEN)-400,450+(5*30),test.c_str(),strlen(test.c_str()));
		 sprintf_s(buffer,"Location: %d",temp[rak]);
		 TextOut(g,GetSystemMetrics(SM_CXSCREEN)-400,250+(5*30),buffer,strlen(buffer));
		 //Sleep(10);

   }
	 if(SS.size() > 5)
		 SS.pop_back();
	}

		void Raster_Line(HDC g, double x1, double y1, double x2, double y2)
		{
			long i,sdx,sdy,dxabs,dyabs,x,y,px,py;
			long dx,dy;
			dx=x2-x1; /* the horizontal distance of the line */
			dy=y2-y1; /* the vertical distance of the line */
			dxabs=abs(dx);
			dyabs=abs(dy);
			sdx=sgn(dx);
			sdy=sgn(dy);
			x=dyabs>>1;
			y=dxabs>>1;
			px=x1;py=y1; 
			if (dxabs>=dyabs) /* the line is more horizontal than vertical */
			{
				for(i=0;i<dxabs;i++)
				{
					y+=dyabs;
					if (y>=dxabs)
					{
						y-=dxabs;py+=sdy;
				}
				px+=sdx;
				SetPixel(g,px,py,RGB(255,0,0));
				//plot_pixel(px,py,color);
			}
		}
		else /* the line is more vertical than horizontal */
		{
			for(i=0;i<dyabs;i++)
			{
				x+=dxabs;
				if (x>=dyabs)
				{
					x-=dyabs;px+=sdx;
				}
				py+=sdy;
				SetPixel(g,px,py,RGB(255,0,0));//plot_pixel(px,py,color);
			}
		} 
		}

		void lineCircle(HDC g,int x1, int y1, int radius)
		{
			//LARGE_INTEGER start, stop;
			//LARGE_INTEGER freq;
			//QueryPerformanceFrequency(&freq);
			//QueryPerformanceCounter(&start);

			double startx = x1 + radius * cos(PI*2);
			double starty = y1 + radius * sin(PI*2);
			double px = x1 + radius * cos(PI*2);
			double py = y1 + radius * sin(PI*2);
			for (float Angle = 0.0f; Angle <= PI*2; Angle += 0.1f)
			{
				double x = x1 + radius * cos(Angle);
				double y = y1 + radius * sin(Angle);
				//use x and y to set your vertices
				Raster_Line(g, px,py,x,y);

				px = x;
				py = y;
			}
			Raster_Line(g, px,py,startx,starty);
		}

		int sgn (long a) 
		{
			if (a > 0) return +1;
			else if (a < 0) return -1;
			else return 0;
		}

		void Raster_Line3D(HDC g, Point start, Point end)
		{
			int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

			dx=end.getX()-start.getX(); /* the horizontal distance of the line */
			dy=end.getY()-start.getY(); /* the vertical distance of the line */
			dxabs=abs(dx);
			dyabs=abs(dy);
			sdx=sgn(dx);
			sdy=sgn(dy);
			x=dyabs>>1;
			y=dxabs>>1;
			px=start.getX();
			py=start.getY();

			if (dxabs>=dyabs) /* the line is more horizontal than vertical */
			{
			for(i=0;i<dxabs;i++)
			{
			y+=dyabs;
			if (y>=dxabs)
			{
			y-=dxabs;
			py+=sdy;
			}
			px+=sdx;
			SetPixel(g,px,py,RGB(255,0,0));
			}
			}
			else /* the line is more vertical than horizontal */
			{
			for(i=0;i<dyabs;i++)
			{
			x+=dxabs;
			if (x>=dyabs)
			{
			x-=dyabs;
			px+=sdx;
			}
			py+=sdy;
			SetPixel(g,px,py,RGB(255,0,0));

			}
		}
		}

		Point3D projection(Point3D vertex)
		{
			float cameraviewx = 0;
			float cameraviewy = 0;
			float cameraviewz = 30;
			//float dir = -1;
			//float speed = 20;
			float focallength = 300.0;
			float scaleration = focallength / (focallength + vertex.getZ() - cameraviewz);
			float xp = (vertex.getX() - cameraviewx) * scaleration;
			float yp = (vertex.getY() - cameraviewy) * scaleration;
			Point3D temp(xp,yp,vertex.getZ());
			return temp;
		}
		void Scatter()
		{
		}

		void player(HDC g, int x, int y)
		{
			int x_size = 16;
			int y_size = 16;
			float zoom = 10.0;
			std::vector< vector<grid_node> > v_grid;
			vector<grid_node> row(x_size);

			for( int i = 0; i < y_size; i++ )
			{
				for(int j = 0; j < row.size(); j++)
				{
					row[j].name = "Nimbus";
					row[j].solid = 1;
					row[j].x = 	x;
					row[j].y = y;
				}
				v_grid.push_back(row);
			}

				for (int i = 0; i < v_grid.size(); i++)       // loops through each row of vy
				{
					for (int j = 0; j < v_grid[i].size(); j++)
					{// loops through each element of each row
						if(v_grid[i][j].solid == 1)
						{
							SetRect(&box,v_grid[i][j].x-zoom,v_grid[i][j].y-zoom,v_grid[i][j].x+zoom,v_grid[i][j].y+zoom);
							FillRect(g,&box,(HBRUSH)GetStockObject(GRAY_BRUSH));
							SetPixelV(g,v_grid[i][j].x,v_grid[i][j].y,RGB(0,rand()%255,0));
						}
						test[i+j] = box;
					}// prints the jth element of the ith row
				}
				if(x != -1)
				SetRect(&active_item,x-10,y-10,x+10,y+10);
			FillRect(g,&active_item,(HBRUSH)GetStockObject(GRAY_BRUSH));
		}

    ~Derived()
    {
        cout<<"Derived class destructor"<<endl;
    }
};

class Weather : virtual public Base
{
private:
	int _weather_value;
	string _weather_condition;
	RECT *re;
public:
    Weather()
    {
				_weather_value = rand()%12 + 2;
				_weather_condition = "Not set\n";
        cout<<"Weather class constructor"<<endl;
    }

		string print() 
		{
			if(_weather_value == 2)
			{
				_weather_condition = "Sweltering Heat\n";
			}
			else
				if(_weather_value == 3)
				{
					_weather_condition = "Very sunny\n";
				}
				else
					if(_weather_value > 3)
					{
						_weather_condition = "Nice\n";
					}
					else
						if(_weather_value == 11)
						{
							_weather_condition = " Pouring rain\n";
						}
						else
							if(_weather_value == 12)
							{
								_weather_condition = "Blizzard\n";
							}
							else
								if( _weather_value > 12 )
								{
									_weather_condition = "Weather error\n";
								}

			return _weather_condition;
		}

		int average(int turns)
		{
			return _weather_value;
		}

		HBITMAP Image()
		{
			CBitmap* Bitmap;
			Bitmap = new CBitmap();
			return Bitmap->Load("pics/lightning.bmp");
		}

		RECT *Grid(HDC g,int x_size, int y_size)
		{
			return re;
		}

		// Issues: Cant keep up with mouse movement
		void Cursor(HDC g, POINT p)
		{
						for( int x = 0; x < GetSystemMetrics(SM_CXSCREEN); x++ )
							SetPixelV(g, x, p.y,RGB(0,255,0));
							for( int y = 0; y < GetSystemMetrics(SM_CYSCREEN); y++ )
								SetPixelV(g, p.x, y,RGB(0,255,0));
		}

		void movement_left(HDC g, int moves[24])
		{
		}

		void ball_location(HDC g, int location)
		{
			char buffer[100];
			sprintf_s(buffer,"Location %d\n", location);
			TextOut(g,GetSystemMetrics(SM_CXSCREEN)-300,450,buffer,strlen(buffer));
		}

		void Raster_Line(HDC g, double x1, double y1, double x2, double y2)
		{
		}

		void lineCircle(HDC g, int x1, int y1, int radius)
		{
			//LARGE_INTEGER start, stop;
			//LARGE_INTEGER freq;
			//QueryPerformanceFrequency(&freq);
			//QueryPerformanceCounter(&start);

			double startx = x1 + radius * cos(PI*2);
			double starty = y1 + radius * sin(PI*2);
			float px = x1 + radius * cos(PI*2);
			float py = y1 + radius * sin(PI*2);
			for (float Angle = 0.0f; Angle <= PI*2; Angle += 0.1f)
			{
				float x = x1 + radius * cos(Angle);
				float y = y1 + radius * sin(Angle);
				//use x and y to set your vertices
				Raster_Line(g, px,py,x,y);

				px = x;
				py = y;
			}
			Raster_Line(g, px,py,startx,starty);
		}

		int sgn (long a) 
		{
			if (a > 0) return +1;
			else if (a < 0) return -1;
			else return 0;
		}

		void Raster_Line3D(HDC g, Point start, Point stop)
		{
		}

		Point3D projection(Point3D vertex)
		{
			Point3D temp(0,0,0);
			return temp;
		}
		
		void status(HDC g, string text)
		{
		}

		void Scatter()
		{
		}

		void player(HDC g, int x, int y)
		{
		}
    ~Weather()
    {
        cout<<"Weather class destructor"<<endl;
    }
};