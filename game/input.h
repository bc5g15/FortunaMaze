//#include "ruota.h"
#include <stdint.h>
#include <avr/io.h>
#include "ruota.h"
#include "lcd.h"

typedef enum {Up, Right, Down, Left, Center} button;
// typedef enum{North, South, East, West} orientation;

uint8_t button_pressed(button b);

void set_input_orientation(orientation o);