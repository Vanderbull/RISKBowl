#ifndef TOLLE_CSCATTER_H
#define TOLLE_CSCATTER_H
#include "Tolle_CTemplates.h"

//class CTemplates;

class CScatter : public CTemplates
{
private:

protected:

	Coord x_org;
	Coord y_org;
	int rand_num;

public:

	CScatter::CScatter();
	
	int length()
	{
	}
	
	~CScatter() {};
};
#endif