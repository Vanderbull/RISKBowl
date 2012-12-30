#include <iostream>
using namespace std;
#include "enums.h"
#include "Tolle_CTemplates.h"

void CTemplates::Throw_in()
{
	int rand_num = rand()%Sideline_Result::Down;

	if(rand_num < Sideline_Result::Down)
	{
	};
	if(rand_num < Sideline_Result::Straight)
	{
	};
	if(rand_num < Sideline_Result::Up);
	// if upward diagonally then check length first
	// after that add 1 to x and y that amount of times
	// and the reversed if the direction shows downward angle
}
void CTemplates::Scatter()
{
}
int CTemplates::direction()
{
	// this one should be overwritten by a specific function
	// for scatter and one for throw in.
	return 0;
}
int CTemplates::length()
{
	// primarly for the sideline part
	// as the scatter only will be moving one square
	// must with the call to this function check
	return 1;
}