#include "plants/dandelion.hpp"

void Dandelion::action()
{

    for(int i=0;i<3;++i) 
    {
        if(rand()%100 >= GROW_CHANCE)
            continue;

        basicMovementHandle();

        basicCollisionHandle();
    }
}