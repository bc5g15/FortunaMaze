/***
 * 
 * This header provides some helpful methods.
 * Designed to allow the game to be easily setup from within a main loop
 * 
 */


//#include "map.h"
#include "player.h"
#include "bintree.h"
#include "rbacktrack.h"
#include "input.h"
#include <stdlib.h>

#define MIN_TREASURE 5

typedef enum {EASY, HARD} difficulty;

void setup_set_orientation(orientation o);

void draw_tutorial_map();

void setup_tutorial_player();

void draw_maze(int i);

void setup_maze();

void add_treasure();

void add_exit();

void replace_player();

void set_difficulty(difficulty d);