#include "plants.h"
#include <vector>
#include "world.h"
#include "animals.h"




void Dandelion::action()
{

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

CollisionAction Belladonna::collision()
{
    CollisionAction action;
    action.realStrength = 0;
    action.killAfterDefeat = true;

    return action;
}

void SosnowskyHogweed::action()
{
    //clear();
    //world->draw();
    std::vector< std::pair <int,int>> directions = world->getAiDirections();//[rand()%8];
    Organism *targetOrganism;
    Coordinate coordinate;
    for(int i=0; i<NORMAL_AI; ++i)
    {
        coordinate.x = positionX + directions[i].first;
        coordinate.y = positionY + directions[i].second;
        if(!isInBounds(world->getBoardSize(), coordinate))
            continue;
        targetOrganism = world->getOrganismDisplay()[coordinate.x][coordinate.y];
        if(targetOrganism != nullptr)
        {
            auto organism = dynamic_cast<Animal *>(targetOrganism);
            if(organism == nullptr)
                continue;
            //world->getOrganisms()[targetOrganism->getIndex()]->setIsDeadStatus(true);
            world->getOrganismDisplay()[coordinate.x][coordinate.y] = nullptr;
        }
    }
    int chance = rand()%100;
    //mvprintw(5,2, "%s",getName());
    //mvprintw(6,2,"GROW% = %d", chance);
    //mvprintw(8,2,"PosX = %d PosY =%d", positionX, positionY);
    //refresh();
    if(chance >= GROW_CHANCE)
    {
        return;
    
    }
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