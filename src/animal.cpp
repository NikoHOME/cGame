#include "animal.h"
#include "world.h"
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "func.h"

void Animal::draw() const
{
    std::cout<<"$ ";
}

void Animal::action()
{
    srand(time(0));

    int width = world->getWidth();
    int height = world->getHeight();

    std:: pair <int,int> direction = world->getAiDirections()[rand()%8];
    //std::cout<<direction.first<<" "<<direction.second<<"\n";
    while(!isInBounds(width, height, positionX + direction.first, positionY + direction.second))
    {
        direction = world->getAiDirections()[rand()%8];
        std::cout<<direction.first<<" "<<direction.second<<"\n";
    }
    world->addActionToQueue({positionX, positionY, positionX + direction.first, positionY + direction.second, index});
}