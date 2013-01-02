#ifndef DEFINES_H
#define DEFINES_H

#include <array>

using namespace std;
// these where defined in graphics.cpp
//#pragma comment(lib,"psapi.lib")
//#pragma comment(lib,"odbc32.lib")
//#pragma comment(lib,"odbccp32.lib")
//#pragma comment(lib,"winmm.lib")
//#pragma comment(lib,"vfw32.lib")

#define PI 3.14



char buffer[100];
int x = 0;
int y = 0;
RECT defines_rect = {800,0,940,100};

enum {BLITZER,CATCHER,THROWER,LINEMAN,BLOCKER};
enum {AMAZON      ,CHAOS       ,CHAOS_DWARF,
	  DARK_ELF    ,DWARF,ELF   ,GOBLIN,
	  HALFLING    ,HIGH_ELF    ,HUMAN,
	  KHEMRI      ,LIZARDMAN   ,NECROMANTIC,
	  NORSE       ,NURGLE      ,OGRE,
	  ORC         ,SKAVEN      ,UNDEAD,
	  VAMPIRE     ,WOOD_ELF    ,NONE};
enum {LOGO = 1, TEAMLOGOS128,FIELD_BLIZZARD,CUBE,BUTTON,LIGHTING,ORCTEAM,DARKELFTEAM,DWARFTEAM,HIGHELFTEAM,HUMANTEAM,SKAVENTEAM,BOARD,SKAVEN_L,SKAVEN_SV,SKAVEN_T,SKAVENS,MENU_BACK,STARCHART = 20};

typedef struct data
{
	RECT box[255][255];
	HBRUSH tile_brush[255];
	int player_locations[24];
	int player_has_moved[24];
	int player_movement_left[24];
	int ball_location;
} data;

static int player_type[24] = {BLITZER,BLITZER,BLOCKER,BLOCKER,THROWER,THROWER,LINEMAN,LINEMAN,LINEMAN,LINEMAN,LINEMAN,LINEMAN, BLITZER,BLITZER,CATCHER,CATCHER,THROWER,THROWER,LINEMAN,LINEMAN,LINEMAN,LINEMAN,LINEMAN,LINEMAN};
#endif