#include "mazehelp.h"

void fill()
{
    int i, j;
    for(i=0; i<SCRN_MAX_HEIGHT; i++)
    {
        for(j=0; j<SCRN_MAX_WIDTH; j++)
        {
            drawWall(j, i);
        }
    }
}

void drawWall(uint8_t x, uint8_t y)
{
    drawWithColour(' ', x, y, BLACK, WHITE);
}

void drawFloor(uint8_t x, uint8_t y)
{
    setScreenChar('.', x,y);
}