#include "setup.h"

int mazeNum = 0;

int exit_x = 0;
int exit_y = 0;

difficulty currentDifficulty = EASY;

void setup_set_orientation(orientation o)
{
    set_orientation(o);
    set_input_orientation(o);
    clear_screen();
    display_top("Welcome to Fortuna Maze!");
}

void draw_tutorial_map()
{
    // char mid[7*7];
	// ScreenBlock sc;
	// sc.width = 7;
	// sc.height = 7;
	// sc.blockval = mid;
	// makeRoom(&sc);
	// displayBlock(&sc, 3, 3);
    // displayBlock(&sc, 12, 4);

    makeRoom(9,7,0,0);
    makeRoom(5, 8, 12, 4);
    drawPath(9,5,12,5);

    addTreasure(8,8);
    addTreasure(15, 7);

    // char mid2[6*8];
    // ScreenBlock sc2;
    // sc.width = 6;
    // sc.height = 8;
    // sc.blockval = mid2;
    // makeRoom(&sc2);
    //displayBlock(&sc2, 13, 4);
}

void setup_tutorial_player()
{
    // player->x = 5;
    // player->y = 5;
    // player->standingOn = '.';
    // player->display = '@';
    // player->colour = RED;

    // setPlayer(player);
    start_player(1,1);
}

void draw_maze(int i)
{
    // makeMaze_binaryTree((i)%4);
    srand(i);
    makeMaze_rBackTrack();
    mazeNum = 0;
}

void setup_maze()
{
    if(mazeNum %5 != 0 && currentDifficulty==HARD)
    {
        makeMaze_binaryTree((mazeNum++)%4);
    }
    else if(currentDifficulty==HARD)
    {
        makeMaze_rBackTrack();
        mazeNum++;
    }
    else
    {
        makeMaze_binaryTree((mazeNum++)%4);
    }
}

void add_treasure()
{
    int t;
    int add = rand() %5;
    for(t=0; t<MIN_TREASURE+add; t++)
    {
        int x = (rand() % (SCRN_MAX_HEIGHT - 4)) + 1;
        int y = (rand() % (SCRN_MAX_WIDTH - 4)) + 1;

        addTreasure(x, y);
    }

    if(rand()%2)
    {
        //Add big treasure
        int x = (rand() % (SCRN_MAX_HEIGHT - 4)) + 1;
        int y = (rand() % (SCRN_MAX_WIDTH - 4)) + 1;

        addBigTreasure(x, y);
    }
}

void add_exit()
{
    int x = (rand() % (SCRN_MAX_HEIGHT-6)) + 2;
    int y = (rand() % (SCRN_MAX_WIDTH-6)) + 2;

    if(exit_x==x && exit_y==y)
    {
        if(x>0)
        {
            x-=1;
        }
        else
        {
            x+=1;
        }
    }
    exit_x = x;
    exit_y = y;
    addExit(x, y);
}

void replace_player()
{
    // int x = ((rand() % (SCRN_MAX_HEIGHT/2)) * 2) + INIT_X;
    // int y = ((rand() % (SCRN_MAX_WIDTH/2)) * 2) + INIT_Y;

    // set_player_pos(x, y);
    redraw();
}

void set_difficulty(difficulty d)
{
    currentDifficulty = d;
}