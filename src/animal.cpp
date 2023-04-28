#include "animal.hpp"
#include "world.hpp"
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "func.hpp"

void Animal::basicMovementHandle()
{
    movementAction.direction = world->getAiDirections()[rand() % NORMAL_AI];

    Coordinate coordinate;
    coordinate.x = positionX + movementAction.direction.first;
    coordinate.y = positionY + movementAction.direction.second;
    

    while(!isInBounds(world->getBoardSize(), coordinate))
    {
        movementAction.direction = world->getAiDirections()[rand() % NORMAL_AI];
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
        //printName();
        //std::cout<<" : "<<positionX<<" "<<positionY<<" -> "<<movementAction.newPositionX<<" "<<movementAction.newPositionY<<"\n";
        std::swap(*thisOrganism, *otherOrganism);
        setPositionX(movementAction.newPositionX);
        setPositionY(movementAction.newPositionY);
        return;
    }
    Animal *thisAnimal = dynamic_cast<Animal *>(*thisOrganism);
    if(thisAnimal->reproduceCollision(*otherOrganism))
        return;

    CollisionAction thisCollision = collision(), otherCollision = (*otherOrganism)->collision();
    
    if(thisCollision.escaped == true)
        return;


    if(otherCollision.escaped == true)
    {
        //moveOrganism(thisOrganism, movementAction.newPositionX, movementAction.newPositionY);
        return;
    }
    (*thisOrganism)->killIfStronger(*otherOrganism, thisCollision, otherCollision);
}


void Animal::action()
{

    basicMovementHandle();

    basicCollisionHandle();

}

CollisionAction Animal::collision()
{
    CollisionAction action;
    action.realStrength = strength;

    return action;
}

bool Animal::reproduceCollision(Organism *inputOrganism)
{
    Organism **thisOrganism = &world->getOrganismDisplay()[positionX][positionY];
    Organism **otherOrganism = &world->getOrganismDisplay()[inputOrganism->getPositionX()][inputOrganism->getPositionY()];

    auto animal1 = dynamic_cast<Animal *>(*thisOrganism);
    auto animal2 = dynamic_cast<Animal *>(*otherOrganism);
    if(!animal2)
        return false;
    if(!animal1->isSameSpecies(animal2))
        return false;
    
    World *world = animal1->getWorld();

    std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
    std::vector< std::pair <int,int>> emptyCells;

    Organism *targetOrganism;
    Coordinate coordinate;
    for(int i=0; i < NORMAL_AI; ++i)
    {
        coordinate.x = animal1->getPositionX() + directions[i].first;
        coordinate.y = animal1->getPositionY() + directions[i].second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        targetOrganism = world->getOrganismDisplay()[coordinate.x][coordinate.y];
        if(targetOrganism == nullptr)
            emptyCells.push_back({coordinate.x,coordinate.y});
    }
    for(int i=0; i < NORMAL_AI; ++i)
    {
        coordinate.x = (*otherOrganism)->getPositionX() + directions[i].first;
        coordinate.y = (*otherOrganism)->getPositionY() + directions[i].second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        targetOrganism = world->getOrganismDisplay()[coordinate.x][coordinate.y];
        if(targetOrganism == nullptr)
            emptyCells.push_back({coordinate.x,coordinate.y});
    } 
    if(emptyCells.size() == 0)
        return true;

    std::pair <int,int> direction = emptyCells[rand()%emptyCells.size()];

    Organism *baby = animal1->reproduce(direction.first, direction.second);
    
    if(baby == nullptr)
        return true;

    Message message;
    message.animal1 = baby->getName();
    message.message = baby->getBornMessage();
    message.animal2 = " ";
    world->getManager()->pushMessage(message);

    world->pushOrganism(baby);
    return true;

}
