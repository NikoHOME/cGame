#pragma once
#include <vector>
#include <queue>
#include "organism.hpp"
#include <ncurses.h>



#define NORMAL_AI 4
#define ANTILOPE_AI 12



#include "manager.hpp"
#include "classes.hpp"
#include "action.hpp"
#include "func.hpp"

class CompareOrganism {
    public:
        bool operator()(Organism *a, Organism *b)
        {
            if(a->getInnitiative() < b->getInnitiative())
                return true;
            if(a->getInnitiative() == b->getInnitiative())
                return a->getIndex() < b->getIndex();
            return false;
        }
};

#define DISPLAY_TYPE        std::vector <std::vector<Organism*>>
#define DIRECTIONS_TYPE     std::vector <std::pair <int,int>>
#define QUEUE_TYPE          std::priority_queue <Organism*, std::vector<Organism*>, CompareOrganism>

class World
{
    
    DISPLAY_TYPE organismDisplay;  
    DIRECTIONS_TYPE aiDirections;
    QUEUE_TYPE moveQueue;
    
    std::queue <Organism *> deadOrganisms;

    Manager *manager;
    BoardSize boardSize;
    WINDOW *window;
    int turn = 0;
    int newAnimalIndex = 0;
    int playerPosX, playerPosY;
    char playerInput;
    bool playerAlive = true;
    int lastTimeAbilityUsed = -10;
    int AbilityDuration = 0;


    public:
        void draw();
        void initializeWindow();
        //bool handleInput();
        //void processInput();
        void nextTurn();
        World(int height, int width, bool copy = false);
        void pushOrganism(Organism *organism);

        bool playerCanUseAbility();
        bool playerHasAbility();
        
        int getWidth()                      { return boardSize.width;}
        int getHeight()                     { return boardSize.height;}
        int getTurn()                       { return turn;}
        int getPlayerPosX()                 { return playerPosX;}
        int getPlayerPosY()                 { return playerPosY;}
        WINDOW *getWindow()                 { return window;}
        bool getPlayerAliveStatus()         { return playerAlive;}
        char getPlayerAction()              { return playerInput;}
        char &getRefPlayerAction()          { return playerInput;}
        BoardSize getBoardSize()            { return boardSize;}

        void setPlayerPosX(int x)           { playerPosX = x;}
        void setPlayerPosY(int y)           { playerPosY = y;}
        int &getRefLastTimeAbilityUsed()    { return lastTimeAbilityUsed;}
        int &getRefgAbilityDuration()       { return AbilityDuration;}

        DIRECTIONS_TYPE &getAiDirections()  { return aiDirections;}
        DISPLAY_TYPE &getOrganismDisplay()  { return organismDisplay;}
        QUEUE_TYPE &getQueue()              { return moveQueue;}
        Manager *getManager()               { return manager;}

        WorldData getWorldData();
        void setManager(Manager *manager)   { this->manager = manager;}
        void pushDeadOrganism(Organism *org){ deadOrganisms.push(org);}
        void setWorldData(WorldData data);

        void spawnAnimals();
        void spawnPlants();
        

        //void stepNextTurn();

        friend void spawnAnimals(World *world);
        friend void spawnPlants(World *world);
};