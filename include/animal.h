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
        void draw() const;
        void basicMovementHandle();
        void basicCollisionHandle();
        virtual void printName() const { std::cout<<"Animal";}
        virtual bool isSameSpecies(Organism *animal) = 0;

};


