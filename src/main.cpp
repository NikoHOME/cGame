#include <iostream>
#include "world.h"
#include "organism.h"
#include "plant.h"
#include "animal.h"
#include "animals.h"

int main()
{
    World world(5,5);
    
    Plant plant(2,2,2,2);
    Plant plant1(2,2,2,3);
    Plant plant2(2,2,2,4);
    Turtle animal(3,4);
    Fox fox(3,3);
    Fox fox1(4,3);

    world.pushOrganism(&plant);
    world.pushOrganism(&plant1);
    world.pushOrganism(&plant2);
    world.pushOrganism(&animal);
    world.pushOrganism(&fox);
    world.pushOrganism(&fox1);
    
    world.draw();

    world.nextTurn();


    world.draw();


    world.nextTurn();

    world.draw();


    return 0;
}