#pragma once
#include "organism.h"

struct MovementAction
{
    std:: pair <int,int> direction;
    int newPositionX, newPositionY;
};

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
        virtual Organism *reproduce(Organism *animal, int x,int y) = 0; 
};


