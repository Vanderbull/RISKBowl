typedef struct
{
	char type;
	int color;
	bool solid;
} grid_node_t2;

typedef struct griden2
{
	int solid;
	string name;
	float x;
	float y;
	HBITMAP picture;
	grid_node_t2 testing;
	T_Player someone;
} grid_node2;

typedef struct
{
	grid_node_t2 *grid_node2[256][256];
	int board[256][256];
	int height;
	int width;
} grid_t2;