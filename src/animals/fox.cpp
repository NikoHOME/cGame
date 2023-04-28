#include "animals/fox.hpp"

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
        auto target = world->getOrganismDisplay()[coordinate.x][coordinate.y];
        if(target == nullptr || target->getStrength() <= strength)
            safeDirections.push_back(directions[i]);
    }

    if(safeDirections.size() == 0)
        return;

    movementAction.direction = safeDirections[rand()%safeDirections.size()];
    movementAction.newPositionX = positionX + movementAction.direction.first;
    movementAction.newPositionY = positionY + movementAction.direction.second;
    
    basicCollisionHandle();

}