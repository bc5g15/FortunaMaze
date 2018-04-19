#include "setup.h"

int mazeNum = 0;

void setup_set_orientation(orientation o)
{
    set_orientation(o);
    set_input_orientation(o);
    clear_screen();
    display_top("Hello");
}

void draw_tutorial_map()
{
    // char mid[7*7];
	// ScreenBlock sc;
	// sc.width = 7;
	// sc.height = 7;
	// sc.blockval = mid;
	// makeRoom(&sc);
	// displayBlock(&sc, 3, 3);
    // displayBlock(&sc, 12, 4);

    makeRoom(9,7,0,0);
    makeRoom(5, 8, 12, 4);
    drawPath(9,5,12,5);

    addTreasure(8,8);
    addTreasure(15, 7);

    // char mid2[6*8];
    // ScreenBlock sc2;
    // sc.width = 6;
    // sc.height = 8;
    // sc.blockval = mid2;
    // makeRoom(&sc2);
    //displayBlock(&sc2, 13, 4);
}

void setup_tutorial_player()
{
    // player->x = 5;
    // player->y = 5;
    // player->standingOn = '.';
    // player->display = '@';
    // player->colour = RED;

    // setPlayer(player);
    start_player(1,1);
}

void draw_maze(int i)
{
    makeMaze_binaryTree((i)%4);
}

void setup_maze()
{
    makeMaze_binaryTree((mazeNum++)%4);
}

void add_treasure()
{
    int t;
    for(t=0; t<5; t++)
    {
        int x = (rand() % (SCRN_MAX_HEIGHT/2)) * 2;
        int y = (rand() % (SCRN_MAX_WIDTH/2)) * 2;

        addTreasure(x, y);
    }
}

void add_exit()
{
    int x = (rand() % (SCRN_MAX_HEIGHT/2)) * 2;
    int y = (rand() % (SCRN_MAX_WIDTH/2)) * 2;

    addExit(x, y);
}

void random_move_player()
{
    // int x = ((rand() % (SCRN_MAX_HEIGHT/2)) * 2) + INIT_X;
    // int y = ((rand() % (SCRN_MAX_WIDTH/2)) * 2) + INIT_Y;

    // set_player_pos(x, y);
    redraw();
}