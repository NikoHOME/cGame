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
    Wolf wolf(4,4);

    Antilope antilope(0,1);
    Antilope antilope2(0,0);
    Antilope antilope3(1,0);

    world.pushOrganism(&plant);
    world.pushOrganism(&plant1);
    world.pushOrganism(&plant2);
    world.pushOrganism(&animal);
    world.pushOrganism(&fox);
    world.pushOrganism(&fox1);
    world.pushOrganism(&wolf);
    world.pushOrganism(&antilope);
    world.pushOrganism(&antilope2);
    world.pushOrganism(&antilope3);

    world.draw();

    world.nextTurn();


    world.draw();


    world.nextTurn();

    world.draw();


    return 0;
}