#include <vector>
#include <math.h>
#include <list>
#include <iostream>
#include <vector>
using namespace std;

class BasePlayer
{
public:

	std::string Name; // Name of the Player ex. Barik Farblast
	int Team;
	int Cost;
	int MA;
	int ST;
	int AG;
	int AV;

	int AddPlayer(int iTeam){ cout << "Adding " << iTeam << " to this league..." << endl; };
	int DropPlayer(int iTeamPosition){ cout << "Removing " << iTeamPosition << " from this league..." << endl; };
	int RenderPlayere() { cout << "Rendering this league on screen..." << endl; };
	int GetPlayerName() { cout << "Asking team class for its name..." << endl; };

    BasePlayer()
    {
		Team.clear();
        cout << "Base Player class constructor initialized..." << endl;
    }

	virtual ~BasePlayer()
    {
        cout << "Base Player class ended..." << endl;
    }

	//virtual string print() = 0; // pure virtual
};
