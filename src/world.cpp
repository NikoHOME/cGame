#include "world.h"
#include "func.h"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "animals.h"
#include "plants.h"

#define MAX_BOARD_SIZE_Y (LINES/2-1) //Max window size based on terminal
#define MAX_BOARD_SIZE_X (COLS/4)





WINDOW *createMenu(int maxy,int maxx,int heightght,int widthth)
{
    WINDOW *window = newwin(heightght,widthth,(maxy-heightght)/2,(maxx-widthth)/2);
    box(window, 0, 0);
    keypad(window,true);
    return window;
}

void World::processInput()
{
    Player *player = dynamic_cast<Player *>(organismDisplay[playerPosX][playerPosY]);
    if(!player) playerAlive = false;
    switch(playerInput)
    {
        case MOVE_UP: case MOVE_DOWN: case MOVE_LEFT: case MOVE_RIGHT:
            if(!playerAlive)
                break;
            player->inputAction();
            nextTurn();
            draw();
            break;
        case NEXT_TURN:
            nextTurn();
            draw();
            break;
        case SLOW_TURN:
            stepNextTurn();
            draw();
            break;
            
    }
}

bool World::handleInput()
{
    int key = wgetch(window);
    switch(key)
    {
        case KEY_UP:
            playerInput = MOVE_UP;
            break;
        case KEY_LEFT:
            playerInput = MOVE_LEFT;
            break;
        case KEY_DOWN:
            playerInput = MOVE_DOWN;
            break;
        case KEY_RIGHT:
            playerInput = MOVE_RIGHT;
            break;
        case NEXT_TURN:
            playerInput = NEXT_TURN;
            break;
        case SLOW_TURN:
            playerInput = SLOW_TURN;
            break;
        case QUIT_KEY:
            return false;
            break;
    }
    return true;
}



void World::initializeWindow()
{
	initscr();
    cbreak();
    noecho();
    refresh();
	curs_set(0);
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    start_color();
    use_default_colors();
    init_pair(BASIC_COLOUR, COLOR_WHITE, COLOR_BLACK);

    init_pair(WOLF_COLOUR, COLOR_BLACK+8, COLOR_BLACK);
    init_pair(FOX_COLOUR, COLOR_RED+8, COLOR_BLACK);
    init_pair(SHEEP_COLOUR, COLOR_WHITE, COLOR_BLACK);
    init_pair(TURTLE_COLOUR, COLOR_GREEN, COLOR_BLACK);
    init_pair(ANTILOPE_COLOUR, COLOR_RED, COLOR_BLACK);

    init_pair(GRASS_COLOUR, COLOR_GREEN+8, COLOR_BLACK);
    init_pair(GUARANA_COLOUR, COLOR_MAGENTA+8, COLOR_BLACK);
    init_pair(BELLADONA_COLOUR, COLOR_BLUE, COLOR_BLACK);
    init_pair(HOGWEED_COLOUR, COLOR_CYAN, COLOR_BLACK);
    init_pair(DANDELION_COLOUR, COLOR_YELLOW, COLOR_BLACK);

    init_pair(PLAYER_COLOUR, COLOR_BLACK, COLOR_WHITE);


	//Turn off ESC delay
	ESCDELAY = 25;


	//maxBoardsize used in custom board size
	int maxy,maxx,maxBoardSize;
	getmaxyx(stdscr,maxy,maxx);

	if(MAX_BOARD_SIZE_X>MAX_BOARD_SIZE_Y)
		maxBoardSize=MAX_BOARD_SIZE_Y;
	else
		maxBoardSize=MAX_BOARD_SIZE_X;
    
	window = createMenu(maxy,maxx,boardSize.height+2,boardSize.width+2);

    
    refresh();
	wrefresh(window);
}

std::ostream& operator<<(std::ostream &out,const Action &action)
{
    out<<action.previousPositionX<<" "<<action.previousPositionY<<" -> "<<action.newPositionX<<" "<<action.newPositionY;
    return out;
}

std::ostream& operator<<(std::ostream &out,const Organism &organism)
{
    out<<"{"<<organism.getPositionX()<<" "<<organism.getPositionY()<<" "<<organism.getIndex()<<"} ";
    //organism.draw();
    return out;
}

void World::draw()
{

    mvprintw(4,2,"Turn: %d",turn);
    refresh();
    for(int i = 0; i < boardSize.height; ++i)
    {
        for(int j = 0; j < boardSize.width; ++j)
        {
            wattron(window,COLOR_PAIR(BASIC_COLOUR));
            attron(COLOR_PAIR(BASIC_COLOUR));
            if(organismDisplay[j][i] != nullptr)
                mvwprintw(window,i+1,j+1,organismDisplay[j][i]->getChar());
            else
                mvwprintw(window,i+1,j+1,".");
            
        }
    }
   
    box(window,0,0);
    wrefresh(window);
}

void World::pushOrganism(Organism *organism)
{
    organism->setWorld(this);
    organismDisplay[organism->getPositionX()][organism->getPositionY()] = organism;
    organism->setIndex(newAnimalIndex++);
    //organism->setIndex(organisms.size());
    //organisms.push_back(organism);
    
}

std::vector <std::pair <int,int>> &World::getAiDirections()
{
    return aiDirections;
}
std::vector <std::vector<Organism*>> &World::getOrganismDisplay()
{
    return organismDisplay;
}


int World::getHeight()
{
    return boardSize.height;
}
int World::getWidth()
{
    return boardSize.width;
}
int World::getTurn()
{
    return turn;
}
BoardSize World::getBoardSize()
{
    return boardSize;
}
WINDOW *World::getWindow()
{
    return window;
}
char World::getPlayerAction()
{
    return playerInput;
}
int World::getPlayerPosX()
{
    return playerPosX;
}
int World::getPlayerPosY()
{
    return playerPosY;
}
std::priority_queue <Organism*, std::vector<Organism*>, CompareOrganism> &World::getQueue()
{
    return moveQueue;
}
void World::addActionToQueue(Action action)
{
    actions.push(action);
}



void World::setPlayerPosX(int x)
{
    playerPosX = x;
}
void World::setPlayerPosY(int y)
{
    playerPosY = y;
}

void World::nextTurn()
{
    ++turn;
    for(int i=0; i<boardSize.width; ++i)
    {
        for(int j=0; j<boardSize.height; ++j)
        {
            if(organismDisplay[i][j] != nullptr && (i!=playerPosX && j!=playerPosY))
            {
                moveQueue.push(organismDisplay[i][j]);
                //sleep(1);
                //organismDisplay[i][j]->action();
                //draw();
            }
        }
    }

    while(!moveQueue.empty())
    {
        auto top = moveQueue.top();
        moveQueue.pop();
        if(top == nullptr || top->getIsDeadStatus())
            continue;
        top->action();
        draw();
    }
}

void World::stepNextTurn()
{
    ++turn;
    for(int i=0; i<boardSize.width; ++i)
    {
        for(int j=0; j<boardSize.height; ++j)
        {
            if(organismDisplay[i][j] != nullptr)
            {
                moveQueue.push(organismDisplay[i][j]);
                //sleep(1);
                //organismDisplay[i][j]->action();
                //draw();
            }
        }
    }

    while(!moveQueue.empty())
    {
        auto top = moveQueue.top();
        moveQueue.pop();
        if(top == nullptr || top->getIsDeadStatus())
            continue;
        top->action();
        draw();
        usleep(100000);
    }
}

#define WOLF_MULTIPLIER 3
#define FOX_MULTIPLIER 7
#define SHEEP_MULTIPLIER 5
#define TURTLE_MULTIPLIER 2
#define ANTILOPE_MULTIPLIER 3

#define GRASS_MULTIPLIER 10
#define DANDELION_MULTIPLIER 5
#define BELLADONA_MULTIPLIER 2
#define HOGWEED_MULTIPLIER 1
#define GUARANA_MULTIPLIER 3


World::World(int width, int height)
{
    boardSize.width = width;
    boardSize.height = height;
    organismDisplay.resize(width);
    for(int i=0; i < width; ++i)
        organismDisplay[i].resize(height);

    aiDirections.push_back({0,-1});
    aiDirections.push_back({0,1});
    aiDirections.push_back({-1,0});
    aiDirections.push_back({1,0});

    for(auto dir : aiDirections) 
    {
        aiDirections.push_back({dir.first*2,dir.second*2});
    }
    aiDirections.push_back({1,1});
    aiDirections.push_back({1,-1});
    aiDirections.push_back({-1,1});
    aiDirections.push_back({-1,-1});

    srand(time(0));

    spawnAnimals(this);
    spawnPlants(this);

    Organism *player = new Player(rand() % width, rand() % height);
    playerPosX = player->getPositionX();
    playerPosY = player->getPositionY();
    pushOrganism(player);
}

void spawnAnimals(World *world)
{
    Organism *newOrganism;
    int width = world->boardSize.width;
    int height = world->boardSize.height;

    int average = (width + height) / 8;
    int wolfAmmount = rand() % average * WOLF_MULTIPLIER;
    int foxAmmount = rand() % average * FOX_MULTIPLIER;
    int sheepAmmount = rand() % average * SHEEP_MULTIPLIER;
    int turtleAmmount = rand() % average * TURTLE_MULTIPLIER;
    int antilopeAmmount = rand() % average * ANTILOPE_MULTIPLIER;

    for(int i = 0; i < wolfAmmount - (rand() % average); ++i)
    {
        newOrganism =  new Wolf(rand() % width, rand() % height);
        world->pushOrganism(newOrganism);
    }

    for(int i = 0; i < sheepAmmount - (rand() % average); ++i)
    {
        newOrganism =  new Sheep(rand() % width, rand() % height);
        world->pushOrganism(newOrganism);
    }

    for(int i = 0; i < foxAmmount - (rand() % average); ++i)
    {
        newOrganism =  new Fox(rand() % width, rand() % height);
        world->pushOrganism(newOrganism);
    }    

    for(int i = 0; i < turtleAmmount - (rand() % average); ++i)
    {
        newOrganism =  new Turtle(rand() % width, rand() % height);
        world->pushOrganism(newOrganism);
    }
    
    for(int i = 0; i < antilopeAmmount - (rand() % average); ++i)
    {
        newOrganism =  new Antilope(rand() % width, rand() % height);
        world->pushOrganism(newOrganism);
    }
}

void spawnPlants(World *world)
{
    Organism *newOrganism;
    int width = world->boardSize.width;
    int height = world->boardSize.height;

    int average = (width + height) / 8;
    int grassAmmount = rand() % average * GRASS_MULTIPLIER;
    int belladonaAmmount = rand() % average * BELLADONA_MULTIPLIER;
    int hogweedAmmount = rand() % average * HOGWEED_MULTIPLIER;
    int dandelionAmmount = rand() % average * DANDELION_MULTIPLIER;
    int guaranaAmmount = rand() % average * GUARANA_MULTIPLIER;

    for(int i = 0; i < grassAmmount - (rand() % average); ++i)
    {
        newOrganism =  new Grass(rand() % width, rand() % height);
        world->pushOrganism(newOrganism);
    }

    for(int i = 0; i < belladonaAmmount - (rand() % average); ++i)
    {
        newOrganism =  new Belladonna(rand() % width, rand() % height);
        world->pushOrganism(newOrganism);
    }

    for(int i = 0; i < hogweedAmmount - (rand() % average); ++i)
    {
        newOrganism =  new SosnowskyHogweed(rand() % width, rand() % height);
        world->pushOrganism(newOrganism);
    }    

    for(int i = 0; i < dandelionAmmount - (rand() % average); ++i)
    {
        newOrganism =  new Dandelion(rand() % width, rand() % height);
        world->pushOrganism(newOrganism);
    }
    
    for(int i = 0; i < guaranaAmmount - (rand() % average); ++i)
    {
        newOrganism =  new Guarana(rand() % width, rand() % height);
        world->pushOrganism(newOrganism);
    }
}