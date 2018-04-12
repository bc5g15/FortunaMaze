#include "lcd.h"

#define FONTWIDTH  6
#define FONTHEIGHT 8

#define SCRN_RESERVED_ROWS 2
#define SCRN_SHIFT 1

#define SCRN_MAX_WIDTH (int)(LCDHEIGHT/FONTWIDTH)
#define SCRN_MAX_HEIGHT (int)(LCDWIDTH/FONTHEIGHT) - SCRN_RESERVED_ROWS

typedef struct{
    uint8_t width;
    uint8_t height;
    char *blockval;
} ScreenBlock;

/*
By default
Unless maybe I should use a vertical view?
Max width = 53
Max Height = 
*/

char getScreenChar(uint8_t x, uint8_t y);

/*
Relies on a custom method in the lcd
display library
*/
void setScreenChar (char c, uint8_t x, uint8_t y);

void swapTile(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

void displayBlock(ScreenBlock *sc, uint8_t x, uint8_t y);

void drawWithColour(char c, uint8_t x, uint8_t y,
    uint16_t foreground, uint16_t background);

void display_top(char *str);
void display_bottom(char *str);

//Block commands

void setBlockRow(char* row, ScreenBlock* b, int pos);

