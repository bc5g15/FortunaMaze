/* COMP2215 Task 5---SKELETON */

#include "os.h"
#include <avr/pgmspace.h>
#include "myStrings.h"
#define MAXLEN  53
#define MAXROWS 25

#define TIMER_START 60

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
void draw_game_over();

int check_pause();

void get_tail(int, const char*);

FIL File;                   /* FAT File */

MOB player;

int timer_active = 0;
int timer_value = TIMER_START;
int timer_reset = 0;
int maze_depth = 1;


int position = 0;

int rposition = 0;
int active = 0;

int lhand = 0;


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
    //os_add_task( collect_delta,   500, 1);
	os_add_task( manage_timer,    1000, 0);
	os_add_task( game_loop,		   100, 1);
    //os_add_task( check_switches,  100, 1);
	// os_add_task( show_pattern_one, 2000, 1);
	// os_add_task( show_pattern_two, 3000, 1);

	
	os_led_brightness(0);

    sei();
    for(;;){}

}

/*
TODO
Fix treasure generation locations. *
Add higher value treasure * 
Refactor timer code maybe
Add additional maze generation types
Add pause button * 
Ensure exits can't go in the same place twice *
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
				return 3;
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
			timer_active = 1;
			state++;
			break;
		case 5 :
		//Handling input
			input_handler();
			k = check_pause();
			if(k==1)
			{
				timer_active = 0;
				return 6;
			}
			if(timer_value<=0)
			{
				timer_active = 0;
				return 7;
			}
			break;
		case 6 : 
		//Paused
			k=check_pause();
			if(k==1)
			{
				timer_active = 1;
				return 5;
			}
			display_top("PAUSED");
			break;
		case 7 :
		//Game Over screen
			draw_game_over();
			timer_reset = 1;
			return 3;

	}

	return state;
}

int check_pause()
{
	if(button_pressed(Center))
	{
		return 1;
	}
	return 0;
}

int manage_timer(int state)
{
	switch(state)
	{
		case 0:
		 os_led_brightness(200);
		 if(timer_active)
		 {
			 os_led_brightness(0);
			 timer_value = TIMER_START;
			 return 1;
		 }
		 break;
		case 1:
		 if(timer_active)
		 {
			timer_value--;
			char myout[40];
			snprintf(myout, sizeof(myout), "Depth: %3d   Time: %03d", maze_depth, timer_value);
			display_top(myout);
		 }
		//  if(!timer_active)
		//  {
		// 	 timer_value = TIMER_START;
		// 	return 0;
		//  }
		 if(timer_reset)
		 {
			 timer_value = TIMER_START;
			 timer_reset = 0;
			 return 0;
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
	int i;
	display_char_xy(' ', 5, 80);
	for(i=1; i<37; i++)
		display_char(' ');
	displayBlock(&sc, 1, 10);
	display_char_xy(' ', 5, 172);
	for(i=1; i<37; i++)
		display_char(' ');
}

void draw_game_over()
{

	int i;
	display_char_xy('*', 6, 32);
	for(i=1; i<21; i++)
	{
		display_char('*');
	}
	display_string_xy("*   GAME   OVER    *", 6, 40);
	display_char_xy('*', 6, 48);
	for(i=1; i<21; i++)
	{
		display_char('*');
	}
	char myout[40];
	snprintf(myout, sizeof(myout),
		"* Reached Depth: %3d*", maze_depth);
	display_string_xy(myout, 6, 56);
	snprintf(myout, sizeof(myout),
	 	"*Gold Collected: %3d*", get_gold());
	display_string_xy(myout, 6, 64);
	display_char_xy('*', 6, 72);
	for(i=1; i<21; i++)
	{
		display_char('*');
	}
	display_string_xy("* Press Any Button  *", 6, 80);
	display_string_xy("*    To Restart     *", 6, 88);
	display_char_xy('*', 6, 96);
	for(i=1; i<21; i++)
	{
		display_char('*');
	}

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
	if(button_pressed(Down))
	{
		p_move(south);
	}
	else if(button_held(Down))
	{
		// movePlayer(south);
		// display_top("SOUTH");
		// display_bottom("SOUTH");
		p_move(south);
	}
	if(button_pressed(Up))
	{
		p_move(north);
	}
	else if(button_held(Up))
	{
		// movePlayer(north);
		// display_top("NORTH");
		// display_bottom("NORTH");
		p_move(north);
	}
	if(button_pressed(Left))
	{
		p_move(west);
	}
	else if(button_held(Left))
	{
		// movePlayer(west);
		// display_top("WEST");
		// display_bottom("WEST");
		p_move(west);
	}
	if(button_pressed(Right))
	{
		p_move(east);
	}
	else if(button_held(Right))
	{
		// movePlayer(east);
		// display_top("EAST");
		// display_bottom("EAST");
		p_move(east);

	}

	if(is_on_exit())
	{
		maze_depth++;
		timer_value += 10 +(rand()% 15);
		setup_maze();
		add_treasure();

		random_move_player();
		add_exit();
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
