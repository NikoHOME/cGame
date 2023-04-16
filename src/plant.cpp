#include "plant.h"
#include "world.h"
#include <iostream>

void Plant::draw() const
{
    std::cout<<"@ ";
}

CollisionAction Plant::collision()
{
    CollisionAction action;
    
    action.realStrength = strength;


    return action;
}