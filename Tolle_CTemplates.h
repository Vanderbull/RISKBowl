#ifndef TOLLE_CTEMPLATES_H
#define TOLLE_CTEMPLATES_H

typedef double Coord;


class CTemplates
{
private:

protected:

	Coord x_org;
	Coord y_org;
	int rand_num;

public:

	CTemplates::CTemplates(Coord x, Coord y) :
			x_org(x), y_org(y), rand_num(0) {};
	
	virtual void Throw_in();
	virtual void Scatter();
	virtual int direction();
	virtual int length();

	~CTemplates() {};
};
#endif