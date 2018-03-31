
#include "name.h"

#define UPPERA (int)'A'
#define UPPERZ (int)'Z'
#define DIFF (UPPERZ-UPPERA)

CURSOR c;

int i_xpos;
int i_ypos;

int position;
int letter;
char name[9];

//Lets start by simply displaying the entire alphabet on the screen

void name_init(int x, int y)
{
    i_xpos = x;
    i_ypos = y;
    position = 0;
    name[0] = '\0';
}

int name_start(int state)
{
 //3 - Responding to user input
 return 1;
}

void simple_name()
{

    if(get_switch_press(_BV(SWW)) || get_switch_rpt(_BV(SWW)))
    {
        position--;
        position %= DIFF;
    }
}

void draw()
{
    
}

void show_screen()
{
 return;
}