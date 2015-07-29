#include <vector>
#include <math.h>
#include <list>
#include <iostream>
#include <vector>
using namespace std;

class BaseLeague
{
public:

	std::string Name; // Name of the League ex. Circle League
	std::vector<int> Team; // Pointer to different teams in this league

	int AddTeam(int iTeam){ cout << "Adding " << iTeam << " to this league..." << endl; };
	int DropTeam(int iTeamPosition){ cout << "Removing " << iTeamPosition << " from this league..." << endl; };
	int RenderLeague() { cout << "Rendering this league on screen..." << endl; };
	int GetTeamName() { cout << "Asking team class for its name..." << endl; };

	BaseLeague()
	{
		Team.clear();
		cout << "Base League class constructor initialized..." << endl;
	}

	virtual ~BaseLeague()
	{
        	cout << "Base League class destroyed..." << endl;
	}
};
