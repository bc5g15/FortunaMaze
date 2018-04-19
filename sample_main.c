/* COMP2215 Task 5---SKELETON */

#include "os.h"
#include <avr/pgmspace.h>
#include "myStrings.h"
#define MAXLEN  53
#define MAXROWS 25

#define TIMER_START 300

#define RDEPTH 1000

int blink(int);
int update_dial(int);
int collect_delta(int);
int check_switches(int);
int freeRam(int);
int recurse(int);
int show_pattern_one(int);
int show_pattern_two(int);
int manage_timer(int);

int game_loop(int);
void input_handler();
void drawMap();
int pick_orientation();
int swap_or_start();
void draw_start_screen();

void get_tail(int, const char*);

FIL File;                   /* FAT File */

MOB player;

int timer_active = 0;
int timer_value = 300;


int position = 0;

int rposition = 0;
int active = 0;

int lhand = 0;

//Implement a cyclic array
//Can we make this its own method?

int recurse(int state)
{
	//A waste variable to eat the stack
	volatile int waste[10];
	rposition++;
	if(active && (rposition <RDEPTH))
	{
		recurse(state);
	}
	if(rposition>= RDEPTH)
	{
		display_string("Recurse Done\n");
		rposition = 0;
		freeRam(1);
	}
	return state;
}

void get_tail(int rows, const char* filename)
{
	
	int j = 0;
	char myring[rows][MAXLEN];
	f_mount(&FatFs, "", 0);
		if(f_open(&File, filename, FA_READ | FA_OPEN_EXISTING) == FR_OK)
		{
			//Read the last 25 lines of the file?
			//Is it possible to work backwards?
			//Gets will read line by line.

			//Blank out the original array, otherwise loads
			//of garbage data
			for (j=0; j<rows; j++)
			{
				myring[j][0] = '\0';
			}
			j=0;
			while(!f_eof(&File))
			{
				f_gets(myring[j++], MAXLEN, &File);
				j%=rows;
			}
			f_close(&File);

			display_string("Read File");
			int i;
			for(i=0;i<rows;i++)
			{
				display_string(myring[j++]);
				j%=rows;
			}
			display_string("End of File\n");

		}
		else
		{
			display_string("Can't open file!\n");
		}
}




void main(void) {
    os_init();

	//os_add_task( recurse, 		  100, 1);
	//os_add_task( freeRam, 		 1000, 1);
    //os_add_task( blink,            30, 1);
    os_add_task( collect_delta,   500, 1);
	os_add_task( game_loop,		  100, 1);
    //os_add_task( check_switches,  100, 1);
	// os_add_task( show_pattern_one, 2000, 1);
	// os_add_task( show_pattern_two, 3000, 1);

	
	os_led_brightness(0);

    sei();
    for(;;){}

}

/*
TODO
Add good opening screen - Maybe done?
Add game timer that enables the game
Add Game Over screen
*/
int game_loop(int state)
{
	int k;
	switch(state)
	{
		case 1 :
			setup_set_orientation(North);
			// display_string("Are you left or right handed?\n");
			// display_string("Press the appropriate (L/R) button\n");
			// draw_maze(0);
			state++;
			break;
		case 2 :
			draw_maze(0);
			// display_string_xy("READY?", 100, 100);
			// display_string_xy("Get to the exit before the time runs out!", 1, 108);
			// display_string_xy("Get as much treasure as you can!", 1, 116);
			// display_string_xy("Press the button to swap handedness", 1, 200);
			// display_string_xy("(Left/Right", 10, 210);
			// display_string_xy("Press one of the arrow keys to start!", 2, 220);
			// myret=pick_orientation();
			draw_start_screen();
			state++;
			break;
		case 3 :
			k = swap_or_start();
			if(k==1)
			{
				k=0;
				return 2;
			}
			if(k==2)
			{
				k=0;
				return 4;
			} else
			{
				state = 3;
			}
			break;
		case 4 :
		//Setting up
			//draw_tutorial_map();
			srand(1);
			setup_maze();
			add_treasure();
			add_exit();
			setup_tutorial_player();
			state++;
			break;
		case 5 :
		//Handling input
			input_handler();
			break;

	}

	return state;
}

int manage_timer(int state)
{
	switch(state)
	{
		case 0:
		 os_led_brightness(255);
		 break;
		case 1:
		 if(timer_active)
		 {
			 snprintf()
		 }
	}

	return state;
}

void draw_start_screen()
{
	PGM_P x = MAIN_MENU;
	ScreenBlock sc;
	sc.width = 37;
	sc.height = 11;
	sc.blockval = x;
	displayBlock(&sc, 1, 10);
}

int swap_or_start()
{
	if(get_switch_press(_BV(SWC)))
	{
		if(!lhand)
		{
			setup_set_orientation(South);
			lhand = 1;
			return 1;
		}
		else
		{
			setup_set_orientation(North);
			lhand = 0;
			return 1;
		}
	}

	if(button_pressed(Left) || button_pressed(Right) 
	 || button_pressed(Up) || button_pressed(Down))
	 {
		 return 2;
	 }

	return 0;
}

int pick_orientation()
{
	//Left handed
	if(get_switch_press(_BV(SWW)))
	{
		setup_set_orientation(South);
		return 1;
	}

	//Right handed
	if(get_switch_press(_BV(SWE)))
	{
		setup_set_orientation(North);
		return 1;
	}

	return 0;
}

void input_handler()
{
	//button_pressed(D)
	if(button_held(Down))
	{
		// movePlayer(south);
		// display_top("SOUTH");
		// display_bottom("SOUTH");
		p_move(south);
	}
	if(button_held(Up))
	{
		// movePlayer(north);
		// display_top("NORTH");
		// display_bottom("NORTH");
		p_move(north);
	}
	if(button_held(Left))
	{
		// movePlayer(west);
		// display_top("WEST");
		// display_bottom("WEST");
		p_move(west);
	}
	if(button_held(Right))
	{
		// movePlayer(east);
		// display_top("EAST");
		// display_bottom("EAST");
		p_move(east);

	}

	if(is_on_exit())
	{
		setup_maze();
		add_treasure();
		add_exit();
		random_move_player();
	}
}


int freeRam(int state)
{
	//Will this work?
	extern int __heap_start, *__brkval;
	volatile int v;
	int myfree = (int) &v - (__brkval == 0? 
		(int)&__heap_start 
		: (int) __brkval);	
	char strout[20];
	snprintf(strout, sizeof(strout), "RAM Left: %i", myfree);
	display_string_preserve_xy(strout, (uint16_t)0, (uint16_t)0);
	return state;
}



int collect_delta(int state) {
	position += os_enc_delta();
	return state;
}




int blink(int state) {
	static int light = 0;
	uint8_t level;

	if (light < -120) {
		state = 1;
	} else if (light > 254) {
		state = -20;
	}


	/* Compensate somewhat for nonlinear LED
           output and eye sensitivity:
        */
	if (state > 0) {
		if (light > 40) {
			state = 2;
		}
		if (light > 100) {
			state = 5;
		}
	} else {
		if (light < 180) {
			state = -10;
		}
		if (light < 30) {
			state = -5;
		}
	}
	light += state;

	if (light < 0) {
		level = 0;
	} else if (light > 255) {
		level = 255;
	} else {
		level = light;
	}

	os_led_brightness(level);
	return state;
}
