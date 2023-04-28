#include "world.hpp"
#include "func.hpp"
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "animals.hpp"
#include "plants.hpp"

#define ABILITY_COOLDOWN 10
#define ABILITY_DURATION 5

bool World::playerCanUseAbility()
{
    if(turn - lastTimeAbilityUsed >= ABILITY_COOLDOWN)
        return true;
    return false;
}

bool World::playerHasAbility()
{
    if(AbilityDuration > 0 )
        return true;
    return false;
}



void World::initializeWindow()
{

	//maxBoardsize used in custom board size
	int maxy,maxx,maxBoardSize;
	getmaxyx(stdscr,maxy,maxx);

	window = newwin(boardSize.height+2, (boardSize.width)*2+2, (maxy-boardSize.height+2)/2, (maxx-((boardSize.width)*2+2))/2);
    box(window, 0, 0);
    keypad(window,true);

    
    refresh();
	wrefresh(window);
}

void World::draw()
{

    for(int i = 0; i < boardSize.height; ++i)
    {
        for(int j = 0; j < boardSize.width; ++j)
        {
            wattron(window,COLOR_PAIR(BASIC_COLOUR));
            attron(COLOR_PAIR(BASIC_COLOUR));
            if(organismDisplay[j][i] != nullptr)
            {
                mvwprintw(window,i+1,j*2+1,organismDisplay[j][i]->getChar());
                wattron(window,COLOR_PAIR(BASIC_COLOUR));
                mvwprintw(window,i+1,j*2+2," ");
            }
            else
                mvwprintw(window,i+1,j*2+1,". ");
            
        }
    }
    mvprintw(4,10,"O Turn: %d",turn);
    if(playerCanUseAbility())
        mvprintw(6,10,"O Ability avaible      ");
    else
        mvprintw(6,10,"X Ability not avaible ");
    if(playerHasAbility())
        mvprintw(8,10,"O Ability duration: %d",AbilityDuration);
    else
        mvprintw(8,10,"X Ability duration: %d",AbilityDuration);
    if(playerAlive && organismDisplay[playerPosX][playerPosY] != nullptr)
        mvprintw(10,10,"Player Strength: %d", organismDisplay[playerPosX][playerPosY]->getStrength());
    else
        playerAlive = false;

    mvprintw(12,10,"n - Next turn");     
    mvprintw(13,10,"q - Quit");  
    mvprintw(14,10,"e - Use ability");  
    mvprintw(15,10,"Arrows - Movement");  
    mvprintw(16,10,"s - Save");
    mvprintw(17,10,"l - Load");


    refresh();
    box(window,0,0);
    wrefresh(window);
}

void World::pushOrganism(Organism *organism)
{
    Organism *oldOrganism = organismDisplay[organism->getPositionX()][organism->getPositionY()];
    if(oldOrganism != nullptr)
    {
        pushDeadOrganism(oldOrganism);
    }

    organism->setWorld(this);
    organismDisplay[organism->getPositionX()][organism->getPositionY()] = organism;
    organism->setIndex(newAnimalIndex++);
    //organism->setIndex(organisms.size());
    //organisms.push_back(organism);
    
}


void World::nextTurn()
{
    mvprintw(4,10,"X Turn: %d",turn);
    refresh();
    for(int i=0; i<boardSize.width; ++i)
    {
        for(int j=0; j<boardSize.height; ++j)
        {
            if(organismDisplay[i][j] != nullptr && (!playerAlive || (i!=playerPosX && j!=playerPosY)))
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
        if(top->getIsDeadStatus())
            continue;

        top->action();
    }

    while(!deadOrganisms.empty())
    {
        auto front = deadOrganisms.front();
        deadOrganisms.pop();
        Animal *animal = dynamic_cast<Animal *>(front);
        if(animal != nullptr)
        {
            delete animal;
            continue;
        }

        Plant *plant = dynamic_cast<Plant *>(front);
        if(plant != nullptr)
        {
            delete plant;
            continue;
        }
    }

    if(playerHasAbility())
        --AbilityDuration;
    ++turn;
}

World::World(int height, int width, bool copy)
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

    int size = aiDirections.size();

    for(int i = 0; i < size; ++i) 
    {
        auto dir = aiDirections[i];
        aiDirections.push_back({dir.first*2,dir.second*2});
    }
    aiDirections.push_back({1,1});
    aiDirections.push_back({1,-1});
    aiDirections.push_back({-1,1});
    aiDirections.push_back({-1,-1});

    if(!copy)
    {
        srand(time(0));

        spawnAnimals();
        spawnPlants();

        Organism *player = new Player(rand() % width, rand() % height);
        playerPosX = player->getPositionX();
        playerPosY = player->getPositionY();
        pushOrganism(player);
    }
}

WorldData World::getWorldData()
{
    WorldData data;

    data.AbilityDuration = AbilityDuration;
    data.boardSize = boardSize;
    data.lastTimeAbilityUsed = lastTimeAbilityUsed;
    data.newAnimalIndex = newAnimalIndex;
    data.playerAlive = playerAlive;
    data.playerInput = playerInput;
    data.playerPosX = playerPosX;
    data.playerPosY = playerPosY;
    data.turn = turn;

    return data;
}

void World::setWorldData(WorldData data)
{
    AbilityDuration = data.AbilityDuration; 
    boardSize = data.boardSize;
    lastTimeAbilityUsed = data.lastTimeAbilityUsed;
    newAnimalIndex = data.newAnimalIndex;
    playerAlive = data.playerAlive;
    playerInput = data.playerInput;
    playerPosX = data.playerPosX;
    playerPosY = data.playerPosY;
    turn = data.turn;
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


void World::spawnAnimals()
{
    Organism *newOrganism;
    int width = boardSize.width;
    int height = boardSize.height;

    int average = (width + height) / 8 + 1;
    int wolfAmmount = rand() % average * WOLF_MULTIPLIER;
    int foxAmmount = rand() % average * FOX_MULTIPLIER;
    int sheepAmmount = rand() % average * SHEEP_MULTIPLIER;
    int turtleAmmount = rand() % average * TURTLE_MULTIPLIER;
    int antilopeAmmount = rand() % average * ANTILOPE_MULTIPLIER;

    for(int i = 0; i < std::max(wolfAmmount - (rand() % average),1); ++i)
    {
        newOrganism =  new Wolf(rand() % width, rand() % height);
        pushOrganism(newOrganism);
    }

    for(int i = 0; i < std::max(sheepAmmount - (rand() % average),1); ++i)
    {
        newOrganism =  new Sheep(rand() % width, rand() % height);
        pushOrganism(newOrganism);
    }

    for(int i = 0; i < std::max(foxAmmount - (rand() % average),1); ++i)
    {
        newOrganism =  new Fox(rand() % width, rand() % height);
        pushOrganism(newOrganism);
    }    

    for(int i = 0; i < std::max(turtleAmmount - (rand() % average),1); ++i)
    {
        newOrganism =  new Turtle(rand() % width, rand() % height);
        pushOrganism(newOrganism);
    }
    
    for(int i = 0; i < std::max(antilopeAmmount - (rand() % average),1); ++i)
    {
        newOrganism =  new Antilope(rand() % width, rand() % height);
        pushOrganism(newOrganism);
    }
}

void World::spawnPlants()
{
    Organism *newOrganism;
    int width = boardSize.width;
    int height = boardSize.height;

    int average = (width + height) / 8 + 1;
    int grassAmmount = rand() % average * GRASS_MULTIPLIER;
    int belladonaAmmount = rand() % average * BELLADONA_MULTIPLIER;
    int hogweedAmmount = rand() % average * HOGWEED_MULTIPLIER;
    int dandelionAmmount = rand() % average * DANDELION_MULTIPLIER;
    int guaranaAmmount = rand() % average * GUARANA_MULTIPLIER;

    for(int i = 0; i < std::max(grassAmmount - (rand() % average),1); ++i)
    {
        newOrganism =  new Grass(rand() % width, rand() % height);
        pushOrganism(newOrganism);
    }

    for(int i = 0; i < std::max(belladonaAmmount - (rand() % average),1); ++i)
    {
        newOrganism =  new Belladonna(rand() % width, rand() % height);
        pushOrganism(newOrganism);
    }

    for(int i = 0; i < std::max(hogweedAmmount - (rand() % average),1); ++i)
    {
        newOrganism =  new SosnowskyHogweed(rand() % width, rand() % height);
        pushOrganism(newOrganism);
    }    

    for(int i = 0; i < std::max(dandelionAmmount - (rand() % average),1); ++i)
    {
        newOrganism =  new Dandelion(rand() % width, rand() % height);
        pushOrganism(newOrganism);
    }
    
    for(int i = 0; i < std::max(guaranaAmmount - (rand() % average),1); ++i)
    {
        newOrganism =  new Guarana(rand() % width, rand() % height);
        pushOrganism(newOrganism);
    }
}