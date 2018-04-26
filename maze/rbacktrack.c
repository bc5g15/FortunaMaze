#include "rbacktrack.h"

//UNFINISHED

typedef enum {UP, DOWN, LEFT, RIGHT, NONE} mydir;

void carve_passages_from(uint8_t, uint8_t);
void get_random_dirs(mydir *);
int check_tile(uint8_t, uint8_t);
void draw_tile(uint8_t, uint8_t, mydir);
void draw_special(uint8_t, uint8_t);
mydir reverse(mydir d);

void makeMaze_rBackTrack()
{
    fill();
    // uint8_t x = ((rand() *2) % (SCRN_MAX_WIDTH-INIT_X)) + INIT_X;
    // uint8_t y = ((rand() *2) % (SCRN_MAX_HEIGHT-INIT_Y)) + INIT_Y;
    uint8_t x = 1;
    uint8_t y = 1;
    carve_passages_from(x, y);
}

void carve_passages_from(uint8_t x, uint8_t y)
{
   mydir custom[4];
   get_random_dirs(custom);
   int i;
   for(i=0;i<4;i++)
   {
       uint8_t newx = x;
       uint8_t newy = y;
       //DO THINGS HERE
       switch(custom[i])
       {
            case UP :
             newy-=DIV_Y;
             break;
            case DOWN :
             newy+=DIV_Y;
             break;
            case LEFT :
             newx -= DIV_X;
             break;
            case RIGHT :
             newx+=DIV_X;
             break;
            default :
             break;
       }
       if(check_tile(newx, newy))
       {
           draw_tile(newx, newy, reverse(custom[i]));
           draw_tile(x, y, custom[i]);
           carve_passages_from(newx, newy);
       }
       //_delay_ms(20);
   } 
}

mydir reverse(mydir d)
{
    switch(d)
    {
        case UP:
         return DOWN;
        case DOWN:
         return UP;
        case LEFT:
         return RIGHT;
        case RIGHT:
         return LEFT;
        default:
         return NONE;
    }
}

/*
Check this method, it might be a bit suspect
*/
int check_tile(uint8_t x, uint8_t y)
{
    if(x<INIT_X || y<INIT_Y || x>=(SCRN_MAX_WIDTH-INIT_X)
    || y>= ((SCRN_MAX_HEIGHT-INIT_X)) || getScreenChar(x, y)=='.')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


void get_random_dirs(mydir *dirs)
{
    mydir basic[4] = {UP, DOWN, LEFT, RIGHT};
    int i;
    for(i=0;i<4;i++)
    {
        int x = rand() % 4;
        if(basic[x]!=NONE)
        {
            dirs[i]=basic[x];
            basic[x] = NONE;
        }
    }
}

void draw_tile(uint8_t x, uint8_t y, mydir m)
{   
    drawFloor(x, y);
    switch(m)
    {
        case UP:
            drawFloor(x, y-1);
            if(y>INIT_Y)
            {
                // drawFloor(x, y-2);
            }
            break;
        case DOWN:
            drawFloor(x, y+1);
            if(y<INIT_Y)
            {
                // drawFloor(x, y+2);
            }
            break;
        case RIGHT:
            drawFloor(x+1, y);
            if(x<SCRN_MAX_WIDTH-INIT_X)
            {
                // drawFloor(x+2, y);
            }
            break;
        case LEFT:
            drawFloor(x-1, y);
            if(x>INIT_X)
            {
                // drawFloor(x-2, y);
            }
            break;
        default :
            break;
    }
}

void draw_special(uint8_t x, uint8_t y)
{
    setScreenChar(',', x, y);
}