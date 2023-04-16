#include "func.h"
#include <iostream>
#include "organism.h"
#include "world.h"

bool isInBounds(BoardSize boardSize, Coordinate coordinate)
{
    if(coordinate.x >= 0 && coordinate.x < boardSize.width)
        if(coordinate.y >= 0 && coordinate.y < boardSize.height)
            return true;
    return false;
}

void killIfStronger(Organism **thisOrganism, Organism **otherOrganism, CollisionAction thisCollision, CollisionAction otherCollision)
{

    AttackAction action;


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


    if(action.thisAttackerStrength > action.otherDefenderStrength)
    {
        //std::cout<<action.thisAttackerStrength<< " " << action.otherDefenderStrength << "\n";
        (*thisOrganism)->printName();
        std::cout<<" : Attack :";
        (*otherOrganism)->printName();
        std::cout<<" killed by ";
        (*thisOrganism)->printName();
        std::cout<<"\n";   

        (*thisOrganism)->setPositionX((*otherOrganism)->getPositionX());
        (*thisOrganism)->setPositionY((*otherOrganism)->getPositionY());
        (*thisOrganism)->getWorld()->getOrganisms()[(*otherOrganism)->getIndex()]->setIsDeadStatus(true);
        *otherOrganism = nullptr;
        std::swap(*thisOrganism, *otherOrganism); 
    }
    
    if(thisCollision.stopAfterAttack)
        return;
    if(otherCollision.stopAfterDefence)
        return;

    
    if(action.otherAttackerStrength > action.thisDefenderStrength)
    {
        //std::cout<<action.thisDefenderStrength<< " " << action.otherAttackerStrength << "\n";
        (*thisOrganism)->printName();
        std::cout<<" : Defence : ";
        (*thisOrganism)->printName();
        std::cout<<" killed by ";
        (*otherOrganism)->printName();
        std::cout<<"\n";    

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
