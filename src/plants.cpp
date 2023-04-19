#include "plants.h"
#include <vector>
#include "world.h"
#include "animals.h"

#define GROW_CHANCE 10


void Dandelion::action()
{
    srand(time(0));

    for(int i=0;i<3;++i) 
    {
        if(rand()%100 >= GROW_CHANCE)
            continue;

        basicMovementHandle();

        basicCollisionHandle();
    }
}

CollisionAction Guarana::collision()
{
    CollisionAction action;
    action.realStrength = strength;
    action.givesStrength = true;
    action.givenStrength = 3;
    

    return action;
}

CollisionAction WolfBerry::collision()
{
    CollisionAction action;
    action.realStrength = 0;
    action.killAfterDefeat = true;

    return action;
}

void SosnowskyHogweed::action()
{
    srand(time(0));

    std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
    Organism *targetOrganism;
    Coordinate coordinate;
    for(auto i : directions)
    {
        coordinate.x = positionX + i.first;
        coordinate.y = positionY + i.second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        targetOrganism = world->getOrganismDisplay()[coordinate.x][coordinate.y];
        if(targetOrganism != nullptr)
        {
            auto organism = dynamic_cast<Animal *>(targetOrganism);
            if(organism == nullptr)
                continue;
            world->getOrganisms()[targetOrganism->getIndex()]->setIsDeadStatus(true);
            world->getOrganismDisplay()[coordinate.x][coordinate.y] = nullptr;
        }
    }

    if(rand()%100 >= GROW_CHANCE)
        return;

    basicMovementHandle();

    basicCollisionHandle();
    
}

CollisionAction SosnowskyHogweed::collision()
{
    CollisionAction action;
    action.realStrength = 0;
    action.killAfterDefeat = true;

    return action;
}