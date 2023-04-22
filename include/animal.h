#pragma once
#include "organism.h"
#include "action.h"

class Animal : public Organism
{
    using Organism::Organism;
    protected:
        MovementAction movementAction;
    public:
        virtual void action();
        virtual CollisionAction collision();
        virtual const char *getName() const { return "Animal";}
        virtual const char *getChar() const { return "?";}
        void basicMovementHandle();
        void basicCollisionHandle();
        virtual bool isSameSpecies(Organism *animal) = 0;

};


