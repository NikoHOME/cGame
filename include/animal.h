#pragma once
#include "organism.h"

#define BASIC_ANIMAL_MOVEMENT \
    std:: pair <int,int> direction = world->getAiDirections()[rand()%8];\
    while(!isInBounds(width, height, positionX + direction.first, positionY + direction.second))\
        direction = world->getAiDirections()[rand()%8];\
    int newPositionX = positionX + direction.first;\
    int newPositionY = positionY + direction.second;


#define BASIC_ANIMAL_COLLISION \
    Organism **thisOrganism, **otherOrganism;\
    \
    thisOrganism = &world->getOrganismDisplay()[positionX][positionY];\
    otherOrganism = &world->getOrganismDisplay()[newPositionX][newPositionY];\
    \
    if(*otherOrganism == NULL)\
    {\
        std::swap(*thisOrganism, *otherOrganism);\
        setPositionX(newPositionX);\
        setPositionY(newPositionY);\
        return;\
    }\
    \
    collisionAction thisCollision = collision(), otherCollision = (*otherOrganism)->collision();\
    \
    killIfStronger(thisOrganism, otherOrganism, thisCollision.temporaryStrength, otherCollision.temporaryStrength, thisCollision.canKill, otherCollision.canKill);\
    if(otherCollision.stopAfterThis)\
        return;\
    if(!otherCollision.canDieAfterFail)\
        killIfStronger(thisOrganism, otherOrganism, thisCollision.realStrength, otherCollision.realStrength, false, true);\
    else\
        killIfStronger(thisOrganism, otherOrganism, thisCollision.realStrength, otherCollision.realStrength, true, true);

class Animal : public Organism
{
    using Organism::Organism;
    public:
        virtual void action();
        virtual collisionAction collision();
        void draw() const;
        virtual void printName() const { std::cout<<"Animal";}
};


