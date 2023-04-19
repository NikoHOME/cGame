#pragma once
#include "organism.h"
#include "action.h"

class Plant : public Organism
{
    using Organism::Organism;
    protected:
        MovementAction movementAction;
    public:
        void action();
        CollisionAction collision();
        void draw() const;
        virtual void printName() const { std::cout<<"Plant";}
        void basicMovementHandle();
        void basicCollisionHandle();
};