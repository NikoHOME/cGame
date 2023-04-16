#pragma once
#include <vector>
#include <queue>
#include "organism.h"


#include "classes.h"
#include "action.h"
#include "func.h"

class World
{
    
    std::vector <std::vector<Organism*>> organismDisplay;
    std::vector <Organism*> organisms;   
    std::vector <std::pair <int,int>> aiDirections;
    std::queue <Action> actions;
    BoardSize boardSize;

    public:
        void draw();
        void nextTurn();
        World(int wid, int hei)
        {
            boardSize.width = wid;
            boardSize.height = hei;
            organismDisplay.resize(boardSize.height);
            for(int i=0; i < boardSize.width; ++i)
                organismDisplay[i].resize(boardSize.width);
            
            for(int i =- 1; i <= 1; ++i)
                for(int j =- 1; j <= 1; ++j)
                    if(i != 0 || j != 0)
                        aiDirections.push_back({i,j});
            

        };
        void pushOrganism(Organism *organism);
        int getWidth();
        int getHeight();
        BoardSize getBoardSize();

        std::vector <std::pair <int,int>> &getAiDirections();
        std::vector <std::vector<Organism*>> &getOrganismDisplay();
        std::vector <Organism*> &getOrganisms();
        void addActionToQueue(Action action);
};