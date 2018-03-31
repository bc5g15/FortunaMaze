#include "setup.h"

void draw_tutorial_map()
{
    char mid[7*7];
	ScreenBlock sc;
	sc.width = 7;
	sc.height = 7;
	sc.blockval = mid;
	makeRoom(&sc);
	displayBlock(&sc, 3, 3);
    displayBlock(&sc, 12, 4);

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
    player->x = 5;
    player->y = 5;
    player->standingOn = '.';
    player->display = '@';
    player->colour = RED;

    setPlayer(player);
}