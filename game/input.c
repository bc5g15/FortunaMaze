#include "input.h"

// orientation currentOrientation;

uint8_t buttons[5];

void set_input_orientation(orientation o)
{
    uint8_t switches[] = {_BV(SWW), _BV(SWN),
         _BV(SWE), _BV(SWS)};
    int start = 0;
    // currentOrientation = o;
    if(o==West) {start=1;}
    else if(o==North) {start = 2;}
    else if(o==East) {start = 3;}

    int i;
    for(i=0;i<4;i++)
    {
        buttons[i] = switches[(start +i) %4];
    }
    buttons[4] = _BV(SWC);
}

/*
Check to make sure this is correct
*/
uint8_t button_pressed(button b)
{
    return get_switch_press(buttons[b]);
}
