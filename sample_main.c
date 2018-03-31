/* COMP2215 Task 5---SKELETON */

#include "os.h"
#define MAXLEN  53
#define MAXROWS 25

#define RDEPTH 1000

int blink(int);
int update_dial(int);
int collect_delta(int);
int check_switches(int);
int freeRam(int);
int recurse(int);
int show_pattern_one(int);
int show_pattern_two(int);

int game_loop(int);
void input_handler();
void drawMap();

void get_tail(int, const char*);

FIL File;                   /* FAT File */

MOB player;


int position = 0;

int rposition = 0;
int active = 0;

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
	os_add_task( freeRam, 		 1000, 1);
    //os_add_task( blink,            30, 1);
    os_add_task( collect_delta,   500, 1);
	os_add_task( game_loop,		  100, 1);
    //os_add_task( check_switches,  100, 1);
	// os_add_task( show_pattern_one, 2000, 1);
	// os_add_task( show_pattern_two, 3000, 1);

	
	

    sei();
    for(;;){}

}

int game_loop(int state)
{
	switch(state)
	{
		case 1 :
			draw_tutorial_map();
			state++;
			break;
		case 2 :
			setup_tutorial_player(&player);
			state++;
			break;
		case 3 :
			input_handler();
			break;

	}

	return state;
}

void input_handler()
{
	if(get_switch_press(_BV(SWS)))
	{
		movePlayer(south);
	}
	if(get_switch_press(_BV(SWN)))
	{
		movePlayer(north);
	}
	if(get_switch_press(_BV(SWW)))
	{
		movePlayer(west);
	}
	if(get_switch_press(_BV(SWE)))
	{
		movePlayer(east);
	}
}

void drawMap()
{
	char mid[7*7];
	ScreenBlock sc;
	sc.width = 7;
	sc.height = 7;
	sc.blockval = mid;
	makeRoom(&sc);
	displayBlock(&sc, 3, 3);
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

int show_pattern_one(int state)
{
	char mine[15];
	int i;
	for(i=0;i<15;i++)
	{
		mine[i] = 'B';
	}
	ScreenBlock sc;
	sc.width = 3;
	sc.height = 5;
	sc.blockval = mine;

	ScreenBlock *addr = &sc;
	setBlockRow("###", addr, 0);
	setBlockRow("#.#", addr, 1);
	setBlockRow("#.#", addr, 2);
	setBlockRow("#.#", addr, 3);
	setBlockRow("###", addr, 4);
	displayBlock(&sc, 6, 5);
	return state;
}

int show_pattern_two(int state)
{
	char mine[15];
	int i;
	for(i=0;i<15;i++)
	{
		mine[i] = 'A';
	}
	ScreenBlock sc;
	sc.width = 5;
	sc.height = 3;
	sc.blockval = mine;
	displayBlock(&sc, 5, 5);
	return state;
}


int collect_delta(int state) {
	position += os_enc_delta();
	return state;
}

int check_switches(int state) {

	if(get_switch_long(_BV(SWS)))
	{
		display_string("[L] South\n");
		printf("South Switch Long");
	}

	if(get_switch_long(_BV(SWN)))
	{
		display_string("[L] North\n");
		printf("North Switch Long");

	}

	if (get_switch_long(_BV(SWE))) {
		display_string("[L] East\n");
		printf("East Switch Long");
	}

	if(get_switch_long(_BV(SWW)))
	{
		display_string("[L] West\n");
		printf("Toggle recurse");
		active = ~active;
		if(active)
		{
			display_string("recursing\n");
		}
	}

	if (get_switch_press(_BV(SWN))) {
			display_string("North\n");
	}

	if (get_switch_press(_BV(SWE))) {
			display_string("East\n");
	}

	if (get_switch_press(_BV(SWS))) {
			display_string("South\n");
			//get_tail(25, "lines.txt");
	}

	if (get_switch_press(_BV(SWW))) {
			display_string("West\n");
	}

	if (get_switch_long(_BV(SWC))) {
		f_mount(&FatFs, "", 0);
		if (f_open(&File, "myfile.txt", FA_WRITE | FA_OPEN_ALWAYS) == FR_OK) {
			f_lseek(&File, f_size(&File));
			f_printf(&File, "Encoder position is: %d \r\n", position);
			f_close(&File);
			display_string("Wrote position\n");
		} else {
			display_string("Can't write file! \n");
		}

	}

	if (get_switch_short(_BV(SWC))) {
			display_string("[S] Centre\n");
	}

	if (get_switch_short(_BV(SWN))) {
		display_string("[S] North\n");
	}

	if (get_switch_rpt(_BV(SWN))) {
			display_string("[R] North\n");
	}

	if (get_switch_rpt(_BV(SWE))) {
			display_string("[R] East\n");
	}

	if (get_switch_rpt(_BV(SWS))) {
			display_string("[R] South\n");
	}

	if (get_switch_rpt(_BV(SWW))) {
			display_string("[R] West\n");
	}

	if (get_switch_rpt(SWN)) {
			display_string("[R] North\n");
	}

	

	if (get_switch_long(_BV(OS_CD))) {
		display_string("Detected SD card.\n");
	}

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
