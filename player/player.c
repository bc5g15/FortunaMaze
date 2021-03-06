#include <stdio.h>
#include "player.h"

void check_tile_stand();

PLAYER p;
int standing_on_exit = 0;

void p_move(enum direction dir)
{
    move(&(p.m), dir);
    check_tile_stand();
    display_status();
}

void start_player(uint8_t x, uint8_t y)
{
    //Set up a player with the default
    //Image set
    p.m.x = x;
    p.m.y = y;
    p.m.standingOn = '.';
    p.m.display = '@';
    p.m.colour = GREEN;
    p.gold = 0;
    // p.health = 30;
    standing_on_exit = 0;
    drawMOB(&p.m);
}

void display_status()
{
    char strout[SCRN_MAX_WIDTH];
    snprintf(strout, sizeof(strout), "GOLD: %04i", p.gold);
    display_bottom(strout);
}

void check_tile_stand()
{
    switch(p.m.standingOn)
    {
        case TREASURE :
            p.gold++;
            p.m.standingOn = '.';
            break;
        case BIG_TREASURE :
            p.gold+= BIG_TREASURE_VALUE;
            p.m.standingOn = '.';
            break;
        case EXIT :
            standing_on_exit = 1;
            p.m.standingOn = '>';
            break;
        default :
            break;
    }
}

int is_on_exit()
{
    return standing_on_exit;
}

void set_player_pos(uint8_t x, uint8_t y)
{
    p.m.x = x;
    p.m.y = y;
    standing_on_exit = 0;
    drawMOB(&p.m);
    
}

void redraw()
{
    standing_on_exit=0;
    drawMOB(&p.m);
}

uint16_t get_gold()
{
    return p.gold;
}