#include <iostream>
#include "world.h"
#include "organism.h"
#include "plant.h"
#include "animal.h"

int main()
{
    World world(5,5);
    
    Plant plant(2,2,2,2);
    Animal animal(2,2,3,4);

    world.pushOrganism(&plant);
    world.pushOrganism(&animal);
    
    world.draw();

    world.nextTurn();


    world.draw();


    world.nextTurn();

    world.draw();


    return 0;
}