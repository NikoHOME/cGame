#include "plant.h"
#include "world.h"
#include <iostream>

void Plant::draw() const
{
    std::cout<<"@ ";
}

collisionAction Plant::collision()
{
    return {strength,strength,false,false,true};
}