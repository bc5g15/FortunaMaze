#include "screen.h"

/*
Now this works.
It may be worth creating some helper methods for the struct
*/

char screen[SCRN_MAX_HEIGHT][SCRN_MAX_WIDTH];

char getScreenChar(uint8_t x, uint8_t y)
{
    return screen[y][x];
}

void display_top(char *str)
{
    int i;
    for(i=0;(str[i])&&(i<SCRN_MAX_WIDTH);i++)
    {
        display_char_xy(str[i], (i*FONTWIDTH), 0);
    }
    for(;i<SCRN_MAX_WIDTH;i++)
    {
        display_char_xy(' ', (i*FONTWIDTH),0);
    }
}

void display_bottom(char *str)
{
    int i;
    for(i=0;(str[i])&&(i<SCRN_MAX_WIDTH);i++)
    {
        display_char_xy(str[i], (i*FONTWIDTH), 
            (display.height - FONTHEIGHT));
    }
    for(;i<SCRN_MAX_WIDTH;i++)
    {
        display_char_xy(' ', (i*FONTWIDTH),
            (display.height - FONTHEIGHT));
    }
}

void setScreenChar(char c, uint8_t x, uint8_t y)
{
    screen[y][x] = c;
    display_char_xy(c, (x*FONTWIDTH), ((y+SCRN_SHIFT)*FONTHEIGHT));
}

void swapTile(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    char c1 = getScreenChar(x1, y1);
    char c2 = getScreenChar(x2, y2);

    setScreenChar(c1, x2, y2);
    setScreenChar(c2, x1, y1);
}

void displayBlock(ScreenBlock *sc,
 uint8_t x, uint8_t y)
{
    // char strout[10];
    // snprintf(strout, sizeof(strout), "%d %d\n", sc->height, sc->width);
    // display_string(strout);
    int i, j;
    for(i=0; (i<(sc->height)) && (i<(SCRN_MAX_HEIGHT+y)); i++)
    {
        for(j=0; (j<sc->width) && (j<(SCRN_MAX_WIDTH+x)); j++)
        {
            setScreenChar(sc->blockval[j+(i*sc->width)], (j+x), (i+y));
        }
    }
}

void drawWithColour(char c, uint8_t x, uint8_t y,
    uint16_t foreground, uint16_t background)
{
    uint16_t oldf = display_get_foreground();
    uint16_t oldb = display_get_background();
    set_display_colour(foreground, background);
    setScreenChar(c, x, y);
    set_display_colour(oldf, oldb);
}

void setBlockRow(char* row, ScreenBlock* b, int pos)
{
    int i;
    int start = b->width * pos;
    for(i=0; i<(b->width);i++)
    {
        b->blockval[start+i] = row[i];
    }
}