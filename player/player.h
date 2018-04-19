#include "map.h"

/*
This file will include a special struct
that adds additional player data to the mob
struct
*/

typedef struct {
 MOB m;
 //uint8_t health;
 uint32_t gold;
} PLAYER;

// void p_moveto(char c);
// void p_stand(char c);

void p_move(enum direction dir);

void start_player(uint8_t x, uint8_t y);

void display_status();

//I hate this method, but 
//I'm not sure how to resolve the dependancy conflict
int is_on_exit();

void set_player_pos(uint8_t x, uint8_t y);

void redraw();