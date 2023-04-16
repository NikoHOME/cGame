#include "animals.h"
#include <vector>
#include "world.h"
#include "func.h"

#define INF INT32_MAX

void Fox::action()
{
    srand(time(0));

    std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
    std::vector< std::pair <int,int>> safeDirections;

    Organism *targetOrganism;
    Coordinate coordinate;
    for(auto i : directions)
    {
        coordinate.x = positionX + i.first;
        coordinate.y = positionY + i.second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        targetOrganism = world->getOrganismDisplay()[positionX + i.first][positionY + i.second];
        if(targetOrganism == nullptr || targetOrganism->getStrength() <= strength)
            safeDirections.push_back(i);
    }

    if(safeDirections.size() == 0)
        return;

    movementAction.direction = safeDirections[rand()%safeDirections.size()];
    movementAction.newPositionX = positionX + movementAction.direction.first;
    movementAction.newPositionY = positionY + movementAction.direction.second;
    
    basicCollisionHandle();

}

void Turtle::action()
{
    srand(time(0));

    if(rand()%4 != 0)
        return;
    
    basicMovementHandle();

    basicCollisionHandle();
}


CollisionAction Turtle::collision()
{
    CollisionAction action;
    action.realStrength = strength;
    action.hasTempDefenceStrength = true;
    action.tempDefenceStrength = 4;

    return action;
}


void Antilope::action()
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
    if(rand()%2 == 0)
    {
        if(world->getOrganismDisplay()[coordinate.x][coordinate.y] == nullptr)
        {
            coordinate.x = positionX + movementAction.direction.first * 2;
            coordinate.y = positionY + movementAction.direction.second * 2; 
            if(!isInBounds(world->getBoardSize(), coordinate))
            {
                coordinate.x = positionX + movementAction.direction.first;
                coordinate.y = positionY + movementAction.direction.second; 
            }
        }
    }
    
    movementAction.newPositionX = coordinate.x;
    movementAction.newPositionY = coordinate.y;
    
    basicCollisionHandle();

}


CollisionAction Antilope::collision()
{
    srand(time(0));

    CollisionAction action;

    if(rand()%2 == 0)
    {
        action.realStrength = strength;
        return action;
    }

    std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
    std::vector< std::pair <int,int>> safeDirections;

    Organism *targetOrganism;
    Coordinate coordinate;
    for(auto i : directions)
    {
        coordinate.x = positionX + i.first;
        coordinate.y = positionY + i.second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        targetOrganism = world->getOrganismDisplay()[positionX + i.first][positionY + i.second];
        if(targetOrganism == nullptr)
            safeDirections.push_back(i);
    }
    
    if(safeDirections.size() == 0)
    {
        action.realStrength = strength;
        return action;
    }
    Organism **thisOrganism = &world->getOrganismDisplay()[positionX][positionY];

    std::pair <int,int> direction = safeDirections[rand()%safeDirections.size()];


    moveOrganism(thisOrganism, positionX + direction.first, positionY + direction.second);


    action.realStrength = strength;
    action.escaped = true;

    return action;
}
