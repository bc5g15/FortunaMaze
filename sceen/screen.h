/**
 * 
 * The Screen files provide an may of interaction with the screen as an array of characters
 * 
 */

#ifndef SCREEN_DEF
#define SCREEN_DEF 1

#include "lcd.h"

#define FONTWIDTH  6
#define FONTHEIGHT 8

#define SCRN_RESERVED_ROWS 2
#define SCRN_SHIFT 1

#define SCRN_MAX_WIDTH (int)(LCDWIDTH/FONTWIDTH)
#define SCRN_MAX_HEIGHT ((int)((LCDHEIGHT/FONTHEIGHT) - SCRN_RESERVED_ROWS))

typedef struct{
    uint8_t width;
    uint8_t height;
    const char *blockval;
} ScreenBlock;

/*
With a vertical view
Max width = 40
Max Height = 40
*/

/**
 * Gets the currently logged character at the given position
 */
char getScreenChar(uint8_t x, uint8_t y);

/**
*Sets the character at a given screen position
*/
void setScreenChar(char c, uint8_t x, uint8_t y);

/**
 * Checking that this method is unnecessary
 */
// void swapTile(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

/**
 * Display a static block of text at a position.
 * This method is used to draw the Game Start screen
 * and Game Over screen
 */
void displayBlock(ScreenBlock *sc, uint8_t x, uint8_t y);

/**
 * Set a character at a specified position with a 
 * speciied foreground and background
 */
void drawWithColour(char c, uint8_t x, uint8_t y,
    uint16_t foreground, uint16_t background);


/**
 * Helper methods to display a character string
 * at the top or bottom of the screen.
 */
void display_top(char *str);
void display_bottom(char *str);

#endif