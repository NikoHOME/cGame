#pragma once
#include "organism.hpp"
#include "action.hpp"

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
        virtual const char *getKillMessage() const override {return "overgrown";}
        virtual const char *getBornMessage() const override {return "sprouted";}
        virtual void write(std::ofstream &file) = 0;
        void basicMovementHandle();
        void basicCollisionHandle();
};