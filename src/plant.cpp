#include "plant.h"
#include "world.h"
#include <iostream>

#define GROW_CHANCE 10

void Plant::draw() const
{
    std::cout<<"@ ";
}


void Plant::basicMovementHandle()
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
    if(emptyCells.size() == 0)
    {
        movementAction.newPositionX = -1;
        return;
    }
    movementAction.direction = emptyCells[rand()%emptyCells.size()];

    movementAction.newPositionX = movementAction.direction.first;
    movementAction.newPositionY = movementAction.direction.second;
}

void Plant::basicCollisionHandle()
{   
    if(movementAction.newPositionX == -1)
        return;

    Organism *baby = this->reproduce(movementAction.newPositionX, movementAction.newPositionY);

    world->pushOrganism(baby);
}

void Plant::action()
{
    srand(time(0));

    if(rand()%100 >= GROW_CHANCE)
        return;

    basicMovementHandle();

    basicCollisionHandle();
}

CollisionAction Plant::collision()
{
    CollisionAction action;
    action.realStrength = strength;

    return action;
}