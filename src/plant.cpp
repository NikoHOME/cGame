#include "plant.hpp"
#include "world.hpp"
#include <iostream>





void Plant::basicMovementHandle()
{
    std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
    std::vector< std::pair <int,int>> emptyCells;
    Coordinate coordinate;
    for(int i=0; i<NORMAL_AI; ++i)
    {
        coordinate.x = positionX + directions[i].first;
        coordinate.y = positionY + directions[i].second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        auto target = world->getOrganismDisplay()[coordinate.x][coordinate.y];
        if(target == nullptr)
            emptyCells.push_back({coordinate.x,coordinate.y});
    }
    //mvprintw(8,2,"PosX = %d PosY =%d", positionX, positionY);
    //mvprintw(7,2,"emptyCells = %d", emptyCells.size());
    //refresh();
    if(emptyCells.size() == 0)
    {
        movementAction.newPositionX = -1;
        return;
    }
    movementAction.direction = emptyCells[rand()%emptyCells.size()];

    //mvprintw(9,2,"DirX = %d DirY =%d", movementAction.direction.first, movementAction.direction.second);
    //refresh();

    movementAction.newPositionX = movementAction.direction.first;
    movementAction.newPositionY = movementAction.direction.second;
}

void Plant::basicCollisionHandle()
{   
    if(movementAction.newPositionX == -1)
        return;

    Organism *baby = this->reproduce(movementAction.newPositionX, movementAction.newPositionY);

    Message message;
    message.animal1 = baby->getName();
    message.message = baby->getBornMessage();
    message.animal2 = " ";
    world->getManager()->pushMessage(message);
    
    world->pushOrganism(baby);
    world->draw();
}

void Plant::action()
{

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