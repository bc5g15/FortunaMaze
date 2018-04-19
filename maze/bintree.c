#include "bintree.h"

typedef struct {
    int width;
    int height;
    uint8_t x;
    uint8_t y;
} TileHolder;

void fill();

typedef enum {
    UP, DOWN, LEFT, RIGHT
} mydir;

void drawFloor(uint8_t, uint8_t);
void drawWall(uint8_t, uint8_t);
void drawTile(TileHolder *, mydir);
int valid(TileHolder *, mydir);

void makeMaze_binaryTree(int type)
{
    int width = SCRN_MAX_WIDTH;
    int height = SCRN_MAX_HEIGHT;

    // int startx = rand() % width;
    // int starty = rand() % height;
    mydir dirop[2];
    switch(type)
    {
        case 0:
            dirop[0] = UP;
            dirop[1] = LEFT;
            break;
        case 1:
            dirop[0] = UP;
            dirop[1] = RIGHT;
            break;
        case 2:
            dirop[0] = LEFT;
            dirop[1] = DOWN;
            break;
        case 3:
            dirop[0] = RIGHT;
            dirop[1] = DOWN;
    }
    
    TileHolder th;
    th.width = width;
    th.height = height;

    fill();

    int i, j;

    for(j=1; j<height-DIV_Y; j+=DIV_Y)
    {
        for(i=1; i<width-DIV_X; i+=DIV_X)
        {
            th.x = i;
            th.y = j;
            if(!valid(&th, dirop[0]) && !valid(&th, dirop[1]))
            {
                //drawFloor(i*DIV_X, j*DIV_Y);
            }
            else if(!valid(&th, dirop[0]))
            {
                drawTile(&th, dirop[1]);
            }
            else if(!valid(&th, dirop[1]))
            {
                drawTile(&th, dirop[0]);
            }
            else
            {
                int choice = rand() %2;
                drawTile(&th, dirop[choice]);
            }
            _delay_ms(10);
        }
    }
}

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

/*
TODO:
FIX THIS SO RIGHT AND DOWN
WORK CORRECTLY
*/
int valid(TileHolder *th, mydir m)
{
    int x = (th->x);
    int y = (th->y);

    switch(m)
    {
        case UP:
            return (y-INIT_Y);
        case DOWN:
            return (th->height-1) - (y+2);
        case LEFT:
            return (x-INIT_X);
        case RIGHT:
            return (th->width-1) - (x+2);
    }
    return 0;
}

void drawTile(TileHolder *th, mydir m)
{
    uint8_t x = (th->x);
    uint8_t y = (th->y);
    
    drawFloor(x, y);
    switch(m)
    {
        case UP:
            drawFloor(x, y-1);
            if(th->y>0)
            {
                drawFloor(x, y-2);
            }
            break;
        case DOWN:
            drawFloor(x, y+1);
            if(th->y<th->height-1)
            {
                drawFloor(x, y+2);
            }
            break;
        case RIGHT:
            drawFloor(x+1, y);
            if(th->x<th->width-1)
            {
                drawFloor(x+2, y);
            }
            break;
        case LEFT:
            drawFloor(x-1, y);
            if(th->x>0)
            {
                drawFloor(x-2, y);
            }
            break;
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