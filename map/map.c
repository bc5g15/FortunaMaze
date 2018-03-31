#include "map.h"

MOB player;

void shiftMob(MOB*, uint8_t, uint8_t);
uint8_t getMin(uint8_t, uint8_t);
uint8_t getMax(uint8_t, uint8_t);

void movePlayer(enum direction dir)
{
    move(&player, dir);
}

void move(MOB *m, enum direction dir)
{
    switch(dir)
    {
        case north :
            shiftMob(m, m->x, m->y-1);
            break;
        case east :
            shiftMob(m, m->x+1, m->y);
            break;
        case south :
            shiftMob(m, m->x, m->y+1);
            break;
        case west :
            shiftMob(m, m->x-1, m->y);
    }
}

void shiftMob(MOB *m, uint8_t x, uint8_t y)
{
    char next = getScreenChar(x,y);
    if(next=='.')
    {
        char c = m->standingOn;
        setScreenChar(c, m->x, m->y);
        drawWithColour(m->display, x, y,
            m->colour, BLACK);
        m->x = x;
        m->y = y;
    }
}

void setPlayer(MOB *m)
{
    player = *m;
    drawWithColour(m->display, m->x, m->y,
    m->colour, BLACK);
}

void makeRoom(ScreenBlock *sc)
{
    int i,j;

    //Top row
    for(j=0;j<sc->width;j++)
    {
        sc->blockval[j] = M_HWALL;
    }

    for(i=1; i<sc->height-1;i++)
    {
        int midstart = i*sc->width;
        sc->blockval[midstart] = M_VWALL;
        for(j=1;j<sc->width-1;j++)
        {
            sc->blockval[midstart + j] = M_FLOOR;
        }
        sc->blockval[midstart+j] = M_VWALL;
    }

    //Bottom row
    for(j=0;j<sc->width;j++)
    {
        sc->blockval[j+(i*sc->width)] = M_HWALL;
    }
}

void makeRoom(uint8_t width, uint8_t height, uint8_t xpos,
    uint8_t ypos)
{
    uint8_t i j;

    //Top row
    for(j=0; j<width; j++)
    {
        setScreenChar(M_HWALL, xpos+j, ypos);
    }

    //Midsection
    for(i=1; i<height-1; i++)
    {
        setScreenChar(M_VWALL, xpos, ypos+i)
        for(j=1;j<width-1;j++)
        {
            setScreenChar(M_FLOOR, xpos+j, ypos+i);
        }
        setScreenChar(M_VWALL, xpos+j, ypos+i);
    }

    //Bottom Row
    for(j=0; j<width; j++)
    {
        setScreenChar(M_HWALL, xpos+j, ypos+i);
    }
}

void drawPath(uint8_t x1, uint8_t y1, uint8_t x2,
    uint8_t y2)
{
    //Simply draw horizontally then vertically
    uint8_t start = getMin(x1,x2);
    uint8_t end = getMax(x1,x2);

    //May need to shuffle around the y1,x2 thing;
    uint8_t i;
    for(i=start; i<=end; i++)
    {
        setScreenChar(M_PATH, i, y1);
    }

    start = getMin(y1, y2);
    end = getMax(y1, y2);
    for(i=start; i<=end; i++)
    {
        setScreenChar(M_PATH, x2, i);
    }
    
}

uint8_t getMin(uint8_t fst, uint8_t snd)
{
    if(fst<snd)
    {
        return fst;
    }
    else {return snd;}
}

uint8_t getMax(uint8_t fst, uint8_t snd)
{
    uint8_t output = fst>snd ? fst : snd;
    return output;
}