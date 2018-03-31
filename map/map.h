#include "screen.h"

#define M_PATH '#'
#define M_VWALL '|'
#define M_HWALL '-'
#define M_FLOOR '.'
#define M_PATH '#'

// typedef struct{
//     uint8_t x;
//     uint8_t y;
//     uint16_t background;
//     uint16_t foreground;
//     char display;
    
// } Tile;

typedef struct {
    uint8_t x;
    uint8_t y;
    char standingOn;
    char display;
    uint16_t colour;
} MOB;

// MOB Player;
// Player.display='@';
// Player.standingOn='.';
// Player.colour = RED;

enum direction {north, south, east, west};

void move(MOB* m, enum direction dir);

void movePlayer(enum direction dir);

void setPlayer(MOB *m);

void makeRoom(ScreenBlock *sc);

void makeRoom(uint8_t width, uint8_t height, uint8_t xpos,
    uint8_t ypos);

void drawPath(uint8_t x1, uint8_t y1, uint8_t x2,
 uint8_t y2);