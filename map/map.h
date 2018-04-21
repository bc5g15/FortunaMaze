#ifndef MAP_DEF
#define MAP_DEF
#include "screen.h"
#include <stdlib.h>

#define M_PATH '#'
#define M_VWALL '|'
#define M_HWALL '-'
#define M_FLOOR '.'
#define M_BLOCK ' '
#define M_UP '>'

#define BIG_TREASURE '*'
#define BIG_TREASURE_FORE CYAN
#define BIG_TREASURE_BACK BLUE
#define BIG_TREASURE_VALUE 5
#define TREASURE '$'
#define EXIT '<'
#define EXIT_FORE RED
#define EXIT_BACK CYAN

// typedef struct{
//     uint8_t x;
//     uint8_t y;
//     uint16_t background;
//     uint16_t foreground;
//     char display;
    
typedef struct {
    uint8_t x;
    uint8_t y;
    char standingOn;
    char display;
    uint16_t colour;
} MOB;

// } Tile;

// MOB Player;
// Player.display='@';
// Player.standingOn='.';
// Player.colour = RED;

enum direction {north, south, east, west};


void move(MOB* m, enum direction dir);

// void movePlayer(enum direction dir);

// void setPlayer(MOB *m);

void drawMOB(MOB* m);

/*
In theory these shouldn't be necessary if I load from
a file, but these will be useful while I build things
from programs
*/

// void makeRoomOld(ScreenBlock *sc);

void makeRoom(uint8_t width, uint8_t height, uint8_t xpos,
    uint8_t ypos);

void drawPath(uint8_t x1, uint8_t y1, uint8_t x2,
 uint8_t y2);

 void addTreasure(uint8_t x, uint8_t y);

 void addBigTreasure(uint8_t x, uint8_t y);

 void addExit(uint8_t x, uint8_t y);

 #endif