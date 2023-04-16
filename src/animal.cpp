#include "animal.h"
#include "world.h"
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "func.h"

void Animal::draw() const
{
    std::cout<<"? ";
}

void Animal::basicMovementHandle()
{
    movementAction.direction = world->getAiDirections()[rand()%8];

    Coordinate coordinate;
    coordinate.x = positionX + movementAction.direction.first;
    coordinate.y = positionY + movementAction.direction.second;
    

    while(!isInBounds(world->getBoardSize(), coordinate))
    {
        movementAction.direction = world->getAiDirections()[rand()%8];
        coordinate.x = positionX + movementAction.direction.first;
        coordinate.y = positionY + movementAction.direction.second;  
    }
    movementAction.newPositionX = positionX + movementAction.direction.first;
    movementAction.newPositionY = positionY + movementAction.direction.second;
}

void Animal::basicCollisionHandle()
{
    Organism **thisOrganism, **otherOrganism;
    thisOrganism = &world->getOrganismDisplay()[positionX][positionY];
    otherOrganism = &world->getOrganismDisplay()[movementAction.newPositionX][movementAction.newPositionY];
    if(*otherOrganism == nullptr)
    {
        printName();
        std::cout<<" : "<<positionX<<" "<<positionY<<" -> "<<movementAction.newPositionX<<" "<<movementAction.newPositionY<<"\n";
        std::swap(*thisOrganism, *otherOrganism);
        setPositionX(movementAction.newPositionX);
        setPositionY(movementAction.newPositionY);
        return;
    }
    

    if((*thisOrganism)->getName() == (*otherOrganism)->getName())
    {
        std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
        std::vector< std::pair <int,int>> emptyCells;

        Organism *targetOrganism;
        Coordinate coordinate;
        for(auto i : directions)
        {
            coordinate.x = positionX + i.first;
            coordinate.y = positionY + i.second;
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
            return;

        std::pair <int,int> direction = emptyCells[rand()%emptyCells.size()];

        Organism *baby = reproduce(*otherOrganism, direction.first, direction.second);
        
        if(baby == nullptr)
            return;

        world->pushOrganism(baby);


        return;
    }
    
    
    CollisionAction thisCollision = collision(), otherCollision = (*otherOrganism)->collision();
    


    if(thisCollision.escaped == true)
        return;


    if(otherCollision.escaped == true)
    {
        moveOrganism(thisOrganism, movementAction.newPositionX, movementAction.newPositionY);
        return;
    }
    
    

    
    killIfStronger(thisOrganism, otherOrganism, thisCollision, otherCollision);
    //if(otherCollision.stopAfterDefence)
    //    return;
    //if(thisCollision.stopAfterAttack)
    //    return;
    //killIfStronger(thisOrganism, otherOrganism, thisCollision.realStrength, otherCollision.realStrength, false, true);
}


void Animal::action()
{
    srand(time(0));

    basicMovementHandle();

    basicCollisionHandle();

}

CollisionAction Animal::collision()
{
    CollisionAction action;
    action.realStrength = strength;

    return action;
}