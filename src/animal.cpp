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
    
    if(reproduceCollision(thisOrganism, otherOrganism))
        return;

    CollisionAction thisCollision = collision(), otherCollision = (*otherOrganism)->collision();
    
    if(thisCollision.escaped == true)
        return;


    if(otherCollision.escaped == true)
    {
        moveOrganism(thisOrganism, movementAction.newPositionX, movementAction.newPositionY);
        return;
    }
    
    killIfStronger(thisOrganism, otherOrganism, thisCollision, otherCollision);
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