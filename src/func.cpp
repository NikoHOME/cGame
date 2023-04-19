#include "func.h"
#include <iostream>
#include "organism.h"
#include "animal.h"
#include "world.h"

bool isInBounds(BoardSize boardSize, Coordinate coordinate)
{
    if(coordinate.x >= 0 && coordinate.x < boardSize.width)
        if(coordinate.y >= 0 && coordinate.y < boardSize.height)
            return true;
    return false;
}

void setAction(AttackAction &action, CollisionAction thisCollision, CollisionAction otherCollision)
{
    if(thisCollision.hasTempAttackStrength)
        action.thisAttackerStrength = thisCollision.tempAttackStrength;
    else
        action.thisAttackerStrength = thisCollision.realStrength;
    
    if(thisCollision.hasTempDefenceStrength)
        action.thisDefenderStrength = thisCollision.tempDefenceStrength;
    else
        action.thisDefenderStrength = thisCollision.realStrength;


    if(otherCollision.hasTempAttackStrength)
        action.otherAttackerStrength = otherCollision.tempAttackStrength;
    else
        action.otherAttackerStrength = otherCollision.realStrength;
    
    if(otherCollision.hasTempDefenceStrength)
        action.otherDefenderStrength = otherCollision.tempDefenceStrength;
    else
        action.otherDefenderStrength = otherCollision.realStrength; 
}


void killIfStronger(Organism **thisOrganism, Organism **otherOrganism, CollisionAction thisCollision, CollisionAction otherCollision)
{

    AttackAction action;

    setAction(action, thisCollision, otherCollision);

    if(action.thisAttackerStrength > action.otherDefenderStrength)
    {
        //std::cout<<action.thisAttackerStrength<< " " << action.otherDefenderStrength << "\n";
        (*thisOrganism)->printName();
        std::cout<<" : Attack :";
        (*otherOrganism)->printName();
        std::cout<<" killed by ";
        (*thisOrganism)->printName();
        std::cout<<"\n";   
        if(otherCollision.givesStrength)
        {
            (*thisOrganism)->setStrength((*thisOrganism)->getStrength() + otherCollision.givenStrength);
        }
        if(otherCollision.killAfterDefeat)
        {
            (*thisOrganism)->getWorld()->getOrganisms()[(*thisOrganism)->getIndex()]->setIsDeadStatus(true);
            (*thisOrganism)->getWorld()->getOrganisms()[(*otherOrganism)->getIndex()]->setIsDeadStatus(true);
            *thisOrganism = nullptr;
            *otherOrganism = nullptr;
            return;
        }

        (*thisOrganism)->setPositionX((*otherOrganism)->getPositionX());
        (*thisOrganism)->setPositionY((*otherOrganism)->getPositionY());
        (*thisOrganism)->getWorld()->getOrganisms()[(*otherOrganism)->getIndex()]->setIsDeadStatus(true);
        *otherOrganism = nullptr;
        std::swap(*thisOrganism, *otherOrganism); 
    }
    /*
    if(thisCollision.stopAfterAttack)
        return;
    if(otherCollision.stopAfterDefence)
        return;
*/
    
    if(action.otherAttackerStrength > action.thisDefenderStrength)
    {
        //std::cout<<action.thisDefenderStrength<< " " << action.otherAttackerStrength << "\n";
        (*thisOrganism)->printName();
        std::cout<<" : Defence : ";
        (*thisOrganism)->printName();
        std::cout<<" killed by ";
        (*otherOrganism)->printName();
        std::cout<<"\n";    
        if(thisCollision.givesStrength)
        {
            (*otherOrganism)->setStrength((*otherOrganism)->getStrength() + thisCollision.givenStrength);
        }

        (*thisOrganism)->getWorld()->getOrganisms()[(*thisOrganism)->getIndex()]->setIsDeadStatus(true);
        *thisOrganism = nullptr;
    }
}

void moveOrganism(Organism **organism, int x, int y)
{
    World *world = (*organism)->getWorld();
    Organism **empty = &world->getOrganismDisplay()[x][y]; 

    (*organism)->setPositionX(x);
    (*organism)->setPositionY(y);

    (*organism)->printName();
    std::cout<<" : "<<(*organism)->getPositionX()<<" "<<(*organism)->getPositionY()<<" -> "<<x<<" "<<y<<"\n";

    std::swap(*empty, *organism); 
}



bool reproduceCollision(Organism **thisOrganism, Organism **otherOrganism)
{
    auto animal1 = dynamic_cast<Animal *>(*thisOrganism);
    auto animal2 = dynamic_cast<Animal *>(*otherOrganism);
    if(!animal1->isSameSpecies(animal2))
        return false;
    
    World *world = animal1->getWorld();

    std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
    std::vector< std::pair <int,int>> emptyCells;

    Organism *targetOrganism;
    Coordinate coordinate;
    for(auto i : directions)
    {
        coordinate.x = animal1->getPositionX() + i.first;
        coordinate.y = animal1->getPositionY() + i.second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        targetOrganism = world->getOrganismDisplay()[coordinate.x][coordinate.y];
        if(targetOrganism == nullptr)
            emptyCells.push_back({coordinate.x,coordinate.y});
    }
    for(auto i : directions)
    {
        coordinate.x = (*otherOrganism)->getPositionX() + i.first;
        coordinate.y = (*otherOrganism)->getPositionY() + i.second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        targetOrganism = world->getOrganismDisplay()[coordinate.x][coordinate.y];
        if(targetOrganism == nullptr)
            emptyCells.push_back({coordinate.x,coordinate.y});
    } 
    if(emptyCells.size() == 0)
        return false;

    std::pair <int,int> direction = emptyCells[rand()%emptyCells.size()];

    Organism *baby = animal1->reproduce(direction.first, direction.second);
    
    if(baby == nullptr)
        return false;

    world->pushOrganism(baby);
    return true;

}
