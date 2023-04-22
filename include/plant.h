#pragma once
#include "organism.h"
#include "action.h"

#define GROW_CHANCE 10

class Plant : public Organism
{
    using Organism::Organism;
    protected:
        MovementAction movementAction;
    public:
        void action();
        CollisionAction collision();
        virtual const char *getChar() const {return "?";}
        virtual const char *getName() const {return "Plant";}
        void basicMovementHandle();
        void basicCollisionHandle();
};