#include "organism.h"
#include <iostream>
#include <algorithm>

class World;

int Organism::getStrength() const
{
    return strength;
}
int Organism::getInnitiative() const
{
    return innitiative;
}
int Organism::getPositionX() const
{
    return positionX;
}
int Organism::getPositionY() const
{
    return positionY;
}
int Organism::getIndex() const
{
    return index;
}
World *Organism::getWorld() const
{
    return world;
}


void Organism::setStrength(int str)
{
    strength = str;
}
void Organism::setInnitiative(int ini)
{
    innitiative = ini;
}
void Organism::setPositionX(int x)
{
    positionX = x;
}
void Organism::setPositionY(int y)
{
    positionY = y;
}
void Organism::setIndex(int ind)
{
    index = ind;
}
void Organism::setWorld(World *world)
{
    this->world = world;
}
        
Organism::Organism(const Organism &organism)
{
    this->strength = organism.getStrength();
    this->innitiative = organism.getInnitiative();
    this->positionX = organism.getPositionX();
    this->positionY = organism.getPositionY();
    this->world = organism.getWorld();
}




