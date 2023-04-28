#include <iostream>
#include "world.hpp"
#include "organism.hpp"
#include "plant.hpp"
#include "plants.hpp"
#include "animal.hpp"
#include "animals.hpp"
#include "manager.hpp"


int main()
{
    Manager manager;
    manager.initializeCurses();
    manager.inputWorldSize();
    manager.initializeMessageWindow();

    

    while(manager.handleInput())
    {
        manager.processInput();
    }


    endwin();

    return 0;
}