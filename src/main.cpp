#include <iostream>
#include "world.h"
#include "organism.h"
#include "plant.h"
#include "plants.h"
#include "animal.h"
#include "animals.h"

int main()
{
    World world(5,5);
    
    SosnowskyHogweed grass1(2,2);
    SosnowskyHogweed grass2(2,3);
    SosnowskyHogweed grass3(2,4);
    Turtle animal(3,4);
    Fox fox(3,3);
    Fox fox1(4,3);
    Wolf wolf(4,4);

    Antilope antilope(0,1);
    Antilope antilope2(0,0);
    Antilope antilope3(1,0);

    world.pushOrganism(&grass1);
    world.pushOrganism(&grass2);
    world.pushOrganism(&grass3);
    world.pushOrganism(&animal);
    world.pushOrganism(&fox);
    world.pushOrganism(&fox1);
    world.pushOrganism(&wolf);
    world.pushOrganism(&antilope);
    world.pushOrganism(&antilope2);
    world.pushOrganism(&antilope3);

    for(int i=0 ;i<20; ++i)
    {
        world.draw();

        world.nextTurn();
    }


    return 0;
}