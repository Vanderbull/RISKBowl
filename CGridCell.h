#ifndef CGRIDCELL_H
#define CGRIDCELL_H

class CGridCell
{
private:



public:

	int mCellID;
    int PosX;
	int PosY;
    int mCellType;
	CGridCell *UP;
	CGridCell *DOWN;
	CGridCell *LEFT;
	CGridCell *RIGHT;

	CGridCell()
	{
		mCellID = 0;
		PosX = 0;
		PosY = 0;
		mCellType = 0;
		UP = 0;
		DOWN = 0;
		LEFT = 0;
		RIGHT = 0;
	};
	~CGridCell(){};
};
#endif