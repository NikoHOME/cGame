#include "animal.h"
#include "world.h"
#include <iostream>
#include <time.h>
#include <cstdlib>

#include "func.h"

void Animal::draw() const
{
    std::cout<<"? ";
}


void Animal::action()
{
    srand(time(0));

    int width = world->getWidth();
    int height = world->getHeight();

    BASIC_ANIMAL_MOVEMENT

    BASIC_ANIMAL_COLLISION

}

collisionAction Animal::collision()
{
    return{strength,strength,true,false,true};
}