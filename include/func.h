#pragma once
#include "classes.h"


struct Coordinate
{
    int x, y;
};

struct BoardSize
{
    int width, height;
};


bool isInBounds(BoardSize boardSize, Coordinate coordinate);
void killIfStronger(Organism **thisOrganism, Organism **otherOrganism, CollisionAction thisCollision, CollisionAction otherCollision);

void moveOrganism(Organism **organism, int x, int y);