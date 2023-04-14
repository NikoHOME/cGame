#include "world.h"
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
    for(int i=0; i<height; ++i)
    {
        for(int j=0; j<width; ++j)
        {
            
            if(organismDisplay[j][i] != nullptr)
                organismDisplay[j][i]->draw();
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

int World::getHeight()
{
    return height;
}
int World::getWidth()
{
    return width;
}

void World::addActionToQueue(Action action)
{
    actions.push(action);
}

void World::nextTurn()
{

    for(auto organism : organisms)
    {
        organism->action();
    }
    while(!actions.empty())
    {
        Action action = actions.front();
        actions.pop();
        //std::cout<<action<<"\n";
        //std::cout<<*organismDisplay[action.previousPositionX][action.previousPositionY]<<"\n";
        std::swap(organismDisplay[action.newPositionX][action.newPositionY],
                organismDisplay[action.previousPositionX][action.previousPositionY]); 
        
        organisms[action.organismIndex]->setPositionX(action.newPositionX);
        organisms[action.organismIndex]->setPositionY(action.newPositionY);
    }
}