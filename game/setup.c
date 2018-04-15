#include "setup.h"

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

    makeRoom(7,7,3,3);
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

void setup_tutorial_player(MOB * player)
{
    // player->x = 5;
    // player->y = 5;
    // player->standingOn = '.';
    // player->display = '@';
    // player->colour = RED;

    // setPlayer(player);
    start_player(5,5);
}