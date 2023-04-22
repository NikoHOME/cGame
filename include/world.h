#pragma once
#include <vector>
#include <queue>
#include "organism.h"
#include <ncurses.h>

#define MOVE_UP 11
#define MOVE_DOWN 12
#define MOVE_LEFT 13
#define MOVE_RIGHT 14

#define QUIT_KEY 'q'    //Control Keys
#define NEXT_TURN 'n'
#define SLOW_TURN 's'

#define NORMAL_AI 4
#define ANTILOPE_AI 12


#define WOLF_COLOUR 1
#define SHEEP_COLOUR 2
#define FOX_COLOUR 3
#define TURTLE_COLOUR 5
#define ANTILOPE_COLOUR 6

#define GRASS_COLOUR 7
#define DANDELION_COLOUR 8
#define BELLADONA_COLOUR 9
#define HOGWEED_COLOUR 10
#define GUARANA_COLOUR 11

#define PLAYER_COLOUR 12

#define BASIC_COLOUR 13

#include "classes.h"
#include "action.h"
#include "func.h"

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

class World
{
    
    std::vector <std::vector<Organism*>> organismDisplay;  
    std::vector <std::pair <int,int>> aiDirections;
    std::priority_queue <Organism*, std::vector<Organism*>, CompareOrganism> moveQueue;
    std::queue <Action> actions;
    BoardSize boardSize;
    WINDOW *window;
    int turn = 0;
    int newAnimalIndex = 0;
    int playerPosX, playerPosY;
    char playerInput;
    bool playerAlive = true;

    public:
        void draw();
        void initializeWindow();
        bool handleInput();
        void processInput();
        void nextTurn();
        World(int width, int height);
        void pushOrganism(Organism *organism);
        
        int getWidth();
        int getHeight();
        int getTurn();
        int getPlayerPosX();
        int getPlayerPosY();
        WINDOW *getWindow();
        char getPlayerAction();
        BoardSize getBoardSize();

        void setPlayerPosX(int x);
        void setPlayerPosY(int y);

        std::vector <std::pair <int,int>> &getAiDirections();
        std::vector <std::vector<Organism*>> &getOrganismDisplay();
        std::priority_queue <Organism*, std::vector<Organism*>, CompareOrganism> &getQueue();
        void addActionToQueue(Action action);

        void stepNextTurn();

        friend void spawnAnimals(World *world);
        friend void spawnPlants(World *world);
};