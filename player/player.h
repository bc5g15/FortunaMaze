#include "map.h"

/*
This file will include a special struct
that adds additional player data to the mob
struct
*/

typedef struct {
 MOB m;
 uint8_t health;
 uint8_t gold;
} PLAYER;

// void p_moveto(char c);
// void p_stand(char c);

void p_move(enum direction dir);

void start_player(uint8_t x, uint8_t y);

void display_status();