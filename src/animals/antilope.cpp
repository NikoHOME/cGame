#include "animals/antilope.hpp"


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


    moveOrganism(positionX + direction.first, positionY + direction.second);


    action.realStrength = strength;
    action.escaped = true;

    return action;
}