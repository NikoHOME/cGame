#include "plants/belladona.hpp"


CollisionAction Belladonna::collision()
{
    CollisionAction action;
    action.realStrength = strength;
    action.killAfterDefeat = true;

    return action;
}