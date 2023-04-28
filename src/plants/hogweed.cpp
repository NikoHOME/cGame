#include "plants/hogweed.hpp"
#include "animal.hpp"

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
            Organism *killTarget = world->getOrganismDisplay()[coordinate.x][coordinate.y];
            CollisionAction action = killTarget->collision();
            if(!action.isImmortal)
            {
                Message message1;
                message1.animal1 = getName();
                message1.animal2 = killTarget->getName();
                message1.message = getKillMessage();
                getWorld()->getManager()->pushMessage(message1);

                killTarget->die();
            }
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
    action.realStrength = strength;
    action.killAfterDefeat = true;

    return action;
}