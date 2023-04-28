#include "animals/turtle.hpp"

void Turtle::action()
{

    if(rand()%4 != 0)
        return;
    
    basicMovementHandle();

    basicCollisionHandle();
}

CollisionAction Turtle::collision()
{
    CollisionAction action;
    action.realStrength = strength;
    action.hasTempDefenceStrength = true;
    action.tempDefenceStrength = 5; // 5  so it loses against strength 5

    return action;
}