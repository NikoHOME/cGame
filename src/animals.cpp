#include "animals.h"
#include <vector>
#include "world.h"
#include "func.h"

void Fox::action()
{
    srand(time(0));

    int width = world->getWidth();
    int height = world->getHeight();



    std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
    std::vector< std::pair <int,int>> safeDirections;

    Organism *targetOrganism;

    for(auto i : directions)
    {
        if(!isInBounds(width, height, positionX + i.first, positionY + i.second))
            continue;
        targetOrganism = world->getOrganismDisplay()[positionX + i.first][positionY + i.second];
        if(targetOrganism == nullptr || targetOrganism->getStrength() <= strength)
            safeDirections.push_back(i);
    }

    if(safeDirections.size() == 0)
        return;

    std::pair <int,int> direction = safeDirections[rand()%safeDirections.size()];


    int newPositionX = positionX + direction.first;
    int newPositionY = positionY + direction.second;

    BASIC_ANIMAL_COLLISION
}

void Turtle::action()
{
    srand(time(0));

    if(rand()%4 != 0)
        return;
    
    int width = world->getWidth();
    int height = world->getHeight();


    BASIC_ANIMAL_MOVEMENT

    BASIC_ANIMAL_COLLISION
}


collisionAction Turtle::collision()
{
    return{strength,4,false,false,false,false};
}