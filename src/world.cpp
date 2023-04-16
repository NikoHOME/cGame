#include "world.h"
#include "func.h"
#include <iostream>



std::ostream& operator<<(std::ostream &out,const Action &action)
{
    out<<action.previousPositionX<<" "<<action.previousPositionY<<" -> "<<action.newPositionX<<" "<<action.newPositionY;
    return out;
}

std::ostream& operator<<(std::ostream &out,const Organism &organism)
{
    out<<"{"<<organism.getPositionX()<<" "<<organism.getPositionY()<<" "<<organism.getIndex()<<"} ";
    organism.draw();
    return out;
}

void World::draw()
{
    for(int i = 0; i < boardSize.height; ++i)
    {
        for(int j = 0; j < boardSize.width; ++j)
        {
            
            if(organismDisplay[j][i] != nullptr)
                organismDisplay[j][i]->draw();
            else
                std::cout<<". ";

            
        }
        std::cout<<"   ";
        for(int j = 0; j < boardSize.width; ++j)
        {
            
            if(organismDisplay[j][i] != nullptr)
            {
                if(organismDisplay[j][i]->getPositionX() != j || organismDisplay[j][i]->getPositionY() != i)
                    std::cout<<"! ";
                else
                    std::cout<<"* ";
            }
            else
                std::cout<<". ";

            
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";
/*
    for(auto i: organisms)
    {
        std::cout<<*i<<"\n";
    }*/
}

void World::pushOrganism(Organism *organism)
{
    organism->setWorld(this);
    organismDisplay[organism->getPositionX()][organism->getPositionY()] = organism;
    organism->setIndex(organisms.size());
    organisms.push_back(organism);
    
}

std::vector <std::pair <int,int>> &World::getAiDirections()
{
    return aiDirections;
}
std::vector <std::vector<Organism*>> &World::getOrganismDisplay()
{
    return organismDisplay;
}
std::vector <Organism*> &World::getOrganisms()
{
    return organisms;
}

int World::getHeight()
{
    return boardSize.height;
}
int World::getWidth()
{
    return boardSize.width;
}
BoardSize World::getBoardSize()
{
    return boardSize;
}


void World::addActionToQueue(Action action)
{
    actions.push(action);
}

void World::nextTurn()
{

    for(auto organism : organisms)
    {
        if(!organism->getIsDeadStatus())
            organism->action();/*
    }
    while(!actions.empty())
    {
        Action action = actions.front();
        actions.pop();
        
        Organism *target = organismDisplay[action.newPositionX][action.newPositionY];
        target->collision(action);*/
        //organisms[action.organismIndex]->collision(action);
        //std::cout<<action<<"\n";
        //std::cout<<*organismDisplay[action.previousPositionX][action.previousPositionY]<<"\n";
        //std::swap(organismDisplay[action.newPositionX][action.newPositionY],
        //        organismDisplay[action.previousPositionX][action.previousPositionY]); 
        //
        //organisms[action.organismIndex]->setPositionX(action.newPositionX);
        //organisms[action.organismIndex]->setPositionY(action.newPositionY);
        //draw();
    }
}