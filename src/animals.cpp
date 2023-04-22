#include "animals.h"
#include <vector>
#include "world.h"
#include "func.h"

#define INF INT32_MAX

void Fox::action()
{

    std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
    std::vector< std::pair <int,int>> safeDirections;

    Coordinate coordinate;
    for(int i=0; i<NORMAL_AI; ++i)
    {
        coordinate.x = positionX + directions[i].first;
        coordinate.y = positionY + directions[i].second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        auto target = world->getOrganismDisplay()[positionX + directions[i].first][positionY + directions[i].second];
        if(target == nullptr || target->getStrength() < strength)
            safeDirections.push_back(directions[i]);
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
    action.tempDefenceStrength = 5; // 5  so it loses against strength 5

    return action;
}


void Antilope::action()
{
    movementAction.direction = world->getAiDirections()[rand() % ANTILOPE_AI];

    Coordinate coordinate;
    coordinate.x = positionX + movementAction.direction.first;
    coordinate.y = positionY + movementAction.direction.second;
    

    while(!isInBounds(world->getBoardSize(), coordinate))
    {
        movementAction.direction = world->getAiDirections()[rand() % ANTILOPE_AI];
        coordinate.x = positionX + movementAction.direction.first;
        coordinate.y = positionY + movementAction.direction.second;  
    }
    
    movementAction.newPositionX = coordinate.x;
    movementAction.newPositionY = coordinate.y;
    
    basicCollisionHandle();

}


CollisionAction Antilope::collision()
{

    CollisionAction action;

    if(rand()%2 == 0)
    {
        action.realStrength = strength;
        return action;
    }

    std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
    std::vector< std::pair <int,int>> safeDirections;


    Coordinate coordinate;
    for(auto i : directions)
    {
        coordinate.x = positionX + i.first;
        coordinate.y = positionY + i.second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        auto target = world->getOrganismDisplay()[positionX + i.first][positionY + i.second];
        if(target == nullptr)
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


void Player::inputAction()
{
    Coordinate coordinate;
    coordinate.x = positionX;
    coordinate.y = positionY;
    World *world = getWorld();
    switch(world->getPlayerAction())
    {
        case MOVE_UP:
            coordinate.y--;
            break;
        case MOVE_DOWN:
            coordinate.y++;
            break;
        case MOVE_LEFT:
            coordinate.x--;
            break;
        case MOVE_RIGHT:
            coordinate.x++;
            break;
    }

    if(!isInBounds(world->getBoardSize(), coordinate))
        return;
    movementAction.newPositionX = coordinate.x;
    movementAction.newPositionY = coordinate.y;
    world->getQueue().push(world->getOrganismDisplay()[positionX][positionY]);

}

void Player::action()
{
    basicCollisionHandle();
    getWorld()->setPlayerPosX(positionX);
    getWorld()->setPlayerPosY(positionY);
}
