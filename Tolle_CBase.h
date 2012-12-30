#include <vector>
#include <math.h>
#include <list>
using namespace std;

#include "Tolle_CBitmap.h"
#include "Tolle_Player.h"
#include "Tolle_Grid.h"

typedef struct
{int x;
} bajs;
class Tolle_CBase
{
public:
	std::vector< vector<grid_node2> > v_grid;
  Tolle_CBase(){}
	virtual void Init( HDC g ) = 0;
	virtual void Grid(int x_amount, int y_size, float zoom, HBITMAP hbm) = 0;
	virtual void Draw() = 0;
	virtual void Check(grid_node2 *gn) = 0;
	virtual void active_node(grid_node2 *gn) = 0;
	virtual void SetBitmap( HBITMAP hbm, int x, int y) = 0;
	virtual void Print() = 0;
  virtual ~Tolle_CBase (){}
};

class Derived2 : virtual public Tolle_CBase
{
private:
	float _zoom;
	grid_node2 active;
	HDC CBase_HDC;
	vector<grid_node2> nodes;
	vector <grid_node2>::iterator Iter;


public:
    Derived2(){}

		void Init(HDC g)
		{
			CBase_HDC = g;
		}

		void Grid(int x_amount, int y_size, float zoom, HBITMAP hbm)
		{
			_zoom = zoom;
			v_grid.erase(v_grid.begin(), v_grid.end());
			nodes.resize(x_amount);

			for( int i = 0; i < y_size; i++ )
			{
				for(int j = 0; j < nodes.size(); j++)
				{
					nodes[j].name = "Nimbus";
					nodes[j].solid = rand()%2;
					nodes[j].x = 	j*_zoom;
					nodes[j].y = i*_zoom;
					nodes[j].picture = hbm;
					nodes[j].testing.color = 255;
					nodes[j].someone._st = 10;
				}
				v_grid.push_back(nodes);
			}
		}
		
		void Draw()
		{
			for (int i = 0; i < v_grid.size(); i++)       // loops through each row of v_grid
			{
				for (int j = 0; j < v_grid[i].size(); j++)
				{// loops through each element of each row
					if(v_grid[i][j].solid)
					{
						SetPixelV(CBase_HDC,v_grid[i][j].x,v_grid[i][j].y,RGB(0,255,0));
					}
				}// prints the jth element of the ith row
			}
		}

		void Check(grid_node2 *gn)
		{
			for (int i = 0; i < v_grid.size(); i++)       // loops through each row of v_grid
			{
				for (int j = 0; j < v_grid[i].size(); j++)
				{// loops through each element of each row
					if ( v_grid[i][j].solid == 1 )
					if ( gn->x <= v_grid[i][j].x+15 && gn->x >= v_grid[i][j].x-15)
					if ( gn->y <= v_grid[i][j].y+15 && gn->y >= v_grid[i][j].y-15)
					{
						SetPixelV(CBase_HDC,v_grid[i][j].x,v_grid[i][j].y,RGB(255,0,0));
						if ( i != 0 && i != v_grid.size()-1)
						{						
							if ( j != 0 && j != v_grid[i].size()-1 )
							{
								if ( v_grid[i-1][j].solid == 1 )
									SetPixelV(CBase_HDC,v_grid[i-1][j].x,v_grid[i-1][j].y,RGB(255,0,0));
								if ( v_grid[i+1][j].solid == 1 )
									SetPixelV(CBase_HDC,v_grid[i+1][j].x,v_grid[i+1][j].y,RGB(255,0,0));
								if ( v_grid[i+1][j-1].solid == 1 )
									SetPixelV(CBase_HDC,v_grid[i+1][j-1].x,v_grid[i+1][j-1].y,RGB(255,0,0));
								if ( v_grid[i][j-1].solid == 1 )
									SetPixelV(CBase_HDC,v_grid[i][j-1].x,v_grid[i][j-1].y,RGB(255,0,0));
								if ( v_grid[i-1][j-1].solid == 1 )
									SetPixelV(CBase_HDC,v_grid[i-1][j-1].x,v_grid[i-1][j-1].y,RGB(255,0,0));
								if ( v_grid[i][j+1].solid == 1 )
									SetPixelV(CBase_HDC,v_grid[i][j+1].x,v_grid[i][j+1].y,RGB(255,0,0));
								if ( v_grid[i-1][j+1].solid == 1 )
									SetPixelV(CBase_HDC,v_grid[i-1][j+1].x,v_grid[i-1][j+1].y,RGB(255,0,0));
								if ( v_grid[i+1][j+1].solid == 1 )
									SetPixelV(CBase_HDC,v_grid[i+1][j+1].x,v_grid[i+1][j+1].y,RGB(255,0,0));
							}
						}
					}
				}
			}
		}

		void active_node(grid_node2 *gn)
		{
		}
		void SetBitmap( HBITMAP hbm, int x, int y)
		{
			v_grid[x][y].picture = hbm;
		}

		void Print()
		{
			for( int temp = 0; temp < 24; temp++)
			{
				char buffer[100];
					sprintf_s(buffer,"%d has MOVED",temp);
					TextOut(CBase_HDC,600,200+(temp*20),buffer,strlen(buffer));
			}
		}
    ~Derived2()
    {
        cout<<"Derived2 class destructor"<<endl;
    }
};