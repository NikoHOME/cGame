#include "func.h"
#include <iostream>
#include "organism.h"
#include "world.h"
bool isInBounds(int width, int height, int x, int y)
{
    if(x>=0 && x<width && y>=0 && y<height)
        return true;
    return false;
}

void killIfStronger(Organism **thisOrganism, Organism **otherOrganism, int ownStrength, int otherStrength, bool thisCanKill, bool otherCanKill)
{
    if(thisCanKill && (ownStrength > otherStrength))
    {
        (*thisOrganism)->printName();
        std::cout<<" : ";
        (*otherOrganism)->printName();
        std::cout<<" killed by ";
        (*thisOrganism)->printName();
        std::cout<<"\n";   

        (*thisOrganism)->setPositionX((*otherOrganism)->getPositionX());
        (*thisOrganism)->setPositionY((*otherOrganism)->getPositionY());
        (*thisOrganism)->getWorld()->getOrganisms()[(*otherOrganism)->getIndex()]->setIsDeadStatus(true);
        *otherOrganism = nullptr;
        std::swap(*thisOrganism, *otherOrganism); 
    }
    else if(otherCanKill && (ownStrength < otherStrength))
    {
        (*thisOrganism)->printName();
        std::cout<<" : ";
        (*thisOrganism)->printName();
        std::cout<<" killed by ";
        (*otherOrganism)->printName();
        std::cout<<"\n";    

        (*thisOrganism)->getWorld()->getOrganisms()[(*thisOrganism)->getIndex()]->setIsDeadStatus(true);
        *thisOrganism = nullptr;
    }
}
