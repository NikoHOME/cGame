#include <iostream>
#include "world.h"
#include "organism.h"
#include "plant.h"
#include "plants.h"
#include "animal.h"
#include "animals.h"

int main()
{
    World world(100,50);

    world.initializeWindow();
    world.draw();

    while(world.handleInput())
    {
        world.processInput();
    }


    endwin();

    return 0;
}