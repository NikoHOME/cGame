#include "plants/guarana.hpp"

CollisionAction Guarana::collision()
{
    CollisionAction action;
    action.realStrength = strength;
    action.givesStrength = true;
    action.givenStrength = 3;
    

    return action;
}