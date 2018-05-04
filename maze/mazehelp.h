/***
 * 
 * This header file defines some helpful methods for all maze generation algorithms
 * 
 */

#ifndef MAZE_HELPER
#define MAZE_HELPER

#include "screen.h"
#include <stdlib.h>
#include <util/delay.h>

#define DIV_X 2
#define DIV_Y 2
#define INIT_X 1
#define INIT_Y 1

/**
 * Black out the entire screen with wall characters
 */
void fill();


/**
 * draw a character that is recognised as a floor
 */
void drawFloor(uint8_t x, uint8_t y);

#endif